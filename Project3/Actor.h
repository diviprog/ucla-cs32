#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject {
  public:
    Actor(int imageID, int startX, int startY, StudentWorld* world, int dir = none);
    virtual void doSomething() = 0;
    virtual int type() = 0;
    StudentWorld* getWorld();
    bool isWall();
    virtual void setHealth(int health) {}
    virtual int getHealth() { return 0; }
    virtual bool blocksPlayer() { return true; }
    virtual void getHurt() {};
  private:
    StudentWorld* m_world;
};

class Alive : public Actor{
  public:
    Alive(int imageID, int startX, int startY, StudentWorld* world, int dir = none);
    void setHealth(int health) { m_health = health; }
    int getHealth() { return m_health; }
    virtual void doSomething() = 0;
    virtual int type() = 0;
    void move(int dir);
  private:
    int m_health;
};

class Wall : public Actor {
  public:
    Wall(int startX, int startY, StudentWorld* world);
    virtual void doSomething() {};
    virtual int type() { return IID_WALL; }
};

class Avatar : public Alive {
  public:
    Avatar(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual int type() { return IID_PLAYER; }
    void getHurt();
    void addPeas(int amt);
    int getPeas() { return m_peas; }
  private:
    int m_peas;
};

class Robot : public Alive {
  public:
    Robot(int imageID, int startX, int startY, StudentWorld* world, int dir);
    virtual void getHurt();
    int getTicks() { return m_ticks; }
    int getCurrentTick() { return m_currentTick; }
    void setCurrentTick(int n) { m_currentTick = n; }
    virtual void doSomething() = 0;
    virtual int type() = 0;
private:
    int m_ticks;
    int m_currentTick;
};

class RageBot : public Robot {
  public:
    RageBot(int x, int y, StudentWorld* world, int dir);
    virtual void doSomething();
    virtual int type() { return IID_RAGEBOT; }
};

class ThiefBot : public Robot {
  public:
    ThiefBot(int imageID, int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void getHurt();
    void dropBackGoodie();
    void move();
    int generateUniqueRandoms(std::vector<int> randDirNumbers);
    int getPickedGoodie() { return m_pickedGoodie; }
    void setPickedGoodie(int goo) { m_pickedGoodie = goo; }
    virtual int type() { return IID_THIEFBOT; }
  private:
    int m_distanceBeforeTurning;
    int m_walkedDistance;
    int m_pickedGoodie;
};

class MeanThiefBot : public ThiefBot {
  public:
    MeanThiefBot(int imageID, int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual int type(){ return IID_MEAN_THIEFBOT;}
};

class ThiefBotFactory : public Actor {
  public:
    ThiefBotFactory(int startX, int startY, StudentWorld* world, int tbotType);
    virtual void doSomething();
    virtual int type() { return IID_ROBOT_FACTORY; }
  private:
    int m_tbotToProduce;
};

class Exit : public Actor {
  public:
    Exit(int x, int y, StudentWorld* world);
    virtual void doSomething();
    virtual bool blocksPlayer() { return false; }
    virtual int type() { return IID_EXIT; }
};

class Marble : public Alive {
  public:
    Marble(int startX, int startY, StudentWorld* world);
    virtual void doSomething() {};
    virtual void getHurt() { setHealth(getHealth()-2); }
    virtual int type() { return IID_MARBLE; }
};

class Pit : public Alive {
  public:
    Pit(int x, int y, StudentWorld* world);
    virtual void doSomething();
    virtual int type() { return IID_PIT; }
};

class Pea : public Alive {
  public:
    Pea(int startX, int startY, StudentWorld* world, int dir, Actor* owner);
    virtual void doSomething();
    virtual bool blocksPlayer(){ return false; }
    virtual int type(){ return IID_PEA; }
  private:
    Actor* m_owner;
};

class PickupableItem : public Actor {
  public:
    PickupableItem(int imageID, int x, int y, StudentWorld* world, int scoreVal);
    virtual void doSomething();
    int getScoreValue() { return m_scoreValue; }
    virtual bool blocksPlayer() { return false; }
    virtual int type() = 0;
  private:
    int m_scoreValue;
};

class Crystal : public PickupableItem {
  public:
    Crystal(int x, int y, StudentWorld* world);
    virtual int type() { return IID_CRYSTAL; }
};

class ExtraLifeGoodie : public PickupableItem {
  public:
    ExtraLifeGoodie(int x, int y, StudentWorld* world);
    virtual int type() { return IID_EXTRA_LIFE; }
};

class RestoreHealthGoodie : public PickupableItem {
  public:
    RestoreHealthGoodie(int x, int y, StudentWorld* world);
    virtual int type() { return IID_RESTORE_HEALTH; }
};

class AmmoGoodie : public PickupableItem {
  public:
    AmmoGoodie(int x, int y, StudentWorld* world);
    virtual int type() { return IID_AMMO; }
};

#endif // ACTOR_H_
