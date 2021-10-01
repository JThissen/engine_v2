#version 460 core

in vec3 position;
in vec2 textureCoords;

layout (location = 0) out vec4 fragment;
layout (location = 1) out vec4 fragment1;
layout (location = 2) out vec4 fragment2;
// layout (location = 1) out int fragmentId;
// layout (location = 2) out vec4 depth;

uniform int hasTexture;
uniform int isDepthTexture;
uniform vec4 color;
uniform sampler2DArray quadTexture;
uniform int layer;
uniform float nearPlane;
uniform float farPlane;
uniform int id;

float linearize_depth(float d,float zNear,float zFar) {
    float z_n = 2.0 * d - 1.0;
    return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

void main() {
  if(hasTexture == 1) {
    // vec4 tex = texture(quadTexture, textureCoords).rgba;
    // fragment = tex;
  } else if(isDepthTexture == 1) {
    fragment = vec4(vec3(texture(quadTexture, vec3(textureCoords, 0)).r), 1.0);
    fragment1 = vec4(vec3(texture(quadTexture, vec3(textureCoords, 1)).r), 1.0);
    fragment2 = vec4(vec3(texture(quadTexture, vec3(textureCoords, 2)).r), 1.0);
  } else {
    fragment = color;
  }
  // fragmentId = id;
  // depth = vec4(vec3(linearize_depth(gl_FragCoord.z, nearPlane, farPlane) / farPlane), 1.0);
}