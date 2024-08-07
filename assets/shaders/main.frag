#version 330 core

in vec4 fragColor;
in vec2 texPos;

uniform sampler2D tex;

out vec4 outputColor;

void main()
{
    vec4 color = texture(tex, texPos);
    outputColor = color * fragColor;
}