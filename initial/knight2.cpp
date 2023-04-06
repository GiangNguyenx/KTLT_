#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */


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
    ifstream readEventFile(file_armyknights);
    string line, param;
    int lineIndex = 1, knightIndex = 0, paramIndex = 0;
    int id, hp, maxhp, level, gil, antidote;
    int knightParams[6];

    while(getline(readEventFile, line)){
        stringstream ss(line);
        while(getline(ss, param, ' ')){
            if (lineIndex == 1){
                this->numKnights = stoi(param);
                this->knightList = new BaseKnight*[this->numKnights];
                break;
            }
            else {
                knightParams[paramIndex++] = stoi(param);
                break;
            }
        }
        
        if (lineIndex != 1){
            id = knightParams[0];
            hp = knightParams[1];
            maxhp = knightParams[2];
            level = knightParams[3];
            gil = knightParams[4];
            antidote = knightParams[5];

            this->knightList[knightIndex++] = BaseKnight::create(id, hp, maxhp, level, gil, antidote);
        }
        paramIndex = 0;
        lineIndex++;
    }

}

/* * * END implementation of class ArmyKnights * * */


/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
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
}

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
}

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
}

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
}

/* * * END implementation of Knights classes * * */

