#include "Line.h"

#include <cmath>

Line::Line(const sf::Vector2f& a, const sf::Vector2f& b) :
    a(a),
    b(b),
    color(sf::Color::Yellow),
    thickness(5.f)
{
    make();

    for (int i = 0; i < 4; ++i)
        vertices[i].color = color;
}

void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(vertices, 4, sf::Quads);
}

void Line::make()
{
    sf::Vector2f direction = a - b;
    sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

    vertices[0].position = a + offset;
    vertices[1].position = b + offset;
    vertices[2].position = b - offset;
    vertices[3].position = a - offset;
}
