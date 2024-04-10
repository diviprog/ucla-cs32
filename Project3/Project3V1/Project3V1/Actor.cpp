//
//  Actor.cpp
//  Project3V1
//
//  Created by Devansh Mishra on 19/02/24.
//

#include "Actor.h"
#include "StudentWorld.h"

////////////////////////////////////////////
/// Actor implementation
////////////////////////////////////////////

Actor::Actor(int imageID, int startX, int startY, StudentWorld* world) : GraphObject(imageID, startX, startY) {};

////////////////////////////////////////////
/// Wall implementation
////////////////////////////////////////////

Wall::Wall(int imageID, int startX, int startY, StudentWorld* world) : Actor(IID_WALL, startX, startY, world) {};

////////////////////////////////////////////
/// Avatar Implementation
////////////////////////////////////////////

Avatar::Avatar(int imageID, int startX, int startY, StudentWorld* world) : Actor(IID_PLAYER, startX, startY, world) {};


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
