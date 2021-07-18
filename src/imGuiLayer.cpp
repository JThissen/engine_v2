#include "imGuiLayer.hpp"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace engine {
  ImGuiLayer::ImGuiLayer() : Layer("imGuiLayer") {
    // t.b.d.
  }

  void ImGuiLayer::push() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    ImGui_ImplOpenGL3_Init("#version 410");
  }

  void ImGuiLayer::remove() {
    // t.b.d.
  }

  void ImGuiLayer::update(engine::DeltaTime deltaTime) {
    ImGuiIO& io = ImGui::GetIO();
    App& app = App::get();
    io.DisplaySize = ImVec2(static_cast<float>(app.window->width), static_cast<float>(app.window->height));
    io.DeltaTime = deltaTime.seconds();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    bool show = true;
    ImGui::ShowDemoWindow(&show);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGuiLayer::event(Event& event) {
    switch(event.eventType) {
      case Event::EventType::MousePressed: {
        mousePressedEvent(static_cast<MousePressedEvent&>(event));
        break;
      }
      case Event::EventType::MouseReleased: {
        mouseReleasedEvent(static_cast<MouseReleasedEvent&>(event));
        break;
      }
      case Event::EventType::MouseScrolled: {
        mouseScrolledEvent(static_cast<MouseScrolledEvent&>(event));
        break;
      }
      case Event::EventType::MousePosition: {
        mousePositionEvent(static_cast<MousePositionEvent&>(event));
        break;
      }
      case Event::EventType::WindowResized: {
        windowResizedEvent(static_cast<WindowResizedEvent&>(event));
        break;
      }
    }
  }

  void ImGuiLayer::mousePressedEvent(MousePressedEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.button] = true;
  }

  void ImGuiLayer::mouseReleasedEvent(MouseReleasedEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.button] = false;
  }

  void ImGuiLayer::mouseScrolledEvent(MouseScrolledEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += static_cast<float>(event.xOffset);
    io.MouseWheel += static_cast<float>(event.yOffset);
  }

  void ImGuiLayer::mousePositionEvent(MousePositionEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(static_cast<float>(event.x), static_cast<float>(event.y));
  }

  void ImGuiLayer::windowResizedEvent(WindowResizedEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(event.width, event.height);

    if (event.width > 0 && event.height > 0) {
      io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
      std::cout << event.width << ", " << event.height << std::endl;
      glViewport(0, 0, event.width, event.height);
    }
  }
}
