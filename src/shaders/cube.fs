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

in vec4 color;
in vec3 normal;
in vec3 position;

uniform Material material;
uniform vec3 ambientLightColor;
uniform float ambientLightIntensity;
uniform vec3 eye;
uniform int id;

void main() {
  //https://en.wikipedia.org/wiki/Phong_reflection_model
  fragment = vec4(0.0, 0.0, 0.0, 1.0);

  for(int i = 0; i < lights.length(); i++) {
    LightData light = lights[i];
    vec3 ambient = ambientLightColor * ambientLightIntensity * material.ambientFactor;
    float dist = distance(light.position, vec4(position,1.0));
    if (light.radius < dist) continue;
		float distanceIntensity = 1 - dist / light.radius;
    vec3 lightColorIntensity = light.color.rgb * light.intensity; 
    vec3 l = normalize(light.position.xyz - position);
    vec3 n = normalize(normal);
    vec3 diffuse = material.diffuseFactor * max(dot(n, l), 0.0) * lightColorIntensity;
    vec3 v = normalize(eye - position);
    vec3 specular = material.specularFactor * pow(max(dot(reflect(-l, n), v), 0.0), material.shininessFactor) * lightColorIntensity;
    vec3 phong = ambient + diffuse + specular;
    fragment.rgb += phong * distanceIntensity;
  }
  fragmentId = id;
}
