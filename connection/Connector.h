#pragma once

#include <SFML/Graphics.hpp>

class Gate;

class Connector
{
    public:
        Connector(Gate& gate, sf::Vector2f relative_pos);
        virtual ~Connector();

        void draw(sf::RenderTarget &target, sf::Transform transform, const Gate& gate) const;

        bool selected = false;

    protected:
        Gate& owner;

        sf::Vector2f relative_pos;

        mutable sf::CircleShape circle;

    private:
};
