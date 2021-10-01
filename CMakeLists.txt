cmake_minimum_required(VERSION 3.13.4)
project(engine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

set(CPP_FILES
  src/main.cpp
  src/window.cpp
  src/app.cpp
  src/deltaTime.cpp
  src/event.cpp
  src/eventBusThread.cpp
  src/eventBus.cpp
  src/keyEvent.cpp
  src/mouseEvent.cpp
  src/windowEvent.cpp
  src/key.cpp
  src/layer.cpp
  src/layers.cpp
  src/imGuiLayer.cpp
  src/imgui_impl_opengl3.cpp
  src/imgui_impl_glfw.cpp
  src/windowInput.cpp
  src/mouse.cpp
  src/uuid.cpp
  src/renderer/context.cpp
  src/renderer/shader.cpp
  src/renderer/shaderBuilder.cpp
  src/renderer/layout.cpp
  src/renderer/layoutBuffer.cpp
  src/renderer/renderer.cpp
  src/renderer/orthographicCamera.cpp
  src/renderer/perspectiveCamera.cpp
  src/renderer/geometry.cpp
  src/renderer/cascadedShadowMaps.cpp
  src/opengl/openglContext.cpp
  src/opengl/openglVertexBuffer.cpp
  src/opengl/openglIndexBuffer.cpp
  src/opengl/openglVertexArray.cpp
  src/opengl/openglRenderer.cpp
  src/opengl/openglTexture.cpp
  src/opengl/openglFrameBuffer.cpp
  src/sandbox/sandboxLayer.cpp
  src/sandbox/sandbox.cpp
  src/scene/component.cpp
  src/scene/scene.cpp
)

add_executable(${PROJECT_NAME} ${CPP_FILES})

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git") 
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT_GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update failed")
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
  message(FATAL_ERROR "Unable to download the GLFW submodules.")
endif()

add_subdirectory(external/glad)
add_subdirectory(external/glfw) 
add_subdirectory(external/glm)
add_subdirectory(external/imgui)
add_subdirectory(external/stb_image)

target_include_directories(${PROJECT_NAME} 
  PUBLIC external/glfw/include
  PUBLIC external/glm/glm
  PUBLIC external/imgui
  PUBLIC external/stb_image
  PUBLIC external/entt
)

# link_directories default path is ./build
target_link_directories(${PROJECT_NAME} 
  PUBLIC external/glfw/src
  PUBLIC external/glm
  PUBLIC external/imgui
  PUBLIC external/stb_image
)

target_link_libraries(${PROJECT_NAME} 
  glad
  glfw
  glm
  imgui
  stb_image
  libimm32.a #https://github.com/AllenDang/giu/issues/151
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
