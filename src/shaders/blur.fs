#version 460 core

layout (location = 0) out vec4 fragment;

in vec4 color;
in vec3 normal;
in vec3 position;
in vec2 textureCoords;

uniform sampler2D texture_1;
uniform int horizontal;
uniform float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
  vec2 texelSize = 1.0 / vec2(textureSize(texture_1, 0));
  vec3 result = texture(texture_1, textureCoords).rgb * weight[0];
  if(horizontal == 1) {
    for(int i = 1; i < 5; i++) {
      result += texture(texture_1, textureCoords + vec2(texelSize.x * i, 0.0)).rgb * weight[i];
      result += texture(texture_1, textureCoords - vec2(texelSize.x * i, 0.0)).rgb * weight[i];
    }
  } 
  else {
    for(int i = 1; i < 5; i++) {
      result += texture(texture_1, textureCoords + vec2(0.0, texelSize.y * i)).rgb * weight[i];
      result += texture(texture_1, textureCoords - vec2(0.0, texelSize.y * i)).rgb * weight[i];
    }
  }
  fragment = vec4(result, 1.0);
}