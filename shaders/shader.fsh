#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 outTex;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float vis;

void main()
{
    FragColor = mix(texture(texture1, outTex), texture(texture2, -outTex), vis);
}