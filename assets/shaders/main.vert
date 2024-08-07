#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexPos;
layout (location = 3) in ivec2 aLightMapPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float time;
uniform sampler2D lightMap;

out vec4 fragColor;
out vec2 texPos;

void main(void)
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    
    vec4 light = texture(lightMap,
        clamp(aLightMapPos / 256.0,
            vec2(0.5 / 16.0),
            vec2(15.5 / 16.0)));
    fragColor = aColor * light;
    texPos = aTexPos;
}
