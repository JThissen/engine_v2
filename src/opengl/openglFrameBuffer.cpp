#include "openglFrameBuffer.hpp"
#include "../utils.hpp"

namespace engine {
  FrameBuffer::FrameBuffer(int width, int height, int colorAttachments, bool depthAttachment) {
    create(width, height, colorAttachments, depthAttachment);
  }

  FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &bufferId);
    glDeleteTextures(colorAttachmentIds.size(), colorAttachmentIds.data());
    glDeleteTextures(1, &depthAttachmentId);
  }

  void FrameBuffer::create(int width, int height, int colorAttachments, bool depthAttachment) {
    this->colorAttachmentIds.resize(colorAttachments);
    glCreateFramebuffers(1, &bufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, bufferId);
    glCreateTextures(GL_TEXTURE_2D, this->colorAttachmentIds.size(), this->colorAttachmentIds.data());
    
    for(int i = 0; i < this->colorAttachmentIds.size(); i++) {
      glBindTexture(GL_TEXTURE_2D, this->colorAttachmentIds[i]);
      attachColorTexture(this->colorAttachmentIds[i], width, height, GL_RGB8, GL_RGB, i);
    }

    if(depthAttachment) {
      glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachmentId);
      glBindTexture(GL_TEXTURE_2D, depthAttachmentId);
      attachDepthTexture(depthAttachmentId, width, height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL);
    }

    Utils::print("Framebuffer status", glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void FrameBuffer::recreate(int width, int height) {
    if(bufferId) {
      glDeleteFramebuffers(1, &bufferId);
      glDeleteTextures(colorAttachmentIds.size(), colorAttachmentIds.data());
      glDeleteTextures(1, &depthAttachmentId);
      bool hasDepthAttachment = depthAttachmentId ? true : false; 
      int originalSize = colorAttachmentIds.size();
      colorAttachmentIds.clear();
      depthAttachmentId = 0;
      create(width, height, originalSize, hasDepthAttachment);
    }
  }

  void FrameBuffer::attachColorTexture(unsigned int textureId, int width, int height, int internalFormat, int format, int index) {
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, textureId, 0);
  }

  void FrameBuffer::attachDepthTexture(unsigned int textureId, int width, int height, int internalFormat, int format) {
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_INT_24_8, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);
  }

  void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, bufferId);
  }

  void FrameBuffer::bindTexture(unsigned int textureId) {
    glBindTexture(GL_TEXTURE_2D, textureId);
  }

  void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void FrameBuffer::onResize(int width, int height) {
    this->width = width;
    this->height = height;
    recreate(width, height);
  }
}
