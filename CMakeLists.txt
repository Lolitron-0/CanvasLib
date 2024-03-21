cmake_minimum_required(VERSION 3.14)

project(
    CanvasLib
    VERSION 0.1.0
    DESCRIPTION "Tiny graphics GLFW lib for fast prototyping"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

# ---- Declare library ----

add_library(
    ${CMAKE_PROJECT_NAME}
    source/Color.cpp
    source/Colors.cpp
    source/CanvasLib.cpp
)

add_library(CanvasLib::CanvasLib ALIAS ${CMAKE_PROJECT_NAME})
if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC CANVASLIB_STATIC_DEFINE)
endif()

target_include_directories(
    ${CMAKE_PROJECT_NAME} ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    ${CMAKE_PROJECT_NAME} SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

# ---- Tests ----

if(CANVAS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# ---- Dependencies ----
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_USE_WAYLAND ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC OpenGL::GL)
