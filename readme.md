# A_Star algorithm 

## Demo 

### Full demo can be seen [here](https://youtu.be/AdAd_ArT5LE)
![](https://github.com/rick-n-shawty/A_star/blob/main/astar.gif)

## Background 
A* (A-Star) algorithm is one of the best path finding algorithms due to its completeness and efficiency. This algorithm was developed in [the Shakey](https://en.wikipedia.org/wiki/Shakey_the_robot) project for a mobile robot that could plan its own actions. A* is used in robotics, artificial intelligence, networks and map applicatios. Compared to [Dijkstra's algorithm](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/), A* is a "smart" algortihm due to its heuristic function. 

## Algorithm Description 
The algorithm relies on two main parameters: g(n) and h(n). g(n) is a cost function, which tells how long is the route from current node to the start node. h(n) is a heauristic function that roughly estimates how long is the route from current node to the goal node. Essentially, g(n) is a function that looks backwards while h(n) is a function that looks forward. We evaluate f(n) = g(n) + h(n) and pick the node with the lowest value of f(n). 

## Getting started on macOS 
- clone the repository 
``` sh
git clone https://github.com/rick-n-shawty/A_star.git
```
- make file 
``` sh
make
```
- run the program 
```sh 
./bin/main
```


## References
https://www.geeksforgeeks.org/a-search-algorithm/ 

https://en.wikipedia.org/wiki/A*_search_algorithm

https://youtu.be/A60q6dcoCjw?si=6jONgjsgPCbUtE45

https://youtu.be/icZj67PTFhc?si=w3FPw0i6ewTu4ILc