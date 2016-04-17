#include "glue/GlInternal.h"

std::map<GlBuffer::Target, GLenum> mapBufferTarget =
{
    { GlBuffer::Target::Array, GL_ARRAY_BUFFER },
    { GlBuffer::Target::ElementArray, GL_ELEMENT_ARRAY_BUFFER }
};

std::map<GlBuffer::Usage, GLenum> mapBufferUsage =
{
    { GlBuffer::Usage::StreamCopy, GL_STREAM_COPY },
    { GlBuffer::Usage::StreamDraw, GL_STREAM_DRAW },
    { GlBuffer::Usage::StreamRead, GL_STREAM_READ },
    { GlBuffer::Usage::StaticCopy, GL_STATIC_COPY },
    { GlBuffer::Usage::StaticDraw, GL_STATIC_DRAW },
    { GlBuffer::Usage::StaticRead, GL_STATIC_READ },
    { GlBuffer::Usage::DynamicCopy, GL_DYNAMIC_COPY },
    { GlBuffer::Usage::DynamicDraw, GL_DYNAMIC_DRAW },
    { GlBuffer::Usage::DynamicRead, GL_DYNAMIC_READ }
};

std::map<GlVertexBuffer::VertexAttribute::Type, GLenum> mapVertexAttributeType =
{
    { GlVertexBuffer::VertexAttribute::Byte, GL_BYTE },
    { GlVertexBuffer::VertexAttribute::UnsignedByte, GL_UNSIGNED_BYTE },
    { GlVertexBuffer::VertexAttribute::Short, GL_SHORT },
    { GlVertexBuffer::VertexAttribute::UnsignedShort, GL_UNSIGNED_SHORT },
    { GlVertexBuffer::VertexAttribute::Int, GL_INT },
    { GlVertexBuffer::VertexAttribute::UnsignedInt, GL_UNSIGNED_INT },
    { GlVertexBuffer::VertexAttribute::Float, GL_FLOAT },
};

std::map<GlVertexArray::Primitive, GLenum> mapVertexArrayPrimitive =
{
    { GlVertexArray::Primitive::Points, GL_POINTS },
    { GlVertexArray::Primitive::LineStrip, GL_LINE_STRIP },
    { GlVertexArray::Primitive::LineLoop, GL_LINE_LOOP },
    { GlVertexArray::Primitive::Lines, GL_LINES },
    { GlVertexArray::Primitive::TriangleStrip, GL_TRIANGLE_STRIP },
    { GlVertexArray::Primitive::TriangleFan, GL_TRIANGLE_FAN },
    { GlVertexArray::Primitive::Triangles, GL_TRIANGLES }
};

std::map<GlIndexBuffer::IndexType, GLenum> mapIndexBufferIndexType =
{
    { GlIndexBuffer::UCHAR, GL_UNSIGNED_BYTE },
    { GlIndexBuffer::USHORT, GL_UNSIGNED_SHORT },
    { GlIndexBuffer::UINT, GL_UNSIGNED_INT }
};

std::map<GlFrameBuffer::Target, GLenum> mapFrameBufferTarget =
{
    { GlFrameBuffer::Target::ReadBuffer, GL_READ_FRAMEBUFFER },
    { GlFrameBuffer::Target::DrawBuffer, GL_DRAW_FRAMEBUFFER },
    { GlFrameBuffer::Target::DrawReadBuffer, GL_FRAMEBUFFER }
};

std::map<GlFrameBuffer::Attachment, GLenum> mapFrameBufferAttachment =
{
    { GlFrameBuffer::Attachment::Color0, GL_COLOR_ATTACHMENT0 },
    { GlFrameBuffer::Attachment::Color1, GL_COLOR_ATTACHMENT1 },
    { GlFrameBuffer::Attachment::Color2, GL_COLOR_ATTACHMENT2 },
    { GlFrameBuffer::Attachment::Color3, GL_COLOR_ATTACHMENT3 },
    { GlFrameBuffer::Attachment::Color4, GL_COLOR_ATTACHMENT4 },
    { GlFrameBuffer::Attachment::Color5, GL_COLOR_ATTACHMENT5 },
    { GlFrameBuffer::Attachment::Color6, GL_COLOR_ATTACHMENT6 },
    { GlFrameBuffer::Attachment::Color7, GL_COLOR_ATTACHMENT7 },
    { GlFrameBuffer::Attachment::Color8, GL_COLOR_ATTACHMENT8 },
    { GlFrameBuffer::Attachment::Depth, GL_DEPTH_ATTACHMENT },
    { GlFrameBuffer::Attachment::Stencil, GL_STENCIL_ATTACHMENT }
};

