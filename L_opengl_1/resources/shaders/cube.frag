#version 330 core
in vec2 TexCoord;

out vec4 color;
in vec3 Normal;
in vec3 FragPos;

// Texture samplers
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

/* --- light --- */
uniform vec3    objectColor;
uniform vec3    lightColor;
uniform float   ambientStrength;
uniform vec3    lightPos;
uniform vec3    viewPos;


void main()
{
    // color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
    
    /* --- ambient --- */
    vec3 ambient = ambientStrength * lightColor;
    
    /* --- diffuse --- */
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;
    
    /* --- specular --- */
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    /* --- calculate result --- */
    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f);
}
