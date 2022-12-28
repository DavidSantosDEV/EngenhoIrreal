#shader vertex
#version 330 core
	
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
out vec3 Color;

void main()
{
	Color = color;
	gl_Position = vec4(position, 0.0, 1.0);
};

#shader fragment
#version 330 core

in vec3 Color;
out vec4 outColor;

void main()
{
	outColor = vec4(Color, 1.f);
};