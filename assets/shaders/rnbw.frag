#version 460 core

in vec2 uv;

out vec4 FragColor;

uniform float time;

void main() {
    vec3 color = vec3(
        0.5 + 0.5 * sin(time + uv.x * 5.0),
        0.5 + 0.5 * sin(time + uv.y * 5.0),
        0.5 + 0.5 * sin(time)
    );

    FragColor = vec4(color, 1.0);
}