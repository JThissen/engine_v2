#version 460 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec2 layoutTextureCoords;
out vec3 position;
out vec2 textureCoords;

uniform float time;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
  position = layoutPosition;
  textureCoords = layoutTextureCoords;
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(layoutPosition.xyz, 1.0);
}