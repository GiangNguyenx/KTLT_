#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(BaseKnight *knight, int phoenixdownI, int antidote)
{
    this->item = nullptr;
    this->knight = nullptr;
}
/* * * END implementation of class BaseBag * * */

int setLimitGil(int gil){
    return gil > 999? 999 : gil;
}
/* * * BEGIN implementation of class BaseKnight * * */
bool isPrime(int n){
    for (int i = 2; i < n; i++){
        if (n % i == 0){return 0;}
    }

    return 1;
}
void splitNumber(int n, int& a, int& b, int& c){
    /* 
        This function support to split a abc-integer format to a, b, c
        Example: 123 -> 1, 2, 3
    */
    c = n % 100;
    b = ((n - c) % 10) % 10;
    a = (int)(n / 100);
}
bool isSet3OfPythagorean(int n){
    int a, b, c;
    if (n >= 100 && n <= 999){
        splitNumber(n, a, b, c);
        if (a * a + b * b == c * c)
            return true;
    }
    return false;
}
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    /*
        This function return a type of Knight for each condition of <maxhp>:
        * Paladin: <maxhp> is a prime number
        * Lancelot: <maxhp> is 888
        * Dragon: <maxhp> is a integer and has (abc) format
            1) Has 3 number
            2) a^2 + b^2 = c^2
        * Normal: None of the above types
    */
    if (isPrime(maxhp)) return new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    else if (maxhp == 888) return new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    else if (isSet3OfPythagorean(maxhp)) return new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    else return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + "hp:" + to_string(hp) 
        + "maxhp:" + to_string(maxhp)
        + "level:" + to_string(level)
        + "gil:" + to_string(gil)
        + bag->toString()
        + "knight_type:" + typeString[knightType]
        + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */


/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string('-', 50) << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    // Create a array of knights with BaseKnight type array.
    this->knightList = nullptr;
    this->numKnights = 0;

    /* 
        Read file with input = "file_armyknights"
        File format:
            <num_of_knights>
            <HP> <level> <phoenixdown> <gil> <antidote>
    */
    ifstream readArmyFile(file_armyknights);
    string line, param;
    int lineIndex = 1, knightIndex = 0, paramIndex = 0;
    int id, hp, maxhp, level, gil, antidote, phoenixdownI;
    int knightParams[6];

    while(getline(readArmyFile, line)){
        stringstream ss(line);
        while(getline(ss, param, ' ')){
            if (lineIndex == 1){
                this->numKnights = stoi(param);
                this->currentNumKnights = this->numKnights;
                this->knightList = new BaseKnight*[this->numKnights];
                break;
            }
            else {
                knightParams[paramIndex++] = stoi(param);
                // break;
            }
        }
        
        if (lineIndex != 1){
            id = knightIndex;
            hp = knightParams[0];
            maxhp = knightParams[0];
            level = knightParams[1];
            phoenixdownI = knightParams[2];
            gil = knightParams[3];
            antidote = knightParams[4];
            // print << id << " " << hp << " " << maxhp << " " << 
            this->knightList[knightIndex++] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
        }
        paramIndex = 0;
        lineIndex++;
    }

}

