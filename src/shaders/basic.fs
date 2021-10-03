#version 460 core

in vec3 position;
in vec2 textureCoords;

layout (location = 0) out vec4 fragment;
layout (location = 1) out int fragmentId;
layout (location = 2) out vec4 brightness;

uniform int hasTexture;
uniform vec4 color;
uniform sampler2D quadTexture;
uniform float nearPlane;
uniform float farPlane;
uniform int id;

float linearize_depth(float d,float zNear,float zFar) {
    float z_n = 2.0 * d - 1.0;
    return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

void main() {
  if(hasTexture == 1) {
    vec4 tex = texture(quadTexture, textureCoords).rgba;
    fragment = tex;
  } else {
    fragment = color;
  }
  fragmentId = id;
  brightness = color;
}