#include <iostream> //c in/out stream
#include <fstream> //file in/out stream
#include <string> //to allow the use of std::string functions
#include <vector> //to allow the use of vector functions

/* 
 * Changes from the recursive version include
 * 1. using a stack to store the nodes
 * 2. using a while loop instead of recursion
 * 3. using a struct to create a node
*/

/**
 * @brief Node struct for the backtracking algorithm in while loop
 * 
 */
struct Node{
    int row;
    int col;
    int sum;
    bool first;
    char dir;
    bool up;
    bool down;
    bool left;
    bool right;
    Node *next;
    Node *prev;
};

/**
 * @brief Converts a text file into a 2d matrix using vectors
 * 
 * @param fName - the file name
 * @return std::vector<std::vector<int> > mat - a 2d matrix
 */
std::vector<std::vector<int> > FileToMatrix( std::string fName ) {
    int n; //declare a variable to be used by file stream
    std::ifstream fin; // fin stands for file in; this is the file that will be opened
    fin.open( fName ); //open file and set variable fin to the opened file
    std::vector<std::vector<int> > mat; //declare empty matrix
    if ( fin.is_open() ) {
        int h = -1; //default height of the matrix
        int l = -1; //default length of the matrix
        //defaults are values that are not to appear and are set as placeholder values
        int k = 0; //current row of matrix being accessed
        while( !fin.eof() ) {
            if ( h == -1 || l == -1 ) { //check if height and length are set
                fin >> h >> l; //set height and length
                mat.push_back(std::vector<int>()); // create an empty row
            } //if
            else if ( mat[k].size() == l ) { // check if row length is reached
                if (k+1 < h){ // if next counter is still less than the declared height
                    k++;
                    mat.push_back(std::vector<int>()); //new empty row
                } else { //max height reached
                    return mat;
                }
            } //else if
            else { //height and length are set and max row length is not reached
                fin >> n; //set new integer
                mat[k].push_back( n ); //push integer into the matrix
            } //else
        } //while
    } //if
    return mat;
} //FileToMatrix

/**
 * @brief prints the matrix
 * 
 * @param mat 
 */
void PrintMatrix( std::vector<std::vector<int> > mat ) {
    for ( int i = 0; i < mat.size(); i++ ) { // iterate over rows
        for ( int j = 0; j < mat[i].size(); j++ ) { //iterate over elements in row
            std::cout << mat[i][j] << " "; // print element
        } //for j
        std::cout << std::endl; //start new line
    } //for i
} //PrintMatrix

/**
 * @brief validate the map and print the map if valid
 * 
 * @param map 
 * @return true - if the map is valid
 * @return false - if the map is not valid
 */
bool ValidateAndPrintMap( std::vector<std::vector<char> > map ) {
    std::vector<std::vector<char> > defVec; //a vector with unused character to declare false
    defVec.push_back(std::vector<char>());
    defVec[0].push_back('F');
    if ( map == defVec ) { //if map is invalid
        std::cout << "Integer not found!" << std::endl; //start new line
        return false;
    } //if
    else {
        for ( int i = 0; i < map.size(); i++ ) { // iterate over rows
            for ( int j = 0; j < map[i].size(); j++ ) { //iterate over elements in row
                std::cout << map[i][j] << " "; // print element
            } //for j
            std::cout << std::endl; //start new line
        } //for i
        return true;
    } //else
    return false;
} //ValidateAndPrintMap

/**
 * @brief Create an empty path map with dimensions of matrix
 * 
 * @param mat 
 * @return std::vector<std::vector<char> > - the empty path map
 */
std::vector<std::vector<char> > CreateEmptyMatrixMap( std::vector<std::vector<int> > mat ) {
    std::vector<std::vector<char> > pathMap; //set pathMap matrix
    for ( int i = 0; i < mat.size(); i++ ) { // iterate over rows
        pathMap.push_back( std::vector<char>() ); //push back a row with one empty
        pathMap[pathMap.size() - 1].push_back('-');
        for ( int j = 1; j < mat[i].size(); j++ ) { //iterate over elements in row (starts at 1 because of element above)
            pathMap[i].push_back( '-' ); //push back one empty element
        } //for j
    } //for i
    return pathMap;
} //CreateEmptyMatrixMap


