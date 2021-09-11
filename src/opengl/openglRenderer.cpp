#include "openglRenderer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../utils.hpp"

namespace engine {
    OpenglRenderer::OpenglRenderer() {
      // glEnable(GL_CULL_FACE);
      glEnable(GL_BLEND);
	  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //(src, dest)
	  	glEnable(GL_DEPTH_TEST);
      glEnable(GL_CULL_FACE);
      setFrameBufferData();
      setAxesData();
      setGridData(100.0f, 100.0f);
      setQuadData();

      cubes = std::vector<std::unique_ptr<CubeData>>();
      createCube("CubeLight", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f)));
      createCube("CubeLight", glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.25f)));
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

    std::size_t OpenglRenderer::addLights(std::unique_ptr<CubeData>& object) {
      std::size_t index = object->lightData->lights.size();
      object->shaders["cube"]->updateSSBOBlock(
        object->lightData->lightKey, 
        object->lightData->lights.size() * sizeof(Light), 
        static_cast<void*>(object->lightData->lights.data())
      );
      return index;
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

    void OpenglRenderer::createCube(const std::string& internalName, const glm::mat4& modelMatrix) {
      std::unique_ptr<CubeData> cubeData = std::make_unique<CubeData>();
      cubeData->id = cubes.empty() ? 0 : cubes.size();
      cubeData->name = "Cube" + std::to_string(cubeData->id);
      cubeData->internalName = internalName;
      glGenBuffers(2, cubeData->bufferIds);
      glBindBuffer(GL_ARRAY_BUFFER, cubeData->bufferIds[0]);
      glBufferData(GL_ARRAY_BUFFER, cubeGeometry.size() * sizeof(float), static_cast<void*>(cubeGeometry.data()), GL_STATIC_DRAW);
      glGenVertexArrays(1, &(cubeData->vaoId));
      glBindVertexArray(cubeData->vaoId);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
      glBindBuffer(GL_ARRAY_BUFFER, cubeData->bufferIds[1]);
      glBufferData(GL_ARRAY_BUFFER, cubeColor.size() * sizeof(unsigned char), static_cast<void*>(cubeColor.data()), GL_STATIC_DRAW);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(unsigned char) * 4, nullptr);

      cubeData->shaders.insert({"outline", setShader("outline")});
      cubeData->shaders.insert({"cube", setShader("cube")});
      cubeData->shaders.insert({"basic", setShader("basic")});
      cubeData->lightData = std::make_unique<LightData>();
      cubeData->lightData->lights = {};
      cubeData->lightData->lightKey = 1u;
      cubeData->lightData->material.ambientFactor    = 0.25f;
      cubeData->lightData->material.diffuseFactor    = 0.15f;
      cubeData->lightData->material.specularFactor   = 0.3f;
      cubeData->lightData->material.shininessFactor  = 4.0f;

      if(cubeData->internalName == "Cube") {
        cubeData->shaders["cube"]->useProgram();
        cubeData->shaders["cube"]->setUniform3fv({ 1.0f, 1.0f, 1.0f }, "ambientLightColor");
        cubeData->shaders["cube"]->setUniform1f(0.5f, "ambientLightIntensity");
        cubeData->shaders["cube"]->setUniform1f(cubeData->lightData->material.ambientFactor, "material.ambientFactor");
        cubeData->shaders["cube"]->setUniform1f(cubeData->lightData->material.diffuseFactor, "material.diffuseFactor");
        cubeData->shaders["cube"]->setUniform1f(cubeData->lightData->material.specularFactor, "material.specularFactor");
        cubeData->shaders["cube"]->setUniform1f(cubeData->lightData->material.shininessFactor, "material.shininessFactor");
        cubeData->shaders["cube"]->setUniform1i(cubeData->id, "id");
        cubeData->shaders["cube"]->disuseProgram();
        cubeData->shaders["cube"]->createSSBOBlock(cubeData->lightData->lightKey, cubeData->lightData->lights.size() * sizeof(Light), static_cast<void*>(cubeData->lightData->lights.data()));
        
        Light frontLight, backLight;
        frontLight.position = { 0.0f, 0.0f, 2.0f, 0.0f };
        frontLight.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        frontLight.intensity = 2.0f;
        frontLight.attenuation = 0.0f;
        frontLight.radius = 20.0f;
        backLight.position = { -40.0f, 0.0f, 0.0f, 0.0f };
        backLight.color = { 0.5f, 0.5f, 0.5f, 0.5f };
        backLight.intensity = 1.0f;
        backLight.attenuation = 0.0f;
        backLight.radius = 20.0f;
        cubeData->lightData->lights.push_back(frontLight);
        cubeData->lightData->lights.push_back(backLight);
        addLights(cubeData);
      }
      
      cubeData->transformData.modelMatrix = modelMatrix;
      cubeData->transformData.rotation = { 0.0f, 0.0f, 0.0f };
      cubeData->transformData.scale = cubeData->internalName == "CubeLight" ? glm::vec3(0.25f) : glm::vec3(1.0f);
      cubes.push_back(std::move(cubeData));
    }

    void OpenglRenderer::drawCubes(const glm::vec3& eyePosition, int objectSelectedId) {
      for(int i = 0; i < cubes.size(); i++) {
        //outline pass
        if(objectSelectedId == i) {
          glCullFace(GL_FRONT); 
          cubes[i]->shaders["outline"]->useProgram();
          glm::mat4 modelMatrixScaled = glm::scale(cubes[i]->transformData.modelMatrix, glm::vec3(1.025f, 1.025f, 1.025f));
          glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["outline"]->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrixScaled));
    	    glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["outline"]->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["outline"]->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
          cubes[i]->shaders["outline"]->setUniform3fv(eyePosition, "eye");
          glBindVertexArray(cubes[i]->vaoId);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          glBindVertexArray(0);
          cubes[i]->shaders["outline"]->disuseProgram();
        }
        //normal pass
        glCullFace(GL_BACK);
        if(cubes[i]->internalName == "Cube") {
          cubes[i]->shaders["cube"]->useProgram();
          glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["cube"]->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubes[i]->transformData.modelMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["cube"]->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["cube"]->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

          cubes[i]->shaders["cube"]->setUniform1i(cubes[i]->id, "id");
          cubes[i]->shaders["cube"]->setUniform1f(cubes[i]->lightData->material.ambientFactor, "material.ambientFactor");
          cubes[i]->shaders["cube"]->setUniform1f(cubes[i]->lightData->material.diffuseFactor, "material.diffuseFactor");
          cubes[i]->shaders["cube"]->setUniform1f(cubes[i]->lightData->material.specularFactor, "material.specularFactor");
          cubes[i]->shaders["cube"]->setUniform1f(cubes[i]->lightData->material.shininessFactor, "material.shininessFactor");
          cubes[i]->shaders["cube"]->setUniform3fv(eyePosition, "eye");


          //we need to update the light data.


          cubes[i]->shaders["cube"]->setSSBOBlockSubData(
            cubes[i]->lightData->lightKey,
            0,
            static_cast<void*>(cubes[i]->lightData->lights.data()),
            sizeof(Light) * cubes[i]->lightData->lights.size()
          );
        } else if(cubes[i]->internalName == "CubeLight") {
          cubes[i]->shaders["basic"]->useProgram();
          glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["basic"]->program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubes[i]->transformData.modelMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["basic"]->program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    	    glUniformMatrix4fv(glGetUniformLocation(cubes[i]->shaders["basic"]->program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
          cubes[i]->shaders["basic"]->setUniform4fv(glm::vec4(1.0, 1.0, 1.0, 1.0), "color");
        }

        glBindVertexArray(cubes[i]->vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        cubes[i]->shaders["cube"]->disuseProgram();
        cubes[i]->shaders["basic"]->disuseProgram();
      }
    }

    void OpenglRenderer::objectsUpdateLights() {
      for(int i = 0; i < cubes.size(); i++) {
        cubes[i]->lightData->lights
      }
    }

    void OpenglRenderer::setAxesData() {
      axesData = std::make_unique<AxesData>();
      glGenBuffers(2, axesData->bufferIds);
      glBindBuffer(GL_ARRAY_BUFFER, axesData->bufferIds[0]);
      glBufferData(GL_ARRAY_BUFFER, axesGeometry.size() * sizeof(float), static_cast<void*>(axesGeometry.data()), GL_STATIC_DRAW);
      glGenVertexArrays(1, &(axesData->vaoId));
      glBindVertexArray(axesData->vaoId);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
      glBindBuffer(GL_ARRAY_BUFFER, axesData->bufferIds[1]);
      glBufferData(GL_ARRAY_BUFFER, axesColor.size() * sizeof(unsigned char), static_cast<void*>(axesColor.data()), GL_STATIC_DRAW);
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
