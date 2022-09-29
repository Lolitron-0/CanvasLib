#include <string>
#include <iostream>

#include "CanvasLib/CanvasLib.hpp"


class Particle {
public:
    Particle(const canv::Color& color)
        :mCoords(20,100), mColor(color)
    {

    }
    auto update(canv::Canvas& canvas) -> void
    {
        canvas.setDrawMode(canv::Canvas::DrawMode::Outline);
        canvas.setFillColor(mColor);
        canvas.drawEllipse(mCoords.x, mCoords.y, 20, 20);
    }
private:
    canv::Color mColor;
    canv::Vec2<float> mCoords;
};



auto update(canv::Canvas& canvas) -> void
{
}

auto main() -> int
{
    auto canvas = canv::Canvas(500, 300);
    std::vector<Particle> parts;
    parts.push_back(Particle(canv::Colors::lightBlue));
    canvas.setUpdateFunction([&canvas, &parts](){
        std::for_each(parts.begin(), parts.end(), [&canvas](Particle& el){
            el.update(canvas);
        });
    });
    canvas.start();

    return 0;
}
