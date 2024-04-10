#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

int StudentWorld::init()
{
    string curLevel = "level0" + to_string(getLevel()) + ".txt";
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found ||
        result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    for (int x = 0; x < VIEW_WIDTH; x++) {
        for (int y = 0; y < VIEW_WIDTH; y++) {
            Level::MazeEntry item = lev.getContentsOf(x, y);
            switch(item) {
                default:
                    break;
                case Level::empty:
                    break;
                case Level::exit:
                    m_actors.push_back(new Exit(x, y, this));
                    break;
                case Level::player:
                    m_player = new Avatar(x, y, this);
                    break;
                case Level::horiz_ragebot:
                    m_actors.push_back(new RageBot(x,y,this,Actor::right));
                    break;
                case Level::vert_ragebot:
                    m_actors.push_back(new RageBot(x,y,this,Actor::down));
                    break;
                case Level::thiefbot_factory:
                    m_actors.push_back(new ThiefBotFactory(x,y,this,IID_THIEFBOT));
                    break;
                case Level::mean_thiefbot_factory:
                    m_actors.push_back(new ThiefBotFactory(x,y,this,IID_MEAN_THIEFBOT));
                    break;
                case Level::marble:
                    m_actors.push_back(new Marble(x,y,this));
                    break;
                case Level::pit:
                    m_actors.push_back(new Pit(x,y,this));
                    break;
                case Level::crystal:
                    m_actors.push_back(new Crystal(x,y,this));
                    m_totalCrystals++;
                    break;
                case Level::restore_health:
                    m_actors.push_back(new RestoreHealthGoodie(x,y,this));
                    break;
                case Level::extra_life:
                    m_actors.push_back(new ExtraLifeGoodie(x,y,this));
                    break;
                case Level::ammo:
                    m_actors.push_back(new AmmoGoodie(x,y,this));
                    break;
                case Level::wall:
                    m_actors.push_back(new Wall(x, y, this));
                    break;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    updateDisplayText();
        
    m_player->doSomething();
        
    for(int i = 0; i<m_actors.size(); i++){
        m_actors[i]->doSomething();
        
        if(m_player->getHealth() <= 0){
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
            
        if(m_levelComplete){
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
        
    removeDeadActors();
        
    if(m_bonus > 0) m_bonus--;
        
    if(m_player->getHealth() <= 0){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
        
    if(m_levelComplete){
        return GWSTATUS_FINISHED_LEVEL;
    }
        
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    while(!m_actors.empty()){
        delete m_actors[0];
        m_actors.erase(m_actors.begin());
    }
    delete m_player;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Actor* StudentWorld::isActorOnLocation(int x, int y) {
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            return m_actors[i];
        }
    }
    return nullptr;
}

bool StudentWorld::canMarbleMove(int x, int y) {
    Actor *actor = isActorOnLocation(x, y);
    
    if (actor != nullptr) {
        if (actor->type() == IID_PIT) return true;
        else if (actor->type() == IID_EXIT) {
            if (actor->isVisible()) return false;
            return true;
        }
        return false;
    }
    return true;
}

bool StudentWorld::canPlayerMove(int x, int y) {
    
    bool blocksPlayer = false;
    
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
            if (m_actors[i]->type() == IID_MARBLE) {
                int dir = m_player->getDirection();
                switch(dir) {
                    case Actor::up:
                        if (canMarbleMove(x, y+1)) m_actors[i]->moveTo(x, y+1);
                        break;
                    case Actor::down:
                        if (canMarbleMove(x, y-1)) m_actors[i]->moveTo(x, y-1);
                        break;
                    case Actor::right:
                        if (canMarbleMove(x+1, y)) m_actors[i]->moveTo(x+1, y);
                        break;
                    case Actor::left:
                        if (canMarbleMove(x-1, y)) m_actors[i]->moveTo(x-1, y);
                        break;
                    default:
                        break;
                }
            }
        }
        if(m_actors[i]->getX() == x && m_actors[i]->getY() == y)
        {
            if(m_actors[i]->blocksPlayer()) blocksPlayer = true;
        }
    }
    if (blocksPlayer) return false;
    return true;
}

void StudentWorld::addActorToVector(Actor *a) {
    m_actors.push_back(a);
}

void StudentWorld::updateDisplayText()
{
    
    ostringstream oss;
    
    int score = getScore();
    oss.fill('0');
    oss << "Score: " << setw(7) << score;
    oss << "  ";
    
    int level = getLevel();
    oss.fill('0');
    oss << "Level: " << setw(2) << level;
    oss << "  ";
    
    int lives = getLives();
    oss.fill(' ');
    oss << "Lives: " << setw(2) << lives;
    oss << "  ";
    
    int health =  ((double)(m_player->getHealth())/20) * 100;
    oss.fill(' ');
    oss << "Health: " << setw(3) << health;
    oss << "%" << "  ";
    
    int ammo = m_player->getPeas();
    oss.fill(' ');
    oss << "Ammo: " << setw(3) << ammo;
    oss << "  ";
    
    int bonus = m_bonus;
    oss.fill(' ');
    oss << "Bonus: " << setw(4) << bonus;
    oss << "  ";
    
    setGameStatText(oss.str());
}

void StudentWorld::removeDeadActors()
{
    for(int i = 0; i<m_actors.size(); i++){
        Alive *currentActor = dynamic_cast<Alive*>(m_actors[i]);
        
        if (currentActor != nullptr && currentActor->getHealth() <= 0){
            currentActor->setVisible(false);
            delete m_actors[i];
            m_actors.erase(m_actors.begin()+i);
            continue;
        }
    }
}

bool StudentWorld::isMarbleAbovePit(Pit* p) {
    for (int i = 0; i < m_actors.size(); i++) {
        if (m_actors[i]->type() == IID_MARBLE && m_actors[i]->getX() == p->getX() && m_actors[i]->getY() == p->getY()) {
            m_actors[i]->setHealth(0);
            return true;
        }
    }
    return false;
}

bool StudentWorld::isPlayerAbovePickupableItem(PickupableItem *p) {
    if (abs(m_player->getX() - p->getX()) < 0.1 && abs(m_player->getY() - p->getY()) < 0.1){
        increaseScore(p->getScoreValue());

        if(p->type() == IID_CRYSTAL)
        {
            m_collectedCrystals++;
        }
        else if(p->type() == IID_EXTRA_LIFE)
        {
            incLives();
        }
        else if(p->type() == IID_RESTORE_HEALTH)
        {
            m_player->setHealth(20);
        }
        else if(p->type() == IID_AMMO)
        {
            m_player->addPeas(20);
        }
        return true;
    }
    return false;
}

bool StudentWorld::isPlayerAboveExit(Exit *exit) {
    if (m_player->getX() == exit->getX() && m_player->getY() == exit->getY()) {
        increaseScore(m_bonus+2000);
        m_levelComplete = true;
        return true;
    }
    return false;
}

void StudentWorld::levelCompleted() {
    m_levelComplete = true;
}

bool StudentWorld::collectedAllCrystals() {
    return m_collectedCrystals == m_totalCrystals;
}

bool StudentWorld::canPeaMove(int x, int y, Actor* owner)
{
    if(owner->type() != IID_PLAYER){
        if(m_player->getX() == x && m_player->getY() == y)
        {
            m_player->getHurt();
            return false;
        }
    }

    bool returnValue = true;
    for(int i = 0; i<m_actors.size(); i++){
        if(m_actors[i]->getX() == x && m_actors[i]->getY() == y)
        {
            // hit walls and robot factories, do nothing
            if(m_actors[i]->type() == IID_WALL){
                returnValue = false;
            }
            
            if(m_actors[i]->type() == IID_ROBOT_FACTORY){
                returnValue = false;
            }
            
            if (m_actors[i]->type() == IID_MARBLE){
                m_actors[i]->getHurt();
                returnValue = false;
            }
            
            if(owner->type() != IID_RAGEBOT && m_actors[i]->type() == IID_RAGEBOT){
                m_actors[i]->getHurt();
                if(m_actors[i]->getHealth() <= 0 && owner->type() == IID_PLAYER) increaseScore(100);
                returnValue = false;
            }
            
            if(m_actors[i]->type() == IID_THIEFBOT){
                m_actors[i]->getHurt();
                if(m_actors[i]->getHealth() <= 0 && owner->type() == IID_PLAYER) increaseScore(10);
                returnValue = false;
            }
            
            if(owner->type() != IID_MEAN_THIEFBOT && m_actors[i]->type() == IID_MEAN_THIEFBOT){
                m_actors[i]->getHurt();
                if(m_actors[i]->getHealth() <= 0 && owner->type() == IID_PLAYER) increaseScore(20);
                returnValue = false;
            }
        }
    }
    return returnValue;
}

int StudentWorld::getBonusPoints() {
    return m_bonus;
}

bool StudentWorld::shouldBotFirePea(Robot *bot) {
    if((m_player->getY() == bot->getY()))
        {
            if(bot->getDirection() == Actor::left && m_player->getX() < bot->getX()) {
                for(int x = bot->getX()-1; x>=m_player->getX(); x--){
                    Actor* temp = isActorOnLocation(x,bot->getY());
                    if(temp != nullptr && (temp->type() == IID_MARBLE || temp->type() == IID_WALL || temp->type() == IID_RAGEBOT || temp->type() == IID_THIEFBOT || temp->type() == IID_MEAN_THIEFBOT || temp->type() == IID_ROBOT_FACTORY))
                    {
                        return false;
                    }
                }
                return true;
            }
            else if(bot->getDirection() == Actor::right && m_player->getX() > bot->getX()){
                for(int x = bot->getX()+1; x<=m_player->getX(); x++){
                    Actor* temp = isActorOnLocation(x,bot->getY());
                        if(temp != nullptr && (temp->type() == IID_MARBLE || temp->type() == IID_WALL || temp->type() == IID_RAGEBOT || temp->type() == IID_THIEFBOT || temp->type() == IID_MEAN_THIEFBOT || temp->type() == IID_ROBOT_FACTORY))
                        {
                            return false;
                        }
                }
                return true;
            }
            return false;
        }
        
        else if((m_player->getX() == bot->getX()))
        {
            if(bot->getDirection() == Actor::down && m_player->getY() < bot->getY()) {
                for(int y = bot->getY()-1; y>=m_player->getY(); y--){
                    Actor* temp = isActorOnLocation(bot->getX(),y);
                    if(temp != nullptr && (temp->type() == IID_MARBLE || temp->type() == IID_WALL || temp->type() == IID_RAGEBOT || temp->type() == IID_THIEFBOT || temp->type() == IID_MEAN_THIEFBOT || temp->type() == IID_ROBOT_FACTORY))
                    {
                        return false;
                    }
                }
                return true;
            }
            else if(bot->getDirection() == Actor::up && m_player->getY() > bot->getY()){
                for(int y = bot->getY()+1; y<=m_player->getY(); y++){
                    Actor* temp = isActorOnLocation(bot->getX(),y);
                    if(temp != nullptr && (temp->type() == IID_MARBLE || temp->type() == IID_WALL || temp->type() == IID_RAGEBOT || temp->type() == IID_THIEFBOT || temp->type() == IID_MEAN_THIEFBOT || temp->type() == IID_ROBOT_FACTORY)) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;
}

bool StudentWorld::createPea(int x, int y, Actor *owner) {
    int dir = owner->getDirection();
    int p_x = owner->getX();
    int p_y = owner->getY();
    
    switch (dir) {
        case Actor::up:
            x = p_x; y = p_y+1;
            break;
        case Actor::down:
            x = p_x; y = p_y-1;
            break;
        case Actor::right:
            y = p_y; x = p_x+1;
            break;
        case Actor::left:
            y = p_y; x = p_x-1;
            break;
        default:
            break;
    }
    
    if (isActorOnLocation(x, y)) return false;
    m_actors.push_back(new Pea(x, y, this, dir, owner));
    return true;
}

bool StudentWorld::canBotMove(int x, int y)
{
    
    if(m_player->getX() == x && m_player->getY() == y){
        return false;
    }
    
    for(int i = 0; i<m_actors.size(); i++){
        if(m_actors[i]->getX() == x && m_actors[i]->getY() == y)
        {
            if(m_actors[i]->type() == IID_MARBLE || m_actors[i]->type() == IID_WALL || m_actors[i]->type() == IID_PIT || m_actors[i]->type() == IID_RAGEBOT || m_actors[i]->type() == IID_THIEFBOT || m_actors[i]->type() == IID_MEAN_THIEFBOT || m_actors[i]->type() == IID_ROBOT_FACTORY)
            {
                return false;
            }
        }
    }
    
    return true;
}

bool StudentWorld::isThiefBotOnLocation(int x, int y) {
    for(int i = 0; i<m_actors.size(); i++){
        if(m_actors[i]->type() == IID_THIEFBOT || m_actors[i]->type() == IID_MEAN_THIEFBOT)
            if(m_actors[i]->getX() == x && m_actors[i]->getY() == y)
                return true;
    }
        
    return false;
}

Actor* StudentWorld::isThiefBotOnGoodie(ThiefBot *bot) {
    for(int i = 0; i<m_actors.size(); i++) {
        if(m_actors[i]->type() == IID_EXTRA_LIFE || m_actors[i]->type() == IID_RESTORE_HEALTH || m_actors[i]->type() == IID_AMMO) {
            if(m_actors[i]->getX() == bot->getX() && m_actors[i]->getY() == bot->getY()) {
                return m_actors[i];
            }
        }
    }
    return nullptr;
}
