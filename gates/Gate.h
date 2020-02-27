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

        virtual void update(float delta) = 0;

        virtual void makeImGuiInterface() = 0;

        bool selected = false;

        static sf::Font icon_font;

        sf::Vector2f position;
        int rotation = 0;
        int size = 2;

    protected:
        std::vector<std::shared_ptr<Input>> inputs;
        std::vector<std::shared_ptr<Output>> outputs;

        virtual void drawGate(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    private:
        void drawPorts(sf::RenderTarget &target, sf::RenderStates states) const;
};
