#ifndef GLVERTEXBUFFER_H
#define GLVERTEXBUFFER_H

#include "glue/GlConfig.h"
#include "glue/GlBuffer.h"

#include <vector>

/**
 * The GlVertexBuffer class represents a list of vertices with one or more attributes.
 * Currently only supports non-interleaved buffers.
 * A GlVertexBuffer objects is best used with a \ref GlVertexArray that will automatically set the vertex attribute pointers.
 */
class GlVertexBuffer : public GlBuffer
{
public:
    /// Describes a single vertex attribute
	struct VertexAttribute
	{
        enum Type
        {
            Byte,
            UnsignedByte,
            Short,
            UnsignedShort,
            Int,
            UnsignedInt,
            Float
        };

        VertexAttribute(unsigned int index, int size, Type type, bool normalized=false);
        unsigned int index;   ///< index of the attribute in the buffer
        int size;     ///< number of compenents (e.g. 2 for vec2)
        size_t stride; ///< number of bytes between two attribute values (only required for interleaved buffers)
        size_t pointer; ///< number of bytes to the first attribute value
        Type type;    ///< value type of the attribute (e.g. float)
        bool normalized;   ///< Signals if the value should be accessed normalized
	};

    /**
     * Creates a new, empty vertex buffer.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGenBuffers.xhtml">glGenBuffers</a>
     */
    GlVertexBuffer();

    /**
     * Copies the vertices with one or multiple attributes to the buffer.
     * The number of elements in the vector determines the number of vertices.
     * If multiple attributes are passed, all must have the same number of elements.
     * The argument index determines the attribute index (e.g. a0 is index 0, the next attribute is index 1)
     * This will override any previously set data.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBufferData.xhtml">glBufferData</a>
     */
    template<typename T, typename... U>
    void setData(Usage usage, std::vector<T> a0, std::vector<U>... a);

    /**
     * Returns the current number of vertices in the buffer.
     */
	size_t numVertices() const;

    /**
     * Returns the number of attributes for each vertex
     */
	size_t numAttributes() const;

    /**
     * Returns the attribute with the given index.
     */
	VertexAttribute attribute(unsigned int index) const;

protected:
    /// Computes the size in bytes of the vector
	template<typename T>
	size_t getBufferSize(std::vector<T> a0);

    /// Computes the size in bytes of all vectors combined
    template<typename T, typename... U>
    size_t getBufferSize(std::vector<T> a0, std::vector<U>... a);

    /// Copies the vector to the buffer starting from the offset
	template<typename T>
	void setSubData(size_t offset, std::vector<T> a0);

    /// Copies all vectors to the buffer starting from the offset.
    template<typename T, typename... U>
    void setSubData(size_t offset, std::vector<T> a0, std::vector<U>... a);

    /// Creates a VertexAttribute for the template type and index.
	template<typename T>
    VertexAttribute createAttribute(unsigned int index);

private:
	std::vector<VertexAttribute> _attributes;
	size_t _numVertices;
};

template<typename T, typename... U>
void GlVertexBuffer::setData(Usage usage, std::vector<T> a0, std::vector<U>... a)
{
    // clear previous data
	_attributes.clear();

	_numVertices = a0.size();

    // Determine the summerized size of all attributes
	size_t byteSize = getBufferSize(a0, a...);
    // Allocate the memory for the buffers
    GlBuffer::setData(usage, nullptr, byteSize);

    // Copy the data of each attribute
	setSubData(0, a0, a...);
}

template<typename T>
size_t GlVertexBuffer::getBufferSize(std::vector<T> a0)
{
	return a0.size() * sizeof(T);
}

template<typename T, typename... U>
size_t GlVertexBuffer::getBufferSize(std::vector<T> a0, std::vector<U>... a)
{
    // Take the first vector, compute the byte size and recursively add the size of the remaining vectors
	return a0.size() * sizeof(T) + getBufferSize(a...);
}

template<typename T>
void GlVertexBuffer::setSubData(size_t offset, std::vector<T> a0)
{
    // Saves the properties of the current attribute
	VertexAttribute attribute = createAttribute<T>(_attributes.size());
	attribute.stride = 0;
	attribute.pointer = offset;
	_attributes.push_back(attribute);

    // Copy the data to the buffer
	GlBuffer::setSubData(&a0[0], getBufferSize(a0), offset);
}

template<typename T, typename... U>
void GlVertexBuffer::setSubData(size_t offset, std::vector<T> a0, std::vector<U>... a)
{
    // Saves the properties of the current attribute
	VertexAttribute attribute = createAttribute<T>(_attributes.size());
	attribute.stride = 0;
	attribute.pointer = offset;
	_attributes.push_back(attribute);

    ///Copy the data to the buffer
	GlBuffer::setSubData(&a0[0], getBufferSize(a0), offset);
    // Sets the offset point to after the current buffer
	offset += getBufferSize(a0);
    // Recursively copy the data for the remainging vectors
	setSubData(offset, a...);
}

#endif // GLVERTEXBUFFER_H
