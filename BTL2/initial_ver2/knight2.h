#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

/* Prototypes of classes */
class BaseBag;
class BaseItem;
class BaseKnight;
class BaseOpponent;
class Events;
class ArmyKnights;
class Antidote;
class Phoenix;
/* End of Prototypes */

enum ItemType {ANTIDOTE = 0, PHOENIX /* TODO: */};

class BaseBag {
    class BagNode {
    public:
        BaseItem* baseItem;
        BagNode* next;
        BagNode(BaseItem* item, BagNode* ptrNext = NULL);
        ~BagNode();
    };
    BagNode* headItem;
    int count;
    int maxSize;

    BaseItem* item;
    BaseKnight* knight;
public:
    BaseBag(int phoenixdown, int antidote, int max = -1);
    BaseBag(BaseKnight* knight, int phoenixdownI, int antidote);
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;

    virtual BaseItem * getAndCheckItem(ItemType itemType, BaseKnight* baseKnight);
    virtual bool useItem(ItemType itemType, BaseKnight * baseKnight);
    virtual void removeLastItem();
};

class BaseOpponent {
    // BaseOpponent(BaseOpponent * opponent);
protected:
    ArmyKnights* knights;
    int baseDamage;
    int gil;
    int eventOrder, eventCode;
    int typeOfOpponent;
    int level;
public:
    void tradeDame(int HP, int, int);
    static int calcLevelO(int eventOrder, int eventCode);

    BaseOpponent(int level, int numOfType, int gil, int baseDamage);
    int getTypeOfOpponent(){ return this->typeOfOpponent; }
    int getLevel() { return this->level; }
    int getGil() { return this->gil; } 
    int getBaseDamage() { return this->baseDamage; }
};
class MadBear: public BaseOpponent {
    // int baseDamage = 10;
    // int gil = 100;
    // int eventOrder, eventCode;
    // ArmyKnights* knights;
public:
    MadBear(int, int, ArmyKnights*);
    // void tradeDame(int HP, int, int);
};
class Bandit: public BaseOpponent {
public:
    Bandit(int, int, ArmyKnights*);
    // void tradeDame(int, int, int);
};
class Tornbery: public BaseOpponent {
public:
    Tornbery(int, int, ArmyKnights*);
};
class QueenOfCards: public BaseOpponent {
public:
    QueenOfCards(int, int, ArmyKnights*);
};
class LordLupin: public BaseOpponent {
public:
    LordLupin(int, int, ArmyKnights *);
};
class Elf: public BaseOpponent {
public:
    Elf(int, int, ArmyKnights *);
};
class Troll: public BaseOpponent {
public:
    Troll(int, int, ArmyKnights*);
};
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
    double baseDamageMultiplier;
public:
    friend class ArmyKnights;
    void setID(int id) { this->id = id;}
    void setHP(int hp) { this->hp = hp;}
    void setMaxHP(int maxhp) {this->maxhp = maxhp;}
    void setLevel(int level) {this->level = level > 10? 10: level;}
    void setGil(int gil) {this->gil = gil > 999? 999: gil;}
    void setAntidote(int antidote) {this->antidote = antidote;}
    int getID() const { return id; }
    int getMaxHP() const { return maxhp; }
    int getHP() const { return hp; }
    int getLevel() const { return level; }
    int getGil() const { return gil; }
    int getAntidote() const { return antidote; }
    KnightType getKnightType() const { return knightType; }
    BaseBag* getBag() const { return bag; }
    bool knightIsDead() { return hp <= 0; }
    
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    virtual void fight(BaseOpponent * opponent) = 0;
    string toString() const;
    virtual bool checkConditionForHp();

protected:
    virtual void winningWithMinor(BaseOpponent * opponent){
        this->gil += opponent->getGil();
    }
    virtual void winningWithTornbery(){
        this->level = this->level + 1;
        if (this->level > 10) this->level = 10;
    }
    virtual void losingWithMinor(BaseOpponent * opponent){
        // cout << "Base: " << opponent->getBaseDamage() << ' ' << opponent->getLevel() << endl;
        int damage = opponent->getBaseDamage() * (opponent->getLevel() - this->level);
        // cout << "Damage: " << hp << ' ' << damage << endl;
        this->hp = this->hp - damage;
        // cout << "Damage: " << hp << ' ' << damage << endl;
        checkConditionForHp();
        // cout << "Damage: " << hp << ' ' << damage << endl;
    }
    virtual void losingWithTornbery(){
        if (antidote > 0){
            antidote--;
            bag->useItem(ANTIDOTE, this);
        }
        else{
            for (int i = 0; i < 3; i++){
                bag->removeLastItem();
            }
            this->hp = this->hp - 10;
            checkConditionForHp();
        }
    }
    virtual void winningWithQueen(){
        this->gil *= 2;
    }
    virtual void losingWithQueen(){
        this->gil = this->gil / 2;
    }
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

class Equipments{
    bool hasSpear;
    bool hasShield;
    bool hasSword;
    bool hasHair;
    bool hasDefeatedByOmega;
    bool hasDefeatedByHades;
public:
    Equipments(){
        hasSpear = false;
        hasShield = false;
        hasSword = false;
        hasHair = false;
        hasDefeatedByOmega = false;
        hasDefeatedByHades = false;
    }
    friend class ArmyKnights;
};
class ArmyKnights {
    BaseKnight** knightList;
    int numKnights;
    int currentNumKnights;
    Equipments equipments;
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

private:
    void deleteKnightWithIndex(int index);
    bool handleEvent(int eventOrder, int eventNumber);
    bool fightMinor(int eventOrder, int eventNumber);
    bool fightTornbery(int eventOrder);
    bool fightQueenOfCards(int eventOrder);
    void meetNina();
    void meetDurianGarden();
    bool fightOmegaWeapon();
    bool fightHades();
    bool fightUltimecia();
    void takePhoenixdown(int);
    void takeMinorItems(int);
    void takeExcalibur();
    void passGilToPreKnight(int, int);
};

class BaseItem {
protected:
    BaseItem* nextItem;
    ItemType itemType;
public:
    BaseItem* getNextItem() const { return nextItem; }
    void setNextItem(BaseItem* item) { nextItem = item;}
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType getType(){ return itemType; }
    virtual string toString() = 0;
    virtual ~BaseItem() {}
};
class Antidote: public BaseItem{
public:
    Antidote();
    ~Antidote();
    bool canUse( BaseKnight *knight);
    void use( BaseKnight *knight);
    string toString(){ return "Antidote"; }
};

class Phoenix: public BaseItem{
private:
    int phoenixType;
public:
    Phoenix(int num = 1){
        this->itemType = PHOENIX;
        this->phoenixType = num;
    }

    string toString(){ 
        string itemType[4] = {"I", "II", "III", "IV"};
        return "Phoenix" + itemType[phoenixType - 1];
    }
    bool canUse( BaseKnight *knight);
    void use( BaseKnight *knight);
};

// class PhoenixDownI: public BaseItem{
//     bool canUse( BaseKnight *knight);
//     void use( BaseKnight *knight);
// };
// class PhoenixDownII: public BaseItem{
//     bool canUse( BaseKnight *knight);
//     void use( BaseKnight *knight);
// };
// class PhoenixDownIII: public BaseItem{
//     bool canUse( BaseKnight *knight);
//     void use( BaseKnight *knight);
// };
// class PhoenixDownIV: public BaseItem{
//     bool canUse( BaseKnight *knight);
//     void use( BaseKnight *knight);
// };

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