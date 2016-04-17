#include "glue/GlVertexBuffer.h"

GlVertexBuffer::VertexAttribute::VertexAttribute(unsigned int i, int s, Type t, bool normalized):
	index(i),
    size(s),
	stride(0),
    pointer(0),
    type(t),
    normalized(normalized)
{

}

GlVertexBuffer::GlVertexBuffer():
    GlBuffer(GlBuffer::Target::Array),
	_numVertices(0)
{

}

size_t GlVertexBuffer::numVertices() const
{
	return _numVertices;
}

size_t GlVertexBuffer::numAttributes() const
{
	return _attributes.size();
}

GlVertexBuffer::VertexAttribute GlVertexBuffer::attribute(unsigned int index) const
{
	if(index < _attributes.size())
	{
		return _attributes.at(index);
	}
	else
	{
        return VertexAttribute(0, 0, VertexAttribute::Float);
	}
}

template<>
GlVertexBuffer::VertexAttribute GlVertexBuffer::createAttribute<float>(unsigned int index)
{
    return VertexAttribute(index, 1, VertexAttribute::Float);
}

template<>
GlVertexBuffer::VertexAttribute GlVertexBuffer::createAttribute<glm::vec2>(unsigned int index)
{
    return VertexAttribute(index, 2, VertexAttribute::Float);
}

template<>
GlVertexBuffer::VertexAttribute GlVertexBuffer::createAttribute<glm::vec3>(unsigned int index)
{
    return VertexAttribute(index, 3, VertexAttribute::Float);
}

template<>
GlVertexBuffer::VertexAttribute GlVertexBuffer::createAttribute<glm::vec4>(unsigned int index)
{
    return VertexAttribute(index, 4, VertexAttribute::Float);
}

