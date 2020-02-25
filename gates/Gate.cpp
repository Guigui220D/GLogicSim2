#include "Gate.h"

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
    drawGate(target, states);
    drawPorts(target);
}

void Gate::drawPorts(sf::RenderTarget &target) const
{
    for (const std::shared_ptr<Input>& input : inputs)
        input->draw(target, *this);

    for (const std::shared_ptr<Output>& output : outputs)
        output->draw(target, *this);
}
