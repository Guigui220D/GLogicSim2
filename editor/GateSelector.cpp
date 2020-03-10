#include "GateSelector.h"

#include "imgui.h"

#include "Gate.h"

#include "../Program.h"

#include <cmath>

GateSelector::GateSelector(Program& program) :
    Selector(program)
{
    //ctor
}

GateSelector::~GateSelector()
{
    //dtor
}

void GateSelector::update(float delta)
{
    if (!moving_gate)
        return;

    if (std::shared_ptr<Gate> spt = selected_gate.lock())
    {
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
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mpos = program.render_window.mapPixelToCoords(sf::Mouse::getPosition(program.render_window));

        bool clicked = false;
        for (std::shared_ptr<Gate>& gate : program.gates)
        {
            if (gate->takeClick(mpos))
            {
                deselect();
                selected_gate = gate;
                gate->selected = true;
                clicked = true;
                break;
            }
        }
        return clicked;
    }
    return false;
}

void GateSelector::deselect()
{
    if (std::shared_ptr<Gate> spt = selected_gate.lock())
        spt->selected = false;
    moving_gate = false;
    selected_gate.reset();
}

void GateSelector::doImGui()
{
    if (std::shared_ptr<Gate> spt = selected_gate.lock())
    {
        spt->makeImGuiInterface();

        ImGui::Separator();

        ImGui::SliderInt("Angle", &spt->rotation, -4, 4, "");
        ImGui::SliderInt("Size", &spt->size, 1, 3, "");

        if (ImGui::Button("Delete"))
        {
            //TODO
            deselect();
        }

        if (ImGui::Button("Deselect"))
            deselect();

        if (ImGui::Button("Move"))
            moving_gate = true;
    }
    else
        ImGui::Text("Click on a gate to select it");
}

void GateSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {}

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
