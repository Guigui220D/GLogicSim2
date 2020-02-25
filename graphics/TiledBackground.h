#pragma once

#include <SFML/Graphics.hpp>

class TiledBackground : public sf::Drawable
{
    public:
        TiledBackground();
        ~TiledBackground();

        void updateWithView(const sf::View& view);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::VertexArray va;
        sf::Texture t;
};
