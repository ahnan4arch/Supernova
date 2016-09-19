#include "Image.h"

//#include "PNGRead.h"
//#include "JPEGRead.h"
//#include "TGARead.h"
//#include "TIFFRead.h"
#include "ImageRead.h"
#include "platform/Log.h"
#include <assert.h>

Image::Image() {
    imageRead = NULL;
}

Image::Image(const char* relative_path){
    loadRawImage(relative_path);
    imageRead = NULL;
}

Image::~Image() {
    releaseImage();
    if (imageRead != NULL)
        delete imageRead;
}

void Image::loadRawImage(const char* relative_path) {
    assert(relative_path != NULL);

    FILE* file_stream = fopen(relative_path, "rb");
    assert (file_stream != NULL);
    //imageRead = getImageFormat(relative_path, file_stream);
    //if (imageRead == NULL)
    //    Log::Error(LOG_TAG, "Not supported image type from: %s", relative_path);
    //assert (imageRead != NULL);
    imageRead = new ImageRead();
    rawImage = imageRead->getRawImage(file_stream);
    
    assert(ferror(file_stream) == 0);
    fclose(file_stream);
}
/*
ImageRead* Image::getImageFormat(const char* relative_path, FILE* file_stream){
    unsigned int magic;
    unsigned char buf[4];
    
    if ((fread(&buf[0], 4, 1, file_stream) != 1) ||
        (fseek(file_stream, 0, SEEK_SET) != 0)) {
        return NULL;
    }
    
    magic = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    
    if (magic == 0x89504E47U) {
        //return new PNGRead();
    } else if (magic >= 0xFFD8FF00U && magic <= 0xFFD8FFFFU) {
        //return new JPEGRead();
    } else if (magic == 0x49492A00 || magic == 0x4D4D002A) {
        //return new TIFFRead();
    //} else if (magic == 0x47494638) {
        // format GIF;
    } else if (buf[0] == 'B' && buf[1] == 'M') {
        //return new JPEGRead();
    //}else if(strstr(relative_path, ".tga") != NULL || strstr(relative_path, ".TGA") != NULL) {
         //return new TGARead();
    }
    
    unsigned char
    TGAuncompressedheader[12]={ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},	// Uncompressed TGA Header
    TGAcompressedheader[12]={ 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0},	// Uncompressed TGA Header
    actualHeader[12];	// Used To Compare TGA Header

    
    if (fread(actualHeader, 1, sizeof(actualHeader), file_stream) != sizeof(actualHeader)){
        return NULL;
    }
    if (
             (memcmp(TGAuncompressedheader, actualHeader, sizeof(TGAuncompressedheader)) == 0) ||
             (memcmp(TGAcompressedheader, actualHeader, sizeof(TGAcompressedheader)) == 0)
        ){
        fseek(file_stream, 0, SEEK_SET);
        return new TGARead();
}
    
    //free(buf);
    //free(actualHeader);
    
    //return new TGARead();

    return NULL;
}
*/

RawImage Image::getRawImage(){
    return rawImage;
}

void Image::releaseImage(){
    rawImage.releaseImageData();
}