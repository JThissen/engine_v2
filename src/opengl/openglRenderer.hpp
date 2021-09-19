#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "../headers.hpp"
#include "../opengl/openglVertexArray.hpp"
#include "../renderer/shaderBuilder.hpp"
#include "../opengl/openglTexture.hpp"
#include "../renderer/geometry.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine {
  enum class ObjectType { CUBE, PLANE, LIGHT };
  struct MeshData {
    unsigned int vaoId;
    std::vector<unsigned int> bufferIds;
  };
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

  struct TransformData {
    glm::mat4 modelMatrix;
    glm::vec3 rotation;
    glm::vec3 scale;
  };

  class Object {
    public:
    int id;
    std::string name;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    TransformData transformData;
    MeshData meshData;
    virtual ObjectType getObjectType() = 0;
    virtual ~Object() = default;
  };

  struct LightData {
    glm::vec4 position;
    glm::vec4 color;
    float intensity;
    float attenuation;
    float radius;
    float padding;
  };

  class Light : public Object {
    public:
    int lightDataContainerIndex;
    unsigned int SSBOBufferId;
    unsigned int bindingIndex;
    virtual ObjectType getObjectType() {
      return ObjectType::LIGHT;
    }
  };

  struct Material {
    float ambientFactor;
    float diffuseFactor;
    float specularFactor;
    float shininessFactor;
  };

  class Cube : public Object {
    public:
    virtual ObjectType getObjectType() {
      return ObjectType::CUBE;
    }
    Material material; //replace by lightMaterial
  };

  class Plane : public Object {
    public:
    virtual ObjectType getObjectType() {
      return ObjectType::PLANE;
    }
    Material material; //replace by lightMaterial
  };

  class OpenglRenderer {
    public:
    enum class MeshType { CUBE, PLANE };
    ShaderBuilder shaderBuilder;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    glm::mat4 lightViewProjection = glm::mat4(1.0f);
    std::unique_ptr<QuadData> quadData;
    std::unique_ptr<FrameBufferData> frameBufferData;
    std::unique_ptr<AxesData> axesData;
    std::vector<LightData> lightDataContainer;
    std::unique_ptr<GridData> gridData;
    std::unique_ptr<Material> materialData;
    std::vector<std::unique_ptr<Object>> objects;
    unsigned int SSBOBufferId;
    std::vector<float> gridGeometry;
    bool depthPass = false;
    unsigned int depthAttachmentId;

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
    void drawQuad(const glm::mat4& modelMatrix, unsigned int& textureId);
    void setAxesData();
    void setGridData(float x = 10.0f, float z = 10.0f);
    void drawAxes(const glm::mat4& modelMatrix);
    void drawObjects(const glm::vec3& eyePosition, int objectSelectedId, float nearPlane, float farPlane);
    void drawGrid(const glm::mat4& modelMatrix);
    void createCube(const glm::mat4& modelMatrix = glm::mat4(1.0f));
    void createPlane(const glm::mat4& modelMatrix = glm::mat4(1.0f));
    void createLight(LightData lightData, const glm::mat4& modelMatrix = glm::mat4(1.0f));
    MeshData createMesh(MeshType meshType);
    std::unique_ptr<Shader> setShader(const std::string& shaderName);

    private:
    void setFrameBufferData();
    void setQuadData();
  };
}

#endif