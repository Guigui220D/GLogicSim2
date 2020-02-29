#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Line.h"
#include "TiledBackground.h"

#include "imgui.h"

#include "Gate.h"
#include "Connector.h"

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

        Line menu_line;

        sf::CircleShape selected_marker;

        bool dragging = false;
        sf::Vector2f drag_origin;

        void deselectGate();

        std::vector<std::shared_ptr<Gate>> gates;
        std::weak_ptr<Gate> selected_gate;
        std::weak_ptr<Connector> selected_connected;

        bool moving_gate = false;
        bool grid_mode = true;

        static const char* gate_type_names[];
};
