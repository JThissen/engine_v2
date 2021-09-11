#version 460 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec4 layoutColor;

out vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
  color = layoutColor;
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(layoutPosition.xyz, 1.0);
}