
#ifndef ImageRead_h
#define ImageRead_h

#include "RawImage.h"
#include <stdio.h>

class ImageRead{
    
public:
    
    virtual RawImage getRawImage(FILE* file);
    
    virtual ~ImageRead();
    
};


#endif /* ImageRead_h */
