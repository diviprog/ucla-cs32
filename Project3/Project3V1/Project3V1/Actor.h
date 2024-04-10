#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject {
  public:
    Actor(int imageID, int startX, int startY, StudentWorld* world);
  private:
    StudentWorld* m_world;
};


class Wall : public Actor {
  public:
    Wall(int startX, int startY, StudentWorld* world);
  private:
};

class Avatar : public Actor {
  public:
    Avatar(int startX, int startY, StudentWorld* world);
  private:
    int m_hp;
    int m_peas;
};

#endif // ACTOR_H_
