#version 460 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec2 layoutTexCoords;
layout (location = 2) in vec3 layoutNormal;

out vec3 position;
out vec3 normal;
out vec2 texCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
  texCoords = layoutTexCoords;
  normal = mat3(transpose(inverse(modelMatrix))) * layoutNormal;
  position = (modelMatrix * vec4(layoutPosition, 1.0)).rgb;
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(layoutPosition.xyz, 1.0);
}