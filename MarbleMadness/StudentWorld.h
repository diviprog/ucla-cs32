#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;

class StudentWorld : public GameWorld
{
  public:
    StudentWorld(string assetPath) : GameWorld(assetPath) { levelPath = assetPath; }
    ~StudentWorld() { cleanUp(); }
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    Actor* isActorOnLocation(int x, int y);
    bool canPlayerMove(int x, int y);
    bool canMarbleMove(int x, int y);
    void addActorToVector(Actor* a);
    bool isMarbleAbovePit(Pit* p);
    bool isPlayerAbovePickupableItem(PickupableItem* p);
    bool isPlayerAboveExit(Exit* exit);
    void levelCompleted();
    bool collectedAllCrystals();
    bool canPeaMove(int x, int y, Actor* owner);
    int getBonusPoints();
    bool shouldBotFirePea(Robot* bot);
    bool createPea(int x, int y, Actor* owner);
    bool canBotMove(int x, int y);
    bool isThiefBotOnLocation(int x, int y);
    Actor* isThiefBotOnGoodie(ThiefBot* bot);

  private:
    vector<Actor*> m_actors;
    Avatar* m_player;
    bool m_levelComplete = false;
    string levelPath;
    int m_totalCrystals = 0;
    int m_collectedCrystals = 0;
    int m_bonus = 1000;
    
    void updateDisplayText();
    void removeDeadActors();
};

#endif // STUDENTWORLD_H_
