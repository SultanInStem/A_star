#include <iostream> 
#include <SFML/Graphics.hpp>
#ifndef CELL_HPP 
#define CELL_HPP 

class Cell{
    private: 
        sf::RectangleShape rect; 
        Cell* parent = nullptr; 
        std::vector<Cell*> neighbors; 

    public: 
        Cell(float x=0, float y=0); 
        ~Cell(); 
        bool isWall = false;
        bool isVisited = false; 

        float cost = std::numeric_limits<float>::infinity(); // blue
        float heuristic = std::numeric_limits<float>::infinity();  // red
        float f = 0; 
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
        void setParent(Cell*& newParent){
            parent = newParent; 
        }
        void setColor(sf::Color color){
            rect.setFillColor(color);
        }
        void setNeighbors(std::vector<Cell*> cellNeighbors){
            neighbors = cellNeighbors; 
        }
        sf::Vector2f getPos(){
            return rect.getPosition(); 
        }
        float getLength(){
            return rect.getSize().x; 
        }
        std::vector<Cell*> getNeighbors(){
            return neighbors;
        }
        Cell* getParent(){
            return parent; 
        }
};

#endif 