#include <iostream>
#include "Canvas.hpp"
#include "Cell.hpp"
#include <cmath>
#include <random> 
#include <thread>
using std::cout;
bool isPathFound = false; 


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
    float pivot = arr[high]->heuristic; 
    int i = low - 1; 

    for (int j = low; j < high; ++j) {
        if (arr[j]->heuristic < pivot) {
            ++i; 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(std::vector<Cell*>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Partitioning index

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

float getHeuristic(Cell*& a, Cell*& b){
    // diagonal distance heuristic 
    float dx = abs(a->getPos().x - b->getPos().x); 
    float dy = abs(a->getPos().y - b->getPos().y); 
    float h =  1 * (dx + dy) + (sqrt(2) - 2 * 1) * std::min(dx, dy);
    return h; 
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
            if(random < 3.5){
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
    nodeEnd->isWall = false;


    nodeStart = &cells[0][0];  

    nodeStart->cost = 0; 
    nodeStart->heuristic = getHeuristic(nodeStart, nodeEnd); 

    openSet.push_back(nodeStart);

    sf::ContextSettings settings; 
    settings.antialiasingLevel = 5;
    window.create(sf::VideoMode(size, size), "A_star",  sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(60);  
}

Canvas::~Canvas(){};



void Canvas::resetCells(){
    isPathFound = false; 
    openSet.clear(); 
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            cells[i][j].reset();
        }
    }
}
void Canvas::run(){
    while(window.isOpen()){
        handleEvents(); 
        update(); 
        render(); 
    }
}

void Canvas::update(){
    if(!openSet.empty()){ 
        // This is a main loop of A* 
        // openSet serves a purpose of a heap  
        // so we access only 0 index as a current node
        Cell* currentNode = openSet[0]; 
        std::vector<Cell*> neighbors = currentNode->getNeighbors(); 
        for(Cell* item : neighbors){
            // if we reached the end node 
            // we must must terminate tho it might not be the best path 
            // the optimization is worth it and this path is good enough 
            if(item == nodeEnd){
                item->setParent(currentNode);
                openSet.clear(); 
                isPathFound = true;
                return;
            } 
            // we do not check nodes that are walls 
            if(item->isWall) continue;
            float distanceBetweenNodes = getDistance(currentNode->getPos(), item->getPos());

            // main condition of the A* 
            if(currentNode->cost < item->cost + distanceBetweenNodes){
                // update the neighbor 
                item->setParent(currentNode);
                item->cost = currentNode->cost + distanceBetweenNodes;
                item->heuristic = getHeuristic(item, nodeEnd);

            }
            // mark visited notes so
            // we don't process them again 
            if(!item->isVisited){
                item->isVisited = true;
                item->setColor(sf::Color(128,128,128));
                openSet.push_back(item); 
            }
        }
        currentNode->isVisited = true; 
        currentNode->setColor(sf::Color(128,128,128));
        // pop the current node from the heap 
        // and sort the heap based on heauristics 
        openSet.erase(openSet.begin());
        quickSort(openSet, 0, openSet.size() - 1);
    }else{
        if(isPathFound){
            Cell* ptr = nodeEnd->getParent();
            while(ptr != nullptr && ptr != nodeStart){
                ptr->setColor(sf::Color::Blue);
                ptr = ptr->getParent(); 
            }
        }
    }
}

void Canvas::handleEvents(){
    sf::Event event; 
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close(); 
        }
        if(event.type == sf::Event::MouseButtonPressed){
            float mouseX = sf::Mouse::getPosition(window).x;
            float mouseY = sf::Mouse::getPosition(window).y;
            float cellWidth = window.getSize().x / MATRIX_SIZE;
            float cellHeight = window.getSize().y / MATRIX_SIZE; 
            int col = (int) mouseX / cellWidth; 
            int row = (int) mouseY / cellHeight;
            if(cells[row][col].isWall) continue;
            switch (event.mouseButton.button){
                case sf::Mouse::Left: 
                    // choose start node 
                    resetCells();
                    nodeStart = &cells[row][col];
                    nodeStart->cost = 0; 
                    nodeStart->heuristic = getHeuristic(nodeStart, nodeEnd);  
                    openSet.push_back(nodeStart);
                break; 
                case sf::Mouse::Right: 
                    // choose end node 
                    resetCells(); 
                    nodeEnd = &cells[row][col];  
                    nodeStart->cost = 0; 
                    nodeStart->heuristic = getHeuristic(nodeStart, nodeEnd);
                    openSet.push_back(nodeStart); 
                break;
                default: 
                break;
            }
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