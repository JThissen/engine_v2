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
uniform float cascadePlaneDistances[4];
uniform int cascadeCount;
uniform mat4 viewMatrix;
uniform vec3 lightDir;
uniform sampler2DArray shadowMap;

layout (std140, binding = 0) uniform LightSpaceMatrices {
  mat4 lightSpaceMatrices[16];
};

float linearize_depth(float d,float zNear,float zFar) {
    float z_n = 2.0 * d - 1.0;
    return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

// float shadow(vec4 positionLightSpace) {
//   vec3 ndc = positionLightSpace.xyz / positionLightSpace.w; //-1, 1
//   ndc = ndc * 0.5 + 0.5; //0, 1
//   float depth = ndc.z;
//   float shadow = 0.0;
//   float bias = 0.005;
//   vec2 texelSize = 1.0 / textureSize(depthTexture, 0);
//   for(int i = -2; i <= 2; i++) {
//     for(int j = -2; j <= 2; j++) {
//         float texelDepth = texture(depthTexture, ndc.xy + vec2(i, j) * texelSize).r; 
//         shadow += (depth - bias) > texelDepth ? 1.0 : 0.0;        
//     }    
//   }
//   shadow /= 25.0;
//   if(ndc.z > 1.0) {
//     shadow = 0.0;
//   }
//   return shadow;
// }

vec3 cascadedShadowMaps() {
  // 1) select the correct shadow map based on distance to view origin
  vec4 fragPosViewSpace = viewMatrix * vec4(position, 1.0);
  float depthValue = abs(fragPosViewSpace.z);
  int layer = -1;
  for (int i = 0; i < cascadeCount; ++i) {
      if (depthValue < cascadePlaneDistances[i]) {
          layer = i;
          break;
      }
  }
  if (layer == -1) {
      layer = cascadeCount;
  }

  // 2) get depth
  vec4 fragPosLightSpace = lightSpaceMatrices[layer] * vec4(position, 1.0);
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // perspective divide
  projCoords = projCoords * 0.5 + 0.5; // [0, 1]
  float depth = projCoords.z;
  if (depth  > 1.0) {
    return vec3(0.0);
  }

  // 3) calculate bias to prevent z-fighting(based on depth map resolution and slope)
  vec3 n = normalize(normal);
  float bias = max(0.05 * (1.0 - dot(n, lightDir)), 0.005);
  if (layer == cascadeCount) {
    bias *= 1 / (farPlane * 0.5);
  } else {
    bias *= 1 / (cascadePlaneDistances[layer] * 0.5);
  }

  // 4) percentage-closer filtering -- sample and average 3 x 3 matrix
  vec3 shadow = vec3(0.0);
  vec2 texelSize = 1.0 / vec2(textureSize(shadowMap, 0));
  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      float pcfDepth = texture(shadowMap, vec3(projCoords.xy + vec2(i, j) * texelSize, layer)).r; 
      shadow += (depth - bias) > pcfDepth ? 1.0 : 0.0;
    }    
  }
  shadow /= 9.0;
  
  // 5) shadow 0.0 outside of far plane frustum
  if(projCoords.z > 1.0) {
      shadow = vec3(0.0);
  }

  // DEBUG
  // float modifier = 1.0;
  // if(layer == 0) {
  //   shadow.x += modifier;
  // } else if(layer == 1) {
  //   shadow.y += modifier;
  // } else if(layer == 2) {
  //   shadow.z += modifier;
  // } else if(layer == 3) {
  //   shadow.xy += modifier;
  // }
      
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
    vec3 phong = ambient +  (1.0 - cascadedShadowMaps()) * (diffuse + specular);
    fragment.rgb += phong * distanceIntensity;
  }
  fragmentId = id;
  depth = vec4(vec3(linearize_depth(gl_FragCoord.z, nearPlane, farPlane) / farPlane), 1.0);
}
