#include "Output.h"

#include "Gate.h"

Output::Output(sf::Vector2f relative_pos) :
    relative_pos(relative_pos),
    circle(7.f)
{
    circle.setFillColor(sf::Color::Red);
    circle.setOrigin(sf::Vector2f(7.f, 7.f));
}

Output::~Output()
{

}

void Output::draw(sf::RenderTarget &target, sf::Transform transform, const Gate& gate) const
{
    circle.setFillColor(state ? sf::Color::Green : sf::Color::Red);

    transform.translate(relative_pos);

    target.draw(circle, transform);
}
