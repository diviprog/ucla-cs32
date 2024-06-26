#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath)
     : GameWorld(assetPath)
    {
    }
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    virtual ~StudentWorld();

    void addActorToVector(Actor* a);
    
    // bot functions
    bool isBotOnLocation(int x, int y);
    Actor* isThiefBotOnGoodie(ThiefBot* kbot);
    bool shouldBotFirePea(Bot* bot);
    bool canBotMove(int x, int y);
    
    bool isPlayerAboveExit(Exit* e);
    
    bool collectedAllCrystals();
    
    bool isPlayerAbovePickup(PickupableItem* p);
    
    bool canPeaMove(int x, int y, Actor* owner);
    
    bool isMarbleAbovePit(Pit* h);
    
    bool canMarbleMove(int x, int y);
    
    bool canPlayerMove(int x, int y);
    
private:
    std::vector<Actor*> m_actors;
    Player *m_player;
    int m_bonus = 1000;
    int m_totalCrystals = 0;
    int m_collectedCrystals = 0;
    bool m_levelComplete = false;
    
    void updateDisplayText();
    void removeDeadActors();
    Actor* isActorOnLocation(int x, int y);

};

#endif // STUDENTWORLD_H_

