#include "Connector.h"

Connector::Connector(Gate& gate, sf::Vector2f relative_pos) :
    owner(gate),
    relative_pos(relative_pos),
    circle(7.f)
{
    circle.setOrigin(sf::Vector2f(7.f, 7.f));
}

Connector::~Connector()
{}

void Connector::draw(sf::RenderTarget &target, sf::Transform transform, const Gate& gate) const
{
    transform.translate(relative_pos);
    target.draw(circle, transform);
}
