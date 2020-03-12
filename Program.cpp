#include "Program.h"

#include "imgui-SFML.h"

#include <iostream>
#include <cmath>

#include "NotGate.h"

#include "NoSelector.h"
#include "GateSelector.h"

const char* Program::gate_type_names[] =
{
    "Buffer Gate",
    "Not Gate"
};

Program::Program() :
    render_window(sf::VideoMode(640, 480), "GLogicSim2"),
    imgui_io(nullptr),
    menu_line(sf::Vector2f(), sf::Vector2f())
{
}

Program::~Program()
{}

bool Program::init()
{
    selectors.at(0).reset(new GateSelector(*this));
    selectors.at(1).reset(new NoSelector(*this));
    selectors.at(2).reset(new NoSelector(*this));

    render_window.setFramerateLimit(60);

    {
        sf::View v = render_window.getView();
        v.zoom(3.f);
        menu_line.setThickness(3.f * v.getSize().x / render_window.getSize().x);
        render_window.setView(v);
    }

    if (!Gate::icon_font.loadFromFile("arial.ttf"))
        return false;

    ImGui::SFML::Init(render_window);
    imgui_io = &ImGui::GetIO();

    menu_line.setFillColor(sf::Color::Cyan);
    menu_line.setThickness(3.f);

    background.updateWithView(render_window.getView());

    gates.push_back(std::make_shared<NotGate>());

    return true;
}

void Program::run()
{
    sf::Clock delta_clock; float delta;

    while (render_window.isOpen())
    {
        {   //Events
            sf::Event event;

            while (render_window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);

                switch (event.type)
                {
                case sf::Event::Closed:
                    render_window.close();
                    break;

                case sf::Event::Resized:
                    {
                        sf::View v = render_window.getView();

                        v.setSize(sf::Vector2f(render_window.getSize().x, render_window.getSize().y));

                        menu_line.setThickness(3.f * v.getSize().x / render_window.getSize().x);
                        render_window.setView(v);
                        background.updateWithView(v);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    {
                        if (imgui_io->WantCaptureMouse)
                            break;

                        //sf::Vector2f mpos = render_window.mapPixelToCoords(sf::Mouse::getPosition(render_window));

                        if (selectors.at(selected_selector)->handleEvent(event))
                            break;

                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            dragging = true;
                            drag_origin = render_window.mapPixelToCoords(sf::Mouse::getPosition());
                        }
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    dragging = false;
                    break;

                case sf::Event::MouseWheelScrolled:
                    {
                        sf::View v = render_window.getView();

                        v.zoom(1.f + .1f * -event.mouseWheelScroll.delta);

                        menu_line.setThickness(3.f * v.getSize().x / render_window.getSize().x);

                        render_window.setView(v);
                        background.updateWithView(v);
                    }
                    break;

                case sf::Event::KeyPressed:
                    if (selectors.at(selected_selector)->handleEvent(event))
                            break;

                    break;

                default: break;
                }
            }
        }

        //Updates
        delta = delta_clock.getElapsedTime().asSeconds();

        gates.erase(std::remove_if(gates.begin(), gates.end(),
           [](const std::shared_ptr<Gate>& gate) { return gate->remove; }),
           gates.end());

        for (const std::shared_ptr<Gate>& gate : gates)
            gate->update(delta);

        selectors.at(selected_selector)->update(delta);

        if (dragging)
        {
            sf::View v = render_window.getView();

            v.move(drag_origin - render_window.mapPixelToCoords(sf::Mouse::getPosition()));

            render_window.setView(v);

            drag_origin = render_window.mapPixelToCoords(sf::Mouse::getPosition());

            background.updateWithView(v);
        }

        ImGui::SFML::Update(render_window, delta_clock.restart());

        ImGui::Begin("Selected gate");
            sf::Vector2i menu_pos = ImGui::GetCursorScreenPos();

            selectors.at(selected_selector)->doImGui();
        ImGui::End();

        ImGui::Begin("Edition Settings");
            ImGui::Checkbox("Grid mode movement", &grid_mode);
        ImGui::End();

        ImGui::Begin("Gates");
        {
            int i = -1;
            if (ImGui::ListBox("Gates", &i, gate_type_names, sizeof(gate_type_names) / sizeof(void*)))
            {
                Gate* to_add = nullptr;
                switch (i)
                {
                case 1: //Not gate
                    to_add = new NotGate();
                    break;

                default: break;
                }
                if (to_add)
                {
                    selectors.at(selected_selector)->deselect();

                    std::shared_ptr<Gate> g(to_add);

                    gates.push_back(g);
                }
            }
        }
        ImGui::End();

        if (selectors.at(selected_selector)->selected())
            menu_line.setPointA(selectors.at(selected_selector)->getPosition());
        menu_line.setPointB(render_window.mapPixelToCoords(menu_pos));

        //Drawing
        render_window.clear();

        render_window.draw(background);

        for (const std::shared_ptr<Gate>& gate : gates)
            render_window.draw(*gate);

        if (selectors.at(selected_selector)->selected())
            render_window.draw(menu_line);

        render_window.draw(*selectors.at(selected_selector));

        ImGui::SFML::Render(render_window);

        render_window.display();
    }
}

void Program::end()
{
    ImGui::SFML::Shutdown();
}
