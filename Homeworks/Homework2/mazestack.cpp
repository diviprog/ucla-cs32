//
//  mazestack.cpp
//  Homework2V2
//
//  Created by Devansh Mishra on 06/02/24.
//

#include <string>
#include <stack>
#include <iostream>
using namespace std;

class Coord
{
  public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    stack<Coord> coordStack;
    Coord startingCoord(sr,sc);
    maze[startingCoord.r()][startingCoord.c()] = '/'; // this coordinate has been encountered
    coordStack.push(startingCoord);
    
    while(!coordStack.empty()) {
        Coord currentCoord = coordStack.top();
        coordStack.pop();
        if (currentCoord.r() == er && currentCoord.c() == ec) return true; // if current position is same as desired final position, return true
        
        
        if (maze[currentCoord.r()-1][currentCoord.c()] == '.') {
            Coord aCoord(currentCoord.r()-1, currentCoord.c());
            coordStack.push(aCoord);
            maze[aCoord.r()][aCoord.c()] = '/';
        }
        if (maze[currentCoord.r()][currentCoord.c()-1] == '.') {
            Coord aCoord(currentCoord.r(), currentCoord.c()-1);
            coordStack.push(aCoord);
            maze[aCoord.r()][aCoord.c()] = '/';
        }
        if (maze[currentCoord.r()+1][currentCoord.c()] == '.') {
            Coord aCoord(currentCoord.r()+1, currentCoord.c());
            coordStack.push(aCoord);
            maze[aCoord.r()][aCoord.c()] = '/';
        }
        if (maze[currentCoord.r()][currentCoord.c()+1] == '.') {
            Coord aCoord(currentCoord.r(), currentCoord.c()+1);
            coordStack.push(aCoord);
            maze[aCoord.r()][aCoord.c()] = '/';
        }
    }
    return false;
}
