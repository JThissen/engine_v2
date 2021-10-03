#version 460 core

layout (location = 0) out vec4 fragment;
layout (location = 2) out vec4 brightness;

void main() {
  fragment = vec4(0.31, 0.31, 0.31, 1.0);
  brightness = vec4(0.0, 0.0, 0.0, 0.0);
}