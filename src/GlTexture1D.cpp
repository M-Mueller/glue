#include "glue/GlTexture1D.h"
#include "glue/GlInternal.h"

GlTexture1D::GlTexture1D():
    _width(0)
{

}

GlTexture::Type GlTexture1D::type() const
{
    return Type::Texture1D;
}

void GlTexture1D::setImageData(GlTexture::InternalFormat format, int width, GlTexture::PixelFormat pixelFormat, GlTexture::PixelType pixelType, const void* pixeldata)
{
#if defined(GLUE_GL_DEBUG) && defined(GLUE_LOGGING)
    if(!isBound())
        LOG(WARNING) << "Texture1D is not bound!";
#endif
    GL_SAFE_CALL(glTexImage1D(mapTextureType(type()), 0, mapTextureInternalFormat(format), width, 0, mapTexturePixelFormat(pixelFormat), mapTexturePixelType(pixelType), pixeldata));
    _format = format;
    _width = width;
    // disable default midmap levels
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_BASE_LEVEL, 0));
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_MAX_LEVEL, 0));
}

void GlTexture1D::resize(GlTexture::InternalFormat format, int width)
{
#if defined(GLUE_GL_DEBUG) && defined(GLUE_LOGGING)
    if(!isBound())
        LOG(WARNING) << "Texture1D is not bound!";
#endif
    GL_SAFE_CALL(glTexImage1D(mapTextureType(type()), 0, mapTextureInternalFormat(format), width, 0, GL_RED, GL_UNSIGNED_BYTE, 0)); // format and type are irrelevant
    _format = format;
    _width = width;
    // disable default midmap levels
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_BASE_LEVEL, 0));
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_MAX_LEVEL, 0));
}

int GlTexture1D::width()
{
    return _width;
}

bool GlTexture1D::isBound() const
{
    GLint currentId = -1;
    GL_SAFE_CALL(glGetIntegerv(GL_TEXTURE_BINDING_1D, &currentId));
    return currentId == (GLint)_id;
}

