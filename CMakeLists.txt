cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    CanvasLib
    VERSION 0.1.0
    DESCRIPTION "Tiny graphics GLFW lib for fast prototyping"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    ${CMAKE_PROJECT_NAME}
    source/CanvasLib.cpp
)
add_library(CanvasLib::CanvasLib ALIAS ${CMAKE_PROJECT_NAME})


include(GenerateExportHeader)
generate_export_header(
    ${CMAKE_PROJECT_NAME}
    BASE_NAME CanvasLib
    EXPORT_FILE_NAME export/CanvasLib/CanvasLib_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC CANVASLIB_STATIC_DEFINE)
endif()

set_target_properties(
    ${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME CanvasLib
    OUTPUT_NAME CanvasLib
)

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

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)

# ---- Tests ----

if(CANVAS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if(CANVAS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ---- Dependencies ----
include(CMakeFindDependencyMacro)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_dependency(glfw3 CONFIG REQUIRED)
find_dependency(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/GLFW/glfw3.lib)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL)

# ---- Package ----

#include(CMakePackageConfigHelpers)
#
#configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#  "${CMAKE_CURRENT_BINARY_DIR}/CanvasLibConfig.cmake"
#  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CanvasLib
#)
#
#install(FILES
#          "${CMAKE_CURRENT_BINARY_DIR}/CanvasLibConfig.cmake"
#          "${CMAKE_CURRENT_BINARY_DIR}/CanvasLibConfigVersion.cmake"
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CanvasLib
#)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----
set(CanvasLib_DEVELOPER_MODE)
if(NOT CanvasLib_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of CanvasLib"
  )
endif()

include(cmake/dev-mode.cmake)
