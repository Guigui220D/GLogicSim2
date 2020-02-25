#include "Input.h"

#include "Gate.h"

Input::Input(sf::Vector2f relative_pos) :
    relative_pos(relative_pos),
    circle(7.f)
{
    circle.setFillColor(sf::Color::Red);
    circle.setOrigin(sf::Vector2f(7.f, 7.f));
}

Input::~Input()
{

}

void Input::draw(sf::RenderTarget &target, sf::Transform transform, const Gate& gate) const
{
    circle.setFillColor(state ? sf::Color::Green : sf::Color::Red);

    transform.translate(relative_pos);

    target.draw(circle, transform);
}
