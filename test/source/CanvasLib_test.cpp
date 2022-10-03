#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "CanvasLib/CanvasLib.hpp"

using namespace std::chrono_literals;

class Particle;
typedef std::shared_ptr<Particle> ParticlePtr;
typedef std::vector<ParticlePtr>ParticleSystem;

class Particle {
public:

    Particle(const canv::Color& color, float mass, canv::Vec2<float> coords)
        :mCoords(coords), mColor(color), mMass(mass)
    {

    }

    auto update(canv::Canvas& canvas,
                const ParticleSystem& system) -> void {
        rule(system);
        mCoords += mVelocity;

        canvas.setFillColor(mColor);
        canvas.drawEllipse(mCoords.x, mCoords.y, 20, 20);
    }

    auto applyImpulse(const canv::Vec2<float>& imp)-> void {
        mVelocity += imp;
    }

private:
    auto rule(const ParticleSystem& others) -> void {

        for(const ParticlePtr &particle : others) {
                auto d = round(mCoords.distToSquared(particle->mCoords) * 1000)/1000.;
                if((int)d!=0){ //if it's not *this
                auto coeff = mMass*particle->mMass*0.0001/d; // Newton smell bebra
                auto dx = particle->mCoords.x - mCoords.x;
                auto dy = particle->mCoords.y - mCoords.y;

                mVelocity.x += coeff * dx / mMass; // Newton smell bebra 2.0
                mVelocity.y += coeff * dy / mMass;
            }
        }
    }

    float mMass;
    canv::Color mColor;
    canv::Vec2<float> mCoords;
    canv::Vec2<float> mVelocity {0,0};
};



auto main() -> int
{
    srand(time(0));
    auto canvas = canv::Canvas(1000, 800);
    ParticleSystem system;

    system.push_back(std::make_shared<Particle>(canv::Colors::lightBlue, 1, canv::Vec2<float>(500,10)));
    system.back()->applyImpulse({1,0});
    system.push_back(std::make_shared<Particle>(canv::Colors::green, 0.1, canv::Vec2<float>(600,300)));
    system.back()->applyImpulse({3,3});
    system.push_back(std::make_shared<Particle>(canv::Colors::red,2, canv::Vec2<float>(350,550)));
    system.back()->applyImpulse({-2,0});
    system.push_back(std::make_shared<Particle>(canv::Colors::white,10, canv::Vec2<float>(500,500)));
    system.back()->applyImpulse({5,0});
    system.push_back(std::make_shared<Particle>(canv::Colors::blue,6, canv::Vec2<float>(400,400)));
    system.back()->applyImpulse({0,5});
    system.push_back(std::make_shared<Particle>(canv::Colors::grey,100000, canv::Vec2<float>(500,400)));

    canvas.setUpdateFunction([&canvas, &system](){
        std::for_each(system.begin(), system.end(), [&](ParticlePtr& el){
            el->update(canvas, system);
        });
        std::this_thread::sleep_for(1ms);
    });
    canvas.start();

    return 0;
}
