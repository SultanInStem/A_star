#include <iostream>
#include "Canvas.hpp"
#include "Cell.hpp"
#include <cmath>
#include <random> 
using std::cout;


float randomFloat(float min, float max){
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    float randomFloat = distribution(gen);
    return randomFloat;
}


Canvas::Canvas(int size){
    size = (int)(floor(size / MATRIX_SIZE) * MATRIX_SIZE);

    const float cellWidth = size / MATRIX_SIZE;    
    const float cellHeight = size / MATRIX_SIZE;

    for(int row = 0; row < MATRIX_SIZE; row++){
        for(int col = 0; col < MATRIX_SIZE; col++){
            float x = col * cellWidth; 
            float y = row * cellHeight;    
            cells[row][col].setPosition(sf::Vector2f(x, y));
            cells[row][col].setSize(sf::Vector2f(cellWidth, cellHeight));
            float random = randomFloat(0,10);
            if(random < 2){
                cells[row][col].setIsWall(true);
            }
        }
    }

    sf::ContextSettings settings; 
    settings.antialiasingLevel = 5;
    window.create(sf::VideoMode(size, size), "A_star",  sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(60); 
}

Canvas::~Canvas(){   
}

void Canvas::run(){
    float dt; 
    while(window.isOpen()){
        dt = clock.restart().asSeconds();
        handleEvents(); 
        update(dt); 
        render(); 
    }
}

void Canvas::update(float dt){

}

void Canvas::handleEvents(){
    sf::Event event; 
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close(); 
        }
    }
}

void Canvas::render(){
    window.clear(sf::Color::Black); 

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            cells[i][j].show(window);
        }
    }

    window.display();
}