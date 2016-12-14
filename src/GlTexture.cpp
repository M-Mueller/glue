#include "glue/GlTexture.h"
#include "glue/GlTexture2D.h"
#include "glue/GlInternal.h"

GlTexture::GlTexture():
    _id(-1),
    _format(InternalFormat::Invalid)
{
    GL_SAFE_CALL(glGenTextures(1, &_id));
}

GlTexture::~GlTexture()
{
    GL_SAFE_CALL(glDeleteTextures(1, &_id));
}

unsigned int GlTexture::id() const
{
    return _id;
}

GlTexture::InternalFormat GlTexture::format() const
{
    return _format;
}

bool GlTexture::hasDepthFormat() const
{
    return _format == InternalFormat::DepthComponent16 ||
            _format == InternalFormat::DepthComponent24 ||
            _format == InternalFormat::DepthComponent32 ||
            _format == InternalFormat::DepthComponent32F;
}

void GlTexture::bind(int unit)
{
    if(unit >= 0)
    {
        GL_SAFE_CALL(glActiveTexture(GL_TEXTURE0+unit));
    }
    GL_SAFE_CALL(glBindTexture(mapTextureType(type()), _id));
}

void GlTexture::release(int unit)
{
    if(unit >= 0)
    {
        GL_SAFE_CALL(glActiveTexture(GL_TEXTURE0+unit));
    }
    GL_SAFE_CALL(glBindTexture(mapTextureType(type()), 0));
}

void GlTexture::setMinFilter(GlTexture::MinFilter filter)
{
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_MIN_FILTER, mapMinFilter(filter)));
}

void GlTexture::setMagFilter(GlTexture::MagFilter filter)
{
    GL_SAFE_CALL(glTexParameteri(mapTextureType(type()), GL_TEXTURE_MAG_FILTER, mapMagFilter(filter)));
}
