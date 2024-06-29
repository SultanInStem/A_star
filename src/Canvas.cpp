#include "Canvas.hpp"
#include "Cell.hpp"
#include <cmath>

Canvas::Canvas(int size){
    size = (int)(floor(size / 10) * 10);

    const float cellWidth = size / ARRAY_SIZE;
    const float cellHeight = size / ARRAY_SIZE;

    for(int col = 0; col < ARRAY_SIZE; col++){
        for(int row = 0; row < ARRAY_SIZE; row++){
            float x = col * cellWidth; 
            float y = row * cellHeight;    
            cells[col][row].setPosition(sf::Vector2f(x, y));
            cells[col][row].setSize(sf::Vector2f(cellWidth, cellHeight));
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

    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            cells[i][j].show(window);
        }
    }

    window.display();
}