#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class Program;

class Selector : public sf::Drawable
{
    public:
        Selector(Program& program);

        virtual void update(float delta) = 0;

        virtual bool handleEvent(sf::Event& event) = 0;

        virtual void deselect() = 0;

        virtual void doImGui() = 0;

        virtual bool selected() const = 0;

        virtual sf::Vector2f getPosition() const = 0;

    protected:
        Program& program;

    private:
};
