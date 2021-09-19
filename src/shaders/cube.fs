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
layout (location = 2) out vec4 depth;

in vec4 color;
in vec3 normal;
in vec3 position;
in vec4 positionLightSpace;

uniform Material material;
uniform vec3 ambientLightColor;
uniform float ambientLightIntensity;
uniform vec3 eye;
uniform float nearPlane;
uniform float farPlane;
uniform int id;
uniform sampler2D depthTexture;

float linearize_depth(float d,float zNear,float zFar) {
    float z_n = 2.0 * d - 1.0;
    return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

float shadow(vec4 positionLightSpace) {
  vec3 ndc = positionLightSpace.xyz / positionLightSpace.w; //-1, 1
  ndc = ndc * 0.5 + 0.5; //0, 1
  float depth = ndc.z;
  float shadow = 0.0;
  float bias = 0.005;
  vec2 texelSize = 1.0 / textureSize(depthTexture, 0);
  for(int i = -2; i <= 2; i++) {
    for(int j = -2; j <= 2; j++) {
        float texelDepth = texture(depthTexture, ndc.xy + vec2(i, j) * texelSize).r; 
        shadow += (depth - bias) > texelDepth ? 1.0 : 0.0;        
    }    
  }
  shadow /= 25.0;
  if(ndc.z > 1.0) {
    shadow = 0.0;
  }
  return shadow;
}

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
    float sh = shadow(positionLightSpace);
    vec3 phong = ambient + ((diffuse + specular) * (1.0 - sh));
    fragment.rgb += phong * distanceIntensity;
  }
  fragmentId = id;
  depth = vec4(vec3(linearize_depth(gl_FragCoord.z, nearPlane, farPlane) / farPlane), 1.0);
}
