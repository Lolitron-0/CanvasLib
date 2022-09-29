#include "CanvasLib/Color.hpp"
#include <iostream>


namespace canv {

Color::Color()
    :Color(0,255,0)
{

}

Color::Color(uint8 r, uint8 g, uint8 b, uint8 a)
    :r(r),g(g),b(b),a(a)
{

}

Color::Color(const Color &other)
    :Color(other.r, other.g, other.b, other.a)
{}

Color &Color::operator=(const Color &other)
{
    Color tmp(other);
    std::swap(tmp.a, this->a);
    std::swap(tmp.r, this->r);
    std::swap(tmp.g, this->g);
    std::swap(tmp.b, this->b);
    return *this;
}

Color &Color::operator=(Color &&other)
{
    std::swap(other.a, this->a);
    std::swap(other.r, this->r);
    std::swap(other.g, this->g);
    std::swap(other.b, this->b);
    return *this;
}


} // namespace canvas
