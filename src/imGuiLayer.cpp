#include "imGuiLayer.hpp"
#include "app.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace engine {
  ImGuiLayer::ImGuiLayer() : Layer("imGuiLayer") {
    // t.b.d.
  }

  void ImGuiLayer::push() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    App& app = App::get();
    ImGui_ImplGlfw_InitForOpenGL(app.window->window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
  }

  void ImGuiLayer::remove() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void ImGuiLayer::update(engine::DeltaTime deltaTime) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    bool showDemoWindow = true;
    ImGui::ShowDemoWindow(&showDemoWindow);
    
    ImGuiIO& io = ImGui::GetIO();
    App& app = App::get();
    io.DisplaySize = ImVec2(app.window->width, app.window->height);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  }
}
