#include "Cell.hpp"

Cell::Cell(float x, float y){
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Black); 
    rect.setOutlineThickness(2);
}

Cell::~Cell(){
}