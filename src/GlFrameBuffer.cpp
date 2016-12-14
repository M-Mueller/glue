#include "glue/GlFrameBuffer.h"
#include "glue/GlTexture1D.h"
#include "glue/GlTexture2D.h"
#include "glue/GlRenderBuffer.h"
#include "glue/GlInternal.h"

GlFrameBuffer::GlFrameBuffer()
{
    GL_SAFE_CALL(glGenFramebuffers(1, &_id));
}

GlFrameBuffer::~GlFrameBuffer()
{
    GL_SAFE_CALL(glDeleteFramebuffers(1, &_id));
}

void GlFrameBuffer::bind(Target target)
{
    GL_SAFE_CALL(glBindFramebuffer(mapFrameBufferTarget(target), _id));
}


void GlFrameBuffer::release(Target target)
{
    GL_SAFE_CALL(glBindFramebuffer(mapFrameBufferTarget(target), 0));
}

bool GlFrameBuffer::isBound() const
{
    int draw = -1, read = -1;
    GL_SAFE_CALL(glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &draw));
    GL_SAFE_CALL(glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &read));
    return draw == (int)_id || read == (int)_id;
}

void GlFrameBuffer::attach(const GlTexture1D& texture, GlFrameBuffer::Attachment position, int level)
{
#ifdef GLUE_LOGGING
    if(!isBound())
        LOG(WARNING) << "FrameBuffer is not bound!";
    if(position == Attachment::Depth && !texture.hasDepthFormat())
        LOG(WARNING) << "Attaching non-depth format to depth attachment";
    else if(position != Attachment::Depth && texture.hasDepthFormat())
        LOG(WARNING) << "Attaching depth format to color attachment";
#endif

    GL_SAFE_CALL(glFramebufferTexture1D(GL_FRAMEBUFFER, mapFrameBufferAttachment(position), GL_TEXTURE_1D, texture.id(), level));

    if(position != Attachment::Depth && position != Attachment::Stencil)
    {
        if(static_cast<int>(position) >= (int)_attachments.size())
            _attachments.resize(static_cast<int>(position)+1, GL_NONE);
        _attachments.at(static_cast<int>(position)) = mapFrameBufferAttachment(position);
    }
}


void GlFrameBuffer::attach(const GlTexture2D& texture, Attachment position, int level)
{
#ifdef GLUE_LOGGING
    if(!isBound())
        LOG(WARNING) << "FrameBuffer is not bound!";
    if(position == Attachment::Depth && !texture.hasDepthFormat())
        LOG(WARNING) << "Attaching non-depth format to depth attachment";
    else if(position != Attachment::Depth && texture.hasDepthFormat())
        LOG(WARNING) << "Attaching depth format to color attachment";
#endif

    GL_SAFE_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, mapFrameBufferAttachment(position), GL_TEXTURE_2D, texture.id(), level));

    if(position != Attachment::Depth && position != Attachment::Stencil)
    {
        if(static_cast<int>(position) >= (int)_attachments.size())
            _attachments.resize(static_cast<int>(position)+1, GL_NONE);
        _attachments.at(static_cast<int>(position)) = mapFrameBufferAttachment(position);
    }
}

void GlFrameBuffer::attach(const GlRenderBuffer& renderbuffer, Attachment position)
{
#ifdef GLUE_LOGGING
    if(!isBound())
        LOG(WARNING) << "FrameBuffer is not bound!";
    if(position == Attachment::Depth && !renderbuffer.hasDepthFormat())
        LOG(WARNING) << "Attaching non-depth format to depth attachment";
    else if(position != Attachment::Depth && renderbuffer.hasDepthFormat())
        LOG(WARNING) << "Attaching depth format to color attachment";
#endif
    GL_SAFE_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, mapFrameBufferAttachment(position), GL_RENDERBUFFER, renderbuffer.id()));

    if(position != Attachment::Depth && position != Attachment::Stencil)
    {
        if(static_cast<int>(position) >= (int)_attachments.size())
            _attachments.resize(static_cast<int>(position)+1, GL_NONE);
        _attachments.at(static_cast<int>(position)) = mapFrameBufferAttachment(position);
    }
}

void GlFrameBuffer::detach(Attachment position)
{
#ifdef GLUE_LOGGING
    if(!isBound())
        LOG(DEBUG) << "FrameBuffer is not bound!";
#endif

    GL_SAFE_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, mapFrameBufferAttachment(position), GL_TEXTURE_2D, 0, 0));

    if(position != Attachment::Depth && position != Attachment::Stencil)
    {
        if(static_cast<int>(position) < (int)_attachments.size())
        {
            _attachments.at(static_cast<int>(position)) = false;
            // get the last true value and shrink the list to that value
            auto i=_attachments.size()-1;
            for(; i>=0; --i)
            {
                if(_attachments[i] != GL_NONE)
                    break;
            }
            _attachments.resize(i+1);
        }
    }
}

void GlFrameBuffer::assignDrawBuffers()
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "FrameBuffer is not bound!";
#endif

    GL_SAFE_CALL(glDrawBuffers(_attachments.size(), &_attachments[0]));
}

bool GlFrameBuffer::isComplete(Target target) const
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "FrameBuffer is not bound!";
#endif

    GLenum completeness = GL_SAFE_CALL(glCheckFramebufferStatus(mapFrameBufferTarget(target)));
    return completeness == GL_FRAMEBUFFER_COMPLETE;
}

