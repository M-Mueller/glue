#ifndef GLBUFFER_H
#define GLBUFFER_H

#include "glue/GlConfig.h"
#include <cstddef>

/**
 * The GlBuffer class represents different kinds of OpenGL data buffer objects.
 * Since buffer objects can vary between different types, glue offers dedicated derived classes for certain kinds of buffers.
 * Before a buffer can be modified, it must be bound.
 */
class GlBuffer
{
public:
    /// Target of the buffer object that determines its type
    enum class Target
	{
        /// Array objects usually contain vertex data, see \ref GlVertexBuffer
        Array,
        /// ElementArray objects contain index data, see \ref GlIndexBuffer
        ElementArray
	};

    /// A hint how the buffer will be used
    enum class Usage
	{
        StreamCopy,
        StreamDraw,
        StreamRead,
        StaticCopy,
        StaticDraw,
        StaticRead,
        DynamicCopy,
        DynamicDraw,
        DynamicRead
	};

    /** Creates a new, empty buffer of the given type
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenBuffers.xhtml">glGenBuffers</a>
     */
	GlBuffer(Target target);

    /** Deletes the buffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDeleteBuffers.xhtml">glDeleteBuffers</a>
     */
	virtual ~GlBuffer();

    /**
     * Binds the buffer object to its target destination.
     * This will unbind any previously bound buffer objects to the same target.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindBuffer.xhtml">glBindBuffer</a>
     */
	virtual void bind();

    /**
     * Unbinds all buffer objects from the target destination.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindBuffer.xhtml">glBindBuffer</a>
     */
	virtual void release();

    /**
     * Returns true if the buffer object is currently bound to the target.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGet.xhtml">glGet</a>
     */
    virtual bool isBound() const;

    /**
     * Allocates a block of memory of the given size.
     * If the pointer to data is not zero, the memory block will be initialized with data.
     * Otherwise the memory block is only allocated and no data will be copied.
     *
     * The GlBuffer object will not keep a reference to the data pointer, i.e. it can be deleted anytime.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBufferData.xhtml">glBufferData</a>
     */
    virtual void setData(Usage usage, void* data, size_t size);

    /**
     * Copies the given data to the buffer.
     * The offset + size must be smaller or equal to the previous allocated size (see \ref setData).
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBufferSubData.xhtml">glBufferSubData</a>
     */
	virtual void setSubData(void* data, size_t size, size_t offset);

protected:
	const Target _target;
    unsigned int _id;
	size_t _size;
	Usage _usage;
};

#endif // GLBUFFER_H
