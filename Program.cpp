#include "Program.h"

#include "imgui-SFML.h"

#include <iostream>

Program::Program() :
    render_window(sf::VideoMode(640, 480), "GLogicSim2"),
    imgui_io(nullptr)
{
    test.setFillColor(sf::Color::Red);
    test.setRadius(50.f);
}

Program::~Program()
{}

bool Program::init()
{
    render_window.setFramerateLimit(60);

    ImGui::SFML::Init(render_window);
    imgui_io = &ImGui::GetIO();

    background.updateWithView(render_window.getView());

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
                    render_window.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(render_window.getSize().x, render_window.getSize().y)));
                    background.updateWithView(render_window.getView());
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

                default: break;
                }
            }
        }

        //Updates
        delta = delta_clock.getElapsedTime().asSeconds();

        if (dragging)
        {
            sf::View v = render_window.getView();

            v.move(drag_origin - render_window.mapPixelToCoords(sf::Mouse::getPosition()));

            render_window.setView(v);

            drag_origin = render_window.mapPixelToCoords(sf::Mouse::getPosition());

            background.updateWithView(v);
        }

        ImGui::SFML::Update(render_window, delta_clock.restart());

        ImGui::Begin("Box");
            ImGui::Button("Button");
        ImGui::End();

        //ImGui::Beg

        //Drawing
        render_window.clear();

        render_window.draw(background);
        render_window.draw(test);

        ImGui::SFML::Render(render_window);

        render_window.display();
    }
}

void Program::end()
{
    ImGui::SFML::Shutdown();
}
