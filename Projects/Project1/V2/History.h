//
//  History.h
//  V2
//
//  Created by Devansh Mishra on 14/01/24.
//


#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
  private:
    int m_rows;
    int m_cols;
    char m_grid[MAXROWS][MAXCOLS];
};

#endif
