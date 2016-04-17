#ifndef GLSHADER_H
#define GLSHADER_H

#include "glue/GlConfig.h"
#include <string>
#include <stdexcept>

/**
 * The GlShader class represents a single shader.
 * A shader object is only usefull together with a \ref GlProgram.
 */
class GlShader
{
	friend class GlProgram;
public:
	class compile_exception: public std::runtime_error
	{
	public:
		compile_exception(const std::string& errorLog);
	private:
		std::string _errorLog;
	};

    /// Shader type
	enum Type
	{
        VertexShader,
        GeometryShader,
        FragmentShader
	};

    /**
     * Creates a new shader with the given type and the given source.
     * Does not compile the shader yet.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glCreateShader.xhtml">glCreateShader</a>
     */
    GlShader(Type type, const std::string& source);

    /**
     * Deletes the shader.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glDeleteShader.xhtml">glDeleteShader</a>
     */
	virtual ~GlShader();

    /**
     * Sets the source code of the shader.
     * Does not compile the shader.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glShaderSource.xhtml">glShaderSource</a>
     */
	void setSource(const std::string& source);

    /**
     * Tries to compile the shader source that was set before.
     * If the compilation fails a \ref compile_exception is raised that contains the error log as message.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glCompileShader.xhtml">glCompileShader</a>
     */
	void compile();

    /**
     * Returns the compile log of the last compilation.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGetShaderInfoLog.xhtml">glGetShaderInfoLog</a>
     */
	std::string compileLog() const;

    /**
     * Returns true if the shader is successfully compiled and can be used in a program.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGetShader.xhtml">glGetShader</a>
     */
	bool isValid() const;

protected:
	Type _type;
    unsigned int _id;
};

/**
 * The GlVertexShader class represents a vertex shader.
 */
class GlVertexShader: public GlShader
{
public:
    GlVertexShader(const std::string& source);
};

/**
 * The GlGeometryShader class represents a geometry shader.
 */
class GlGeometryShader: public GlShader
{
public:
    GlGeometryShader(const std::string& source);
};

/**
 * The GlFragmentShader class represents a fragment shader.
 */
class GlFragmentShader: public GlShader
{
public:
    GlFragmentShader(const std::string& source);
};



#endif // GLSHADER_H
