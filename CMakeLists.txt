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
    ${PROJECT_NAME}
	STATIC
    source/Color.cpp
    source/Colors.cpp
    source/CanvasLib.cpp
)

add_library(CanvasLib::CanvasLib ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME} ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

include_directories(thirdparty/RenderingAbstraction/include)

add_subdirectory(thirdparty/RenderingAbstraction)
target_link_libraries(${PROJECT_NAME} PUBLIC RenderingAbstraction)


include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(${PROJECT_NAME} 
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
)

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


