#include "TIFFReader.h"
#include "ColorType.h"
#include "platform/Log.h"

extern "C" {
#include "tiffio.h"
}
#include "tiffio.hxx"


TextureFile* TIFFReader::getRawImage(const char* relative_path, std::ifstream* ifile){
    
    uint32* raster;
    uint32  width, height;
    
    TIFF *in = TIFFStreamOpen(relative_path, ifile);
    
    TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(in, TIFFTAG_IMAGELENGTH, &height);
    size_t npixels = width*height;
    
    raster = (uint32*)_TIFFmalloc(width * height * sizeof (uint32));
    if (raster == 0) {
        Log::Error(LOG_TAG, "No space for raster buffer: %s", relative_path);
        return NULL;
    }
    
    /* Read the image in one chunk into an RGBA array */
    if (!TIFFReadRGBAImageOriented(in, width, height, raster, ORIENTATION_TOPLEFT, 0)) {
        _TIFFfree(raster);
        Log::Error(LOG_TAG, "Can`t read TIFF image: %s", relative_path);
        return NULL;
    }

    return new TextureFile((int)width, (int)height, (int)npixels*sizeof(uint32), S_COLOR_RGB_ALPHA, (void*)raster);


}
