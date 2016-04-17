#ifndef GLRENDERBUFFER_H
#define GLRENDERBUFFER_H

#include "glue/GlConfig.h"
#include "glue/GlTexture.h"

/**
 * The GlRenderBuffer class represents a OpenGL renderbuffer object.
 * A renderbuffer is similar to a texture with the main difference that it is write-only.
 * Renderbuffers are used specifically with Framebuffer Objects (FBOs).
 * \see GlFrameBuffer
 */
class GlRenderBuffer
{
public:
    /**
     * Creates a new, empty renderbuffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenRenderbuffers.xhtml">glGenRenderbuffers</a>
     */
    GlRenderBuffer();

    /**
     * Deletes the renderbuffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDeleteRenderbuffers.xhtml">glDeleteRenderbuffers</a>
     */
    virtual ~GlRenderBuffer();

    /**
     * Returns the current format of the renderbuffer.
     */
    GlTexture::InternalFormat format() const;

    /**
     * Returns true if the current InternalFormat is one of the DepthComponent formats.
     */
    virtual bool hasDepthFormat() const;

    /**
     * Returns the current width of the renderbuffer.
     */
    int width() const;

    /**
     * Returns the current height of the renderbuffer.
     */
    int height() const;

    /**
     * Resizes the renderbuffer to the new size and format.
     * The internal storage of the renderbuffer is re-allocated.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glRenderbufferStorage.xhtml">glRenderbufferStorage</a>
     */
    void resize(GlTexture::InternalFormat format, int width, int height);

    /**
     * Binds the renderbuffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindRenderbuffer.xhtml">glBindRenderbuffer</a>
     */
    void bind();

    /**
     * Unbinds any renderbuffer (i.e. binds 0).
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindRenderbuffer.xhtml">glBindRenderbuffer</a>
     */
    void release();

    /**
     * Returns true if this renderbuffer is currently bound.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGet.xhtml">glGet</a>
     */
    bool isBound() const;

    /**
     * Returns the OpenGL id of the renderbuffer.
     */
    unsigned int id() const;

private:
    unsigned int _id;
    GlTexture::InternalFormat _format;
    int _width;
    int _height;
};

#endif // GLRENDERBUFFER_H
