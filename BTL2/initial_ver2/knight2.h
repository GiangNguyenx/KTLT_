#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

/* Prototypes of classes */
class BaseBag;
class BaseItem;
class BaseKnight;
class BaseOppenent;
class Events;
class ArmyKnights;
/* End of Prototypes */

enum ItemType {/* TODO: */};

class BaseBag {
    BaseItem* item;
    BaseKnight* knight;
public:
    BaseBag(BaseKnight* knight, int phoenixdownI, int antidote);
    virtual bool insertFirst(BaseItem * item){return true;};
    virtual BaseItem * get(ItemType itemType){return nullptr;};
    virtual string toString() const{return "BaseBag";};
};

class BaseOpponent {
    // BaseOpponent(BaseOpponent * opponent);
protected:
    virtual void tradeDame(){};
    static int calcLevelO(int eventOrder, int eventCode);
};
class MadBear: public BaseOpponent {
    int baseDamage = 10;
    int gil = 100;
    int eventOrder, eventCode;
    ArmyKnights* knights;
public:
    MadBear(int, int, ArmyKnights*);
    void tradeDame(int HP, int, int);
};
class Bandit: public BaseOpponent {};
class LordLupin: public BaseOpponent {};
class Elf: public BaseOpponent {};
class Troll: public BaseOpponent {};
class Tornbery: public BaseOpponent {};
class QueenOfCards: public BaseOpponent {};
class NinaDeRings: public BaseOpponent {};
class DurianGarden: public BaseOpponent {};
class OmegaWeapon: public BaseOpponent {};
class Hades: public BaseOpponent {};


enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int phoenixdownI;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    void setID(int id) { this->id = id;}
    void setHP(int hp) { this->hp = hp;}
    void setMaxHP(int maxhp) {this->maxhp = maxhp;}
    void setLevel(int level) {this->level = level;}
    void setGil(int gil) {this->gil = gil;}
    void setAntidote(int antidote) {this->antidote = antidote;}
    int getID() const { return id; }
    int getMaxHP() const { return maxhp; }
    int getHP() const { return hp; }
    int getLevel() const { return level; }
    int getGil() const { return gil; }
    int getAntidote() const { return antidote; }
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    virtual void fight(BaseOpponent * opponent) = 0;
    string toString() const;
};

class PaladinKnight : public BaseKnight{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent * opponent);
};
class LancelotKnight : public BaseKnight{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent * opponent);
};
class DragonKnight : public BaseKnight{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent * opponent);
};
class NormalKnight : public BaseKnight{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent * opponent);
};

class ArmyKnights {
    BaseKnight** knightList;
    int numKnights;
    int currentNumKnights;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
    BaseItem* nextItem;
public:
    BaseItem* getNextItem() const { return nextItem; }
    void setNextItem(BaseItem* item) { nextItem = item;}
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};
class Antidote: public BaseItem{
    bool canUse( BaseKnight *knight);
    void use( BaseKnight *knight);
};
class PhoenixDownI: public BaseItem{
    bool canUse( BaseKnight *knight);
    void use( BaseKnight *knight);
};
class PhoenixDownII: public BaseItem{
    bool canUse( BaseKnight *knight);
    void use( BaseKnight *knight);
};
class PhoenixDownIII: public BaseItem{
    bool canUse( BaseKnight *knight);
    void use( BaseKnight *knight);
};
class PhoenixDownIV: public BaseItem{
    bool canUse( BaseKnight *knight);
    void use( BaseKnight *knight);
};

class Events {
    int numEvents;
    int* events;
public:
    Events(const string &file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void startCombat(int eventOrder);
    void run();
};


#endif // __KNIGHT2_H__