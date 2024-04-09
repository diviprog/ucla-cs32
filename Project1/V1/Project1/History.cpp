//
//  History.cpp
//  Project1
//
//  Created by Devansh Mishra on 11/01/24.
//

#include <stdio.h>
#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols){
    for (int i = 0; i < m_rows; i++){
        for (int j = 0; j < m_cols; j++){
            grid[i][j] = '.';
        }
    }
}

bool History::record(int r, int c) {
    if (r > m_rows || c > m_cols || r < 1 || c < 1) {
        return false;
    }
    
    if (grid[r-1][c-1] == '.'){
        grid[r-1][c-1] = 'A';
    }
    else if (grid[r-1][c-1] != 'Z') {
        grid[r-1][c-1]++;
    }
    return true;
}

void History::display() {
    clearScreen();
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
