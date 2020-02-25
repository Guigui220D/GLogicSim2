#include "NotGate.h"

NotGate::NotGate() :
    shape(3)
{
    inputs.push_back(std::make_shared<Input>(sf::Vector2f(-50.f, 0)));
    outputs.push_back(std::make_shared<Output>(sf::Vector2f(50.f, 0)));

    shape.setPoint(0, sf::Vector2f(-45.f, 45.f));
    shape.setPoint(1, sf::Vector2f(45.f, 0.f));
    shape.setPoint(2, sf::Vector2f(-45.f, -45.f));

    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(5.f);
}

NotGate::~NotGate()
{
    //dtor
}

void NotGate::update(float delta)
{
    inputs.at(0)->updateState();
    outputs.at(0)->setState(!inputs.at(0)->getState());
}

void NotGate::drawGate(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape);
}
