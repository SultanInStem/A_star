#include <SFML/Graphics.hpp>
#ifndef CELL_HPP 
#define CELL_HPP 

class Cell{
    private: 
        sf::RectangleShape rect; 
    public: 
        Cell(float x=0, float y=0); 
        ~Cell(); 
};

#endif 