#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#include "GameConstants.h"
#include <vector>
class StudentWorld;

// ACTOR
class Actor: public GraphObject{
    
public:
    Actor(int startX, int startY, StudentWorld* world, int startingDir);
    StudentWorld* getWorld(){
        return m_world;
    }
    virtual void setHealth(int health){}
    virtual int getHealth(){return 0;}
    virtual bool blocksPlayer(){
        return true;
    }
    virtual void gotHurt(){}
    virtual void doSomething() = 0;
    
    virtual bool isCollectable() { return false; }
    virtual bool isBot() {return false; }
    virtual bool isPlayer() {return false; }
    virtual bool isExtraLife() { return false; }
    virtual bool isRestoreHealth() { return false; }
    virtual bool isAmmo() { return false; }
    virtual bool isWall() { return false; }
    virtual bool isMarble() { return false; }
    virtual bool isAlive() { return false; }
    virtual bool isThiefBot() { return false; }
    virtual bool isPea() { return false;}
    virtual bool isRageBot() { return false; }
    virtual bool isFactory() { return false; }
    virtual bool isExit() { return false; }
    virtual bool isCrystal() { return false; }
    virtual bool isMeanThiefBot() { return false; }
    virtual bool isPit() { return false; }
    
private:
    StudentWorld* m_world;
};


// ALIVE
class Alive : public Actor{

public:
    Alive(int startX, int startY, StudentWorld* world, int startingDir);
    void setHealth(int health){
        m_health = health;
    }
    int getHealth(){
        return m_health;
    }
    virtual void doSomething() = 0;
    virtual bool isAlive() { return true; }
    
private:
    int m_health;
};


// PLAYER
class Player : public Alive{
    
public:
    Player(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void gotHurt();
    int getAmmo(){
        return m_ammo;
    }
    void setAmmo(int a){
        m_ammo = a;
    }
    virtual bool isPlayer() { return true; }
    
    
private:
    int m_ammo;
};


// WALL
class Wall : public Actor{
    
public:
    Wall(int startX, int startY, StudentWorld* world);
    virtual void doSomething(){
        
    }
    virtual bool isWall() { return true; }
};


//MARBLE
class Marble : public Alive{
public:
    Marble(int startX, int startY, StudentWorld* world);
    virtual void doSomething(){
        
    }
    virtual void gotHurt(){
        setHealth(getHealth()-2);
    }
    virtual bool isMarble() { return true; }
};


// PEA
class Pea : public Alive{
    
public:
    Pea(int startX, int startY, StudentWorld* world, int startingDir, Actor* owner);
    virtual void doSomething();
    virtual bool blocksPlayer(){
        return false;
    }
    virtual bool isPea() {return true;}
private:
    Actor* m_owner;
};

// HOLE
class Pit : public Alive{
    
public:
    Pit(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual bool isPit() { return true; }
};

// PICKUPABLE ITEM
class PickupableItem : public Alive {
public:
    PickupableItem (int startX, int startY, StudentWorld* world, int scoreVal);
    virtual void doSomething();
    int getScoreValue(){
        return m_scoreValue;
    }
    virtual bool blocksPlayer(){
        return false;
    }
    virtual bool isCollectable() { return true; }
private:
    int m_scoreValue;
};

// JEWEL
class Crystal : public PickupableItem {
public:
    Crystal(int startX, int startY, StudentWorld* world);
    virtual bool isCrystal() { return true; }
};

// Extra Life
class ExtraLife : public PickupableItem {
public:
    ExtraLife(int startX, int startY, StudentWorld* world);
    virtual bool isExtraLife() { return true; }
};

// Restore Health
class RestoreHealth : public PickupableItem {
public:
    RestoreHealth(int startX, int startY, StudentWorld* world);
    virtual bool isRestoreHealth() { return true; }
};

// Ammo
class Ammo : public PickupableItem {
public:
    Ammo(int startX, int startY, StudentWorld* world);
    virtual bool isAmmo() { return true; }
};

// Exit
class Exit : public Actor{
public:
    Exit(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual bool blocksPlayer(){
        return false;
    }
    virtual bool isExit() { return true; }
};

// Bot
class Bot : public Alive{
public:
    Bot(int startX, int startY, StudentWorld* world, int startingDir);
    virtual void gotHurt();
    int getTicks(){
        return m_ticks;
    }
    int getCurrentTick(){
        return m_currentTick;
    }
    void setCurrentTick(int n){
        m_currentTick = n;
    }

    virtual void doSomething() = 0;
    virtual bool isBot() { return true; }
private:
    int m_ticks;
    int m_currentTick;

};


// SnarlBot
class RageBot : public Bot{
public:
    RageBot(int startX, int startY, StudentWorld* world, int startingDir);
    virtual void doSomething();
    virtual bool isRageBot() { return true; }
};


// ThiefBot
class ThiefBot : public Bot{
public:
    ThiefBot(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void gotHurt();
    void dropBackGoodie();
    void move();
    int generateUniqueRandoms(std::vector<int> randDirNumbers);
    
    PickupableItem* getPickedGoodie(){
        return m_pickedGoodie;
    }
    void setPickedGoodie(PickupableItem* goo){
        m_pickedGoodie = goo;
    }
    virtual bool isThiefBot() { return true; }

private:
    int m_distanceBeforeTurning;
    int m_walkedDistance;
    PickupableItem* m_pickedGoodie;
    
};

// Angry Kleptobot
class MeanThiefBot : public ThiefBot{
public:
    MeanThiefBot(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual bool isMeanThiefBot() { return true; }
};

// Robot Factory
class RobotFactory : public Actor{
public:
    RobotFactory(int startX, int startY, StudentWorld* world, int kbotType);
    virtual void doSomething();
    virtual bool isFactory() { return true; }
private:
    int m_botProduced;
};

#endif // ACTOR_H_
