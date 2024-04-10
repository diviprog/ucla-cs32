#include "Actor.h"
#include "StudentWorld.h"

////////////////////////////////////////////
/// Actor implementation
////////////////////////////////////////////

Actor::Actor(int imageID, int startX, int startY, StudentWorld* world, int direction) : GraphObject(imageID, startX, startY, direction), m_world(world) {
    setVisible(true);
};

StudentWorld* Actor::getWorld() {
    return m_world;
}

////////////////////////////////////////////
/// Wall implementation
////////////////////////////////////////////

Wall::Wall(int startX, int startY, StudentWorld* world) : Actor(IID_WALL, startX, startY, world) {}

////////////////////////////////////////////
/// Alive Implementation
////////////////////////////////////////////

Alive::Alive(int imageID, int startX, int startY, StudentWorld* world, int dir) : Actor(imageID, startX, startY, world, dir) {}

void Alive::move(int dir) {
    int x = getX();
    int y = getY();
    switch(dir) {
        case up:
            moveTo(x, y+1);
            break;
        case down:
            moveTo(x, y-1);
            break;
        case right:
            moveTo(x+1, y);
            break;
        case left:
            moveTo(x-1, y);
            break;
    }
}

////////////////////////////////////////////
/// Avatar Implementation
////////////////////////////////////////////

Avatar::Avatar(int startX, int startY, StudentWorld* world) : Alive(IID_PLAYER, startX, startY, world) {
    setHealth(20);
    m_peas = 20;
    setDirection(right);
};

void Avatar::doSomething() {
    if (getHealth() == 0) return;
    
    int ch;
    if (getWorld()->getKey(ch)) {
        switch (ch) {
            case KEY_PRESS_UP:
                setDirection(up);
                if (getWorld()->canPlayerMove(getX(), getY()+1)) moveTo(getX(), getY()+1);
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                if (getWorld()->canPlayerMove(getX(), getY()-1)) moveTo(getX(), getY()-1);
                break;
            case KEY_PRESS_LEFT:
                setDirection(left);
                if (getWorld()->canPlayerMove(getX()-1, getY())) moveTo(getX()-1, getY());
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if (getWorld()->canPlayerMove(getX()+1, getY())) moveTo(getX()+1, getY());
                break;
            case KEY_PRESS_ESCAPE:
                setHealth(0);
                break;
            case KEY_PRESS_SPACE:
                if(m_peas > 0) {
                    m_peas--;
                    getWorld()->createPea(getX(), getY(), this);
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                }
                break;
            default:
                break;
        }
    }
}

void Avatar::getHurt() {
    setHealth(getHealth()-2);
    
    if (getHealth() <= 0)  {
        getWorld()->playSound(SOUND_PLAYER_DIE);
        setHealth(0);
    }
    getWorld()->playSound(SOUND_PLAYER_IMPACT);
}

void Avatar::addPeas(int amt) {
    m_peas += amt;
}

////////////////////////////////////////////
/// Marble Implementation
////////////////////////////////////////////

Marble::Marble(int startX, int startY, StudentWorld* world) : Alive(IID_MARBLE, startX, startY, world)
{
    setHealth(10);
}

////////////////////////////////////////////
/// Pea Implementation
////////////////////////////////////////////

Pea::Pea(int startX, int startY, StudentWorld* world, int dir, Actor* owner) : Alive(IID_PEA, startX, startY, world), m_owner(owner) {
    setDirection(dir);
    setHealth(1);
}

