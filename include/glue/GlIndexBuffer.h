#ifndef GLINDEXBUFFER_H
#define GLINDEXBUFFER_H

#include "glue/GlConfig.h"
#include "glue/GlBuffer.h"

#include <vector>

/**
 * The GlIndexBuffer class a list of indices that can be used for index rendering.
 * A GlIndexBuffer is a \ref GlBuffer of type \ref GlBuffer::Target::ElementArray.
 */
class GlIndexBuffer : public GlBuffer
{
public:
    /// Available index types
    enum IndexType
    {
        UCHAR,
        USHORT,
        UINT
    };

    /**
     * Creates a new, empty index buffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenBuffers.xhtml">glGenBuffers</a>
     */
    GlIndexBuffer();

    /**
     * Sets the buffer data to a list of UCHAR indices.
     * Overrides any existing data in the buffer.
     */
    void setData(Usage usage, std::vector<unsigned char> i);

    /**
     * Sets the buffer data to a list of USHORT indices.
     * Overrides any existing data in the buffer.
     */
    void setData(Usage usage, std::vector<unsigned short> i);

    /**
     * Sets the buffer data to a list of UINT indices.
     * Overrides any existing data in the buffer.
     */
    void setData(Usage usage, std::vector<unsigned int> i);

    /**
     * Returns the current number of indices.
     * This only returns meaningful values if the data was set using the setData methods of GlIndexBuffer
     * and not setData of GlBuffer.
     */
    size_t numIndices() const;

    /**
     * Returns the current type of indices.
     * This only returns a meaningful type if the data was set using the setData methods of GlIndexBuffer
     * and not setData of GlBuffer.
     */
    IndexType indexType() const;

private:
    size_t _numIndices;
    IndexType _type;
};

#endif // GLINDEXBUFFER_H
