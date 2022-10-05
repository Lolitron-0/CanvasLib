cmake_minimum_required(VERSION 3.14)

project(CanvasLibTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)
include(../cmake/windows-set-path.cmake)


# ---- Tests ----

add_executable(CanvasLib_test source/CanvasLib_test.cpp)

#target_link_libraries(CanvasLib_test PRIVATE glfw3)
#target_link_libraries(CanvasLib_test PRIVATE ${CMAKE_SOURCE_DIR}/../build/CanvasLib.lib)


set(CanvasLib_DIR ../build)

if(PROJECT_IS_TOP_LEVEL)
  #find_package(CanvasLib REQUIRED)
  enable_testing()
endif()


#target_link_libraries(CanvasLib_test ${CMAKE_CURRENT_LIST_DIR}/../build/libCanvasLib.a)
find_package(CanvasLib REQUIRED)
target_link_libraries(CanvasLib_test CanvasLib)
#USE PACKAGES IN RELEASE VERSION DUMB (it's for me not for u)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(CanvasLib_test glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(CanvasLib_test OpenGL::GL)

target_compile_features(CanvasLib_test PRIVATE cxx_std_17)
# target_include_directories(CanvasLib_test PRIVATE ../include)

add_test(NAME CanvasLib_test COMMAND CanvasLib_test)
windows_set_path(CanvasLib_test CanvasLib::CanvasLib)



# ---- End-of-file commands ----

add_folders(Test)
