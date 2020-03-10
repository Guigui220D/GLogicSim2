#pragma once

#include "Selector.h"

#include <SFML/Graphics.hpp>

class NoSelector : public Selector
{
    public:
        NoSelector(Program& program);
        ~NoSelector();

        void update(float delta) override;

        bool handleEvent(sf::Event& event) override;

        void deselect() override;

        void doImGui() override;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        bool selected() const override;

        sf::Vector2f getPosition() const override;

    protected:

    private:
};
