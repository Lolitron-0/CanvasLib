#include <string>
#include <iostream>

#include "CanvasLib/CanvasLib.hpp"

namespace canv {

    Canvas::Canvas(int width, int height)
        :mSize(width, height)
    {
        glfwInit();
        this->mpWindowHandle.reset(
            glfwCreateWindow(width, height, "", NULL, NULL), //new value
            std::bind(glfwDestroyWindow, this->mpWindowHandle.get())); //deleter functor
        glfwMakeContextCurrent(mpWindowHandle.get());
        glfwSetErrorCallback([](int errCode, const char* message){
           std::cerr<<message<<std::endl;
        });
        glOrtho(0, 1., 1., 0, -1, 1);

        setUpdateFunction([](){
        });

    }

    void Canvas::start()
    {
        while(!glfwWindowShouldClose(mpWindowHandle.get())){
            glfwPollEvents();

            mUpdateFunction();
            glfwSwapBuffers(mpWindowHandle.get());
        }
    }

    void Canvas::setUpdateFunction(std::function<void ()> upd)
    {
        mUpdateFunction = upd;
    }

    void Canvas::drawRectangle(Color color, float x, float y, float w, float h)
    {
        glColor4ub(color.r, color.g, color.b, color.a);
        glRectf(xToGl(x), yToGl(y), xToGl(x+w), yToGl(y+h));
    }

    Canvas::~Canvas()
    {
        glfwTerminate();
    }

    float Canvas::xToGl(float x)
    {
        return x/mSize.x;
    }

    float Canvas::yToGl(float y)
    {
        return y/mSize.y;
    }

}
