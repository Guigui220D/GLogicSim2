#pragma once

#include <SFML/Graphics.hpp>
#include "Line.h"

class Gate;

class Output
{
    public:
        Output(sf::Vector2f relative_pos);
        ~Output();

        inline void setState(bool new_state) { state = new_state; }
        inline bool getState() { return state; }

        void draw(sf::RenderTarget &target, const Gate& gate) const;

    private:
        bool state = false;

        mutable sf::CircleShape circle;
};
