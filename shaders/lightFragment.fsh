#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    float ambientStr = 0.7f;
    vec3 ambient = ambientStr * lightColor;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffusive = diff * lightColor;

    float specularStr = 0.5f;
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
    vec3 specular = specularStr * spec * lightColor;

    vec3 result = (diffusive + ambient + specular) * objectColor;
    FragColor = vec4(result, 1.0f);
}
