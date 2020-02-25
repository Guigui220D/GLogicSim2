#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "TiledBackground.h"

#include "imgui.h"

class Program
{
    public:
        Program();
        ~Program();

        bool init();
        void run();
        void end();

    private:
        sf::RenderWindow render_window;
        TiledBackground background;

        ImGuiIO* imgui_io;

        bool dragging = false;
        sf::Vector2f drag_origin;

        sf::CircleShape test;

};
