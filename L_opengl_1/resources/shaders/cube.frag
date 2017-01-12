#version 330 core
in vec2 TexCoord;

out vec4 color;

// Texture samplers
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

// light
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
//    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
    
    color = vec4(objectColor * lightColor, 1.0f);
}
