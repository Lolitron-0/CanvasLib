#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "CanvasLib/CanvasLib.hpp"

using namespace std::chrono_literals;

class Particle;
using ParticlePtr = std::shared_ptr<Particle>;
using ParticleSystem = std::vector<ParticlePtr>;

class Particle
{
public:
    Particle(const canv::Color& color, float mass, canv::Vec2<float> coords)
        : m_Coords{ coords },
          m_Color{ color },
          m_Mass{ mass }
    {
    }

    auto Update(canv::Canvas& canvas, const ParticleSystem& system,
                double fpsScale) -> void
    {
        _rule(system, fpsScale);
        m_Coords += fpsScale * m_Velocity;
        canv::Canvas::setWatch("vel", std::string{ m_Velocity });

        canvas.setFillColor(m_Color);
        // canvas.drawEllipse(m_Coords.X, m_Coords.Y, 20, 20);
        canvas.drawRectangle(m_Coords.X, m_Coords.Y, 20, 20);
    }

    auto ApplyImpulse(const canv::Vec2<float>& imp) -> void
    {
        m_Velocity += imp;
    }

private:
    auto _rule(const ParticleSystem& others, double fpsScale) -> void
    {

        for (const ParticlePtr& particle : others)
        {
            float d =
                roundf(m_Coords.DistToSquared(particle->m_Coords) * 1000.F) /
                1000.F;
            if (static_cast<int>(d) != 0)
            { // if it's not *this
                auto coeff = m_Mass * particle->m_Mass * fpsScale * 0.1F /
                             d; // Newton smell bebra
                auto dx = particle->m_Coords.X - m_Coords.X;
                auto dy = particle->m_Coords.Y - m_Coords.Y;

                m_Velocity.X += coeff * dx / m_Mass; // Newton smell bebra 2.0
                m_Velocity.Y += coeff * dy / m_Mass;
            }
        }
    }

    float m_Mass;
    canv::Color m_Color;
    canv::Vec2<float> m_Coords;
    canv::Vec2<float> m_Velocity{ 0, 0 };
};

const auto seed{ time(nullptr) };

auto main() -> int
{
    srand(seed);

    canv::Canvas canvas{ 1000, 800 };
    ParticleSystem system;

    system.push_back(std::make_shared<Particle>(canv::Colors::lightBlue, 1,
                                                canv::Vec2<float>(500, 10)));
    system.back()->ApplyImpulse({ 60, 0 });
    system.push_back(std::make_shared<Particle>(canv::Colors::green, 0.1,
                                                canv::Vec2<float>(600,
                                                300)));
    system.back()->ApplyImpulse({ 30, 30 });
    system.push_back(std::make_shared<Particle>(canv::Colors::red, 2,
                                                canv::Vec2<float>(350,
                                                550)));
    system.back()->ApplyImpulse({ -50, 0 });
    system.push_back(std::make_shared<Particle>(canv::Colors::white, 10,
                                                canv::Vec2<float>(500,
                                                500)));
    system.back()->ApplyImpulse({ 80, 0 });
    system.push_back(std::make_shared<Particle>(canv::Colors::blue, 6,
                                                canv::Vec2<float>(400,
                                                400)));
    system.back()->ApplyImpulse({ 0, 125 });
    system.push_back(std::make_shared<Particle>(canv::Colors::grey, 100000,
                                                canv::Vec2<float>(500,
                                                400)));
    canvas.setUpdateFunction(
        [&canvas, &system](double fpsScale)
        {
            std::for_each(system.begin(), system.end(),
                          [&](ParticlePtr& el)
                          { el->Update(canvas, system, fpsScale); });
            canvas.setFillColor(canv::Colors::red);

            canvas.drawRectangle(100 + (50.F * rand() / RAND_MAX), 100, 30,
            50);
        });

    canvas.start();

    return 0;
}