/**
 * @brief Check if the coordinates are within the list but not last.
 * 
 * @param head 
 * @param row 
 * @param col 
 * @return true 
 * @return false 
 */
bool findNodeNotLast (Node *head, int row, int col) {
    Node *temp = head;
    while (temp->next != nullptr) {
        if (temp->row == row && temp->col == col) {
            return true;
        }
        temp = temp->next;
    }
    return false;
} //findNodeNotLast

/**
 * @brief Check if the coordinates are within the list.
 * 
 * @param row 
 * @param col 
 * @param mat 
 * @return true 
 * @return false 
 */
bool inBounds(int row, int col, std::vector<std::vector<int> > mat) {
    if (row < 0 || col < 0 || row >= mat.size() || col >= mat[row].size()) {
        return false;
    }
    return true;
} //inBounds

/**
 * @brief Find the provided integer by using the sum of the matrix elements passed over.
 * 
 * @param mat the matrix
 * @param pathMap the path map
 * @param n the integer being searched for
 * @param row the current row index
 * @param col the current column index
 * @param sum the running sum
 * @param first determines if it is the first element of the current search
 * @return std::vector<std::vector<char> > - the path map
 */
std::vector<std::vector<char> > GetIntByMatrixSum ( std::vector<std::vector<int> > mat, std::vector<std::vector<char> > pathMap, int n ) {
    std::vector<std::vector<char> > defVec; //a vector with unused character to declare false
    defVec.push_back(std::vector<char>());
    defVec[0].push_back('F');
    Node *head = new Node;
    head->row = 0;
    head->col = 0;
    head->sum = mat[0][0];
    head->first = true;
    head->dir = '*';
    head->up = true;
    head->down = true;
    head->left = true;
    head->right = true;
    head->next = nullptr;
    head->prev = nullptr;
    Node *tail = head;
    while (head != nullptr) {
        if ( !inBounds(tail->row, tail->col, mat) || tail->sum > n || findNodeNotLast(head, tail->row, tail->col)) {
            tail = tail->prev;
            if (tail->first) {
                if(inBounds(head->row, head->col+1, mat)){
                    Node *temp = new Node;
                    temp->row = head->row;
                    temp->col = head->col + 1;
                    temp->sum = mat[temp->row][temp->col];
                    temp->first = true;
                    temp->dir = '*';
                    temp->up = true;
                    temp->down = true;
                    temp->left = true;
                    temp->right = true;
                    temp->next = nullptr;
                    temp->prev = nullptr;
                    delete head;
                    head = temp;
                    tail = head;
                } else if (inBounds(head->row+1, 0, mat)) {
                    Node *temp = new Node;
                    temp->row = head->row + 1;
                    temp->col = 0;
                    temp->sum = mat[temp->row][temp->col];
                    temp->first = true;
                    temp->dir = '*';
                    temp->up = true;
                    temp->down = true;
                    temp->left = true;
                    temp->right = true;
                    temp->next = nullptr;
                    temp->prev = nullptr;
                    delete head;
                    head = temp;
                    tail = head;
                } else {
                    break;
                }
            }
            delete tail->next;
            tail->next = nullptr;
        } 
        else if (tail->sum == n) {
            while (head != nullptr) {
                pathMap[head->row][head->col] = head->dir;
                head = head->next;
            }
            return pathMap;
        }
        else if (tail->up) {
            tail->up = false;
            if (inBounds(tail->row - 1, tail->col, mat)) {
                Node *temp = new Node;
                temp->row = tail->row - 1;
                temp->col = tail->col;
                temp->sum = tail->sum + mat[temp->row][temp->col];
                temp->first = false;
                tail->dir = '^';
                temp->dir = '*';
                temp->up = true;
                temp->down = false;
                temp->left = true;
                temp->right = true;
                temp->next = nullptr;
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }
        } else if (tail->down) {
            tail->down = false;
            if (inBounds(tail->row + 1, tail->col, mat)) {
                Node *temp = new Node;
                temp->row = tail->row + 1;
                temp->col = tail->col;
                temp->sum = tail->sum + mat[temp->row][temp->col];
                temp->first = false;
                tail->dir = 'v';
                temp->dir = '*';
                temp->up = false;
                temp->down = true;
                temp->left = true;
                temp->right = true;
                temp->next = nullptr;
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }
        } else if (tail->left) {
            tail->left = false;
            if(inBounds(tail->row, tail->col - 1, mat)){
                Node *temp = new Node;
                temp->row = tail->row;
                temp->col = tail->col - 1;
                temp->sum = tail->sum + mat[temp->row][temp->col];
                temp->first = false;
                tail->dir = '<';
                temp->dir = '*';
                temp->up = true;
                temp->down = true;
                temp->left = true;
                temp->right = false;
                temp->next = nullptr;
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }
        } else if (tail->right) {
            tail->right = false;
            if(inBounds(tail->row, tail->col + 1, mat)){
                Node *temp = new Node;
                temp->row = tail->row;
                temp->col = tail->col + 1;
                temp->sum = tail->sum + mat[temp->row][temp->col];
                temp->first = false;
                tail->dir = '>';
                temp->dir = '*';
                temp->up = true;
                temp->down = true;
                temp->left = false;
                temp->right = true;
                temp->next = nullptr;
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }
        } else if (tail->first) {
            if(inBounds(head->row, head->col+1, mat)){
                Node *temp = new Node;
                temp->row = head->row;
                temp->col = head->col + 1;
                temp->sum = mat[temp->row][temp->col];
                temp->first = true;
                temp->dir = '*';
                temp->up = true;
                temp->down = true;
                temp->left = true;
                temp->right = true;
                temp->next = nullptr;
                temp->prev = nullptr;
                delete head;
                head = temp;
                tail = head;
            } else if (inBounds(head->row+1, 0, mat)) {
                Node *temp = new Node;
                temp->row = head->row + 1;
                temp->col = 0;
                temp->sum = mat[temp->row][temp->col];
                temp->first = true;
                temp->dir = '*';
                temp->up = true;
                temp->down = true;
                temp->left = true;
                temp->right = true;
                temp->next = nullptr;
                temp->prev = nullptr;
                delete head;
                head = temp;
                tail = head;
            } else {
                break;
            }
        } else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
    } //while
    return defVec;
} //GetIntByMatrixSum

