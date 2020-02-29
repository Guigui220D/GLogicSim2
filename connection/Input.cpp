#include "Input.h"

#include "Gate.h"

Input::Input(Gate& gate, sf::Vector2f relative_pos) :
    Connector(gate, relative_pos)
{}

Input::~Input()
{}