ArmyKnights::~ArmyKnights()
{
    for (int i = 0; i < this->numKnights; i++){
        delete this->knightList[i];
    }
    delete[] this->knightList;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{

    return false;
}

bool ArmyKnights::adventure(Events *events)
{
    this->printInfo();
    return false;
}

int ArmyKnights::count() const
{
    return this->currentNumKnights;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    if (this->currentNumKnights == 0) return nullptr;
    return this->knightList[this->currentNumKnights - 1];
}

bool ArmyKnights::hasPaladinShield() const
{
    return false;
}

bool ArmyKnights::hasLancelotSpear() const
{
    return false;
}

bool ArmyKnights::hasGuinevereHair() const
{
    return false;
}

bool ArmyKnights::hasExcaliburSword() const
{
    return false;
}

/* * * END implementation of class ArmyKnights * * */


/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure()
{
    delete armyKnights;
    delete events;
}

void KnightAdventure::loadArmyKnights(const string &file_armyknights)
{
    this->armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::loadEvents(const string &file_events)
{
    this->events = new Events(file_events);
}

void KnightAdventure::startCombat(int eventOrder)
{
    int eventCode = events->get(eventOrder);
    // cout << eventOrder << endl;
    cout << this->armyKnights->lastKnight()->getMaxHP() << ' ' << armyKnights->lastKnight()->getLevel() << ' ';
    cout << armyKnights->lastKnight()->getHP() << ' ' << armyKnights->lastKnight()->getGil() << endl;
    switch (eventCode)
    {
    case 1:
    {
        MadBear *opponent = new MadBear(eventOrder, this->events->get(eventOrder), this->armyKnights);
        // cout << "---- " << eventOrder << ' ' << this->events->get(eventOrder) << endl;
        opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
    }
    break;
    case 2:
    {
        Bandit *opponent = new Bandit(eventOrder, events->get(eventOrder), this->armyKnights);
        opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
    }
    break;
    case 3:
    {
        LordLupin *opponent = new LordLupin(eventOrder, events->get(eventOrder), this->armyKnights);
        opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
    }
        break;
    case 4:
    {
        Elf *opponent = new Elf(eventOrder, events->get(eventOrder), this->armyKnights);
        opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
    }
        break;
    case 5:
    {
        Troll *opponent = new Troll(eventOrder, events->get(eventOrder), this->armyKnights);
        opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
    }
        break;
    case 6:
    {
        Tornbery *opponent = new Tornbery(eventOrder, events->get(eventOrder), this->armyKnights);
        opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
    }
        break;
    case 7:
    {
        QueenOfCards* opponent = new QueenOfCards(eventOrder, events->get(eventOrder), this->armyKnights);
        opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
    }
        break;
    case 8:
        
        break;
    case 9:
        /* code */
        break;
    case 10:
        /* code */
        break;
    case 11:
        /* code */
        break;
    case 112:
        /* code */
        break;
    case 113:
        /* code */
        break;
    case 114:
        /* code */
        break;
    case 95:
        /* code */
        break;
    case 96:
        /* code */
        break;
    case 97:
        /* code */
        break;
    case 98:
        /* code */
        break;
    case 99:
        /* code */
        break;
    default:
        break;
    }
}

void KnightAdventure::run()
{
    for (int event_index = 0; event_index < this->events->count(); event_index++){
        // int eventCode = this->events->get(event_index);
        this->startCombat(event_index);
        this->armyKnights->printInfo();
    }
}

/* * * END implementation of class KnightAdventure * * */


/* * * BEGIN implementation of class Events * * */
Events::Events(const string &file_events)
{
    this->numEvents = 0;
    this->events = nullptr;
    /* 
        Read file with input = "file_events"
        File format:
            <num>
            <event_1> <event_2> <event_3> <event_4> ...    // Has <num> events
    */
    ifstream readEventFile(file_events);
    string line, event;
    int lineIndex = 1, eventIndex = 0;

    while(getline(readEventFile, line)){
        stringstream ss(line);
        while(getline(ss, event, ' ')){
            switch (lineIndex){
            case 1:
                this->numEvents = stoi(event);
                this->events = new int[this->numEvents];
                break;
            case 2:
                this->events[eventIndex++] = stoi(event);
                break;
            }
        }
        lineIndex++;
    }
}
Events::~Events()
{
    delete[] this->events;
}
int Events::count() const
{
    return this->numEvents;
}
int Events::get(int i) const
{
    return this->events[i];
}

/* * * END implementation of class Events * * */



/* * * BEGIN implementation of Knights classes * * */
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
}

void PaladinKnight::fight(BaseOpponent *opponent)
{
}

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
}

void LancelotKnight::fight(BaseOpponent *opponent)
{
}

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
}

void DragonKnight::fight(BaseOpponent *opponent)
{
}

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
}

void NormalKnight::fight(BaseOpponent *opponent)
{
}

/* * * END implementation of Knights classes * * */


