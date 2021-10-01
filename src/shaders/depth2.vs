#version 460 core

layout (location = 0) in vec3 layoutPosition;

uniform mat4 modelMatrix;

void main() {
  gl_Position = modelMatrix * vec4(layoutPosition.xyz, 1.0);
}