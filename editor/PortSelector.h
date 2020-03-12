#pragma once

#include "Selector.h"

#include <SFML/Graphics.hpp>

#include <memory>

class Connector;

class PortSelector : public Selector
{
    public:
        PortSelector(Program& program);
        ~PortSelector();

        void update(float delta) override;

        bool handleEvent(sf::Event& event) override;

        void deselect() override;

        void doImGui() override;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        bool selected() const override;

        sf::Vector2f getPosition() const override;

    private:

};
