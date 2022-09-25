#include <string>
#include <iostream>

#include "CanvasLib/CanvasLib.hpp"

Canvas::Canvas()
{
    glfwInit();
    mpWindowHandle = glfwCreateWindow(500, 300, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(mpWindowHandle);
    glfwSetErrorCallback([](int errCode, const char* message){
       std::cerr<<message<<std::endl;
    });

    while(!glfwWindowShouldClose(mpWindowHandle)){
        glfwPollEvents();
    }
}

Canvas::~Canvas()
{
    glfwDestroyWindow(mpWindowHandle);
    glfwTerminate();
}
