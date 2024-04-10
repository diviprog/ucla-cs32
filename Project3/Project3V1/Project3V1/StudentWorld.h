//
//  StudentWorld.h
//  Project3V1
//
//  Created by Devansh Mishra on 19/02/24.
//

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Avatar;
class Wall;

class StudentWorld : public GameWorld
{
  public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    StudentWorld();
    virtual ~StudentWorld();

  private:
    Avatar* m_avatar;
    int m_numWalls;
    Wall* m_walls[100];
};

#endif // STUDENTWORLD_H_
