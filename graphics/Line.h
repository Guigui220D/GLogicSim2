#pragma once

#include <SFML/Graphics.hpp>

class Line : public sf::Drawable
{
    public:
        Line(const sf::Vector2f& a, const sf::Vector2f& b);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        inline void setPointA(sf::Vector2f point) { a = point; make(); }
        inline void setPointB(sf::Vector2f point) { b = point; make(); }
        inline void setThickness(float thiccness) { thickness = thiccness; make(); }
        inline void setFillColor(sf::Color col) { color = col; for (int i = 0; i < 4; ++i) vertices[i].color = color; }

    private:
        sf::Vertex vertices[4];

        sf::Vector2f a, b;
        sf::Color color;
        float thickness;

        void make();
};
