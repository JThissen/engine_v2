#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glad/glad.h>
#include "../headers.hpp"

namespace engine {
  class FrameBuffer {
    private:
    public:
    unsigned int bufferId;
    unsigned int colorTextureId;
    unsigned int depthTextureId;
    std::vector<unsigned int> colorAttachmentIds;
    unsigned int depthAttachmentId;
    int width, height;

    FrameBuffer(int width, int height, int colorAttachments = 1, bool depthAttachment = true);
    ~FrameBuffer();
    void create(int width, int height, int colorAttachments, bool depthAttachment);
    void recreate(int width, int height);
    void attachColorTexture(unsigned int textureId, int width, int height, int internalFormat, int format, int index);
    void attachDepthTexture(unsigned int textureId, int width, int height, int internalFormat, int format);
    void bind();
    void bindTexture(unsigned int textureId);
    void unbind();
    void onResize(int width, int height);
  };
}

#endif
