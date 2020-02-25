#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Input.h"
#include "Output.h"

class Gate : public sf::Drawable
{
    public:
        Gate();
        virtual ~Gate();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        inline sf::Vector2f getPosition() const { return position; }
        inline void setPosition(sf::Vector2f new_pos) { position = new_pos; }
        inline void move(sf::Vector2f vector) { position += vector; }

        virtual void update(float delta) = 0;

    protected:
        std::vector<std::shared_ptr<Input>> inputs;
        std::vector<std::shared_ptr<Output>> outputs;

        virtual void drawGate(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    private:
        void drawPorts(sf::RenderTarget &target) const;

        sf::Vector2f position;
};
