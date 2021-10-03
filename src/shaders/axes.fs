#version 460 core

in vec4 color;
layout(location = 0) out vec4 fragment;
layout(location = 2) out vec4 brightness;

void main() {
  fragment = color;
  brightness = vec4(0.0, 0.0, 0.0, 0.0);
}