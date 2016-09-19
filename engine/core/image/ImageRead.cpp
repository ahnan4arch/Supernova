#include "ImageRead.h"

#include "ColorType.h"

#include "FreeImage.h"
#include "FreeImageIO.h"


ImageRead::~ImageRead(){

}

RawImage ImageRead::getRawImage(FILE* file){

    // active only for static linking
#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif

    int type;

    FreeImageIO io;
    SetDefaultIO(&io);

    FIBITMAP *bitmap;
    // Get the format of the image file
    FREE_IMAGE_FORMAT fif =FreeImage_GetFileTypeFromHandle(&io, file, 0);

    // If the format can't be determined, try to guess the format from the file name
    //if(fif == FIF_UNKNOWN) {
    //    fif = FreeImage_GetFIFFromFilename(fname);
    //}

    // Load the data in bitmap if possible
    if(fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) {
        bitmap = FreeImage_LoadFromHandle(fif, &io, (fi_handle)file, 0);
    }
    else {
        bitmap = NULL;
    }


    if(bitmap) {
        unsigned int w = FreeImage_GetWidth(bitmap);
        unsigned int h = FreeImage_GetHeight(bitmap);
        unsigned pixel_size = FreeImage_GetBPP(bitmap);

        // Get a pointer to the pixel data
        BYTE *data = (BYTE*)FreeImage_GetBits(bitmap);


        type = S_COLOR_RGB;
        // Process only RGB and RGBA images
        if(pixel_size == 24) {
            type = S_COLOR_RGB;
        }
        else if (pixel_size == 32) {
            type = S_COLOR_RGB_ALPHA;
        }
        else {
            //std::cerr << "pixel size = " << pixel_size << " don't know how to process this case. I'm out!" << std::endl;
            //exit(-1);
        }

        unsigned char temp;
        int pos;

        for (int i = 0; i < w*h; i++){
            (type == S_COLOR_RGB) ? pos = i * 3 : pos = i * 4;
            temp = data[pos  ];
            data[pos  ] = data[pos+2];
            data[pos+2] = temp;
        }

        return RawImage((int)w, (int)h, (int)pixel_size, type, (void*)data);
    }
    else {
        //std::cerr << "Unable to load the image file " << fname  << " I'm out!" << std::endl;
        //exit(-1);
    }

    // Clean bitmap;
    FreeImage_Unload(bitmap);

    // active only for static linking
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif

    //TODO
    return RawImage();

}
