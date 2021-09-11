#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "../headers.hpp"
#include "../opengl/openglVertexArray.hpp"
#include "../renderer/shaderBuilder.hpp"
#include "../opengl/openglTexture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine {
  struct FrameBufferData {
    std::unique_ptr<OpenglVertexArray> vertexArray;
    std::unique_ptr<Shader> shader;
  };

  struct QuadData {
    std::unique_ptr<OpenglVertexArray> vertexArray;
    std::unique_ptr<Shader> shader;
  };

  struct AxesData {
    unsigned int vaoId;
    unsigned int bufferIds[2];
    std::unique_ptr<Shader> shader;
  };

  struct GridData {
    unsigned int vaoId;
    unsigned int bufferId;
    std::unique_ptr<Shader> shader;
  };

  struct Light {
    glm::vec4 position;
    glm::vec4 color;
    float intensity;
    float attenuation;
    float radius;
    float padding;
  };

  struct Material {
    float ambientFactor;
    float diffuseFactor;
    float specularFactor;
    float shininessFactor;
  };

  struct LightData {
    unsigned int bufferId;
    std::vector<Light> lights;
    Material material;
  };

  struct TransformData {
    glm::mat4 modelMatrix;
    glm::vec3 rotation;
    glm::vec3 scale;
  };

  struct CubeData {
    int id;
    std::string name;
    std::string internalName;
    unsigned int vaoId;
    unsigned int bufferIds[2];
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unique_ptr<LightData> lightData;
    TransformData transformData;
  };

  class OpenglRenderer {
    public:
    ShaderBuilder shaderBuilder;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    std::unique_ptr<QuadData> quadData;
    std::unique_ptr<FrameBufferData> frameBufferData;
    std::unique_ptr<AxesData> axesData;
    // std::unique_ptr<CubeData> cubeData;
    std::unique_ptr<LightData> lightData;
    std::unique_ptr<GridData> gridData;
    std::unique_ptr<Material> materialData;
    std::vector<std::unique_ptr<CubeData>> cubes;
    std::vector<float> gridGeometry;
    std::array<float, 18> axesGeometry = {
      0.0f,0.0f,0.0f,
      100.0f,0.0f,0.0f,
      0.0f,0.0f,0.0f,
      0.0f,100.0f,0.0f,
      0.0f,0.0f,0.0f,
      0.0f,0.0f,100.0f
    };

    std::array<unsigned char, 24> axesColor = {
      138u,65u,75u,255u,
      138u,65u,75u,255u,
      62u,96u,138u,255u,
      62u,96u,138u,255u,
      94u,124u,51u,255u,
      94u,124u,51u,255u
    };

    std::array<float, 216> cubeGeometry = {
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
    1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
    1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
    1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,

    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
    -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
    -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,

    1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
    1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
    1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
    1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
    1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
    1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
    1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
    1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,

    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f
  };

  std::array<unsigned char, 144> cubeColor = {
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
    200u,200u,200u,255u,
};

    OpenglRenderer();
    void setViewport(int x, int y, int width, int height);
    void setClearColor(const glm::vec4& rgba);
    void clear();
    void draw(
      std::shared_ptr<Shader> shader,
      const glm::mat4& modelMatrix,
      const glm::mat4& viewMatrix,
      const glm::mat4& projectionMatrix,
      std::shared_ptr<OpenglVertexArray> vertexArray
    );

    void drawFrameBufferToViewport();
    void drawQuad(const glm::mat4& modelMatrix, const glm::vec4& color);
    void drawQuad(const glm::mat4& modelMatrix, std::shared_ptr<OpenglTexture> texture);
    std::size_t addLights(std::unique_ptr<CubeData>& object);
    void setAxesData();
    void setGridData(float x = 10.0f, float z = 10.0f);
    void drawAxes(const glm::mat4& modelMatrix);
    void drawCubes(const glm::vec3& eyePosition, int objectSelectedId);
    void drawGrid(const glm::mat4& modelMatrix);
    void createCube(const std::string& internalName, const glm::mat4& modelMatrix = glm::mat4(1.0f));
    std::unique_ptr<Shader> setShader(const std::string& shaderName);
    void objectsUpdateLights();

    private:
    void setFrameBufferData();
    void setQuadData();
  };
}

#endif