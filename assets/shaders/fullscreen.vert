#version 460 core

out vec2 uv;

vec2 vertices[3] = vec2[](
    vec2(-1, -1),
    vec2(3, -1),
    vec2(-1, 3)
);

void main() {
    vec2 pos = vertices[gl_VertexID];

    uv = pos * .5 + .5;

    gl_Position = vec4(pos, 0., 1.);
}