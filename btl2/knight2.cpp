#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
bool BaseBag :: insertFirst(BaseItem *item){
    
}
BaseBag :: BaseBag (BaseKnight *knight, int antidote, int phoenixdownI){
    this->item = nullptr;
    this->knight = nullptr;
    
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
bool
isPrime(int n)
{
    // check Prime number
    count = 0;
    if (n == 1)
        return false;
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
                count += 1;
        }
        if (count == 2)
            return true;
        else
            return false;
    }
}
void splitNumber(int n, int a, int b, int c)
{
    // n = 345->a =3 b= 4 c= 5
    c = ((n % 100) % 10);
    b = ((n % 100) / 10);
    a = n / 100;
}
bool isAPythagoreanTriple(int n)
{
    int a, b, c;
    if (n > 100 && n < 999)
        splitNumber(n, a, b, c);
    if ((c * c == a * a + b * b))
        return true;
    else
        return false;
}

BaseKnight *BaseKnight ::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    // this function return a type of Knight for each condition of maxhp
    // returns a pointer that allows us to perform operations on the newly created BaseKnight object,
    // like accessing and changing its members,
    // or passing the object to other methods.
    if (isPrime(maxhp) == 1)
        return new PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    else if (maxhp == 888)
        return new LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    else if (isAPythagoreanTriple(maxhp) == 1)
        return new DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    else
        return new NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
}

string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + "hp:" + to_string(hp) + "maxhp:" + to_string(maxhp) + "level:" + to_string(level) + "gil:" + to_string(gil) + bag->toString() + "knight_type:" + typeString[knightType] + "]";
    return s;
}

// delete newknight

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights :: ArmyKnights(const string &file_armyknights) // constructor of class ArmyKnights - initialize an array of Knights from the data of the file read in .
    : numKnights(numKnights = 0), knightList(knightList = nullptr), currentNumKnights(currentNumKnights = 0)
{
    // this->numKnights = 0;
    // this->knightList = nullptr;
    // file's format:
    // <num> - num of Knights
    // <HP_1> <level_1> <phoenixdownI_1> <gil_1> <antidote_1> - description string  for 1st Knight.
    //...
    // <HP_num> <level_num> <phoenixdownI_num> <gil_num> <antidote_num> - description string for last Knight.
    ifstream readKnightFile(file_armyknights);
    string line, knight;
    int id, hp, maxhp, level, gil, antidote;
    int knight_param[6];
    int line_i = 1, knight_i = 0, param_i = 0;
    while (getline(readKnightFile, line))
    {
        stringstream ss(line);
        while (ss >> knight)
        {
            if (line_i == 1)
            { // line 1 - num of Knights
                numKnights = stoi(knight);
                currentNumKnights = numKnights;
                knightList = new BaseKnight *[numKnights]; // knightList has "numKnights" Knights in array
                break;
            }
            else
            { // Knight's stats from 1 -> last Knight
                knight_param[param_i++] = stoi(knight);
                break;
            }
        }
        if (line_i != 1)
        { 
            id = knight_i;
            hp = knight_param[0];
            maxhp = knight_param[0];
            level = knight_param[1];
            phoenixdownI = knight_param[2];
            gil = knight_param[3];
            antidote = knight_param[4];
            // knightList is a array of "numKnights" Knight's stats
            knightList[knight_i++] = BaseKnight ::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
            // method "create" take in the Knight's stats read from the file and generated matching Knight object.
        }
        line_i++;
    }
}

ArmyKnights :: ~ArmyKnights()
knightList(knightList){
    for (int i = 0; i < numKnights; i++){
        delete knightList[i];
    }
    delete[] knightList;
}
bool fight ( BaseOpponent * opponent ) {
    return false;
}
bool ArmyKnights :: advanture (Events *events) {
    this->printInfo();
    return false;
}

int ArmyKnights :: count() const
{
    return this->currentNumKnights;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    if (this->currentNumKnights == 0) return nullptr;
    return this->knightList[this->currentNumKnights - 1];
}

bool HasPaladinShield() const{
    return false;
}

bool HasLancelotSpear() const {
    return false;
}

bool HasGuinevereHair() const {
    return false;
}

bool HasExcaliburSword() const {
    return false;
}

void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string('-', 50) << endl;
}

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */

/* * * BEGIN implementation of class Events  * * */
// file_events is a variable used to store the name of the input data file for events
Events ::Events(const string &file_events) // Constuctor of class Events - allocates an array of integers to store event code.
    : numEvents(numEvent = 0), events(events = nullptr)
{
    // this->numEvents = 0;
    // this->events = nullptr;
    // /Read file with input = "file_events"
    // file's format:
    // <num>
    // <event_1> <event_2> <event_3> ... <even_num>
    /* * * END implementation of class Events  * * */
    ifstream readEventFile(file_events);
    string line, event;
    int line_i = 1, event_i = 0;
    while (getline(readEventFile, line))
    {
        stringstream ss(line);
        while (ss >> event)
        { // while(getline(ss, event , " ")){}
            switch (line_i)
            {
            case 1: // line 1 - num of events
                numEvents = stoi(event);
                events = new int[numEvents]; // array of event code
                break;
            case 2: // line 2 - event codes
                events[event_i++] = stoi(event);
                break;
            }
        }
        line_i++;
    }
}

Events ::~Events()
    events(events)
{
    delete[] events;
}

int Events :: count() const
    : numEvents(numEvents)
{
    return numEvents;
}

int Events ::get(int i) const
    : events(events)
{
    return events[i];
}
/* * * BEGIN implementation of Knights classes * * */
PaladinKnight ::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : id(id), maxhp(maxhp), level(level), gil(gil), antidote(antidote){} 

LancelotKnight ::Lancelot(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : id(id), maxhp(maxhp), level(level), gil(gil), antidote(antidote){} 

DragonKnight ::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : id(id), maxhp(maxhp), level(level), gil(gil), antidote(antidote){} 
NormalKnight ::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : id(id), maxhp(maxhp), level(level), gil(gil), antidote(antidote){}

                                                                                                                                                                                                                                                                                                              } :


/* * * END implementation of Knights classes * * *