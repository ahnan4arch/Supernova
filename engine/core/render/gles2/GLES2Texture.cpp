#include "GLES2Texture.h"
#include "image/ColorType.h"

GLenum GLES2Texture::getGlColorFormat(const int color_format) {

    switch (color_format) {
        case S_COLOR_GRAY:
            return GL_LUMINANCE;
        case S_COLOR_RGB_ALPHA:
            return GL_RGBA;
        case S_COLOR_RGB:
            return GL_RGB;
        case S_COLOR_GRAY_ALPHA:
            return GL_LUMINANCE_ALPHA;
    }

    return 0;
}


GLuint GLES2Texture::getTextureObjectId(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels) {
    GLuint texture_object_id;

    glGenTextures(1, &texture_object_id);
    //assert(texture_object_id != 0);

    glBindTexture(GL_TEXTURE_2D, texture_object_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_object_id;
}



void GLES2Texture::loadTexture(const char* relative_path) {
    //assert(relative_path != NULL);

    TextureLoader image(relative_path);

    const GLsizei width = image.getRawImage()->getWidth();
    const GLsizei height = image.getRawImage()->getHeight();
    const GLenum type = getGlColorFormat(image.getRawImage()->getColorFormat());
    const GLvoid* pixels = image.getRawImage()->getData();

    gTexture = getTextureObjectId(width, height, type, pixels);
    
    image.getRawImage()->releaseImageData();

}

void GLES2Texture::deleteTexture(){
    glDeleteTextures(1, &gTexture);
}


GLuint GLES2Texture::getTexture(){
    return gTexture;
}
