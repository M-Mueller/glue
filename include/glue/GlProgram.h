#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include "glue/GlConfig.h"
#include "glue/GlShader.h"

#ifdef GLUE_QT
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtGui/QMatrix3x3>
#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>
#endif

#include <glm/glm.hpp>

#include <memory>

/**
 * The GlProgram class represents a OpenGL shader program.
 * A program consists of a vertex, fragment and an optional geometry shader.
 * Programs must be successfully \ref link "linked" before it can be used.
 */
class GlProgram
{
public:
    /**
     * Creates a new GlProgram from the given vertex and fragment shader sources.
     * Automatically compiles the shaders, attaches them to the program and links the program.
     * If any shader stage fails to compile, a \ref GlShader::compile_exception will be raised.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glCreateProgram.xhtml">glCreateProgram</a>,
     * <a href="https://www.opengl.org/sdk/docs/man/html/glAttachShader.xhtml">glAttachShader</a>
     */
	GlProgram(const std::string& vs, const std::string& fs);

    /**
     * Creates a new GlProgram from the given vertex, geometry and fragment shader sources.
     * Automatically compiles the shaders and links them.
     * If any shader stage fails to compile, a \ref GlShader::compile_exception will be raised.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glCreateProgram.xhtml">glCreateProgram</a>,
     * <a href="https://www.opengl.org/sdk/docs/man/html/glAttachShader.xhtml">glAttachShader</a>
     */
    GlProgram(const std::string& vs, const std::string& gs, const std::string& fs);

    /**
     * Creates a new GlProgram from the given vertex, geometry and fragment shaders.
     * The shaders will be \ref GlShader::compile compiled automatically, if they are not valid yet.
     * If all shaders are compiled successfully, the program will be linked.
     * A \ref GlShader::compile_exception will be raised if compilation or linking fails.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glCreateProgram.xhtml">glCreateProgram</a>,
     * <a href="https://www.opengl.org/sdk/docs/man/html/glAttachShader.xhtml">glAttachShader</a>
     */
	GlProgram(std::shared_ptr<GlVertexShader> vs, std::shared_ptr<GlFragmentShader> fs);

    /**
     * Creates a new GlProgram from the given vertex, geometry and fragment shaders.
     * The shaders will be \ref GlShader::compile compiled automatically, if they are not valid yet.
     * If all shaders are compiled successfully, the program will be linked.
     * A \ref GlShader::compile_exception will be raised if compilation or linking fails.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glCreateProgram.xhtml">glCreateProgram</a>,
     * <a href="https://www.opengl.org/sdk/docs/man/html/glAttachShader.xhtml">glAttachShader</a>
     */
	GlProgram(std::shared_ptr<GlVertexShader> vs, std::shared_ptr<GlGeometryShader> gs, std::shared_ptr<GlFragmentShader> fs);

    /**
     * Creates a new GlProgram by loading the vertex and fragment shader sources from the given files.
     * A std::runtime_error is thrown if the files could not be loaded.
     * \see GlProgram(const std::string& vs, const std::string& fs)
     */
    static GlProgram* fromFile(const std::string& vs, const std::string& fs);

    /**
     * Creates a new GlProgram by loading the vertex, geometry and fragment shader sources from the given files.
     * A std::runtime_error is thrown if the files could not be loaded.
     * \see GlProgram(const std::string& vs, const std::string& gs, const std::string& fs)
     */
    static GlProgram* fromFile(const std::string& vs, const std::string& gs, const std::string& fs);

    /**
     * Returns the current vertex shader.
     */
	std::shared_ptr<GlVertexShader> vertexShader() const;

    /**
     * Returns the current geometry shader if any.
     */
	std::shared_ptr<GlGeometryShader> geometryShader() const;

    /**
     * Returns the current vertex shader.
     */
	std::shared_ptr<GlFragmentShader> fragmentShader() const;

    /**
     * Links the shaders to a program.
     * Shaders must be successfully compiled before.
     * Returns true if the linking was successfull, false otherwise.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glLinkProgram.xhtml">glLinkProgram</a>
     */
	bool link();

    /**
     * Returns the log of the last linking.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGetProgramInfoLog.xhtml">glGetProgramInfoLog</a>
     */
    std::string linkLog() const;

    /**
     * Activates the shader program.
     * Overrides any previous active shader program.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml">glUseProgram</a>
     */
	void activate();

    /**
     * Deactivates all shader programs.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml">glUseProgram</a>
     */
	void deactivate();

    /**
     * Binds a user-defined varying out variable of the fragment shader to a color channel.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glBindFragDataLocation.xhtml">glBindFragDataLocation</a>
     */
	void setFragDataLocation(const std::string& name, int colorNumber);

    /**
     * Returns the location of the shader attribute with the given name.
     * If name is not a attribute, -1 is returned.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGetAttribLocation.xhtml">glGetAttribLocation</a>
     */
	int getAttributeLocation(const std::string& name);

    /**
     * Returns the location of the shader uniform with the given name.
     * If name is not a uniform, -1 is returned.
     * \see <a href="https://www.opengl.org/sdk/docs/man/html/glGetUniformLocation.xhtml">glGetUniformLocation</a>
     */
    int getUniformLocation(const std::string& name);

    /**
     * \name Uniforms
     * Sets a uniform with the given name to the given value.
     * The type of the uniform is infered from the overload.
     * Does nothing if the uniform does not exist.
     */
    ///@{
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform1i</a>
    void setUniform(const std::string& name, int value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform1f</a>
    void setUniform(const std::string& name, float value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform1f</a>
    void setUniform(const std::string& name, double value);
#ifdef GLUE_GLM
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniformMatrix4fv</a>
    void setUniform(const std::string& name, const glm::mat4 &value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform3f</a>
    void setUniform(const std::string& name, const glm::vec3 &value);
#endif
#ifdef GLUE_QT
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform2f</a>
    void setUniform(const std::string& name, const QVector2D &value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform3f</a>
    void setUniform(const std::string& name, const QVector3D &value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform4f</a>
    void setUniform(const std::string& name, const QVector4D &value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniformMatrix3fv</a>
    void setUniform(const std::string& name, const QMatrix3x3 &value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniformMatrix4fv</a>
    void setUniform(const std::string& name, const QMatrix4x4 &value);
    /// \see <a href="https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml">glUniform4f</a>
    void setUniform(const std::string& name, const QColor &value);
#endif
    ///@}

private:
    static std::string loadFile(const std::string& filepath);

private:
    unsigned int _id;
	std::shared_ptr<GlVertexShader> _vs;
	std::shared_ptr<GlGeometryShader> _gs;
	std::shared_ptr<GlFragmentShader> _fs;
};

#endif // GLPROGRAM_H
