#include "glue/GlProgram.h"
#include "glue/GlInternal.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <cassert>

GlProgram::GlProgram(const std::string& vs, const std::string& fs):
	GlProgram(std::make_shared<GlVertexShader>(vs), nullptr, std::make_shared<GlFragmentShader>(fs))
{

}

GlProgram::GlProgram(const std::string& vs, const std::string& gs, const std::string& fs):
	GlProgram(std::make_shared<GlVertexShader>(vs), std::make_shared<GlGeometryShader>(gs), std::make_shared<GlFragmentShader>(fs))
{

}

GlProgram::GlProgram(std::shared_ptr<GlVertexShader> vs, std::shared_ptr<GlFragmentShader> fs):
	GlProgram(vs, nullptr, fs)
{

}

GlProgram::GlProgram(std::shared_ptr<GlVertexShader> vs, std::shared_ptr<GlGeometryShader> gs, std::shared_ptr<GlFragmentShader> fs):
	_id(0),
	_vs(vs),
	_gs(gs),
	_fs(fs)
{
	assert(_vs && _fs);

	if(!_vs->isValid())
	{
		_vs->compile();
	}

	if(_gs && !_gs->isValid())
	{
		_gs->compile();
	}

	if(!_fs->isValid())
	{
		_fs->compile();
	}

	_id = GL_SAFE_CALL(glCreateProgram());

	GL_SAFE_CALL(glAttachShader(_id, _vs->_id));
	if(_gs)
		GL_SAFE_CALL(glAttachShader(_id, _gs->_id));
	GL_SAFE_CALL(glAttachShader(_id, _fs->_id));

    link();
}

std::string GlProgram::loadFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if(file.is_open())
    {
        std::stringstream sstream;
        sstream << file.rdbuf();
        return sstream.str();
    }
    else
    {
        throw std::runtime_error("Could not open " + filepath);
    }
    return "";
}

GlProgram *GlProgram::fromFile(const std::string &vs, const std::string &fs)
{
    std::string vsSrc = loadFile(vs);
    std::string fsSrc = loadFile(fs);
    return new GlProgram(vsSrc, fsSrc);
}

GlProgram *GlProgram::fromFile(const std::string &vs, const std::string &gs, const std::string &fs)
{
    std::string vsSrc = loadFile(vs);
    std::string gsSrc = loadFile(gs);
    std::string fsSrc = loadFile(fs);
    return new GlProgram(vsSrc, gsSrc, fsSrc);
}

std::shared_ptr<GlVertexShader> GlProgram::vertexShader() const
{
	return _vs;
}

std::shared_ptr<GlGeometryShader> GlProgram::geometryShader() const
{
	return _gs;
}

std::shared_ptr<GlFragmentShader> GlProgram::fragmentShader() const
{
	return _fs;
}

bool GlProgram::link()
{
	GL_SAFE_CALL(glLinkProgram(_id));
	GLint isLinked;
	GL_SAFE_CALL(glGetProgramiv(_id, GL_LINK_STATUS, &isLinked));

#ifdef GLUE_LOGGING
    LOG(INFO) << "Program linked: " << linkLog();
#endif
    return isLinked == GL_TRUE;
}

std::string GlProgram::linkLog() const
{
    GLint infoLogLength;
    GL_SAFE_CALL(glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength));
    if(infoLogLength <= 0)
        return "";

    GLchar* strInfoLog = new GLchar[infoLogLength + 1];
    GL_SAFE_CALL(glGetProgramInfoLog(_id, infoLogLength, NULL, strInfoLog));

    std::string infoLog(strInfoLog);
    delete strInfoLog;
    return infoLog;

}

void GlProgram::activate()
{
	GL_SAFE_CALL(glUseProgram(_id));
}

void GlProgram::deactivate()
{
	GL_SAFE_CALL(glUseProgram(0));
}

void GlProgram::setFragDataLocation(const std::string& name, int colorNumber)
{
	GL_SAFE_CALL(glBindFragDataLocation(_id, colorNumber, name.c_str()));
}

int GlProgram::getAttributeLocation(const std::string& name)
{
	GLint location = GL_SAFE_CALL(glGetAttribLocation(_id, name.c_str()));
    return location;
}

int GlProgram::getUniformLocation(const std::string& name)
{
    GLint location = GL_SAFE_CALL(glGetUniformLocation(_id, name.c_str()));
    return location;
}

#ifdef GLUE_GLM
void GlProgram::setUniform(const std::string &name, const glm::mat4 &value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniformMatrix4fv(location, 1, false, glm::value_ptr(value)));
}

void GlProgram::setUniform(const std::string& name, const glm::vec3& value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform3fv(location, 3, glm::value_ptr(value)));
}
#endif

void GlProgram::setUniform(const std::__cxx11::string& name, const QColor& value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform4f(location,
                             static_cast<float>(value.redF()),
                             static_cast<float>(value.greenF()),
                             static_cast<float>(value.blueF()),
                             static_cast<float>(value.alphaF())));
}

#ifdef GLUE_QT
void GlProgram::setUniform(const std::string& name, const QVector2D& value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform2f(location, value.x(), value.y()));
}

void GlProgram::setUniform(const std::string& name, const QVector3D& value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform3f(location, value.x(), value.y(), value.z()));
}

void GlProgram::setUniform(const std::string& name, const QVector4D& value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform4f(location, value.x(), value.y(), value.z(), value.w()));
}

void GlProgram::setUniform(const std::string& name, const QMatrix3x3& value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniformMatrix3fv(location, 1, false, value.constData()));
}

void GlProgram::setUniform(const std::string& name, const QMatrix4x4& value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniformMatrix4fv(location, 1, false, value.constData()));
}
#endif

void GlProgram::setUniform(const std::string& name, int value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform1i(location, value));
}

void GlProgram::setUniform(const std::string& name, float value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform1f(location, value));
}

void GlProgram::setUniform(const std::string& name, double value)
{
    int location = getUniformLocation(name);
#ifdef GLUE_LOGGING
    if(location < 0) LOG(DEBUG) << "Uniform " << name << " not found";
#endif
    GL_SAFE_CALL(glUniform1f(location, static_cast<float>(value)));
}
