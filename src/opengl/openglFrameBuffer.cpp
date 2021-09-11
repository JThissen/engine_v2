#include "openglFrameBuffer.hpp"
#include "../utils.hpp"

namespace engine {
  FrameBuffer::FrameBuffer(int width, int height, int colorAttachments, bool depthAttachment) {
    create(width, height, colorAttachments, depthAttachment);
  }

  FrameBuffer::FrameBuffer(const FrameBufferSpecification& spec)
   : spec(spec) {
    for(auto textureFormat : spec.textureFormats) {
      if(isDepthFormat(textureFormat)) {
        depthTextureFormat = textureFormat;
      } else {
        colorTextureFormats.push_back(textureFormat);
      }
    }
    create(spec.width, spec.height, colorTextureFormats.size(), true);
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

      int internalFormat = GL_RGBA8;
      int format = GL_RGBA;

      if(colorTextureFormats[i] == FrameBufferTextureFormat::RGBA8) {
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
      } else if(colorTextureFormats[i] == FrameBufferTextureFormat::RED_INTEGER) {
        internalFormat = GL_R32I;
        format = GL_RED_INTEGER;
      }
      attachColorTexture(this->colorAttachmentIds[i], width, height, internalFormat, format, i);
    }

    if(depthAttachment) {
      glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachmentId);
      glBindTexture(GL_TEXTURE_2D, depthAttachmentId);
      attachDepthTexture(depthAttachmentId, width, height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL);
    }

    if (colorAttachmentIds.size() > 1) {
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(static_cast<int>(colorAttachmentIds.size()), buffers);
		}
		else if(colorAttachmentIds.empty()) {
			glDrawBuffer(GL_NONE); //depth pass only
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
    glViewport(0, 0, width, height);
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

  bool FrameBuffer::isDepthFormat(FrameBufferTextureFormat textureFormat) {
    return textureFormat == FrameBufferTextureFormat::DEPTH24STENCIL8;
  }

  int FrameBuffer::readPixel(int colorAttachmentIndex, int x, int y, int format) {
    glReadBuffer(GL_COLOR_ATTACHMENT0 + colorAttachmentIndex);
    int pixelData;
    glReadPixels(x, y, 1, 1, format, GL_INT, &pixelData);
    return pixelData;
  }
}
