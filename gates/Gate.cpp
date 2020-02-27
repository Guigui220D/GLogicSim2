#include "Gate.h"

sf::Font Gate::icon_font;

Gate::Gate()
{
    //ctor
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
