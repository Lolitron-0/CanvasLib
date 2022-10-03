#include <string>
#include <iostream>
#include <cmath>

#include "CanvasLib/CanvasLib.hpp"

namespace canv {

    Canvas::Canvas(int width, int height)
        :mSize(width, height), mFillColor(255,255,255), mDrawMode(GL_TRIANGLE_FAN)
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
            glClearColor(0,0,0,0);
            glClear(GL_COLOR_BUFFER_BIT);

            mUpdateFunction();
            glfwSwapBuffers(mpWindowHandle.get());
        }
    }

    void Canvas::setUpdateFunction(std::function<void ()> upd)
    {
        mUpdateFunction = upd;
    }

    void Canvas::drawRectangle(float x, float y, float w, float h)
    {
        applyColorGl();
        glBegin(mDrawMode);
        glVertex2f(xToGl(x), yToGl(y));
        glVertex2f(xToGl(x+w), yToGl(y));
        glVertex2f(xToGl(x+w), yToGl(y+h));
        glVertex2f(xToGl(x), yToGl(y+h));
        //glRectf(xToGl(x), yToGl(y), xToGl(x+w), yToGl(y+h));
        glEnd();
    }

    void Canvas::drawEllipse(float cx, float cy, float rx, float ry, int segments)
    {
        cx = xToGl(cx);
        cy = yToGl(cy);
        rx = xToGl(rx);
        ry = yToGl(ry);

        float theta = 2 * 3.1415926 / float(segments);
        float c = cosf(theta);
        float s = sinf(theta);
        float t;

        float x = 1; // we start at angle = 0
        float y = 0;

        applyColorGl();
        glBegin(mDrawMode);
            for(int i = 0; i < segments; i++)
            {
                glVertex2f(x * rx + cx, y * ry + cy);

                t = x;
                x = c * x - s * y;
                y = s * t + c * y;
            }
            glEnd();
    }

    void Canvas::setFillColor(const Color &color)
    {
        mFillColor = color;
    }

    void Canvas::setDrawMode(const DrawMode &drawMode)
    {
        switch (drawMode) {
        case DrawMode::Fill:
            mDrawMode = GL_TRIANGLE_FAN;
            break;
        case DrawMode::Outline:
            mDrawMode = GL_LINE_LOOP;
            break;
        default:
            break;
        }
    }

    Canvas::~Canvas()
    {
        mpWindowHandle.reset();
        glfwTerminate();
    }

    auto Canvas::xToGl(float x) const -> float
    {
        return x/mSize.x;
    }

    auto Canvas::yToGl(float y) const -> float
    {
        return y/mSize.y;
    }

    void Canvas::applyColorGl()
    {
        glColor4ub(mFillColor.r, mFillColor.g, mFillColor.b, mFillColor.a);
    }

}
