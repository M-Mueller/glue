#include "glue/GlIndexBuffer.h"
#include "glue/GlInternal.h"

GlIndexBuffer::GlIndexBuffer():
    GlBuffer(GlBuffer::Target::ElementArray),
    _numIndices(0),
    _type(UCHAR)
{

}

void GlIndexBuffer::setData(GlBuffer::Usage usage, std::vector<unsigned char> i)
{
    GlBuffer::setData(usage, &i[0], i.size() * sizeof(unsigned char));
    _numIndices = i.size();
    _type = UCHAR;
}

void GlIndexBuffer::setData(GlBuffer::Usage usage, std::vector<unsigned short> i)
{
    GlBuffer::setData(usage, &i[0], i.size() * sizeof(unsigned short));
    _numIndices = i.size();
    _type = USHORT;
}

void GlIndexBuffer::setData(GlBuffer::Usage usage, std::vector<unsigned int> i)
{
    GlBuffer::setData(usage, &i[0], i.size() * sizeof(unsigned int));
    _numIndices = i.size();
    _type = UINT;
}

size_t GlIndexBuffer::numIndices() const
{
    return _numIndices;
}

GlIndexBuffer::IndexType GlIndexBuffer::indexType() const
{
    return _type;
}

