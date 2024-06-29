#include <SFML/Graphics.hpp>
#ifndef CELL_HPP 
#define CELL_HPP 

class Cell{
    private: 
        sf::RectangleShape rect; 
        float isWall = false;
    public: 
        Cell(float x=0, float y=0); 
        ~Cell(); 
        void setPosition(sf::Vector2f pos){
            rect.setPosition(pos);
        }
        void setSize(sf::Vector2f size){
            rect.setSize(size);
        }
        void show(sf::RenderWindow& window){
            window.draw(rect);
        }
};

#endif 