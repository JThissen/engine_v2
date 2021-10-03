#version 460 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec4 layoutColor;
layout (location = 2) in vec3 layoutNormal;
layout (location = 3) in vec2 layoutTextureCoords;

out vec4 color;
out vec3 normal;
out vec3 position;
out vec2 textureCoords;

uniform mat4 modelMatrix;

void main() {
  color = layoutColor;
  position = (modelMatrix * vec4(layoutPosition, 1.0)).rgb;
  normal = mat3(transpose(inverse(modelMatrix))) * layoutNormal;
  textureCoords = layoutTextureCoords;
  gl_Position = modelMatrix * vec4(layoutPosition, 1.0);
}