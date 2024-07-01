#include <iostream>
#include "Canvas.hpp"
#include "Cell.hpp"
#include <cmath>
#include <random> 
#include <thread>
using std::cout;
bool isPathFound = false; 

void threadFunc(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
}


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
            if(random < 3){
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
    // cout << openSet.size() << "\n";
    // std::thread myThread(threadFunc);
    // myThread.join();
    if(!openSet.empty()){
        std::vector<Cell*> neighbors; 
        neighbors = openSet[0]->getNeighbors(); 
        for(Cell* item : neighbors){
            if(item == nodeEnd){
                item->setParent(openSet[0]);
                openSet.clear(); 
                isPathFound = true;
                return;
            } 
            if(item->isWall) continue;
            float distanceBetweenNodes = getDistance(openSet[0]->getPos(), item->getPos());
            if(openSet[0]->cost < item->cost + distanceBetweenNodes){
                // update the neighbor 
                item->setParent(openSet[0]);
                item->cost = openSet[0]->cost + distanceBetweenNodes;
                item->heuristic = getHeuristic(item, nodeEnd);

            }
            if(!item->isVisited){
                item->isVisited = true;
                item->setColor(sf::Color(128,128,128));
                openSet.push_back(item); 
            }
        }
        openSet[0]->isVisited = true; 
        openSet[0]->setColor(sf::Color(128,128,128));
        openSet.erase(openSet.begin());
        quickSort(openSet, 0, openSet.size() - 1);
    }else{
        // cout << "DONE \n";
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
        if(event.type == sf::Event::KeyPressed){

        }
        if(event.type == sf::Event::MouseButtonPressed){
            cout << "you pressed the button \n";
            switch (event.mouseButton.button){
                case sf::Mouse::Left: 
                // choose start node 
                break; 
                case sf::Mouse::Right: 
                // choose end node 
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