#include "glue/GlRenderBuffer.h"
#include "glue/GlInternal.h"

GlRenderBuffer::GlRenderBuffer():
    _format(GlTexture::InternalFormat::Invalid),
    _width(0),
    _height(0)
{
    GL_SAFE_CALL(glGenRenderbuffers(1, &_id));
}

GlRenderBuffer::~GlRenderBuffer()
{
    GL_SAFE_CALL(glDeleteRenderbuffers(1, &_id))
}

GlTexture::InternalFormat GlRenderBuffer::format() const
{
    return _format;
}

bool GlRenderBuffer::hasDepthFormat() const
{
    return _format == GlTexture::InternalFormat::DepthComponent16 ||
            _format == GlTexture::InternalFormat::DepthComponent24 ||
            _format == GlTexture::InternalFormat::DepthComponent32 ||
            _format == GlTexture::InternalFormat::DepthComponent32F;
}

int GlRenderBuffer::width() const
{
    return _width;
}

int GlRenderBuffer::height() const
{
    return _height;
}

void GlRenderBuffer::resize(GlTexture::InternalFormat format, int width, int height)
{
#if defined(GLUE_GL_DEBUG) && defined(GLUE_LOGGING)
    if(!isBound())
        LOG(WARNING) << "RenderBuffer is not bound!";
#endif
    GL_SAFE_CALL(glRenderbufferStorage(GL_RENDERBUFFER, mapTextureInternalFormat(format), width, height));
    _format = format;
    _width = width;
    _height = height;
}

void GlRenderBuffer::bind()
{
    GL_SAFE_CALL(glBindRenderbuffer(GL_RENDERBUFFER, _id));
}

void GlRenderBuffer::release()
{
    GL_SAFE_CALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

bool GlRenderBuffer::isBound() const
{
    GLint currentId = -1;
    GL_SAFE_CALL(glGetIntegerv(GL_RENDERBUFFER_BINDING, &currentId));
    return currentId == (GLint)_id;
}

unsigned int GlRenderBuffer::id() const
{
    return _id;
}