void Pea::doSomething() {
    if(getHealth() == 0) return;
        else{
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

////////////////////////////////////////////
/// Pit Implementation
////////////////////////////////////////////

Pit::Pit(int x, int y, StudentWorld* world) : Alive(IID_PIT, x, y, world) {
    setHealth(1);
};

void Pit::doSomething() {
    if (getHealth() <= 0) return;
    
    if (getWorld()->isMarbleAbovePit(this)) {
        setHealth(0);
    }
}

/////////////////////////////////////////////////////////
/// PickupableItem Implementation
/////////////////////////////////////////////////////////

PickupableItem::PickupableItem(int imageID, int x, int y, StudentWorld* world, int scoreVal) : Actor(imageID, x, y, world), m_scoreValue(scoreVal) {
    setHealth(1);
}

void PickupableItem::doSomething() {
    if (getHealth() <= 0) return;
    
    if (getWorld()->isPlayerAbovePickupableItem(this)) {
        getWorld()->playSound(SOUND_GOT_GOODIE);
        setHealth(0);
    }
}

/////////////////////////////////////////////////////////
/// Crystal Implementation
/////////////////////////////////////////////////////////

Crystal::Crystal(int x, int y, StudentWorld* world) : PickupableItem(IID_CRYSTAL, x, y, world, 50) {};

/////////////////////////////////////////////////////////
/// ExtraLifeGoodie Implementation
/////////////////////////////////////////////////////////

ExtraLifeGoodie::ExtraLifeGoodie(int x, int y, StudentWorld* world) : PickupableItem(IID_EXTRA_LIFE, x, y, world, 1000) {};

/////////////////////////////////////////////////////////
/// RestoreHealthGoodie Implementation
/////////////////////////////////////////////////////////

RestoreHealthGoodie::RestoreHealthGoodie(int x, int y, StudentWorld* world) : PickupableItem(IID_RESTORE_HEALTH, x, y, world, 500) {};

/////////////////////////////////////////////////////////
/// AmmoGoodie Implementation
/////////////////////////////////////////////////////////

AmmoGoodie::AmmoGoodie(int x, int y, StudentWorld* world) : PickupableItem(IID_AMMO, x, y, world, 100) {};

/////////////////////////////////////////////////////////
/// Exit Implementation
/////////////////////////////////////////////////////////

Exit::Exit(int x, int y, StudentWorld* world) : Actor(IID_EXIT, x, y, world) {
    setVisible(false);
}

void Exit::doSomething() {
    if(getWorld()->collectedAllCrystals()){
        if(!isVisible()){
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

/////////////////////////////////////////////////////////
/// Robot Implementation
/////////////////////////////////////////////////////////

Robot::Robot(int imageID, int x, int y, StudentWorld* world, int dir) : Alive(imageID, x, y, world, dir) {
    m_currentTick = 1;
    
    m_ticks = (28-getWorld()->getLevel())/4;
    if(m_ticks < 3) m_ticks = 3;
}

void Robot::getHurt() {
    setHealth(getHealth()-2);
    if (getHealth() > 0) getWorld()->playSound(SOUND_ROBOT_IMPACT);
    else getWorld()->playSound(SOUND_ROBOT_DIE);
}

/////////////////////////////////////////////////////////
/// RageBot Implementation
/////////////////////////////////////////////////////////

RageBot::RageBot(int x, int y, StudentWorld* world, int dir) : Robot(IID_RAGEBOT, x, y, world, dir) {
    setHealth(10);
}

void RageBot::doSomething(){
    if (getHealth() <= 0) return;
    
    else if (getCurrentTick() == getTicks()) {
        if(getWorld()->shouldBotFirePea(this)) {
            getWorld()->createPea(getX(), getY(), this);
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        else {
            switch (getDirection()) {
                case up:
                    if (getWorld()->canBotMove(getX(), getY()+1)) moveTo(getX(), getY()+1);
                    else setDirection(down);
                    break;
                case down:
                    if (getWorld()->canBotMove(getX(), getY()-1)) moveTo(getX(), getY()-1);
                    else setDirection(up);
                    break;
                case right:
                    if (getWorld()->canBotMove(getX()+1, getY())) moveTo(getX()+1, getY());
                    else setDirection(left);
                    break;
                case left:
                    if (getWorld()->canBotMove(getX()-1, getY())) moveTo(getX()-1, getY());
                    else setDirection(right);
                    break;
                default:
                    break;
            }
        }
        setCurrentTick(1);
    }
    else {
        setCurrentTick(getCurrentTick()+1);
    }
}

/////////////////////////////////////////////////////////
/// ThiefBot Implementation
/////////////////////////////////////////////////////////

ThiefBot::ThiefBot(int imageID, int startX, int startY, StudentWorld* world) : Robot(imageID, startX, startY, world, right)
{
    setHealth(5);
    
    m_walkedDistance = 0;
    m_distanceBeforeTurning = (rand() % 6) + 1;
    m_pickedGoodie = 0;
}

void ThiefBot::doSomething()
{
    if(getHealth() <= 0) return;
    
    else if(getCurrentTick() == getTicks()){
        // does not include jewels
        Actor* goodie = getWorld()->isThiefBotOnGoodie(this);
        
        //pick up goodie, does not incldue jewels
        if (goodie != nullptr && m_pickedGoodie == 0) {
            int random = (rand() % 10) + 1;
            if(random == 1) {
                m_pickedGoodie = goodie->type();
                goodie->setHealth(0);
                getWorld()->playSound(SOUND_ROBOT_MUNCH);
            }
            else {
                move();
            }
        }
        else {
            move();
        }

        setCurrentTick(1);
    }
    else {
        setCurrentTick(getCurrentTick()+1);
    }
}

int ThiefBot::generateUniqueRandoms(vector<int> randDirNumbers) {
    if(randDirNumbers.size() == 4) return -1;
    
    bool foundARandom = false;
    while (!foundARandom){
        int somethingSimilar = 0;
        int tempRand = (rand() % 4) + 1;
        
        for (int i = 0; i<randDirNumbers.size(); i++) {
            if(tempRand == randDirNumbers[i]) somethingSimilar++;
        }
        if (somethingSimilar == 0){
            foundARandom = true;
            return tempRand;
        }
    }
    return -1;
}

void ThiefBot::move()
{
    bool foundObstruction = false;
    if(m_walkedDistance != m_distanceBeforeTurning) {

        switch (getDirection()) {
            case up:
                if(getWorld()->canBotMove(getX(), getY()+1)) {
                    moveTo(getX(), getY()+1);
                    m_walkedDistance++;
                    return;
                }
                else foundObstruction = true;
                break;
            case down:
                if (getWorld()->canBotMove(getX(), getY()-1)) {
                    moveTo(getX(), getY()-1);
                    m_walkedDistance++;
                    return;
                }
                else foundObstruction = true;
                break;
            case left:
                if (getWorld()->canBotMove(getX()-1, getY())) {
                    moveTo(getX()-1, getY());
                    m_walkedDistance++;
                    return;
                } else foundObstruction = true;
                break;
            case right:
                if (getWorld()->canBotMove(getX()+1, getY())) {
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
                if(getWorld()->canBotMove(getX(), getY()+1)) {
                    setDirection(up);
                    moveTo(getX(), getY()+1);
                    finallyMoved = true;
                    break;
                }
                else {
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
            
            // down
            else if (randomDirNum == 2) {
                if (getWorld()->canBotMove(getX(), getY()-1)) {
                    setDirection(down);
                    moveTo(getX(), getY()-1);
                    finallyMoved = true;
                    break;
                }
                else {
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
            
            // left
            else if(randomDirNum == 3) {
                if(getWorld()->canBotMove(getX()-1, getY())){
                    setDirection(left);
                    moveTo(getX()-1, getY());
                    finallyMoved = true;
                    break;
                }
                else{
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
            
            // right
            else if(randomDirNum == 4) {
                if(getWorld()->canBotMove(getX()+1, getY())){
                    setDirection(right);
                    moveTo(getX()+1, getY());
                    finallyMoved = true;
                    break;
                }
                else {
                    randomVector.push_back(randomDirNum);
                    randomDirNum = generateUniqueRandoms(randomVector);
                }
            }
        }
        
        if(finallyMoved) {
            m_walkedDistance++;
        }
        else {
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

void ThiefBot::getHurt() {
    Robot::getHurt();
        
    if(getHealth() <= 0){
        if(m_pickedGoodie != 0){
            dropBackGoodie();
        }
    }
}

void ThiefBot::dropBackGoodie()
{
    if(m_pickedGoodie == IID_RESTORE_HEALTH){
        RestoreHealthGoodie *droppedGoodie = new RestoreHealthGoodie(getX(),getY(),getWorld());
        getWorld()->addActorToVector(droppedGoodie);
    }
    else if(m_pickedGoodie == IID_EXTRA_LIFE){
        ExtraLifeGoodie *droppedGoodie = new ExtraLifeGoodie(getX(),getY(),getWorld());
        getWorld()->addActorToVector(droppedGoodie);
    }
    else if(m_pickedGoodie == IID_AMMO){
        AmmoGoodie *droppedGoodie = new AmmoGoodie(getX(),getY(),getWorld());
        getWorld()->addActorToVector(droppedGoodie);
    }
}

/////////////////////////////////////////////////////////
/// MeanThiefBot Implementation
/////////////////////////////////////////////////////////

MeanThiefBot::MeanThiefBot(int imageID, int startX, int startY, StudentWorld* world) : ThiefBot(imageID, startX, startY, world) {
    setHealth(8);
}

void MeanThiefBot::doSomething() {
    if(getHealth() <= 0) return;
    
    else if(getCurrentTick() == getTicks()){
        
        // fire bullet
        if(getWorld()->shouldBotFirePea(this)){
            Pea *b = new Pea(getX(), getY(), getWorld(), getDirection(), this);
            getWorld()->addActorToVector(b);
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        
        //pick up goodie, does not include jewels
        else if(getWorld()->isThiefBotOnGoodie(this) != nullptr && getPickedGoodie() == 0){
            int random = (rand() % 10) + 1;
            if(random == 1) {
                setPickedGoodie(getWorld()->isThiefBotOnGoodie(this)->type());
                getWorld()->isThiefBotOnGoodie(this)->setHealth(0);
                getWorld()->playSound(SOUND_ROBOT_MUNCH);
            }
            else {
                move();
            }
        }
        else {
            move();
        }
        setCurrentTick(1);
    }
    else {
        setCurrentTick(getCurrentTick()+1);
    }
    
}

/////////////////////////////////////////////////////////
/// ThiefBotFactory Implementation
/////////////////////////////////////////////////////////

ThiefBotFactory::ThiefBotFactory(int startX, int startY, StudentWorld* world, int tbotType) : Actor(IID_ROBOT_FACTORY, startX, startY, world, none)
{
    m_tbotToProduce = tbotType;
}

void ThiefBotFactory::doSomething()
{
    int x = getX();
    int y = getY();
    int kbots = 0;
    
    //look up
    int i = 1;
    while((y-i)>=0 && i<=3) {
        if(getWorld()->isThiefBotOnLocation(x, y-i))
        {
            kbots++;
        }
        i++;
    }
    
    //look down
    i = 1;
    while((y+i)<VIEW_HEIGHT && i<=3) {
        if(getWorld()->isThiefBotOnLocation(x, y+i))
        {
            kbots++;
        }
        i++;
    }
    
    //look left
    i = 1;
    while((x-i)>=0 && i<=3) {
        if(getWorld()->isThiefBotOnLocation(x-i, y))
        {
            kbots++;
        }
        i++;
    }

    
    //look right
    i = 1;
    while((x+i)<VIEW_WIDTH && i<=3) {
        if(getWorld()->isThiefBotOnLocation(x+i, y))
        {
            kbots++;
        }
        i++;
    }
    

    if(kbots < 3 && getWorld()->isThiefBotOnLocation(getX(), getY()) == false) {
        int randomNum = (rand() % 50) + 1;
        if(randomNum == 1){
            if(m_tbotToProduce == IID_THIEFBOT) {
                ThiefBot *tbot = new ThiefBot(IID_THIEFBOT,x, y, getWorld());
                getWorld()->addActorToVector(tbot);
                getWorld()->playSound(SOUND_ROBOT_BORN);
            }
            else if(m_tbotToProduce == IID_MEAN_THIEFBOT) {
                MeanThiefBot *tbot = new MeanThiefBot(IID_MEAN_THIEFBOT,x, y, getWorld());
                getWorld()->addActorToVector(tbot);
                getWorld()->playSound(SOUND_ROBOT_BORN);
            }
        }
    }
}
