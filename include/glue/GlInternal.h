#ifndef GLINTERNAL_H
#define GLINTERNAL_H

#include "glue/GlConfig.h"
#include "glue/GlBuffer.h"
#include "glue/GlVertexBuffer.h"
#include "glue/GlVertexArray.h"
#include "glue/GlFrameBuffer.h"
#include "glue/GlTexture.h"
#include "glue/GlShader.h"
#include "glue/GlQuery.h"

#include "glad/glad.h"

#ifdef GLUE_LOGGING
#include "easylogging++.h"
#endif

//***********************************************************************
// IMPORTANT: This header must not be included in any other glue headers
//***********************************************************************

// converts strongly type enums to OpenGL enums
// avoids including gl.h in every header
GLenum mapBufferTarget(GlBuffer::Target value);
GLenum mapBufferUsage(GlBuffer::Usage value);
GLenum mapVertexAttributeType(GlVertexBuffer::VertexAttribute::Type value);
GLenum mapVertexArrayPrimitive(GlVertexArray::Primitive value);
GLenum mapIndexBufferIndexType(GlIndexBuffer::IndexType value);
GLenum mapFrameBufferTarget(GlFrameBuffer::Target value);
GLenum mapFrameBufferAttachment(GlFrameBuffer::Attachment value);
GLenum mapTextureType(GlTexture::Type value);
GLenum mapTextureInternalFormat(GlTexture::InternalFormat value);
GLenum mapTexturePixelFormat(GlTexture::PixelFormat value);
GLenum mapTexturePixelType(GlTexture::PixelType value);
GLenum mapShaderType(GlShader::Type value);
GLint mapMinFilter(GlTexture::MinFilter value);
GLint mapMagFilter(GlTexture::MagFilter value);
GLenum mapQueryTarget(GlQuery::Target value);

inline void logGLerror(const char* file, const char* function, int line)
{
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
#ifdef GLUE_LOGGING
        auto logger = el::Loggers::getLogger("default");
        if(error == GL_INVALID_ENUM)
        {
            logger->warn("%v:%v in function '%v': Invalid Enum\n", file, line, function);
        }
        else if(error == GL_INVALID_VALUE)
        {
            logger->warn("%v:%v in function '%v': Invalid Value\n", file, line, function);
        }
        else if(error == GL_INVALID_OPERATION)
        {
            logger->warn("%v:%v in function '%v': Invalid Operation\n", file, line, function);
        }
        else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
        {
            logger->warn("%v:%v in function '%v': Invalid Framebuffer Operation\n", file, line, function);
        }
        else if(error == GL_OUT_OF_MEMORY)
        {
            logger->warn("%v:%v in function '%v': Out of memory\n", file, line, function);
        }
        else
        {
            logger->warn("Warning: %v:%v in function '%v': Unkown error\n", file, line, function);
        }
#endif
    }
}

#ifdef GLUE_GL_DEBUG
#define GL_SAFE_CALL(f) f; logGLerror(__FILE__, __PRETTY_FUNCTION__, __LINE__);
#else
#define GL_SAFE_CALL(f) f
#endif

#endif // GLINTERNAL_H
