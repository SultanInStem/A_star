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

        static const int MATRIX_SIZE = 80; // provide multiples of 10 please
        Cell cells[MATRIX_SIZE][MATRIX_SIZE]; 

        std::vector<Cell*> openSet; 
        Cell* nodeStart; 
        Cell* nodeEnd;

        std::vector<Cell*> findNeighbors(int i, int j){
            std::vector<Cell*> neighbors;
            int di[] = { -1, 1, 0, 0, 1, 1, -1, -1 }; // Change in row
            int dj[] = { 0, 0, 1, -1, 1, -1, 1, -1 }; // Change in column

            // Iterate through each direction
            for (int dir = 0; dir < 8; ++dir) {
                int ni = i + di[dir];
                int nj = j + dj[dir];

                // Check boundaries
                if (ni >= 0 && ni < MATRIX_SIZE && nj >= 0 && nj < MATRIX_SIZE) {
                    neighbors.push_back(&cells[ni][nj]);
                }
            }

            return neighbors;
        }
        void resetCells();

    public: 
        Canvas(int size = 1000); 
        ~Canvas();
        void run(); 
};

#endif 