/* * * BEGIN implementation of Opponents classes * * */
void BaseOpponent::tradeDame(int HP, int level, int eventCode)
{
    int levelO = BaseOpponent::calcLevelO(this->eventOrder, this->eventCode);
    // cout << levelO << ' ' << this->eventOrder << ' ' << this->eventCode << "----\n";

    if (eventCode >=1 && eventCode <= 5){
        if (knights->lastKnight()->getLevel() < levelO) {
            HP = HP - this->baseDamage * (levelO - level);
            this->knights->lastKnight()->setHP(HP);
        }
        else if (knights->lastKnight()->getLevel() >= levelO){
            knights->lastKnight()->setGil(setLimitGil(knights->lastKnight()->getGil() + this->gil));
        }
    }
    else if (eventCode == 6){
        if (knights->lastKnight()->getLevel() >= levelO){
            int newLevel = knights->lastKnight()->getLevel();
            knights->lastKnight()->setLevel(newLevel + 1);
        }
        else if (knights->lastKnight()->getLevel() < levelO) {
            
        }
    }
    else if (eventCode == 7){
        if (knights->lastKnight()->getLevel() >= levelO){
            int newLevel = knights->lastKnight()->getLevel();
            knights->lastKnight()->setLevel(newLevel + 1);
        }
        else if (knights->lastKnight()->getLevel() < levelO) {
            
        }
    }
    else if (eventCode == 8){

    }
    else if (eventCode == 9){

    }
    else if (eventCode == 10){

    }
    else if (eventCode == 11){

    }
}

int BaseOpponent::calcLevelO(int eventOrder, int eventCode)
{
    return (eventOrder + eventCode) % 10 + 1;
}
MadBear::MadBear(int eventOrder, int eventCode, ArmyKnights* knights)
{
    this->gil = 100;
    this->baseDamage = 10;
    this->eventOrder = eventOrder;
    this->eventCode = eventCode;
    this->knights = knights;
}
// void MadBear::tradeDame(int HP, int level, int gil)
// {
//     int levelO = BaseOpponent::calcLevelO(this->eventOrder, this->eventCode);
//     // cout << levelO << ' ' << this->eventOrder << ' ' << this->eventCode << "----\n";
    
//     if (knights->lastKnight()->getLevel() < levelO) {
//         HP = HP - this->baseDamage * (levelO - level);
//         this->knights->lastKnight()->setHP(HP);
//     }
//     else if (knights->lastKnight()->getLevel() >= levelO){
//         knights->lastKnight()->setGil(setLimitGil(knights->lastKnight()->getGil() + this->gil));
//     }
// }

Bandit::Bandit(int, int, ArmyKnights *knights)
{
    this->gil = 150;
    this->baseDamage = 15;
    this->eventOrder = eventOrder;
    this->eventCode = eventCode;
    this->knights = knights;
}

// void Bandit::tradeDame(int HP, int level, int)
// {
//     int levelO = BaseOpponent::calcLevelO(this->eventOrder, this->eventCode);
//     // cout << levelO << ' ' << this->eventOrder << ' ' << this->eventCode << "----\n";
    
//     if (knights->lastKnight()->getLevel() < levelO) {
//         HP = HP - this->baseDamage * (levelO - level);
//         this->knights->lastKnight()->setHP(HP);
//     }
//     else if (knights->lastKnight()->getLevel() >= levelO){
//         knights->lastKnight()->setGil(setLimitGil(knights->lastKnight()->getGil() + this->gil));
//     }
// }

Tornbery::Tornbery(int, int, ArmyKnights *)
{
    this->gil = 0;
    this->baseDamage = 0;
    this->eventOrder = eventOrder;
    this->eventCode = eventCode;
    this->knights = knights;
}
/* * * END implementation of Opponents classes * * */

QueenOfCards::QueenOfCards(int, int, ArmyKnights *)
{
    this->gil = 0;
    this->baseDamage = 0;
    this->eventOrder = eventOrder;
    this->eventCode = eventCode;
    this->knights = knights;
}

LordLupin::LordLupin(int, int, ArmyKnights *)
{
    this->gil = 0;
    this->baseDamage = 0;
    this->eventOrder = eventOrder;
    this->eventCode = eventCode;
    this->knights = knights;
}

Elf::Elf(int, int, ArmyKnights *)
{
    this->gil = 0;
    this->baseDamage = 0;
    this->eventOrder = eventOrder;
    this->eventCode = eventCode;
    this->knights = knights;
}

Troll::Troll(int, int, ArmyKnights *)
{
    this->gil = 0;
    this->baseDamage = 0;
    this->eventOrder = eventOrder;
    this->eventCode = eventCode;
    this->knights = knights;
}
