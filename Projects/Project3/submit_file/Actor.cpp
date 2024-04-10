#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

#include <iostream>
#include <cstdlib>
using namespace std;

// ACTOR
Actor::Actor(int startX, int startY, StudentWorld *world, int startingDir):GraphObject(startX, startY, startingDir), m_world(world)
{
    setVisible(true);
}


//ALIVE
Alive::Alive(int startX, int startY, StudentWorld* world,int startingDir) : Actor(startX, startY, world, startingDir) {}

// PLAYER
Player::Player(int startX, int startY, StudentWorld* world) : Alive(startX, startY, world, right), m_ammo(20) {
    setHealth(20);
    setDirection(right);
}

void Player::doSomething()
{
    if (getHealth() == 0) {
        return;
    }
    else {
        int ch;
        if (getWorld()->getKey(ch)) {
            switch (ch) {
                case KEY_PRESS_ESCAPE:
                    setHealth(0);
                    break;
                    
                case KEY_PRESS_SPACE:
                    if(m_ammo > 0) {
                        Pea *b = new Pea(getX(), getY(), getWorld(), getDirection(), this);
                        getWorld()->addActorToVector(b);
                        m_ammo--;
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                    }
                    break;
                    
                case KEY_PRESS_LEFT:
                    setDirection(left);
                    if(getWorld()->canPlayerMove(getX()-1,getY())) moveTo(getX()-1, getY());
                    break;
                
                case KEY_PRESS_RIGHT:
                    setDirection(right);
                    if(getWorld()->canPlayerMove(getX()+1,getY())) moveTo(getX()+1, getY());
                    break;

                case KEY_PRESS_UP:
                    setDirection(up);
                    if(getWorld()->canPlayerMove(getX(),getY()+1)) moveTo(getX(), getY()+1);
                    break;

                case KEY_PRESS_DOWN:
                    setDirection(down);
                    if(getWorld()->canPlayerMove(getX(),getY()-1)) moveTo(getX(), getY()-1);
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void Player::gotHurt(){

    setHealth(getHealth()-2);
    
    if(getHealth() > 0) {
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
    }
    else {
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
        
};

// WALL
Wall::Wall(int startX, int startY, StudentWorld* world) : Actor(startX, startY, world, none) {}

// Marble
Marble::Marble(int startX, int startY, StudentWorld* world) : Alive(startX, startY, world, right) {
    setHealth(10);
}

// Pea
Pea::Pea(int startX, int startY, StudentWorld* world, int startingDir, Actor* owner) : Alive(startX, startY, world, startingDir) {
    setHealth(1);
    m_owner = owner;
}

void Pea::doSomething()
{
    if (getHealth() == 0) return;
    else {
        getWorld()->canPeaMove(getX(), getY(), m_owner);
        switch (getDirection()) {
            case up:
                if(getWorld()->canPeaMove(getX(), getY()+1, m_owner)){
                    moveTo(getX(), getY()+1);
                }
                else setHealth(0);
                
                break;
                
            case down:
                if(getWorld()->canPeaMove(getX(), getY()-1, m_owner)){
                    moveTo(getX(), getY()-1);
                }
                else setHealth(0);

                break;
                
            case left:
                if(getWorld()->canPeaMove(getX()-1, getY(), m_owner)){
                    moveTo(getX()-1, getY());
                }
                else setHealth(0);

                break;
                
            case right:
                if(getWorld()->canPeaMove(getX()+1, getY(), m_owner)){
                    moveTo(getX()+1, getY());
                }
                else setHealth(0);

                break;
                
            default:
                break;
        }
    }
}

// Pit
Pit::Pit(int startX, int startY, StudentWorld* world) : Alive(startX, startY, world, none)
{
    setHealth(1);
}

void Pit::doSomething()
{
    if(getHealth() == 0) return;
    else{
        if(getWorld()->isMarbleAbovePit(this)){
            setHealth(0);
        }
    }
}

PickupableItem::PickupableItem (int startX, int startY, StudentWorld* world, int scoreVal) : Alive(startX, startY, world, none)
{
    setHealth(1);
    m_scoreValue = scoreVal;
}

void PickupableItem::doSomething()
{
    if(getHealth() == 0) return;
    else{
        if(getWorld()->isPlayerAbovePickup(this)){
            getWorld()->playSound(SOUND_GOT_GOODIE);
            setHealth(0);
        }
    }
}

// Crystal
Crystal::Crystal(int startX, int startY, StudentWorld* world) : PickupableItem (startX, startY, world, 50)
{

}

// Extra Life
ExtraLife::ExtraLife(int startX, int startY, StudentWorld* world) : PickupableItem (startX, startY, world, 1000)
{

}

// Restore Health
RestoreHealth::RestoreHealth(int startX, int startY, StudentWorld* world) : PickupableItem (startX, startY, world, 500)
{

}

// Ammo
Ammo::Ammo(int startX, int startY, StudentWorld* world) : PickupableItem (startX, startY, world, 100)
{
    
}

// Exit
Exit::Exit(int startX, int startY, StudentWorld* world) : Actor(startX, startY, world, none)
{
    setVisible(false);
}

void Exit::doSomething()
{
    cerr <<getWorld()->collectedAllCrystals() <<endl;;
    if(getWorld()->collectedAllCrystals()){
        if(!isVisible()){
            setVisible(true);
            setVisible(true);
            getWorld()->playSound(SOUND_REVEAL_EXIT);
        }
    }
    
    if(isVisible()){
        if(getWorld()->isPlayerAboveExit(this)){
            getWorld()->playSound(SOUND_FINISHED_LEVEL);
        }
    }
}

// Bot
Bot::Bot(int startX, int startY, StudentWorld* world, int startingDir) : Alive(startX, startY, world, startingDir)
{
    m_currentTick = 1;
    
    m_ticks = (28-getWorld()->getLevel()) / 4;
    if(m_ticks < 3)
        m_ticks = 3;
}

void Bot::gotHurt()
{
    setHealth(getHealth()-2);
    if(getHealth() > 0)
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    else{
        getWorld()->playSound(SOUND_ROBOT_DIE);
    }
}


// RageBot
RageBot::RageBot(int startX, int startY, StudentWorld* world, int startingDir) : Bot(startX, startY, world, startingDir)
{
    setHealth(10);
}

void RageBot::doSomething()
{
    if(getHealth() <= 0) return;
    else if(getCurrentTick() == getTicks()){
        if(getWorld()->shouldBotFirePea(this)){
            Pea *b = new Pea(getX(), getY(), getWorld(), getDirection(), this);
            getWorld()->addActorToVector(b);
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }else{
                switch (getDirection()) {
                    case up:
                        if(getWorld()->canBotMove(getX(), getY()+1))
                            moveTo(getX(), getY()+1);
                        else
                            setDirection(down);
                        break;
                    case down:
                        if(getWorld()->canBotMove(getX(), getY()-1))
                            moveTo(getX(), getY()-1);
                        else
                            setDirection(up);
                        break;
                    case left:
                        if(getWorld()->canBotMove(getX()-1, getY()))
                            moveTo(getX()-1, getY());
                        else
                            setDirection(right);
                        break;
                    case right:
                        if(getWorld()->canBotMove(getX()+1, getY()))
                            moveTo(getX()+1, getY());
                        else
                            setDirection(left);
                        break;
                    default:
                        break;
                }
            
        }
        
        setCurrentTick(1);
    }else{
        setCurrentTick(getCurrentTick()+1);
    }
}


// ThiefBot
ThiefBot::ThiefBot(int startX, int startY, StudentWorld* world) : Bot(startX, startY, world, right)
{
    setHealth(5);
    
    m_walkedDistance = 0;
    m_distanceBeforeTurning = (rand() % 6) + 1;
    m_pickedGoodie = 0;
    
}

void ThiefBot::doSomething()
{
    if(getHealth() <= 0){
        return;
    }else if(getCurrentTick() == getTicks()){
        // does not include Crystals
        Actor* goodie = getWorld()->isThiefBotOnGoodie(this);
        
        //pick up goodie, does not incldue Crystals
        if(goodie != nullptr && m_pickedGoodie == nullptr){
            int random = (rand() % 10) + 1;
            if(random == 1){
                
                if (goodie->isRestoreHealth()) m_pickedGoodie = new RestoreHealth(getX(),getY(),getWorld());
                else if (goodie->isAmmo()) m_pickedGoodie = new Ammo(getX(),getY(),getWorld());
                else if (goodie->isExtraLife()) m_pickedGoodie = new ExtraLife(getX(),getY(),getWorld());
                else if (goodie->isCrystal()) m_pickedGoodie = new Crystal(getX(),getY(),getWorld());
                goodie->setHealth(0);
                getWorld()->playSound(SOUND_ROBOT_MUNCH);
            }else{
                move();
            }
        }else{
            move();
        }

        setCurrentTick(1);
    }else{
        setCurrentTick(getCurrentTick()+1);
    }
    
}

void ThiefBot::gotHurt()
{
    Bot::gotHurt();
    
    if(getHealth() <= 0){
        if(m_pickedGoodie != 0){
            dropBackGoodie();
        }
    }
}

void ThiefBot::dropBackGoodie()
{
    if(m_pickedGoodie->isRestoreHealth()){
        RestoreHealth *droppedGoodie = new RestoreHealth(getX(),getY(),getWorld());
        getWorld()->addActorToVector(droppedGoodie);
    }else if(m_pickedGoodie->isExtraLife()){
        ExtraLife *droppedGoodie = new ExtraLife(getX(),getY(),getWorld());
        getWorld()->addActorToVector(droppedGoodie);
    }else if(m_pickedGoodie->isAmmo()){
        Ammo *droppedGoodie = new Ammo(getX(),getY(),getWorld());
        getWorld()->addActorToVector(droppedGoodie);
    }
}

void ThiefBot::move()
{
    bool foundObstruction = false;
    if(m_walkedDistance != m_distanceBeforeTurning){

        switch (getDirection()) {
            case up:
                if(getWorld()->canBotMove(getX(), getY()+1)){
                    moveTo(getX(), getY()+1);
                    m_walkedDistance++;
                    return;
                } else foundObstruction = true;
                break;
            case down:
                if(getWorld()->canBotMove(getX(), getY()-1)){
                    moveTo(getX(), getY()-1);
                    m_walkedDistance++;
                    return;
                } else foundObstruction = true;
                break;
            case left:
                if(getWorld()->canBotMove(getX()-1, getY())){
                    moveTo(getX()-1, getY());
                    m_walkedDistance++;
                    return;
                } else foundObstruction = true;
                break;
            case right:
                if(getWorld()->canBotMove(getX()+1, getY())){
                    moveTo(getX()+1, getY());
                    m_walkedDistance++;
                    return;
                } else foundObstruction = true;
                break;
            default:
                break;
        }
        
    }
    
    if(m_walkedDistance == m_distanceBeforeTurning || foundObstruction)
    {
        
        m_distanceBeforeTurning = (rand() % 6) + 1;
        m_walkedDistance = 0;
        int randomDirNum = (rand() % 4) + 1;
        std::vector<int> randomVector;
        
        int firstLookedDirNum = randomDirNum;
        bool finallyMoved = false;
        
        for(int check = 0; check < 4; check++){
            
            //up
            if(randomDirNum == 1) {
                if(getWorld()->canBotMove(getX(), getY()+1)){
                    setDirection(up);
                    moveTo(getX(), getY()+1);
                    finallyMoved = true;
                    break;
                } else{
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
            
            // down
            else if(randomDirNum == 2) {
                if(getWorld()->canBotMove(getX(), getY()-1)){
                    setDirection(down);
                    moveTo(getX(), getY()-1);
                    finallyMoved = true;
                    break;
                } else{
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
            
            // left
            else if(randomDirNum == 3){
                if(getWorld()->canBotMove(getX()-1, getY())){
                    setDirection(left);
                    moveTo(getX()-1, getY());
                    finallyMoved = true;
                    break;
                } else{
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
            
            // right
            else if(randomDirNum == 4){
                if(getWorld()->canBotMove(getX()+1, getY())){
                    setDirection(right);
                    moveTo(getX()+1, getY());
                    finallyMoved = true;
                    break;
                } else{
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
        }
        
        
        if(finallyMoved){
            m_walkedDistance++;
        }else{
            switch (firstLookedDirNum) {
                case 1:
                    setDirection(up);
                    break;
                case 2:
                    setDirection(down);
                    break;
                case 3:
                    setDirection(left);
                    break;
                case 4:
                    setDirection(right);
                    break;
                default:
                    break;
            }
        }
        
    } // END SECOND IF

}


int ThiefBot::generateUniqueRandoms(vector<int> randDirNumbers)
{
    if(randDirNumbers.size() == 4){
        return -1;
    }
    
    bool foundARandom = false;
    while (!foundARandom){
        int somethingSimilar = 0;
        int tempRand = (rand() % 4) + 1;
        
        for(int i = 0; i<randDirNumbers.size(); i++){
            if(tempRand == randDirNumbers[i])
                somethingSimilar++;
        }
        
        if(somethingSimilar == 0){
            foundARandom = true;
            return tempRand;
        }
    }
    
    return -1;
}

// Angry ThiefBot
MeanThiefBot::MeanThiefBot(int startX, int startY, StudentWorld* world) : ThiefBot(startX, startY, world)
{
    setHealth(8);
}

void MeanThiefBot::doSomething()
{

    if(getHealth() <= 0){
        return;
    }else if(getCurrentTick() == getTicks()){
        
        // fire Pea
        if(getWorld()->shouldBotFirePea(this)){
            Pea *b = new Pea(getX(), getY(), getWorld(), getDirection(), this);
            getWorld()->addActorToVector(b);
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        
        //pick up goodie, does not include Crystals
        }else if(getWorld()->isThiefBotOnGoodie(this) != nullptr && getPickedGoodie() == 0){
            int random = (rand() % 10) + 1;
            if(random == 1){
                Actor* goodie = getWorld()->isThiefBotOnGoodie(this);
                if (goodie->isRestoreHealth()) setPickedGoodie(new RestoreHealth(getX(),getY(),getWorld()));
                else if (goodie->isAmmo()) setPickedGoodie(new Ammo(getX(),getY(),getWorld()));
                else if (goodie->isExtraLife()) setPickedGoodie(new ExtraLife(getX(),getY(),getWorld()));
                else if (goodie->isCrystal()) setPickedGoodie(new Crystal(getX(),getY(),getWorld()));
                getWorld()->isThiefBotOnGoodie(this)->setHealth(0);
                getWorld()->playSound(SOUND_ROBOT_MUNCH);
            }else{
                move();
            }
        }else{
            move();
        }
        
        setCurrentTick(1);
    }else{
        setCurrentTick(getCurrentTick()+1);
    }
    
}

// KBOT Factory
RobotFactory::RobotFactory(int startX, int startY, StudentWorld* world, int botType) : Actor(startX, startY, world, none)
{
    m_botProduced = botType;
}

void RobotFactory::doSomething()
{
    int x = getX();
    int y = getY();
    int bots = 0;

    //look up
    int i = 1;
    while((y-i)>=0 && i<=3){
        if(getWorld()->isBotOnLocation(x, y-i))
        {
            bots++;
        }
        i++;
    }

    //look down
    i = 1;
    while((y+i)<VIEW_HEIGHT && i<=3){
        if(getWorld()->isBotOnLocation(x, y+i))
        {
            bots++;
        }
        i++;
    }

    //look left
    i = 1;
    while((x-i)>=0 && i<=3){
        if(getWorld()->isBotOnLocation(x-i, y))
        {
            bots++;
        }
        i++;
    }


    //look right
    i = 1;
    while((x+i)<VIEW_WIDTH && i<=3){
        if(getWorld()->isBotOnLocation(x+i, y))
        {
            bots++;
        }
        i++;
    }
    

    if(bots < 3 && getWorld()->isBotOnLocation(getX(), getY()) == false){
        int randomNum = (rand() % 50) + 1;
        if(randomNum == 1){
            if(m_botProduced == IID_THIEFBOT){
                ThiefBot *bot = new ThiefBot(getX(), getY(), getWorld());
                getWorld()->addActorToVector(bot);
                getWorld()->playSound(SOUND_ROBOT_BORN);
            }
            else if(m_botProduced == IID_MEAN_THIEFBOT){
                MeanThiefBot *bot = new MeanThiefBot(getX(), getY(), getWorld());
                getWorld()->addActorToVector(bot);
                getWorld()->playSound(SOUND_ROBOT_BORN);
            }
        }
    }
}
