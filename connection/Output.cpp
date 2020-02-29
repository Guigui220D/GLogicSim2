#include "Output.h"

#include "Gate.h"

Output::Output(Gate& gate, sf::Vector2f relative_pos) :
    Connector(gate, relative_pos)
{}

Output::~Output()
{}
