#version 460 core

in vec3 position;
in vec2 textureCoords;

layout (location = 0) out vec4 fragment;
layout (location = 1) out int fragmentId;

uniform int hasTexture;
uniform vec4 color;
uniform sampler2D quadTexture;
uniform int id;

void main() {
  if(hasTexture == 1) {
    vec4 tex = texture(quadTexture, textureCoords).rgba;
    fragment = tex;
  } else {
    fragment = color;
  }
  fragmentId = id;
}