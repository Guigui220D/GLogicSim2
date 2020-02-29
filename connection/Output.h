#pragma once

#include "Line.h"

#include "Connector.h"

class Gate;

class Output : public Connector
{
    public:
        Output(Gate& gate, sf::Vector2f relative_pos);
        ~Output();

        inline void setState(bool new_state) { state = new_state; }
        inline bool getState() { return state; }

    private:
        bool state = false;
};
