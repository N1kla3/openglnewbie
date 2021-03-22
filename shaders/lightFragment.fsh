#version 330 core
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

void main()
{
    float ambientStr = 0.7f;
    vec3 ambient = ambientStr * lightColor;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffusive = diff * lightColor;

    vec3 result = (diffusive + ambient) * objectColor;
    FragColor = vec4(result, 1.0f);
}
