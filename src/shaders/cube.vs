#version 460 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec4 layoutColor;
layout (location = 2) in vec3 layoutNormal;

out vec4 color;
out vec3 normal;
out vec3 position;
out vec4 positionLightSpace;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightViewProjection;

void main() {
  color = layoutColor;
  normal = mat3(transpose(inverse(modelMatrix))) * layoutNormal;
  position = (modelMatrix * vec4(layoutPosition, 1.0)).rgb;
  positionLightSpace = lightViewProjection * vec4(position.xyz, 1.0);
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(layoutPosition.xyz, 1.0);
}