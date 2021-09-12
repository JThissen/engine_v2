#include "openglRenderer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../utils.hpp"
#include "../uuid.hpp"

namespace engine {
    OpenglRenderer::OpenglRenderer() {
      glEnable(GL_BLEND);
	  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //(src, dest)
	  	glEnable(GL_DEPTH_TEST);
      glEnable(GL_CULL_FACE);
      setFrameBufferData();
      setAxesData();
      setGridData(100.0f, 100.0f);
      setQuadData();

      LightData lightData;
      lightData.position = { 0.0f, 0.0f, 7.0f, 0.0f };
      lightData.color = { 13.0f/255.0f, 1.0f, 247.0f/255.0f, 1.0f };
      lightData.intensity = 2.0f;
      lightData.attenuation = 0.0f;
      lightData.radius = 20.0f;

      LightData lightData2;
      lightData2.position = { 4.0f, 0.0f, 0.0f, 0.0f };
      lightData2.color = { 1.0f, 134.0f/255.0f, 13.0f/255.0f, 1.0f };
      lightData2.intensity = 2.0f;
      lightData2.attenuation = 0.0f;
      lightData2.radius = 20.0f;

      createLight(lightData, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 7.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f)));
      createLight(lightData2, glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f)));

      cubes = std::vector<std::unique_ptr<Cube>>();
    }

    void OpenglRenderer::setViewport(int x, int y, int width, int height) {
			glViewport(x, y, width, height);
		}

    void OpenglRenderer::setClearColor(const glm::vec4& rgba) {
			glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
		}

    void OpenglRenderer::clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

    void OpenglRenderer::draw(
			std::shared_ptr<Shader> shader, 
			const glm::mat4& modelMatrix,
			const glm::mat4& viewMatrix,
			const glm::mat4& projectionMatrix,
			std::shared_ptr<OpenglVertexArray> vertexArray
		) {
			shader->useProgram();
			glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(shader->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(shader->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

			vertexArray->bind();
			glDrawElements(GL_TRIANGLES, vertexArray->indexBuffer->size, GL_UNSIGNED_INT, nullptr);
		}

    void OpenglRenderer::setFrameBufferData() {
      std::array<float, 20> quad = {
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f
      };
      std::array<int, 6> indices = { 0, 1, 2, 0, 2, 3 };
      frameBufferData = std::make_unique<FrameBufferData>();
      frameBufferData->vertexArray = std::make_unique<OpenglVertexArray>();
      auto vertexBuffer = std::make_shared<OpenglVertexBuffer>(quad.data(), quad.size(), LayoutBuffer({
        { engine::GLSLType::VEC3, "layoutPosition" },
        { engine::GLSLType::VEC2, "layoutTextureCoords" }
      }));
      auto indexBuffer = std::make_shared<OpenglIndexBuffer>(indices.data(), indices.size());
      frameBufferData->vertexArray->pushVertexBuffer(vertexBuffer);
      frameBufferData->vertexArray->setIndexBuffer(indexBuffer);
      frameBufferData->shader = setShader("basic");
    }

    void OpenglRenderer::drawFrameBufferToViewport() {
      frameBufferData->shader->useProgram();
      frameBufferData->vertexArray->bind();
			glDrawElements(GL_TRIANGLES, frameBufferData->vertexArray->indexBuffer->size, GL_UNSIGNED_INT, nullptr);
    }

    void OpenglRenderer::setQuadData() {
      std::array<float, 20> quad = {
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f
      };
      std::array<int, 6> indices = { 0, 1, 2, 0, 2, 3 };
      quadData = std::make_unique<QuadData>();
      quadData->vertexArray = std::make_unique<OpenglVertexArray>();
      auto vertexBuffer = std::make_shared<OpenglVertexBuffer>(quad.data(), quad.size(), LayoutBuffer({
        { engine::GLSLType::VEC3, "layoutPosition" },
        { engine::GLSLType::VEC2, "layoutTextureCoords" }
      }));
      auto indexBuffer = std::make_shared<OpenglIndexBuffer>(indices.data(), indices.size());
      quadData->vertexArray->pushVertexBuffer(vertexBuffer);
      quadData->vertexArray->setIndexBuffer(indexBuffer);
      quadData->shader = setShader("basic");
    }

    void OpenglRenderer::drawQuad(const glm::mat4& modelMatrix, const glm::vec4& color) {
      quadData->shader->useProgram();
      quadData->shader->setUniform1i(0, "hasTexture");
      quadData->shader->setUniform4fv(color, "color");
			glUniformMatrix4fv(glGetUniformLocation(quadData->shader->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(quadData->shader->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(quadData->shader->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
      quadData->vertexArray->bind();
			glDrawElements(GL_TRIANGLES, quadData->vertexArray->indexBuffer->size, GL_UNSIGNED_INT, nullptr);
      quadData->shader->disuseProgram();
    }

    void OpenglRenderer::drawQuad(const glm::mat4& modelMatrix, std::shared_ptr<OpenglTexture> texture) {
      texture->bind(0);
      quadData->shader->useProgram();
      quadData->shader->setUniform1i(1, "hasTexture");
			glUniformMatrix4fv(glGetUniformLocation(quadData->shader->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(quadData->shader->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(quadData->shader->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
      quadData->vertexArray->bind();
			glDrawElements(GL_TRIANGLES, quadData->vertexArray->indexBuffer->size, GL_UNSIGNED_INT, nullptr);
      quadData->shader->disuseProgram();
    }

    void OpenglRenderer::setGridData(float x, float z) {
      gridData = std::make_unique<GridData>();
      glGenBuffers(1, &gridData->bufferId);
      glBindBuffer(GL_ARRAY_BUFFER, gridData->bufferId);

      for(int i = 0; i <= x; i++) {
        std::vector<float> line = {
          static_cast<float>(i), 0.0f, 0.0f,
          static_cast<float>(i), 0.0f, z
        };
        gridGeometry.insert(gridGeometry.end(), line.begin(), line.end());
      }

      for(int i = 0; i <= z; i++) {
        std::vector<float> line = {
          0.0f, 0.0f, static_cast<float>(i),
          x, 0.0f, static_cast<float>(i)
        };
        gridGeometry.insert(gridGeometry.end(), line.begin(), line.end());
      }
      
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * gridGeometry.size(), static_cast<void*>(gridGeometry.data()), GL_STATIC_DRAW);
      glGenVertexArrays(1, &gridData->vaoId);
      glBindVertexArray(gridData->vaoId);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
      gridData->shader = std::move(shaderBuilder.shader);
      gridData->shader = setShader("grid");
      gridData->shader->setUniform3fv({ 1.0f, 1.0f, 1.0f }, "ambientLightColor");
      gridData->shader->setUniform1f(0.5f, "ambientLightIntensity");
    }

    void OpenglRenderer::drawGrid(const glm::mat4& modelMatrix) {
      gridData->shader->useProgram();
      glUniformMatrix4fv(glGetUniformLocation(axesData->shader->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(axesData->shader->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(axesData->shader->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
      glBindVertexArray(gridData->vaoId);
      glDrawArrays(GL_LINES, 0, gridGeometry.size() / 3);
      glBindVertexArray(0);
      gridData->shader->disuseProgram();
    }

    std::unique_ptr<Shader> OpenglRenderer::setShader(const std::string& shaderName) {
      std::stringstream ss;
      ss << "./../src/shaders/" << shaderName << ".vs";
      std::string vsPath = ss.str();
      ss.str("");
      ss << "./../src/shaders/" << shaderName << ".fs";
      std::string fsPath = ss.str();
      shaderBuilder.createProgram()
        .attachVertexShader(vsPath)
        .attachFragmentShader(fsPath)
        .linkProgram();
      return std::move(shaderBuilder.shader);
    }

    void OpenglRenderer::createLight(LightData lightData, const glm::mat4& modelMatrix) {
      std::unique_ptr<Light> light = std::make_unique<Light>();
      light->id = UUID::createInt();
      light->bindingIndex = 1u;
      light->lightDataContainerIndex = lightDataContainer.size();
      light->name = "Light-" + std::to_string(light->id);
      light->meshData = createMesh(MeshType::CUBE);
      light->shaders.insert({"outline", setShader("outline")});
      light->shaders.insert({"basic", setShader("basic")});
      light->shaders["basic"]->useProgram();
      light->shaders["basic"]->setUniform1i(light->id, "id");
      light->shaders["basic"]->disuseProgram();
      light->transformData.modelMatrix = modelMatrix;
      light->transformData.rotation = { 0.0f, 0.0f, 0.0f };
      light->transformData.scale = glm::vec3(0.25f);

      auto hasLight = std::find_if(objects.begin(), objects.end(), [](std::unique_ptr<Object>& object) {
        return object->getObjectType() == ObjectType::LIGHT;
      });

      if(hasLight == objects.end()) {
        Shader::createSSBOBlock(
          SSBOBufferId, 
          light->bindingIndex, 
          lightDataContainer.size() * sizeof(LightData), 
          static_cast<void*>(lightDataContainer.data())
        );
      }

      lightDataContainer.push_back(lightData);
      Shader::updateSSBOBlock(
        SSBOBufferId,
        lightDataContainer.size() * sizeof(LightData), 
        static_cast<void*>(lightDataContainer.data())
      );
      objects.push_back(std::move(light));
    }

    MeshData OpenglRenderer::createMesh(MeshType meshType) {
      MeshData meshData;
      if(meshType == MeshType::CUBE) {
        meshData.bufferIds = std::vector<unsigned int>(2, 0);
        glGenBuffers(2, meshData.bufferIds.data());
        glBindBuffer(GL_ARRAY_BUFFER, meshData.bufferIds[0]);
        glBufferData(GL_ARRAY_BUFFER, Geometry::cubeGeometry.size() * sizeof(float), static_cast<void*>(Geometry::cubeGeometry.data()), GL_STATIC_DRAW);
        glGenVertexArrays(1, &(meshData.vaoId));
        glBindVertexArray(meshData.vaoId);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
        glBindBuffer(GL_ARRAY_BUFFER, meshData.bufferIds[1]);
        glBufferData(GL_ARRAY_BUFFER, Geometry::cubeColor.size() * sizeof(unsigned char), static_cast<void*>(Geometry::cubeColor.data()), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(unsigned char) * 4, nullptr);
      }
      return meshData;
    }

    void OpenglRenderer::createCube(const glm::mat4& modelMatrix) {
      std::unique_ptr<Cube> cube = std::make_unique<Cube>();
      cube->id = UUID::createInt();
      cube->name = "Cube-" + std::to_string(cube->id);
      cube->meshData = createMesh(MeshType::CUBE);
      cube->shaders.insert({"outline", setShader("outline")});
      cube->shaders.insert({"cube", setShader("cube")});
      cube->shaders.insert({"basic", setShader("basic")});
      cube->material.ambientFactor    = 0.25f;
      cube->material.diffuseFactor    = 0.15f;
      cube->material.specularFactor   = 0.3f;
      cube->material.shininessFactor  = 4.0f;
      cube->shaders["cube"]->useProgram();
      cube->shaders["cube"]->setUniform3fv({ 1.0f, 1.0f, 1.0f }, "ambientLightColor");
      cube->shaders["cube"]->setUniform1f(0.5f, "ambientLightIntensity");
      cube->shaders["cube"]->setUniform1f(cube->material.ambientFactor, "material.ambientFactor");
      cube->shaders["cube"]->setUniform1f(cube->material.diffuseFactor, "material.diffuseFactor");
      cube->shaders["cube"]->setUniform1f(cube->material.specularFactor, "material.specularFactor");
      cube->shaders["cube"]->setUniform1f(cube->material.shininessFactor, "material.shininessFactor");
      cube->shaders["cube"]->setUniform1i(cube->id, "id");
      cube->shaders["cube"]->disuseProgram();
      cube->transformData.modelMatrix = modelMatrix;
      cube->transformData.rotation = { 0.0f, 0.0f, 0.0f };
      cube->transformData.scale = glm::vec3(1.0f);
      objects.push_back(std::move(cube));
    }

    void OpenglRenderer::drawObjects(const glm::vec3& eyePosition, int objectSelectedId) {
      for(int i = 0; i < objects.size(); i++) {
        if(objectSelectedId == objects[i]->id) {
          //outline pass
          glCullFace(GL_FRONT); 
          objects[i]->shaders["outline"]->useProgram();
          glm::mat4 modelMatrixScaled = glm::scale(objects[i]->transformData.modelMatrix, glm::vec3(1.025f, 1.025f, 1.025f));
          glUniformMatrix4fv(glGetUniformLocation(objects[i]->shaders["outline"]->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrixScaled));
    	    glUniformMatrix4fv(glGetUniformLocation(objects[i]->shaders["outline"]->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(objects[i]->shaders["outline"]->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
          objects[i]->shaders["outline"]->setUniform3fv(eyePosition, "eye");
          glBindVertexArray(objects[i]->meshData.vaoId);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          glBindVertexArray(0);
          objects[i]->shaders["outline"]->disuseProgram();
        }
        if(objects[i]->getObjectType() == ObjectType::LIGHT) {
          glCullFace(GL_BACK);
          Light* light = dynamic_cast<Light*>(objects[i].get());
          lightDataContainer[light->lightDataContainerIndex].position = glm::vec4(
            light->transformData.modelMatrix[3][0],
            light->transformData.modelMatrix[3][1],
            light->transformData.modelMatrix[3][2],
            0.0f
          );
          light->shaders["basic"]->useProgram();
          glUniformMatrix4fv(glGetUniformLocation(light->shaders["basic"]->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(light->transformData.modelMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(light->shaders["basic"]->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(light->shaders["basic"]->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
          light->shaders["basic"]->setUniform4fv(lightDataContainer[light->lightDataContainerIndex].color, "color");
          glBindVertexArray(light->meshData.vaoId);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          glBindVertexArray(0);
          light->shaders["basic"]->disuseProgram();

          Shader::setSSBOBlockSubData(
            SSBOBufferId,
            0,
            lightDataContainer.data(),
            lightDataContainer.size() * sizeof(LightData)
          );
        } else if(objects[i]->getObjectType() == ObjectType::CUBE) {
          Cube* cube = dynamic_cast<Cube*>(objects[i].get());
          //normal pass
          glCullFace(GL_BACK);
          cube->shaders["cube"]->useProgram();
          glUniformMatrix4fv(glGetUniformLocation(cube->shaders["cube"]->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cube->transformData.modelMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(cube->shaders["cube"]->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(cube->shaders["cube"]->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
          cube->shaders["cube"]->setUniform1i(cube->id, "id");
          cube->shaders["cube"]->setUniform1f(cube->material.ambientFactor, "material.ambientFactor");
          cube->shaders["cube"]->setUniform1f(cube->material.diffuseFactor, "material.diffuseFactor");
          cube->shaders["cube"]->setUniform1f(cube->material.specularFactor, "material.specularFactor");
          cube->shaders["cube"]->setUniform1f(cube->material.shininessFactor, "material.shininessFactor");
          cube->shaders["cube"]->setUniform3fv(eyePosition, "eye");
          glBindVertexArray(cube->meshData.vaoId);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          glBindVertexArray(0);
          cube->shaders["cube"]->disuseProgram();
        }
      }
    }

    void OpenglRenderer::setAxesData() {
      axesData = std::make_unique<AxesData>();
      glGenBuffers(2, axesData->bufferIds);
      glBindBuffer(GL_ARRAY_BUFFER, axesData->bufferIds[0]);
      glBufferData(GL_ARRAY_BUFFER, Geometry::axesGeometry.size() * sizeof(float), static_cast<void*>(Geometry::axesGeometry.data()), GL_STATIC_DRAW);
      glGenVertexArrays(1, &(axesData->vaoId));
      glBindVertexArray(axesData->vaoId);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
      glBindBuffer(GL_ARRAY_BUFFER, axesData->bufferIds[1]);
      glBufferData(GL_ARRAY_BUFFER, Geometry::axesColor.size() * sizeof(unsigned char), static_cast<void*>(Geometry::axesColor.data()), GL_STATIC_DRAW);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(unsigned char) * 4, nullptr);
      axesData->shader = setShader("axes");
    }

    void OpenglRenderer::drawAxes(const glm::mat4& modelMatrix) {
      axesData->shader->useProgram();
      glUniformMatrix4fv(glGetUniformLocation(axesData->shader->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(axesData->shader->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	glUniformMatrix4fv(glGetUniformLocation(axesData->shader->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
      glBindVertexArray(axesData->vaoId);
      glDrawArrays(GL_LINES, 0, 2);
      glDrawArrays(GL_LINES, 2, 2);
      glDrawArrays(GL_LINES, 4, 2);
      glBindVertexArray(0);
      axesData->shader->disuseProgram();
    }
}
