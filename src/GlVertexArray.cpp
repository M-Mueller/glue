#include "glue/GlVertexArray.h"
#include "glue/GlInternal.h"

GlVertexArray::GlVertexArray(bool autoEnableAttributes):
	_id(0),
    _autoEnableAttributes(autoEnableAttributes),
    _numVertices(0),
    _numIndices(0),
    _indexType(GlIndexBuffer::UCHAR)
{
	GL_SAFE_CALL(glGenVertexArrays(1, &_id));
}

GlVertexArray::~GlVertexArray()
{
	GL_SAFE_CALL(glDeleteVertexArrays(1, &_id));
}

void GlVertexArray::bind()
{
	GL_SAFE_CALL(glBindVertexArray(_id));
}

void GlVertexArray::release()
{
    GL_SAFE_CALL(glBindVertexArray(0));
}

bool GlVertexArray::isBound() const
{
    GLint currentId = -1;
    GL_SAFE_CALL(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentId));
    return currentId == (GLint)_id;
}

void GlVertexArray::setVertexData(GlVertexBuffer& vbo)
{
#ifdef GLUE_LOGGING
    if(!vbo.isBound()) LOG(DEBUG) << "VertexBuffer is not bound!";
#endif

    vbo.bind();

	for(size_t a=0; a<vbo.numAttributes(); ++a)
	{
        // set the layout of each attribute
		auto attribute = vbo.attribute(a);
        GL_SAFE_CALL(glVertexAttribPointer(attribute.index, attribute.size, mapVertexAttributeType(attribute.type), attribute.normalized, attribute.stride, (void*)((char*)0 + attribute.pointer)));
        if(_autoEnableAttributes)
            enableAttribute(a);
	}
    // only store the number of vertices in the VBO
    // the VBO will be accessed directly by the VAO, so we don't need to bind it before drawing
    _numVertices = vbo.numVertices();
}

void GlVertexArray::setIndexBuffer(GlIndexBuffer& ibo)
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "VertexArray is not bound!";
#endif

    ibo.bind();

    // only store the number of indices and index type
    // the IBO will be accessed directly by the VAO, so we don't need to bind it before drawing
    _numIndices = ibo.numIndices();
    _indexType = ibo.indexType();
}

void GlVertexArray::draw(GlVertexArray::Primitive mode)
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "VertexArray is not bound!";
#endif

    GL_SAFE_CALL(glDrawArrays(mapVertexArrayPrimitive(mode), 0, _numVertices));
}

void GlVertexArray::drawElements(GlVertexArray::Primitive mode)
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "VertexArray is not bound!";
#endif

    GL_SAFE_CALL(glDrawElements(mapVertexArrayPrimitive(mode), _numIndices, mapIndexBufferIndexType(_indexType), 0));
}

void GlVertexArray::enableAttribute(unsigned int index)
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "VertexArray is not bound!";
#endif

	GL_SAFE_CALL(glEnableVertexAttribArray(index));
}

void GlVertexArray::disableAttribute(unsigned int index)
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "VertexArray is not bound!";
#endif

	GL_SAFE_CALL(glDisableVertexAttribArray(index));
}

