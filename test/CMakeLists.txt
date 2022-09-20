cmake_minimum_required(VERSION 3.14)

project(CanvasLibTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)
include(../cmake/windows-set-path.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(CanvasLib REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(CanvasLib_test source/CanvasLib_test.cpp)
target_link_libraries(CanvasLib_test PRIVATE CanvasLib::CanvasLib)
target_compile_features(CanvasLib_test PRIVATE cxx_std_17)

add_test(NAME CanvasLib_test COMMAND CanvasLib_test)
windows_set_path(CanvasLib_test CanvasLib::CanvasLib)

# ---- End-of-file commands ----

add_folders(Test)
