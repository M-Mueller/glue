#ifndef GLFRAMEBUFFER_H
#define GLFRAMEBUFFER_H

#include "glue/GlConfig.h"
#include <vector>

class GlTexture1D;
class GlTexture2D;
class GlRenderBuffer;

/**
 * The GlFrameBuffer class represents a OpenGL framebuffer object (FBO).
 * This class keeps track of the attachments assigned with the \ref attach and \ref detach methods.
 * Certain methods (like \ref assignDrawBuffers) won't work correctly if attachments are changed outside the class (e.g. directly with OpenGL calls).
 */
class GlFrameBuffer
{
public:
    /// A framebuffer object can be bound as draw buffer or as a read buffer
    enum class Target
    {
        /// Framebuffer is bound for reading operations (e.g. glReadPixels)
        ReadBuffer,
        /// Framebuffer is bound for drawing operations (e.g. glDrawElements)
        DrawBuffer,
        /// Framebuffer is bound for both as reading and writing
        DrawReadBuffer
    };

    /// This enum type specifies the attachment locations the FBO.
    enum class Attachment
    {
        Color0 = 0,
        Color1 = 1,
        Color2 = 2,
        Color3 = 3,
        Color4 = 4,
        Color5 = 5,
        Color6 = 6,
        Color7 = 7,
        Color8 = 8,
        Depth = 32,
        Stencil = 33
    };

    /**
     * Creates an empty framebuffer object without any attachments.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenFramebuffers.xhtml">glGenFramebuffers</a>
     */
    GlFrameBuffer();

    /**
     * Deletes the framebuffer object.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDeleteFramebuffers.xhtml">glDeleteFramebuffers</a>
     */
    virtual ~GlFrameBuffer();

    /**
     * Binds the framebuffer to the desired target.
     * This will release any currently bound framebuffers.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindFramebuffer.xhtml">glBindFramebuffer</a>
     */
    void bind(Target target = Target::DrawReadBuffer);

    /**
     * Unbinds the current framebuffer from the given target.
     * This binds the default framebuffer (i.e. id 0).
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindFramebuffer.xhtml">glBindFramebuffer</a>
     */
    void release(Target target = Target::DrawReadBuffer);

    /**
     * Returns true if the framebuffer is currently bound as draw or read buffer;
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGet.xhtml">glGet</a>
     */
    bool isBound() const;

    /**
     * Attaches a texture to the framebuffer at a given position.
     * The texture must remain valid as long as it is attached to the framebuffer.
     * The texture is not required to be bound and also won't get bound when calling this method.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glFramebufferTexture.xhtml">glFramebufferTexture1D</a>
     */
    void attach(const GlTexture1D& texture, Attachment position, int level=0);

    /**
     * Attaches a texture to the framebuffer at a given position.
     * The texture must remain valid as long as it is attached to the framebuffer.
     * The texture is not required to be bound and also won't get bound when calling this method.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glFramebufferTexture.xhtml">glFramebufferTexture2D</a>
     */
    void attach(const GlTexture2D& texture, Attachment position, int level=0);

    /**
     * Attaches a renderbuffer to the framebuffer at a given position.
     * The renderbuffer must remain valid as long as it is attached to the framebuffer.
     * The renderbuffer is not required to be bound and also won't get bound when calling this method.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glFramebufferRenderbuffer.xhtml">glFramebufferRenderbuffer</a>
     */
    void attach(const GlRenderBuffer& renderbuffer, Attachment position);

    /**
     * Detaches the texture at a given position from the framebuffer.
     * Does nothing if no texture was attached beforehand.
     */
    void detach(Attachment position);

    /**
     * Sets the draw buffers to the previously attached positions.
     * The draw buffers determine into which attachments the drawing will be stored.
     * The draw buffers are set according to the attachment position, e.g. attachment 0 is set as the first buffer, attachment 1 as the second and so on.
     * Missing attachments set the according draw buffer to None, e.g. if only attachment 0 and attachment 2 are assigned, the draw buffers will be set to Attachment 0, None, Attachment 2.
     * The draw buffers are part of the framebuffer state, i.e. they only have to be re-assigned when the attachments change.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDrawBuffers.xhtml">glDrawBuffers</a>
     */
    void assignDrawBuffers();

    /**
     * Returns true if the framebuffer is complete and can be used for drawing/reading.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glCheckFramebufferStatus.xhtml">glCheckFramebufferStatus</a>
     */
    bool isComplete(Target target = Target::DrawReadBuffer) const;

private:
    unsigned int _id;
    std::vector<unsigned int> _attachments;
};

#endif // GLFRAMEBUFFER_H
