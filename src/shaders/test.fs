#version 460 core

out vec4 color;
in vec3 out_position;
uniform float time;

void main() {
  color = vec4(sin(out_position + time) * 0.5 + 0.5, 1.0);
}
