#include "glue/GlInternal.h"
#include <cassert>

GLenum mapBufferTarget(GlBuffer::Target value)
{
    switch(value)
    {
    case GlBuffer::Target::Array: return GL_ARRAY_BUFFER;
    case GlBuffer::Target::ElementArray: return GL_ELEMENT_ARRAY_BUFFER;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapBufferUsage(GlBuffer::Usage value)
{
    switch(value)
    {
    case GlBuffer::Usage::StreamCopy: return GL_STREAM_COPY;
    case GlBuffer::Usage::StreamDraw: return GL_STREAM_DRAW;
    case GlBuffer::Usage::StreamRead: return GL_STREAM_READ;
    case GlBuffer::Usage::StaticCopy: return GL_STATIC_COPY;
    case GlBuffer::Usage::StaticDraw: return GL_STATIC_DRAW;
    case GlBuffer::Usage::StaticRead: return GL_STATIC_READ;
    case GlBuffer::Usage::DynamicCopy: return GL_DYNAMIC_COPY;
    case GlBuffer::Usage::DynamicDraw: return GL_DYNAMIC_DRAW;
    case GlBuffer::Usage::DynamicRead: return GL_DYNAMIC_READ;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapVertexAttributeType(GlVertexBuffer::VertexAttribute::Type value)
{
    switch(value)
    {
    case GlVertexBuffer::VertexAttribute::Byte: return GL_BYTE;
    case GlVertexBuffer::VertexAttribute::UnsignedByte: return GL_UNSIGNED_BYTE;
    case GlVertexBuffer::VertexAttribute::Short: return GL_SHORT;
    case GlVertexBuffer::VertexAttribute::UnsignedShort: return GL_UNSIGNED_SHORT;
    case GlVertexBuffer::VertexAttribute::Int: return GL_INT;
    case GlVertexBuffer::VertexAttribute::UnsignedInt: return GL_UNSIGNED_INT;
    case GlVertexBuffer::VertexAttribute::Float: return GL_FLOAT;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapVertexArrayPrimitive(GlVertexArray::Primitive value)
{
    switch(value)
    {
    case GlVertexArray::Primitive::Points: return GL_POINTS;
    case GlVertexArray::Primitive::LineStrip: return GL_LINE_STRIP;
    case GlVertexArray::Primitive::LineLoop: return GL_LINE_LOOP;
    case GlVertexArray::Primitive::Lines: return GL_LINES;
    case GlVertexArray::Primitive::TriangleStrip: return GL_TRIANGLE_STRIP;
    case GlVertexArray::Primitive::TriangleFan: return GL_TRIANGLE_FAN;
    case GlVertexArray::Primitive::Triangles: return GL_TRIANGLES;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapIndexBufferIndexType(GlIndexBuffer::IndexType value)
{
    switch(value)
    {
    case GlIndexBuffer::UCHAR: return GL_UNSIGNED_BYTE;
    case GlIndexBuffer::USHORT: return GL_UNSIGNED_SHORT;
    case GlIndexBuffer::UINT: return GL_UNSIGNED_INT;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapFrameBufferTarget(GlFrameBuffer::Target value)
{
    switch(value)
    {
    case GlFrameBuffer::Target::ReadBuffer: return GL_READ_FRAMEBUFFER;
    case GlFrameBuffer::Target::DrawBuffer: return GL_DRAW_FRAMEBUFFER;
    case GlFrameBuffer::Target::DrawReadBuffer: return GL_FRAMEBUFFER;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapFrameBufferAttachment(GlFrameBuffer::Attachment value)
{
    switch(value)
    {
    case GlFrameBuffer::Attachment::Color0: return GL_COLOR_ATTACHMENT0;
    case GlFrameBuffer::Attachment::Color1: return GL_COLOR_ATTACHMENT1;
    case GlFrameBuffer::Attachment::Color2: return GL_COLOR_ATTACHMENT2;
    case GlFrameBuffer::Attachment::Color3: return GL_COLOR_ATTACHMENT3;
    case GlFrameBuffer::Attachment::Color4: return GL_COLOR_ATTACHMENT4;
    case GlFrameBuffer::Attachment::Color5: return GL_COLOR_ATTACHMENT5;
    case GlFrameBuffer::Attachment::Color6: return GL_COLOR_ATTACHMENT6;
    case GlFrameBuffer::Attachment::Color7: return GL_COLOR_ATTACHMENT7;
    case GlFrameBuffer::Attachment::Color8: return GL_COLOR_ATTACHMENT8;
    case GlFrameBuffer::Attachment::Depth: return GL_DEPTH_ATTACHMENT;
    case GlFrameBuffer::Attachment::Stencil: return GL_STENCIL_ATTACHMENT;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapTextureType(GlTexture::Type value)
{
    switch(value)
    {
    case GlTexture::Type::Texture1D: return GL_TEXTURE_1D;
    case GlTexture::Type::Texture2D: return GL_TEXTURE_2D;
    case GlTexture::Type::Texture3D: return GL_TEXTURE_3D;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapTextureInternalFormat(GlTexture::InternalFormat value)
{
    switch(value)
    {
    case GlTexture::InternalFormat::Invalid: return -1;
    case GlTexture::InternalFormat::R8: return GL_R8;
    case GlTexture::InternalFormat::RG8: return GL_RG8;
    case GlTexture::InternalFormat::RGB8: return  GL_RGB8;
    case GlTexture::InternalFormat::RGBA8: return  GL_RGBA8;
    case GlTexture::InternalFormat::R16: return GL_R16;
    case GlTexture::InternalFormat::RG16: return GL_RG16;
    case GlTexture::InternalFormat::RGB16: return GL_RGB16;
    case GlTexture::InternalFormat::RGBA16: return GL_RGBA16;
    case GlTexture::InternalFormat::R16F: return GL_R16F;
    case GlTexture::InternalFormat::RG16F: return GL_RG16F;
    case GlTexture::InternalFormat::RGB16F: return GL_RGB16F;
    case GlTexture::InternalFormat::RGBA16F: return GL_RGBA16F;
    case GlTexture::InternalFormat::R32F: return GL_R32F;
    case GlTexture::InternalFormat::RG32F: return GL_RG32F;
    case GlTexture::InternalFormat::RGB32F: return GL_RGB32F;
    case GlTexture::InternalFormat::RGBA32F: return GL_RGBA32F;
    case GlTexture::InternalFormat::DepthComponent16: return GL_DEPTH_COMPONENT16;
    case GlTexture::InternalFormat::DepthComponent24: return GL_DEPTH_COMPONENT24;
    case GlTexture::InternalFormat::DepthComponent32: return GL_DEPTH_COMPONENT32;
    case GlTexture::InternalFormat::DepthComponent32F: return GL_DEPTH_COMPONENT32F;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapTexturePixelFormat(GlTexture::PixelFormat value)
{
    switch(value)
    {
    case GlTexture::PixelFormat::Red: return GL_RED;
    case GlTexture::PixelFormat::RG: return GL_RG;
    case GlTexture::PixelFormat::RGB: return GL_RGB;
    case GlTexture::PixelFormat::RGBA: return GL_RGBA;
    case GlTexture::PixelFormat::BGR: return GL_BGR;
    case GlTexture::PixelFormat::BGRA: return GL_BGRA;
    }
    assert(false);
    return GL_NONE;
}

GLenum mapTexturePixelType(GlTexture::PixelType value)
{
    switch(value)
    {
    case GlTexture::PixelType::UnsignedByte: return GL_UNSIGNED_BYTE;
    case GlTexture::PixelType::Byte: return GL_BYTE;
    case GlTexture::PixelType::UnsignedShort: return GL_UNSIGNED_SHORT;
    case GlTexture::PixelType::Short: return GL_UNSIGNED_SHORT;
    case GlTexture::PixelType::HalfFloat: return GL_HALF_FLOAT;
    case GlTexture::PixelType::Float: return GL_FLOAT;
    }
    assert(false);
    return GL_NONE;
};

GLenum mapShaderType(GlShader::Type value)
{
    switch(value)
    {
    case GlShader::Type::VertexShader: return GL_VERTEX_SHADER;
    case GlShader::Type::GeometryShader: return GL_GEOMETRY_SHADER;
    case GlShader::Type::FragmentShader: return GL_FRAGMENT_SHADER;
    }
    assert(false);
    return GL_NONE;
}

GLint mapMinFilter(GlTexture::MinFilter value)
{
    switch(value)
    {
    case GlTexture::MinFilter::Nearest: return GL_NEAREST;
    case GlTexture::MinFilter::Linear: return GL_LINEAR;
    case GlTexture::MinFilter::NearestMipMapNearest: return GL_NEAREST_MIPMAP_NEAREST;
    case GlTexture::MinFilter::LinearMipMapNearest: return GL_LINEAR_MIPMAP_NEAREST;
    case GlTexture::MinFilter::NearestMipMapLinear: return GL_NEAREST_MIPMAP_LINEAR;
    case GlTexture::MinFilter::LinearMipMapLinear: return GL_LINEAR_MIPMAP_LINEAR;
    }
    assert(false);
    return -1;
}

GLint mapMagFilter(GlTexture::MagFilter value)
{
    switch(value)
    {
    case GlTexture::MagFilter::Nearest: return GL_NEAREST;
    case GlTexture::MagFilter::Linear: return GL_LINEAR;
    }
    assert(false);
    return -1;
}

GLenum mapQueryTarget(GlQuery::Target value)
{
    switch(value)
    {
    case GlQuery::Target::TimeElapsed: return GL_TIME_ELAPSED;
    }
    assert(false);
    return GL_NONE;
}
