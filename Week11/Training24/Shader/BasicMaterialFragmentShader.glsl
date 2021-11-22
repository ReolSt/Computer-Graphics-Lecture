#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   vec3 position;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec3 fragPosition;
in vec3 normal;
in vec3 viewPosition;

uniform Material material;

#define MaxDirectionalLightCount 16
#define MaxPointLightCount 16
#define MaxSpotLightCount 16

uniform DirectionalLight directionalLights[MaxDirectionalLightCount];
uniform PointLight pointLights[MaxPointLightCount];
uniform SpotLight spotLights[MaxSpotLightCount];

uniform int directionalLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

out vec4 fragColor;

varying mat4 viewMatrix;
varying mat4 projectionMatrix;

vec3 ApplyDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);

    float normalDotLightDir = dot(normal, lightDir);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = vec3(0.0);
    if(normalDotLightDir > 0.0)
    {
        specular = light.specular * spec * material.specular;
    }

    return (ambient + diffuse + specular);
}

vec3 ApplyPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 halfWayDir = normalize(lightDir + viewDir);

    float normalDotLightDir = dot(normal, lightDir);

    float distance = length(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(clamp(dot(normal, halfWayDir), 0.0, 1.0), material.shininess);

    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    if(normalDotLightDir > 0.0)
    {
        diffuse = light.diffuse * diff * material.diffuse;
        specular = light.specular * spec * material.specular;
    }

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 ApplySpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 halfWayDir = normalize(lightDir + viewDir);

    float normalDotLightDir = dot(normal, lightDir);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(normal, halfWayDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = vec3(0.0);
    if(normalDotLightDir > 0.0)
    {
        specular = light.specular * spec * material.specular;
    }

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(normal);
    vec3 fragPos = vec3(fragPosition);
    vec3 viewDir = vec3(viewMatrix * vec4(normalize(viewPosition - fragPos), 1.0));

    vec3 result = vec3(0.0);

    for(int i = 0; i < directionalLightCount; ++i)
    {
        result += ApplyDirectionalLight(directionalLights[i], norm, viewDir);
    }

    for(int i = 0; i < pointLightCount; ++i)
    {
        result += ApplyPointLight(pointLights[i], norm, fragPos, viewDir);
    }

    for(int i = 0; i < spotLightCount; ++i)
    {
        result += ApplySpotLight(spotLights[i], norm, fragPos, viewDir);
    }

    fragColor = vec4(result, 1.0);
}