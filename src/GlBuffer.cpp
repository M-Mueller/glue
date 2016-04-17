#include "glue/GlBuffer.h"
#include "glue/GlInternal.h"
#include <cassert>

GlBuffer::GlBuffer(Target target):
	_target(target),
	_id(0),
	_size(0),
    _usage(Usage::StaticDraw)
{
	GL_SAFE_CALL(glGenBuffers(1, &_id));
}

GlBuffer::~GlBuffer()
{
	GL_SAFE_CALL(glDeleteBuffers(1, &_id));
}

void GlBuffer::bind()
{
    GL_SAFE_CALL(glBindBuffer(mapBufferTarget[_target], _id));
}

void GlBuffer::release()
{
    GL_SAFE_CALL(glBindBuffer(mapBufferTarget[_target], 0));
}

bool GlBuffer::isBound() const
{
    int currentId = -1;
    GLenum target;
    switch (_target) {
    case Target::Array:
        target = GL_ARRAY_BUFFER_BINDING;
        break;
    case Target::ElementArray:
        target = GL_ELEMENT_ARRAY_BUFFER_BINDING;
        break;
    }
    GL_SAFE_CALL(glGetIntegerv(target, &currentId));
    return currentId == (GLint)_id;
}

void GlBuffer::setData(Usage usage, void* data, size_t size)
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "Buffer is not bound!";
#endif

    GL_SAFE_CALL(glBufferData(mapBufferTarget[_target], (GLsizei)size, (GLvoid*)data, mapBufferUsage[usage]));
    _size = size;
}

void GlBuffer::setSubData(void* data, size_t size, size_t offset)
{
#ifdef GLUE_LOGGING
    if(!isBound()) LOG(DEBUG) << "Buffer is not bound!";
#endif

    assert(offset+size <= _size);
    GL_SAFE_CALL(glBufferSubData(mapBufferTarget[_target], (GLintptr)offset, (GLsizei)size, (GLvoid*)data));
}
