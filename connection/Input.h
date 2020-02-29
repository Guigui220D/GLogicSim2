#pragma once

#include <memory>

#include "Output.h"

#include "Connector.h"

class Gate;

class Input : public Connector
{
    public:
        Input(Gate& gate, sf::Vector2f relative_pos);
        ~Input();

        inline bool isConnected() { return (bool)connected_output.lock(); }
        inline void updateState()
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
};
