#pragma once
#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
public:
	static unsigned int CreateProgramFromShaderPath(const char* shaderPath);
	static unsigned int CreateProgram(const char* vertexShader, const char* fragmentShader);
	static int CreateAndCompileShader(const char* source, unsigned int type);
	static ShaderProgramSource ParseShadersFromPath(const char* shaderPath);
};

