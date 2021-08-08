#version 460 core

in vec3 position;
in vec2 textureCoords;

out vec4 color;

uniform float time;
uniform vec4 col;

void main() {
  color = vec4(textureCoords.xy, 0.0, 1.0);
}