std::map<GlTexture::Type, GLenum> mapTextureType =
{
    { GlTexture::Type::Texture1D, GL_TEXTURE_1D },
    { GlTexture::Type::Texture2D, GL_TEXTURE_2D },
    { GlTexture::Type::Texture3D, GL_TEXTURE_3D }
};

std::map<GlTexture::InternalFormat, GLenum> mapTextureInternalFormat =
{
    { GlTexture::InternalFormat::Invalid, -1 },
    { GlTexture::InternalFormat::R8, GL_R8 },
    { GlTexture::InternalFormat::RG8, GL_RG8 },
    { GlTexture::InternalFormat::RGB8,  GL_RGB8 },
    { GlTexture::InternalFormat::RGBA8,  GL_RGBA8 },
    { GlTexture::InternalFormat::R16, GL_R16 },
    { GlTexture::InternalFormat::RG16, GL_RG16 },
    { GlTexture::InternalFormat::RGB16, GL_RGB16 },
    { GlTexture::InternalFormat::RGBA16, GL_RGBA16 },
    { GlTexture::InternalFormat::R16F, GL_R16F },
    { GlTexture::InternalFormat::RG16F, GL_RG16F },
    { GlTexture::InternalFormat::RGB16F, GL_RGB16F },
    { GlTexture::InternalFormat::RGBA16F, GL_RGBA16F },
    { GlTexture::InternalFormat::R32F, GL_R32F },
    { GlTexture::InternalFormat::RG32F, GL_RG32F },
    { GlTexture::InternalFormat::RGB32F, GL_RGB32F },
    { GlTexture::InternalFormat::RGBA32F, GL_RGBA32F },
    { GlTexture::InternalFormat::DepthComponent16, GL_DEPTH_COMPONENT16 },
    { GlTexture::InternalFormat::DepthComponent24, GL_DEPTH_COMPONENT24 },
    { GlTexture::InternalFormat::DepthComponent32, GL_DEPTH_COMPONENT32 },
    { GlTexture::InternalFormat::DepthComponent32F, GL_DEPTH_COMPONENT32F }

};

std::map<GlTexture::PixelFormat, GLenum> mapTexturePixelFormat =
{
    { GlTexture::PixelFormat::Red, GL_RED },
    { GlTexture::PixelFormat::RG, GL_RG },
    { GlTexture::PixelFormat::RGB, GL_RGB },
    { GlTexture::PixelFormat::RGBA, GL_RGBA },
    { GlTexture::PixelFormat::BGR, GL_BGR },
    { GlTexture::PixelFormat::BGRA, GL_BGRA }
};

std::map<GlTexture::PixelType, GLenum> mapTexturePixelType
{
    { GlTexture::PixelType::UnsignedByte, GL_UNSIGNED_BYTE },
    { GlTexture::PixelType::Byte, GL_BYTE },
    { GlTexture::PixelType::UnsignedShort, GL_UNSIGNED_SHORT },
    { GlTexture::PixelType::Short, GL_UNSIGNED_SHORT },
    { GlTexture::PixelType::HalfFloat, GL_HALF_FLOAT },
    { GlTexture::PixelType::Float, GL_FLOAT }
};

std::map<GlShader::Type, GLenum> mapShaderType =
{
    { GlShader::Type::VertexShader, GL_VERTEX_SHADER },
    { GlShader::Type::GeometryShader, GL_GEOMETRY_SHADER },
    { GlShader::Type::FragmentShader, GL_FRAGMENT_SHADER },
};

std::map<GlTexture::MinFilter, GLint> mapMinFilter =
{
    { GlTexture::MinFilter::Nearest, GL_NEAREST },
    { GlTexture::MinFilter::Linear, GL_LINEAR },
    { GlTexture::MinFilter::NearestMipMapNearest, GL_NEAREST_MIPMAP_NEAREST },
    { GlTexture::MinFilter::LinearMipMapNearest, GL_LINEAR_MIPMAP_NEAREST },
    { GlTexture::MinFilter::NearestMipMapLinear, GL_NEAREST_MIPMAP_LINEAR },
    { GlTexture::MinFilter::LinearMipMapLinear, GL_LINEAR_MIPMAP_LINEAR }
};

std::map<GlTexture::MagFilter, GLint> mapMagFilter =
{
    { GlTexture::MagFilter::Nearest, GL_NEAREST },
    { GlTexture::MagFilter::Linear, GL_LINEAR }
};
