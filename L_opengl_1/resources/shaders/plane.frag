#version 330 core
in vec2 TexCoord;

out vec4 color;
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

struct Material
{
    vec3 ambientStr;
    vec3 diffuseStr;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};


/* --- light --- */
uniform float       ambientStrength;
uniform vec3        viewPos;
uniform Material    material;
uniform Light       light;


void main()
{
    vec3 diffuseColor = Color  * material.diffuseStr;
    vec3 ambientColor = diffuseColor * material.ambientStr;
    
    /* --- ambient --- */
    vec3 ambient = light.ambient * ambientColor;
    
    /* --- diffuse --- */
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * (diff * diffuseColor);
    
    /* --- specular --- */
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    /* --- attenuation --- */
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    /* --- calculate result --- */
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
