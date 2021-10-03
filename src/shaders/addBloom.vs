#version 460 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec2 layoutTextureCoords;

out vec3 position;
out vec2 textureCoords;

uniform mat4 modelMatrix;

void main() {
  position = (modelMatrix * vec4(layoutPosition, 1.0)).rgb;
  textureCoords = layoutTextureCoords;
  gl_Position = modelMatrix * vec4(layoutPosition, 1.0);
}