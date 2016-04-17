#include "glue/GlShader.h"
#include "glue/GlInternal.h"

GlShader::compile_exception::compile_exception(const std::string& errorLog):
	std::runtime_error(errorLog)
{

}

GlShader::GlShader(GlShader::Type type, const std::string& source):
	_type(type),
	_id(0)
{
    _id = GL_SAFE_CALL(glCreateShader(mapShaderType[_type]));
	setSource(source);
}

GlShader::~GlShader()
{
	GL_SAFE_CALL(glDeleteShader(_id));
}

void GlShader::setSource(const std::string& source)
{
	const GLchar* src = source.c_str();
	const GLint length = source.size();
	GL_SAFE_CALL(glShaderSource(_id, 1, &src, &length));
}

void GlShader::compile()
{
	GL_SAFE_CALL(glCompileShader(_id));

	GLint status;
	GL_SAFE_CALL(glGetShaderiv(_id, GL_COMPILE_STATUS, &status));

#ifdef GLUE_LOGGING
    LOG(INFO) << "Shader compiled: " << compileLog();
#endif

	if(status != GL_TRUE)
	{
		throw compile_exception(compileLog());
	}
}

std::string GlShader::compileLog() const
{
	GLint infoLogLength;
	GL_SAFE_CALL(glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength));
	if(infoLogLength <= 0)
		return "";

	GLchar* strInfoLog = new GLchar[infoLogLength + 1];
	GL_SAFE_CALL(glGetShaderInfoLog(_id, infoLogLength, NULL, strInfoLog));

	std::string infoLog(strInfoLog);
	delete strInfoLog;
	return infoLog;
}

bool GlShader::isValid() const
{
	if(_id != 0)
	{
		GLint status;
		glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
		return status == GL_TRUE;
	}
	return false;
}


GlVertexShader::GlVertexShader(const std::string& source):
	GlShader(VertexShader, source)
{

}


GlGeometryShader::GlGeometryShader(const std::string& source):
	GlShader(GeometryShader, source)
{

}


GlFragmentShader::GlFragmentShader(const std::string& source):
	GlShader(FragmentShader, source)
{

}
