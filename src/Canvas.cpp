#include <iostream>
#include "Canvas.hpp"
#include "Cell.hpp"
#include <cmath>
#include <random> 
using std::cout;
int i = 0; 

float randomFloat(float min, float max){
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    float randomFloat = distribution(gen);
    return randomFloat;
}
void swap(Cell*& a, Cell*& b) {
    Cell* temp = a;
    a = b;
    b = temp;
}
int partition(std::vector<Cell*>& arr, int low, int high) {
    float pivot = arr[high]->heuristic; // Pivot element
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; ++j) {
        if (arr[j]->heuristic < pivot) {
            ++i; // Increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(std::vector<Cell*>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Partitioning index

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

float getHeuristic(Cell& a, Cell& b){
    // diagonal distance heuristic 
    return 0; 
}
float getDistance(const sf::Vector2f& A, const sf::Vector2f& B){
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
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

    // setting up neighbors 
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            cells[i][j].setNeighbors(findNeighbors(i, j));
        }
    } 

    nodeEnd = &cells[MATRIX_SIZE - 1][MATRIX_SIZE - 1]; 
    nodeStart = &cells[0][0];  

    nodeStart->cost = 0; 
    nodeStart->heuristic = getDistance(nodeStart->getPos(), nodeEnd->getPos());



    openSet.push_back(nodeStart);

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
    if(!openSet.empty()){
        // keep evaluating 
        std::vector<Cell*> neighbors;
        
    }else{
        // no solution 
    }
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
            if(&cells[i][j] == nodeStart) cells[i][j].setColor(sf::Color::Green); 
            else if(&cells[i][j] == nodeEnd) cells[i][j].setColor(sf::Color::Red); 
            cells[i][j].show(window); 
        }
    }

    window.display();
}