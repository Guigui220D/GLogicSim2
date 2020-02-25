#pragma once

#include "Gate.h"

class NotGate : public Gate
{
    public:
        NotGate();
        ~NotGate();

        void drawGate(sf::RenderTarget &target, sf::RenderStates states) const override;

        void update(float delta) override;

        void makeImGuiInterface() override;

    private:
        sf::RectangleShape rect;
        sf::CircleShape circ;
        sf::Text icon;
};
