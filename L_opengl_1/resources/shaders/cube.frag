#version 330 core

out vec4 color;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    sampler2D   diffuse;
    sampler2D   specular;
    float       shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    
    float cutOff;
    float outerCutOff;
    
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
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    
    /* --- spot --- */
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
    diffuse *= intensity;
    specular *= intensity;
    
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
