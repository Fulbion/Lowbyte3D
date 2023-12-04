#include <glad/glad.h>

#include "OpenGL/Graphics/ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const ShaderProgramDesc& i_desc)
{
	this->m_programID = glCreateProgram();
	this->attach(i_desc.vertexShaderPath, ShaderType::VertexShader);;
	this->attach(i_desc.fragmentShaderPath, ShaderType::FragmentShader);;
	this->link();
}

ShaderProgram::~ShaderProgram()
{
	for (UINT i = 0; i < 2; i++)
	{
		glDetachShader(this->m_programID, this->m_attachedShaders[i]);
		glDeleteShader(this->m_attachedShaders[i]);
	}

	glDeleteProgram(this->m_programID);
}

void ShaderProgram::attach(const wchar_t* i_shaderFilePath, const ShaderType& i_type)
{
	std::string shaderCode;

	std::ifstream shaderStream(i_shaderFilePath);

	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}

	else
	{
		return;
	}

	GLuint shaderID = 0;

	switch (i_type)
	{
	case ShaderType::VertexShader:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;

	case ShaderType::FragmentShader:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	default:
		break;
	}

	const char* sourcePointer = shaderCode.c_str();

	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	glAttachShader(this->m_programID, shaderID);

	this->m_attachedShaders[static_cast<int>(i_type)] = shaderID;
}

void ShaderProgram::link()
{
	glLinkProgram(this->m_programID);
}
