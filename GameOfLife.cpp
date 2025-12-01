#include <iostream>
#include <vector>
#include <string>
#include <fstream> // allow c++ to read file
#include <thread> // sleep
#include <chrono> // sleep logic

using namespace std; // don't have to type std everytime

vector<vector<bool>> grid; 

void LoadGrid() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j]) cout << "X";
            else cout << ".";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;

}

int ReadGrid(){

    ifstream myfile; // Creates myfile to read files
    myfile.open("grid.txt");
    int expectedWidth = -1; // -1 b/c we haven't seen the first line yet


    // Check if we can open file
    if (myfile.is_open()) {
        string line;

        // loops through all the lines
        while ( getline(myfile, line) ) {
            vector<bool> row;
            // Skip empty rows
            if (line.empty()) continue;

            for (char c : line) { // goes through every letter in the row
                row.push_back(c == 'x'); // put bool value into our each row wrt x or . in the txt file
            }

            // Check if grid has same row size
            if (expectedWidth == -1) {
                expectedWidth = row.size(); // get size of our grid
            } 
            
            else if (row.size() != expectedWidth) {
                cerr << "Error: Grid is uneven! Row " << grid.size() + 1 
                    << " has " << row.size() << " cells, expected " << expectedWidth << "." << endl;
                return 1;
            }

            // All goes well we add row into our grid
            grid.push_back(row);
        }
        
        myfile.close();

        // Error if file is empty
        if (grid.empty()) {
            cerr << "Error: Grid is  empty." << endl;
            return 1;
        }

        return 0;
    }

    // Error if no file found
    else {
        cout << "Error: No file found, please make a \"grid.txt\" file with cells." << endl;
        return 1;
    }
}

int Counter(int cRow, int cCol) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // ignore center grid
            if (i == 0 && j == 0) continue;

            // initialize neightbor cells
            int nRow = cRow+i;
            int nCol = cCol+j;
            
            // check if neighbor is in boundary, when it is out of bound we ignore it
            if(nRow >= 0 && nRow < grid.size() && nCol >= 0 && nCol <grid[0].size()){
                if(grid[nRow][nCol]) (count++);
            }
        }
    }

    return count;
}

void DeadOfAlive() {
    vector<vector<bool>> NextGrid = grid; 

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            int neightborCount = Counter(i,j);
            
            // if condition not met, dead cell
            if (neightborCount < 2 || neightborCount > 3){
                NextGrid[i][j] = false;
            }
            
            // if condition met, alive  cell
            else {
                if (neightborCount == 3){
                    NextGrid[i][j] = true;
                }
            }
        }
    }
    grid = NextGrid;
}

int main() {

    //Read Grid
    if (ReadGrid() != 0) {
        cout << "Error loading grid." << endl;
        return 1; 
    }
    cout << "-----------------" << endl;
    cout << "Start: \n";
    cout << "-----------------" << endl;
    // Load Grid
    LoadGrid();

    // Generate the next Grids
    int t =0;
    int iterations;
    cout << "How many iterations? : ";
    cin >> iterations;

    while (t <= iterations) {
        cout << "\033[2J\033[1;1H"; // keeps terminal visible for every update
        DeadOfAlive();
        cout << "Next Iteration: \n";
        cout << "-----------------" << endl;
        LoadGrid();
        t++;
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    return 0;
}