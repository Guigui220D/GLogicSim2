#include "Output.h"

#include "Gate.h"

Output::Output(sf::Vector2f relative_pos) :
    circle(7.f)
{
    circle.setPosition(relative_pos);
    circle.setFillColor(sf::Color::Red);
    circle.setOrigin(sf::Vector2f(7.f, 7.f));
}

Output::~Output()
{

}

void Output::draw(sf::RenderTarget &target, const Gate& gate) const
{
    circle.move(gate.getPosition());
    circle.setFillColor(state ? sf::Color::Green : sf::Color::Red);
    target.draw(circle);
    circle.move(-gate.getPosition());
}
