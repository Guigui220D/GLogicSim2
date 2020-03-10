#include "NoSelector.h"

#include "imgui.h"

NoSelector::NoSelector(Program& program) :
    Selector(program)
{
    //ctor
}

NoSelector::~NoSelector()
{
    //dtor
}

void NoSelector::update(float delta) {}

bool NoSelector::handleEvent(sf::Event& event) { return false; }

void NoSelector::deselect() {}

void NoSelector::doImGui() { ImGui::Text("Not in edition mode"); }

void NoSelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {}

bool NoSelector::selected() const { return false; }

sf::Vector2f NoSelector::getPosition() const {}
