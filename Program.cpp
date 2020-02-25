#include "Program.h"

#include "imgui-SFML.h"

#include <iostream>

#include "NotGate.h"

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

    if (!Gate::icon_font.loadFromFile("arial.ttf"))
        return false;

    ImGui::SFML::Init(render_window);
    imgui_io = &ImGui::GetIO();

    menu_line.setFillColor(sf::Color::Black);
    menu_line.setThickness(1.f);

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

                        render_window.setView(v);
                        background.updateWithView(v);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (imgui_io->WantCaptureMouse)
                        break;
                    dragging = true;
                    drag_origin = render_window.mapPixelToCoords(sf::Mouse::getPosition());
                    break;

                case sf::Event::MouseButtonReleased:
                    dragging = false;
                    break;

                case sf::Event::MouseWheelScrolled:
                    {
                        sf::View v = render_window.getView();

                        v.zoom(1.f + .1f * -event.mouseWheelScroll.delta);

                        render_window.setView(v);
                        background.updateWithView(v);
                    }
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::A:
                        selected_gate = gates.at(0);
                        gates.at(0)->selected = true;
                        break;
                    case sf::Keyboard::Escape:
                        if (std::shared_ptr<Gate> spt = selected_gate.lock())
                        {
                            spt->selected = false;
                            selected_gate.reset();
                        }
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
                spt->makeImGuiInterface();

                ImGui::Separator();

                ImGui::SliderFloat("Angle", &spt->angle, -180.f, 180.f, "%f", 1.f);

                if (ImGui::Button("Delete"))
                    gates.erase(std::find(gates.begin(), gates.end(), spt));
            }
            else
                ImGui::Text("Click on a gate to edit it");
        ImGui::End();

        menu_line.setPointB(render_window.mapPixelToCoords(menu_pos));

        //Drawing
        render_window.clear();

        render_window.draw(background);

        for (const std::shared_ptr<Gate>& gate : gates)
            render_window.draw(*gate);

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
