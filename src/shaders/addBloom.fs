#version 460 core

layout (location = 0) out vec4 fragment;

in vec3 position;
in vec2 textureCoords;

layout (binding = 0) uniform sampler2D texture_1;
layout (binding = 1) uniform sampler2D texture_2;

void main() {
  vec3 text1 = texture(texture_1, textureCoords).rgb;
  vec3 text2 = texture(texture_2, textureCoords).rgb;

  fragment = vec4(text1 + text2, 1.0);
}