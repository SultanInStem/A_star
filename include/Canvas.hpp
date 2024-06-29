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

        static const int ARRAY_SIZE = 10;
        Cell cells[ARRAY_SIZE][ARRAY_SIZE];


    public: 
        Canvas(int width=512, int height=512); 
        ~Canvas();
        void run(); 
};

#endif 