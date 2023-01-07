#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 textureCoords;
layout(location = 3) in float textureIndex;

out vec3 Color;
out vec2 TextureCoords;
out float TextureIndex;

void main()
{
	Color = color;
	TextureCoords = textureCoords;
	TextureIndex = textureIndex;
	gl_Position = vec4(position, 1.0);
};

#shader fragment
#version 450 core

in vec3 Color;
in vec2 TextureCoords;
in float TextureIndex;
uniform sampler2D Textures[32];

out vec4 outColor;

void main()
{
	if (Color.rbg == vec3(255, 0, 255)) discard;
	int index = int(TextureIndex);
	outColor = texture(Textures[index], TextureCoords);
};