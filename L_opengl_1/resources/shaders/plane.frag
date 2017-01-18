#version 330 core
#define NR_POINT_LIGHTS 4

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

struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};


uniform vec3        viewPos;
uniform Material    material;
uniform DirLight    dirLight;
uniform PointLight  pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffColor, vec3 ambColor);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffColor, vec3 ambColor);

void main()
{
    /* --- shared vars --- */
    vec3 diffuseColor = Color  * material.diffuseStr;
    vec3 ambientColor = diffuseColor * material.ambientStr;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    /* --- define output value --- */
    vec3 result;
    
    /* --- light direction --- */
    result = CalcDirLight(dirLight, norm, viewDir, diffuseColor, ambientColor);
    
    /* --- calculate light points --- */
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, diffuseColor, ambientColor);
    }
    
    color = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffColor, vec3 ambColor)
{
    vec3 lightDir = normalize(-light.direction);
    
    /* --- diffuse shading --- */
    float diff = max(dot(normal, lightDir), 0.0f);
    
    /* --- specular shading --- */
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    
    /* --- combine results --- */
    vec3 ambient = light.ambient * ambColor;
    vec3 diffuse = light.diffuse * (diff * diffColor);
    vec3 specular = light.specular * (spec * material.specular);
    
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffColor, vec3 ambColor)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    /* --- diffuse --- */
    float diff = max(dot(normal, lightDir), 0.0f);
    
    /* --- specular --- */
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    
    /* --- attenuation --- */
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    /* --- combine results --- */
    vec3 ambient = light.ambient * ambColor;
    vec3 diffuse = light.diffuse * (diff * diffColor);
    vec3 specular = light.specular * (spec * material.specular);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
