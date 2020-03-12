#include "GateSelector.h"

#include "imgui.h"

#include "Gate.h"

#include "../Program.h"

#include <cmath>

GateSelector::GateSelector(Program& program) :
    Selector(program),
    selected_marker(50.f)
{
    selected_marker.setOrigin(sf::Vector2f(50.f, 50.f));
    selected_marker.setFillColor(sf::Color::Transparent);
    selected_marker.setOutlineThickness(4.f);
    selected_marker.setOutlineColor(sf::Color::Red);
}

GateSelector::~GateSelector()
{
    //dtor
}

void GateSelector::update(float delta)
{
    if (std::shared_ptr<Gate> spt = selected_gate.lock())
    {
        selected_marker.setPosition(spt->position);
        selected_marker.setRadius(50.f * spt->size);
        selected_marker.setOrigin(sf::Vector2f(50.f * spt->size, 50.f * spt->size));

        if (!moving_gate)
            return;

        if (program.grid_mode)
        {
            sf::Vector2f pos = program.render_window.mapPixelToCoords(sf::Mouse::getPosition(program.render_window));

            pos /= 100.f;
            pos.x = std::round(pos.x);
            pos.y = std::round(pos.y);
            pos *= 100.f;

            spt->position = pos;
        }
        else
            spt->position = program.render_window.mapPixelToCoords(sf::Mouse::getPosition(program.render_window));
    }
}

bool GateSelector::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (!moving_gate)
            {
                sf::Vector2f mpos = program.render_window.mapPixelToCoords(sf::Mouse::getPosition(program.render_window));

                bool clicked = false;
                for (std::shared_ptr<Gate>& gate : program.gates)
                {
                    if (gate->takeClick(mpos))
                    {
                        deselect();
                        selected_gate = gate;
                        clicked = true;
                        break;
                    }
                }
                return clicked;
            }
            else if (selected())
            {
                moving_gate = false;
                return true;
            }

        }
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            if (selected())
            {
                if (moving_gate)
                {
                    moving_gate = false;
                }
                else
                    deselect();
            }
            return true;
        }
    }

    return false;
}

void GateSelector::deselect()
{
    moving_gate = false;
    selected_gate.reset();
}

void GateSelector::doImGui()
{
    if (std::shared_ptr<Gate> spt = selected_gate.lock())
    {
        if (moving_gate)
        {
            ImGui::Text("You are moving this gate.");
            ImGui::Text("Press escape or click again to stop moving it.");
        }
        else
        {
            spt->makeImGuiInterface();

            ImGui::Separator();

            ImGui::SliderInt("Angle", &spt->rotation, -4, 4, "");
            ImGui::SliderInt("Size", &spt->size, 1, 3, "");

            if (ImGui::Button("Delete"))
            {
                spt->remove = true;
                deselect();
            }

            if (ImGui::Button("Deselect"))
                deselect();

            if (ImGui::Button("Move"))
                moving_gate = true;
        }

    }
    else
        ImGui::Text("Click on a gate to select it");
}

void GateSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (selected())
        target.draw(selected_marker);
}

bool GateSelector::selected() const
{
    return (bool)selected_gate.lock();
}

sf::Vector2f GateSelector::getPosition() const
{
    if (std::shared_ptr<Gate> spt = selected_gate.lock())
    {
        return spt->position;
    }
    else return sf::Vector2f();
}
