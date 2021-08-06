#include "openglRenderer.hpp"
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

    void OpenglRenderer::draw(std::shared_ptr<OpenglVertexArray> vertexArray) {
			glDrawElements(GL_TRIANGLES, vertexArray->indexBuffer->size, GL_UNSIGNED_INT, nullptr);
		}
}
