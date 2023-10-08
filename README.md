# What is this?
### Originally an assignment for an Algo&DS course, I decided to use this assignment to learn heuristics in order to grasp a greater understanding of searches and the benefits of using different methods to solve the same problem. Other things learned include using recursive and non-recursive methods in order to solve the problem.
#### This problem is asking for a matrix of positive integers passed through a file and by passing in a positive integer, we are able to solve the problem by finding a path to summing that number.

## How to use this IntMatrixPathfinder:
#### Firstly, compile the cpp code and run the program as you would run any other compiled executable.
#### Next, the program will ask for a filename. Input a filename as instructed.
###### Each file contains a row count, column count, and the matrix.
#### The program will now ask you to find a number. Enter a number you want to find.
#### You will now either be returned a PathMap to that solution, or the program will tell you that no solution was found.

#### mat.cpp
This is just a starter file that I used so I don't have to restart from scratch every time I create a new algorithm. It provides all the functions except the functions used to solve the solution.

## What are the different solutions to this problem that you have created?

#### matrix.cpp
matrix.cpp is the original solution I created when completing the assignment. As the assignment required recursion in the solution, this pathfinder solves the problem recursively by calling on itself to find a viable solution.
This program uses a Backtracking Depth-First-Search Algorithm, and prioritizes searching in the order of up->down->left->right.

##### From here on out, the majority of solutions should include little to no recursions, as in order to keep the program optimized and prevent stack overflows, pathfinders are best solved using data structures.

#### matrix\_no\_recursion\_long.cpp
matrix\_no\_recursion\_long.cpp is a solution I made when blueprinting ideas of how to solve this pathfinder without using recursion. This pathfinder uses nodes in order to track the current state of the algorithm, which allows easy tracking of data.
This program uses a Backtracking Depth-First-Search Algorithm, and prioritizes searching in the order of up->down->left->right.

#### matrix\_no\_recursion.cpp
matrix\_no\_recursion.cpp is a newer version of matrix\_no\_recursion\_long.cpp, where I reduced the number of lines by nesting two for loops for moving the head, and optimizing creations of nodes by using helper functions. There are other practices used to shorten code, such as an array of references, which are dereferenced to access the data.
This program uses a Backtracking Depth-First-Search Algorithm, and prioritizes searching in the order of up->down->left->right.

##### Now that the basic DFS solutions using basic data structures are out of the way, things can get a lot more interesting. Majority of these solutions involve different heuristic ideologies and data structures in order to solve the problem.

### Depth First Search Algorithms
##### DFS Algorithms will always start at 0,0 as the default, and will iterate from there. These algorithms are built to be efficient and fast at finding solutions. However, it is near impossible for them to find the most optimal solution.

#### matrix\_standard\_dfs.cpp
matrix\_standard\_dfs.cpp runs the same type of algorithm as all the previous pathfinders. It uses std::stack as its primary data type for storing the nodes that need to be traversed.

#### matrix\_greedy\_dfs.cpp
matrix\_greedy\_dfs.cpp builds upon the same functions as standard DFS, but uses the greedy paradigm in order to attempt to optimize the algorithm.

### Breadth First Search Algorithms
##### BFS Algorithms will count ALL the possible starting points and iterate from there. BFS is quite slow at finding solutions, but often guarantees the most optimal solution to be found.

#### matrix\_standard\_bfs.cpp
matrix\_standard\_bfs.cpp

#### matrix\_greedy\_bfs.cpp
matrix\_greedy\_bfs.cpp


//work in progress, may not happen

#### matrix\_simulated\_annealing\_bfs.cpp

### A* Search

#### matrix\_aStar.cpp

### Uniform Cost Search

#### matrix\_uniform\_cost.cpp

### Hill Climbing Search

#### matrix\_hill\_climbing.cpp

