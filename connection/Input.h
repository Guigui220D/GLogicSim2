#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Output.h"

class Gate;

class Input
{
    public:
        Input(sf::Vector2f relative_pos);
        ~Input();

        inline bool isConnected() { return (bool)connected_output.lock(); }

        void draw(sf::RenderTarget &target, const Gate& gate) const;

        inline bool updateState()
        {
            if (std::shared_ptr<Output> spt = connected_output.lock())
            {
                state = spt->getState();
            }
            else
                state = false;
        }

        inline bool getState() const { return state; }

    private:
        std::weak_ptr<Output> connected_output;

        bool state = false;

        mutable sf::CircleShape circle;
};
