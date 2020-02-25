#pragma once

#include <SFML/Graphics.hpp>

class Line : public sf::Drawable
{
    public:
        Line(const sf::Vector2f& point1, const sf::Vector2f& point2);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        sf::Vertex vertices[4];
        sf::Color color;
        float thickness;
};
