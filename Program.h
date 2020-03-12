#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Line.h"
#include "TiledBackground.h"

#include "imgui.h"

#include "Gate.h"
#include "Connector.h"

#include "Selector.h"

#include <vector>
#include <array>
#include <memory>

class Program
{
    friend class Selector;
    friend class GateSelector;
    friend class NoSelector;

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

        bool dragging = false;
        sf::Vector2f drag_origin;

        std::vector<std::shared_ptr<Gate>> gates;

        std::array<std::unique_ptr<Selector>, 3> selectors;
        int selected_selector = 0;

        bool grid_mode = true;

        static const char* gate_type_names[];
        static const char* modes_names[];
};
