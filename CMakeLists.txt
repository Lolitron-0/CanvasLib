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
	STATIC
    source/Color.cpp
    source/Colors.cpp
    source/CanvasLib.cpp
	source/Window.cpp
)

add_library(CanvasLib::CanvasLib ALIAS ${CMAKE_PROJECT_NAME})

target_include_directories(
    ${CMAKE_PROJECT_NAME} ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

include_directories(thirdparty/RenderingAbstraction/include)

add_subdirectory(thirdparty/RenderingAbstraction)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC RenderingAbstraction)

# ---- Tests ----

if(CANVAS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# ---- Dependencies ----
# find_package(glfw3 REQUIRED)
# find_package(OpenGL REQUIRED)
#
# target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw)
# target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC OpenGL::GL)


