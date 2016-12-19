#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

uniform mat4 fullMatrix;

void main()
{
    gl_Position = fullMatrix * vec4(position, 1.0f);
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
