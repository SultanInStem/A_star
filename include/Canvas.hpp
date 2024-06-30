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

        static const int MATRIX_SIZE = 50; // provide multiples of 10 please
        Cell cells[MATRIX_SIZE][MATRIX_SIZE];



    public: 
        Canvas(int size = 1000); 
        ~Canvas();
        void run(); 
};

#endif 