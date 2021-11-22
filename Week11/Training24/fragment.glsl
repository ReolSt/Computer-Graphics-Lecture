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

in vec4 fragPosition;
in vec3 normal;

uniform Material material;
uniform vec3 viewPosition;

Light light;

out vec4 fragColor;

void main()
{
    light.ambient = vec3(0.2, 0.2, 0.2);
    light.diffuse = vec3(0.5, 0.5, 0.5);
    light.specular = vec3(1.0, 1.0, 1.0);
    light.position = vec3(0.5, 0.5, 0.5);

    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(light.position - vec3(fragPosition));
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 viewDirection = normalize(viewPosition - vec3(fragPosition));
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}