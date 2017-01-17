#version 330 core

out vec4 color;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    sampler2D   diffuse;
    vec3        specular;
    float       shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Texture samplers
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

/* --- light --- */
uniform float       ambientStrength;
uniform vec3        viewPos;
uniform Material    material;
uniform Light       light;


void main()
{
    // color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
    
    /* --- ambient --- */
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    
    /* --- diffuse --- */
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    
    /* --- specular --- */
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    /* --- calculate result --- */
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
