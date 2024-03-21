cmake_minimum_required(VERSION 3.14)

project(CanvasLibTests LANGUAGES CXX)

# ---- Tests ----

add_executable(CanvasLib_test source/CanvasLib_test.cpp)

target_link_libraries(CanvasLib_test CanvasLib)

target_compile_features(CanvasLib_test PRIVATE cxx_std_17)
# target_include_directories(CanvasLib_test PRIVATE ../include)

add_test(NAME CanvasLib_test COMMAND CanvasLib_test)
