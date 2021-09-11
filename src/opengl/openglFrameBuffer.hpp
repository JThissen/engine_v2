#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glad/glad.h>
#include "../headers.hpp"

namespace engine {
  enum class FrameBufferTextureFormat {
    None = 0,
    RGBA8,
    RED_INTEGER,
    DEPTH24STENCIL8,
    Depth = DEPTH24STENCIL8
  };

  struct FrameBufferSpecification {
    int width = 0;
    int height = 0;
    std::vector<FrameBufferTextureFormat> textureFormats;
  };

  class FrameBuffer {
    private:
    public:
    unsigned int bufferId;
    unsigned int colorTextureId;
    unsigned int depthTextureId;
    std::vector<unsigned int> colorAttachmentIds;
    std::vector<FrameBufferTextureFormat> colorTextureFormats;
    unsigned int depthAttachmentId;
    FrameBufferTextureFormat depthTextureFormat;
    int width, height;
    FrameBufferSpecification spec;

    FrameBuffer(int width, int height, int colorAttachments = 1, bool depthAttachment = true);
    FrameBuffer(const FrameBufferSpecification& spec);
    ~FrameBuffer();
    void create(int width, int height, int colorAttachments, bool depthAttachment);
    void recreate(int width, int height);
    void attachColorTexture(unsigned int textureId, int width, int height, int internalFormat, int format, int index);
    void attachDepthTexture(unsigned int textureId, int width, int height, int internalFormat, int format);
    void bind();
    void bindTexture(unsigned int textureId);
    void unbind();
    void onResize(int width, int height);
    bool isDepthFormat(FrameBufferTextureFormat textureFormat);
    int readPixel(int colorAttachmentIndex, int x, int y, int format = GL_RED_INTEGER);
  };
}

#endif
