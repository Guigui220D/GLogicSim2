#include "Gate.h"

sf::Font Gate::icon_font;

Gate::Gate() :
    selected_marker(50.f)
{
    selected_marker.setOrigin(sf::Vector2f(50.f, 50.f));
    selected_marker.setFillColor(sf::Color::Transparent);
    selected_marker.setOutlineThickness(4.f);
    selected_marker.setOutlineColor(sf::Color::Red);
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

    if (selected)
        target.draw(selected_marker, states);
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
    if (selected)
        return false;

    sf::Vector2f diff = click_pos - position;
    return (diff.x * diff.x + diff.y * diff.y) <= 50.f * 50.f * size * size;
}