/**
 * @brief main method
 * 
 * @return int
 */
int main() {
    std::string fName; //declare var - fName is the file name of the matrix file
    std::cout << "Please enter the name of a file below. " << std::endl; //get file name
    std::cin >> fName; //set file name

    std::vector<std::vector<int> > mat = FileToMatrix( fName ); //get matrix from file name
    while (mat.empty()) { //checks if the matrix is empty and forces a new file if it is
        std::cout << "That filename was invalid! Please try a different name." << std::endl; //get file name
        std::cin >> fName; //set file name

        mat = FileToMatrix( fName ); //get matrix from file name
    }
    PrintMatrix( mat ); //print matrix
    std::vector<std::vector<char> > pathMap = CreateEmptyMatrixMap( mat );

    int n; //declare var - n is the number being searched for
    std::cout << "-----------------------------------------------\nPlease enter the integer you are looking for. " << std::endl; //get n
    std::cin >> n; //get n

    pathMap = GetIntByMatrixSum( mat, pathMap, n ); //get pathMap
    bool isFound = ValidateAndPrintMap( pathMap ); //check if pathMap is found and print it

    std::string press; //declare var
    std::cout << "Enter anything to exit the file. " << std::endl; //get press
    std::cin >> press; //set press

    return 0; //return successful exit
} //main