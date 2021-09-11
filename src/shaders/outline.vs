#version 460 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec4 layoutColor;
layout (location = 2) in vec3 layoutNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 eye;

void main() {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(layoutPosition, 1.0);
}