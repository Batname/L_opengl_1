#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 fullMatrix;
uniform mat4 model;

void main()
{
    gl_Position = fullMatrix * vec4(position, 1.0f);
    TexCoords = texCoord;
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = normal;
}
