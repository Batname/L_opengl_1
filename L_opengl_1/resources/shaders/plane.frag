#version 330 core
in vec2 TexCoord;

out vec4 color;
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

/* --- light --- */
uniform vec3    lightColor;
uniform float   ambientStrength;
uniform vec3    lightPos;
uniform vec3    viewPos;


void main()
{
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
    vec3 result = (ambient + diffuse + specular) * Color;
    color = vec4(result, 1.0f);
}
