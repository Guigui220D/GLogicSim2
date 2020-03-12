#include "Gate.h"

sf::Font Gate::icon_font;

Gate::Gate()
{

}

Gate::~Gate()
{
    //dtor
}

void Gate::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(position);
    states.transform.rotate(45.f * rotation);
    states.transform.scale(size, size);

    drawGate(target, states);
    drawPorts(target, states);
}

void Gate::drawPorts(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const std::shared_ptr<Input>& input : inputs)
        input->draw(target, states.transform, *this);

    for (const std::shared_ptr<Output>& output : outputs)
        output->draw(target, states.transform, *this);
}

bool Gate::takeClick(sf::Vector2f click_pos) const
{
    sf::Vector2f diff = click_pos - position;
    return (diff.x * diff.x + diff.y * diff.y) <= 50.f * 50.f * size * size;
}
