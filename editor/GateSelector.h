#pragma once

#include "Selector.h"

#include <SFML/Graphics.hpp>

#include <memory>

class Gate;

class GateSelector : public Selector
{
    public:
        GateSelector(Program& program);
        ~GateSelector();

        void update(float delta) override;

        bool handleEvent(sf::Event& event) override;

        void deselect() override;

        void doImGui() override;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        bool selected() const override;

        sf::Vector2f getPosition() const override;

    private:
        std::weak_ptr<Gate> selected_gate;

        bool moving_gate = false;
};
