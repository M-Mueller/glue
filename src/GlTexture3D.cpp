#include "glue/GlTexture3D.h"
#include "glue/GlInternal.h"

GlTexture3D::GlTexture3D():
    _width(0),
    _height(0),
    _depth(0)
{

}

GlTexture::Type GlTexture3D::type() const
{
    return Type::Texture3D;
}

void GlTexture3D::setImageData(GlTexture::InternalFormat format, int width, int height, int depth, GlTexture::PixelFormat pixelFormat, GlTexture::PixelType pixelType, const void* pixeldata)
{
#ifdef GLUE_LOGGING
    if(!isBound())
        LOG(DEBUG) << "Texture3D is not bound!";
#endif
    GL_SAFE_CALL(glTexImage3D(mapTextureType[type()], 0, mapTextureInternalFormat[format], width, height, depth, 0, mapTexturePixelFormat[pixelFormat], mapTexturePixelType[pixelType], pixeldata));
    _format = format;
    _width = width;
    _height = height;
    _depth = depth;
    // disable default midmap levels
    GL_SAFE_CALL(glTexParameteri(mapTextureType[type()], GL_TEXTURE_BASE_LEVEL, 0));
    GL_SAFE_CALL(glTexParameteri(mapTextureType[type()], GL_TEXTURE_MAX_LEVEL, 0));
}

void GlTexture3D::resize(GlTexture::InternalFormat format, int width, int height, int depth)
{
#ifdef GLUE_LOGGING
    if(!isBound())
        LOG(DEBUG) << "Texture3D is not bound!";
#endif
    GL_SAFE_CALL(glTexImage3D(mapTextureType[type()], 0, mapTextureInternalFormat[format], width, height, depth, 0, GL_RED, GL_UNSIGNED_BYTE, 0)); // format and type are irrelevant
    _format = format;
    _width = width;
    _height = height;
    _depth = depth;
    // disable default midmap levels
    GL_SAFE_CALL(glTexParameteri(mapTextureType[type()], GL_TEXTURE_BASE_LEVEL, 0));
    GL_SAFE_CALL(glTexParameteri(mapTextureType[type()], GL_TEXTURE_MAX_LEVEL, 0));
}

int GlTexture3D::width()
{
    return _width;
}

int GlTexture3D::height()
{
    return _height;
}

int GlTexture3D::depth()
{
    return _depth;
}

bool GlTexture3D::isBound() const
{
    GLint currentId = -1;
    GL_SAFE_CALL(glGetIntegerv(GL_TEXTURE_BINDING_3D, &currentId));
    return currentId == (GLint)_id;
}

