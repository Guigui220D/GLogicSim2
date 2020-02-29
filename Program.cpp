#include "Program.h"

#include "imgui-SFML.h"

#include <iostream>
#include <cmath>

#include "NotGate.h"

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

    selected_marker.setOrigin(sf::Vector2f(50.f, 50.f));
    selected_marker.setFillColor(sf::Color::Transparent);
    selected_marker.setOutlineThickness(4.f);
    selected_marker.setOutlineColor(sf::Color::Green);

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

                        sf::Vector2f mpos = render_window.mapPixelToCoords(sf::Mouse::getPosition(render_window));

                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            bool clicked = false;
                            for (std::shared_ptr<Gate>& gate : gates)
                            {
                                if (gate->takeClick(mpos))
                                {
                                    deselectGate();
                                    selected_gate = gate;
                                    gate->selected = true;
                                    clicked = true;
                                    break;
                                }
                            }

                            if (!clicked)
                            {
                                dragging = true;
                                drag_origin = render_window.mapPixelToCoords(sf::Mouse::getPosition());
                            }
                        }

                        if (event.mouseButton.button == sf::Mouse::Right)
                        {
                            if (moving_gate)
                            {
                                moving_gate = false;
                                break;
                            }

                            deselectGate();

                            for (std::shared_ptr<Gate>& gate : gates)
                            {
                                if (gate->takeClick(mpos))
                                {
                                    selected_gate = gate;
                                    gate->selected = true;
                                    moving_gate = true;
                                    break;
                                }
                            }
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
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        deselectGate();
                        break;
                    default: break;
                    }

                    break;

                default: break;
                }
            }
        }

        //Updates
        delta = delta_clock.getElapsedTime().asSeconds();

        for (const std::shared_ptr<Gate>& gate : gates)
            gate->update(delta);

        if (std::shared_ptr<Gate> spt = selected_gate.lock())
            if (moving_gate)
            {
                if (grid_mode)
                {
                    sf::Vector2f pos = render_window.mapPixelToCoords(sf::Mouse::getPosition(render_window));

                    pos /= 100.f;
                    pos.x = std::round(pos.x);
                    pos.y = std::round(pos.y);
                    pos *= 100.f;

                    spt->position = pos;
                }
                else
                    spt->position = render_window.mapPixelToCoords(sf::Mouse::getPosition(render_window));
            }

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

            if (std::shared_ptr<Gate> spt = selected_gate.lock())
            {
                if (moving_gate)
                {
                    ImGui::Text("YOU ARE IN GATE MOVING MODE");
                    ImGui::Text("Right click to place the gate, Escape to cancel");
                    ImGui::Separator();
                }

                spt->makeImGuiInterface();

                ImGui::Separator();

                ImGui::SliderInt("Angle", &spt->rotation, -4, 4, "");
                ImGui::SliderInt("Size", &spt->size, 1, 3, "");

                if (ImGui::Button("Delete"))
                {
                    gates.erase(std::find(gates.begin(), gates.end(), spt));
                    moving_gate = false;
                }

                if (ImGui::Button("Deselect"))
                    deselectGate();

                if (ImGui::Button("Move"))
                    moving_gate = true;

            }
            else
                ImGui::Text("Click on a gate to edit it");
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
                    deselectGate();

                    std::shared_ptr<Gate> g(to_add);

                    gates.push_back(g);
                    selected_gate = g;
                    to_add->selected = true;
                    moving_gate = true;
                }
            }
        }
        ImGui::End();

        if (std::shared_ptr<Gate> spt = selected_gate.lock())
            menu_line.setPointA(spt->position);
        menu_line.setPointB(render_window.mapPixelToCoords(menu_pos));

        //Drawing
        render_window.clear();

        render_window.draw(background);

        sf::Vector2f mpos = render_window.mapPixelToCoords(sf::Mouse::getPosition(render_window));
        for (const std::shared_ptr<Gate>& gate : gates)
        {
            render_window.draw(*gate);
            if (gate->takeClick(mpos))
            {
                selected_marker.setPosition(gate->position);
                float ra = 50.f * gate->size;
                selected_marker.setRadius(ra);
                selected_marker.setOrigin(sf::Vector2f(ra, ra));
                render_window.draw(selected_marker);
            }
        }


        if (selected_gate.lock())
            render_window.draw(menu_line);

        ImGui::SFML::Render(render_window);

        render_window.display();
    }
}

void Program::end()
{
    ImGui::SFML::Shutdown();
}

void Program::deselectGate()
{
    if (std::shared_ptr<Gate> spt = selected_gate.lock())
    {
        spt->selected = false;
        selected_gate.reset();
        moving_gate = false;
    }
}
