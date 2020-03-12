#include "PortSelector.h"

#include "imgui.h"

#include "Gate.h"

#include "../Program.h"

#include <cmath>

PortSelector::PortSelector(Program& program) :
    Selector(program)
{
    //ctor
}

PortSelector::~PortSelector()
{
    //dtor
}

void PortSelector::update(float delta)
{

}

bool PortSelector::handleEvent(sf::Event& event)
{

    return false;
}

void PortSelector::deselect()
{

}

void PortSelector::doImGui()
{
    if (false)
    {

    }
    else
        ImGui::Text("Click on a connector to select it");
}

void PortSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {}

bool PortSelector::selected() const
{
    return false;
}

sf::Vector2f PortSelector::getPosition() const
{
    return sf::Vector2f();
}
