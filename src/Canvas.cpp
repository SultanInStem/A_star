#include "Canvas.hpp"
#include "Cell.hpp"


Canvas::Canvas(int width, int height){



    sf::ContextSettings settings; 
    settings.antialiasingLevel = 5;
    window.create(sf::VideoMode(width, height), "A_star",  sf::Style::Titlebar | sf::Style::Close, settings);
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

    window.display();
}