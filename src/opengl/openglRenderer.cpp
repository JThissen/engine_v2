#include "openglRenderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace engine {
    void OpenglRenderer::init() {
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
    }

    void OpenglRenderer::setViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
			glViewport(x, y, width, height);
		}

    void OpenglRenderer::setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
			glClearColor(r, g, b, a);
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
}
