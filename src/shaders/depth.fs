#version 460 core

struct LightData {
  vec4 position;
  vec4 color;
  float intensity;
  float attenuation;
  float radius;
};

struct Material {
  float ambientFactor;
  float diffuseFactor;
  float specularFactor;
  float shininessFactor;
};

layout (std430, binding = 1) readonly buffer LightsData {
	LightData lights[];
};

layout (location = 0) out vec4 fragment;
layout (location = 1) out int fragmentId;

in vec3 normal;
in vec3 position;
in vec2 texCoords;

uniform Material material;
uniform vec3 ambientLightColor;
uniform float ambientLightIntensity;
uniform vec3 eye;
uniform int id;

void main() {
  gl_FragDepth = gl_FragCoord.z;
}
