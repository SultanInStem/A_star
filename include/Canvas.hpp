#include "Cell.hpp"
#include <SFML/Graphics.hpp>
#ifndef CANVAS_HPP 
#define CANVAS_HPP 

class Canvas{
    private: 
        sf::RenderWindow window; 
        sf::Clock clock;

        void update(float dt);
        void handleEvents(); 
        void render();

        static const int ARRAY_SIZE = 50; // provide multiples of 10 please
        Cell cells[ARRAY_SIZE][ARRAY_SIZE];



    public: 
        Canvas(int size = 1000); 
        ~Canvas();
        void run(); 
};

#endif 