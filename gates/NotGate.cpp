#include "NotGate.h"

#include "imgui.h"

NotGate::NotGate()
{
    inputs.push_back(std::make_shared<Input>(sf::Vector2f(-50.f, 0)));
    outputs.push_back(std::make_shared<Output>(sf::Vector2f(50.f, 0)));

    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(5.f);
    rect.setSize(sf::Vector2f(70.f, 80.f));
    rect.setOrigin(sf::Vector2f(45.f, 40.f));

    circ.setFillColor(sf::Color::White);
    circ.setOutlineColor(sf::Color::Black);
    circ.setOutlineThickness(5.f);
    circ.setRadius(5.f);
    circ.setOrigin(sf::Vector2f(5.f, 5.f));
    circ.setPosition(sf::Vector2f(40.f, 0.f));

    icon.setFillColor(sf::Color::Black);
    icon.setCharacterSize(200.f);
    icon.setScale(sf::Vector2f(.30f, .30f));
    icon.setString("1");
    icon.setFont(Gate::icon_font);
    icon.setPosition(sf::Vector2f(-25.f, -35.f));
    icon.setOrigin(sf::Vector2f(icon.getGlobalBounds().width / 2.f, icon.getGlobalBounds().height / 2.f));

    //setRotation(45.f);
}

NotGate::~NotGate()
{
    //dtor
}

void NotGate::update(float delta)
{
    inputs.at(0)->updateState();
    outputs.at(0)->setState(!inputs.at(0)->getState());

    if (selected)
    {
        icon.setOutlineColor(sf::Color::Red);
        icon.setOutlineThickness(5.f);
    }
    else
    {
        icon.setOutlineColor(sf::Color::Black);
        icon.setOutlineThickness(0.f);
    }
}

void NotGate::makeImGuiInterface()
{
    ImGui::Text("This is a not gate");
    ImGui::Button("Button");
}

void NotGate::drawGate(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect, states);
    target.draw(circ, states);
    target.draw(icon, states);
}
