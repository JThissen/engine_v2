#version 460 core

layout (location = 0) in vec3 layoutPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(layoutPosition.xyz, 1.0);
}