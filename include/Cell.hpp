#include <SFML/Graphics.hpp>
#ifndef CELL_HPP 
#define CELL_HPP 

class Cell{
    private: 
        sf::RectangleShape rect; 
        bool isWall = false;
        bool isVisited = false; 
        float globalGoal;  
        float localGoal; 
        Cell* parent = nullptr; 
        std::vector<Cell*> neighbors;

        
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
        void setIsWall(bool isItWall){
            isWall = isItWall; 
            if(isWall){
                rect.setFillColor(sf::Color::Black);
            }else{
                rect.setFillColor(sf::Color::White);
            }
        }
};

#endif 