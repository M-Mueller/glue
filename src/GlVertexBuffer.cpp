#include "glue/GlVertexBuffer.h"

#include <glm/glm.hpp>

#ifdef GLUE_QT
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#endif

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

#ifdef GLUE_GLM
static_assert(sizeof(glm::vec2) == sizeof(float) * 2, "glm vector type not aligned correctly");
static_assert(sizeof(glm::vec3) == sizeof(float) * 3, "glm vector type not aligned correctly");
static_assert(sizeof(glm::vec4) == sizeof(float) * 4, "glm vector type not aligned correctly");

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
#endif

#ifdef GLUE_QT
static_assert(sizeof(QVector2D) == sizeof(float) * 2, "QVector2D not aligned correctly");
static_assert(sizeof(QVector3D) == sizeof(float) * 3, "QVector3D not aligned correctly");
static_assert(sizeof(QVector4D) == sizeof(float) * 4, "QVector4D not aligned correctly");

template<>
GlVertexBuffer::VertexAttribute GlVertexBuffer::createAttribute<QVector2D>(unsigned int index)
{
    return VertexAttribute(index, 2, VertexAttribute::Float);
}

template<>
GlVertexBuffer::VertexAttribute GlVertexBuffer::createAttribute<QVector3D>(unsigned int index)
{
    return VertexAttribute(index, 3, VertexAttribute::Float);
}

template<>
GlVertexBuffer::VertexAttribute GlVertexBuffer::createAttribute<QVector4D>(unsigned int index)
{
    return VertexAttribute(index, 4, VertexAttribute::Float);
}

#endif

