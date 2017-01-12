#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 lightObjectColor;

uniform mat4 fullMatrix;

out vec3 LightObjectColor;

void main()
{
    gl_Position = fullMatrix * vec4(position, 1.0f);
    LightObjectColor = lightObjectColor;
}
