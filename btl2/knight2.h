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

enum ItemType {ANTIDOTE = 0, PHOENIXDOWNI; PHOENIXDOWNII; PHOENIXDOWNIII; PHOENIXDOWNIV};

class BaseBag {
    BaseBag *item;
    BaseKnight *knight;
    protected:
    // single-linked list structure for knight's items
    class nodeBag{
        public:
        BaseItem *item;   // data of node 
        nodeBag *nextPtr; //pointer to the next node of type nodeBag
        nodeBag(BaseItem *inputItem, nodeBag *pNext = nullptr){
            this->item = inputItem;
            this->nextPtr = pNext;  
        }
        ~nodeBag(){
            if (item != 0) delete item;
        }
    };
    nodeBag *pHead;
    int count; //the number of items of the knight 
public:
    BaseBag (BaseKnight *knight, int antidote, int phoenixdownI, int max = -2004){
        this->pHead = nullptr;
        
    };
    virtual bool insertFirst(BaseItem * item){
        return true;
    };
    virtual BaseItem * get(ItemType itemType) {
        return nullptr;
    };
    virtual string toString() const {
        return "BaseBag";
    };
    virtual useItem(ItemType itemtype, BaseKnight *knight);
    virtual checkItemAndAdd(ItemType itemtype, BaseKnight *knight);
    virtual delItem();
};  
class PaladinBag : public BaseBag{

};
class LancelotBag : public BaseBag{

};
class DragonBag : public BaseBag{

};
class NormalBag : public BaseBag{

};
class BaseOpponent{
    protected:
    virtual void tradeDame(){};
    static int calcLevel0(int eventOrder, int eventCode); 
};

class MadBear : public BaseOpponent{

};
class Bandit : public BaseOpponent{};
class LordLupin : public BaseOpponent{};
class Elf : public BaseOpponent{};
class Troll : public BaseOpponent{};
class Tornbery : public BaseOpponent{};
class QueenOfCards : public BaseOpponent{};
class NinaDeRings : public BaseOpponent{};
class DurianGarden : public BaseOpponent{};
class OmegaWeapon : public BaseOpponent{};
class Hades : public BaseOpponent{};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);

    string toString() const;
};
class PaladinKnight : public BaseKnight{
    public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI );
    void fight(BaseOppenent *oppennent);
};
class LancelotKnight : public BaseKnight{
    public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void fight(BaseOppenent *oppennent);
};
class DragonKnight : public BaseKnight{
    public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void fight(BaseOppenent *oppennent);
};
class NormalKnight : public BaseKnight{
    public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    void fight(BaseOppenent *oppennent);
};

class ArmyKnights {
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight (BaseOpponent *opponent);
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
protected:
    ItemType itemType;
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType getType(){
        return itemType;
    }
    virtual string toString() = 0;
};

class Antidote : public BaseItem{
    public:
    Antidote()
    :itemType(itemType = ANTIDOTE){
    }
    ~Antidote(){}
    string toString(){
        return "Antidote";
    }
    bool canUse(BaseKnight *knight){
        return true;
    }
    void use(BaseKnight *knight){
        return;
    }
};

class PhoenixDownI : public BaseItem{
    public:
    PhoenixDownI()
    :itemType(itemType = PHOENIXDOWNI){
    }
    ~PhoenixDownI(){}
    string toString (){
        return "PhoenixDownI";
    }
    bool canUse(BaseKnight *knight){
        return true;
    }
    bool use(BaseKnight *knight){
        return;
    }
};

class PhoenixDownII : public BaseItem{
public:
    PhoenixDownII()
    :itemType(itemType = PHOENIXDOWNII){
    }
    ~PhoenixDownII(){}
    string toString (){
        return "PhoenixDownII";
    }
    bool canUse(BaseKnight *knight){
        return true;
    }
    bool use(BaseKnight *knight){
        return;
    }
};

class PhoenixDownIII : public BaseItem{
public:
    PhoenixDownIII()
    :itemType(itemType = PHOENIXDOWNIII){
    }
    ~PhoenixDownIII(){}
    string toString (){
        return "PhoenixDownIII";
    }
    bool canUse(BaseKnight *knight){
        return true;
    }
    bool use(BaseKnight *knight){
        return;
    }
};

class PhoenixDownIV : public BaseItem{
public:
    PhoenixDownIV()
    :itemType(itemType = PHOENIXDOWNIV){
    }
    ~PhoenixDownIV(){}
    string toString (){
        return "PhoenixDownIV";
    }
    bool canUse(BaseKnight *knight){
        return true;
    }
    bool use(BaseKnight *knight){
        return;
    }
};
class Events {
public:
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
    void run();
};

#endif // __KNIGHT2_H__