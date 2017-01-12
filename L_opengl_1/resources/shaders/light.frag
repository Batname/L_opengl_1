#version 330 core
in vec3 LightObjectColor;

out vec4 color;

void main()
{
    color = vec4(LightObjectColor, 1.0f);
}
