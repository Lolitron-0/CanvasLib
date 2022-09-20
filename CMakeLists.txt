cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    CanvasLib
    VERSION 0.1.0
    DESCRIPTION "Tiny graphics GLFW lib to fast prototyping"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    CanvasLib_CanvasLib
    source/CanvasLib.cpp
)
add_library(CanvasLib::CanvasLib ALIAS CanvasLib_CanvasLib)

find_package(glfw3 3.3 REQUIRED)

include(GenerateExportHeader)
generate_export_header(
    CanvasLib_CanvasLib
    BASE_NAME CanvasLib
    EXPORT_FILE_NAME export/CanvasLib/CanvasLib_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(CanvasLib_CanvasLib PUBLIC CANVASLIB_STATIC_DEFINE)
endif()

set_target_properties(
    CanvasLib_CanvasLib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME CanvasLib
    OUTPUT_NAME CanvasLib
)

target_include_directories(
    CanvasLib_CanvasLib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    CanvasLib_CanvasLib SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(CanvasLib_CanvasLib PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT CanvasLib_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of CanvasLib"
  )
endif()

include(cmake/dev-mode.cmake)
