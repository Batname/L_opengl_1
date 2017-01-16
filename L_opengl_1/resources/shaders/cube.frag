#version 330 core
in vec2 TexCoord;

out vec4 color;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Texture samplers
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

/* --- light --- */
uniform vec3        lightColor;
uniform float       ambientStrength;
uniform vec3        lightPos;
uniform vec3        viewPos;
uniform Material    material;


void main()
{
    // color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
    
    /* --- ambient --- */
    vec3 ambient = lightColor * material.ambient;
    
    /* --- diffuse --- */
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    /* --- specular --- */
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);
    
    /* --- calculate result --- */
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
