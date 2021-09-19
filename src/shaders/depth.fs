#version 460 core

// layout (location = 0) out vec4 fragment;

in vec3 normal;
in vec3 position;
in vec2 texCoords;

void main() {
  gl_FragDepth = gl_FragCoord.z;
}
