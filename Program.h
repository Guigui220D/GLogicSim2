#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Line.h"
#include "TiledBackground.h"

#include "imgui.h"

#include "Gate.h"

#include <vector>

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

        std::vector<std::shared_ptr<Gate>> gates;
        std::weak_ptr<Gate> selected_gate;
};
