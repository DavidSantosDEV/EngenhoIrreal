#include "Shader.h"
#include <glad/glad.h>
#include "Log.h"
#include <iostream>
#include <fstream>
#include <sstream>

unsigned int Shader::CreateProgramFromShaderPath(const char* shaderPath)
{
	ShaderProgramSource shadersSource = ParseShadersFromPath(shaderPath);
	unsigned int shaderID = CreateProgram(shadersSource.VertexSource.c_str(), 
		shadersSource.FragmentSource.c_str());
	return shaderID;
}

ShaderProgramSource Shader::ParseShadersFromPath(const char* shaderPath)
{
	enum class ShaderType
	{
		None = -1, Vertex = 0, Fragment = 1
	};

	std::ifstream stream(shaderPath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::None;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::Fragment;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateProgram(const char* vertexShader, const char* fragmentShader)
{
	unsigned int vertex = CreateAndCompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fragment = CreateAndCompileShader(fragmentShader, GL_FRAGMENT_SHADER);
	unsigned int program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	GLint success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		LOG_ERROR("ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog);
	}

	glUseProgram(program);

	return program;
}

int Shader::CreateAndCompileShader(const char* source, unsigned int type)
{
	unsigned int id = glCreateShader(type); 
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	GLint success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		LOG_ERROR("ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") 
			<< "::COMPILATION_FAILED\n" << infoLog);
		glDeleteShader(id);
		return -1;
	}
	else
	{
		LOG("COMPILATION::SUCCESS::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));
	}
	return id;
}
