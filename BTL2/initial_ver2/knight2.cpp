#include "knight2.h"


/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(int phoenixdown, int antidote, int max)
{
    this->maxSize = max;
    this->count = 0;
    this->headItem = NULL;

    for (int i = 0; i < phoenixdown; i++){
        BaseItem* newItem = new Phoenix();
        this->insertFirst(newItem);
    }

    for (int i = 0; i < antidote; i++){
        BaseItem* newItem = new Antidote();
        this->insertFirst(newItem);
    }
}
BaseBag::BaseBag(BaseKnight *knight, int phoenixdownI, int antidote)
{
    this->item = nullptr;
    this->knight = nullptr;
}
bool BaseBag::insertFirst(BaseItem *item)
{
    if (count == 0){
        this->headItem = new BagNode(item);
        count++;
        return true;
    }
    else if (maxSize == -1 || count < maxSize){
        BagNode* newItem = new BagNode(item, headItem);
        headItem = newItem;
        count++;
        return true;
    }
    return false;
}
BaseItem *BaseBag::get(ItemType itemType)
{
    BagNode* item = this->headItem;
    while (item != NULL){
        if (item->baseItem->getType() == itemType){
            BaseItem* tmp = item->baseItem;
            return tmp;
        }
        item = item->next;
    }
    return nullptr;
}
string BaseBag::toString() const
{
    string res = "Bag[count=";
    res = res + to_string(count) + ";";
    BagNode* item = this->headItem;
    while (item != NULL){
        res = res + item->baseItem->toString() + ",";
        item = item->next;
    }
    if (res[res.length() - 1] == ','){
        res[res.length() - 1] = ']';
    }
    else res += ']';

    return res;
}
BaseItem *BaseBag::getAndCheckItem(ItemType itemType, BaseKnight *baseKnight)
{
    BagNode* item = this->headItem;
    while (item)
    {
        /* code */
        if (item->baseItem->getType() == itemType && item->baseItem->canUse(baseKnight)){
            BaseItem* tmp = item->baseItem;
            item->baseItem = headItem->baseItem;
            headItem->baseItem = tmp;
            return tmp;
        }
        item = item->next;
    }
    
    return nullptr;
}
bool BaseBag::useItem(ItemType itemType, BaseKnight *baseKnight)
{   
    BaseItem* toUseItem = getAndCheckItem(itemType, baseKnight);
    // cout << "Use " << endl;
    if (toUseItem != nullptr) {
        toUseItem->use(baseKnight);
        BagNode* tmp = headItem;
        headItem = headItem->next;
        count--;
        delete tmp;
        return true;
    }
    return false;
}
void BaseBag::removeLastItem()
{
    if (count > 0){
        BagNode* tmp = headItem;
        headItem = headItem->next;
        count--;
    }
}
/* * * END implementation of class BaseBag * * */


int setLimitGil(int gil){
    return gil > 999? 999 : gil;
}
/* * * BEGIN implementation of class BaseKnight * * */
bool isPrime(int n){
    if (n <= 2) return 0;
    for (int i = 2; i < sqrt(n); i++){
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
    if (isPrime(maxhp)) {
        // cout << "Paladin\n";
        return new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    } 
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
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + ","
        + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

bool BaseKnight::checkConditionForHp()
{
    // cout << "Checking condition\n" << this->bag->useItem(PHOENIX, this);
    
    if (this->bag->useItem(PHOENIX, this)){
        return true;
    } 
    if (this->gil >= 100 && this->hp <= 0){
        this->hp = this->maxhp / 2;
        this->gil = this->gil - 100;
        return true;
    }
    return false;
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
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

void ArmyKnights::deleteKnightWithIndex(int index)
{
    if (knightList && knightList[index]){
        // cout << "Index: " << index << endl;
        delete knightList[index];
        knightList[index] = nullptr;
        this->currentNumKnights--;
    }
}

bool ArmyKnights::handleEvent(int eventOrder, int eventNumber)
{
    // cout << "Meet: " << (this->knightList[0] == nullptr);
    if (eventNumber <= 5){
        return fightMinor(eventOrder, eventNumber);
    }
    else if (eventNumber == 6) {
        return fightTornbery(eventOrder);
    }
    else if (eventNumber == 7) {
        return fightQueenOfCards(eventOrder);
    }
    else if (eventNumber == 8) {
        // cout << "Meet nina: " << (this->knightList[0] == nullptr);
        meetNina();
        return 1;

    }
    else if (eventNumber == 9) {
        meetDurianGarden();
        return 1;

    }
    else if (eventNumber == 10) {
        return fightOmegaWeapon();
    }
    else if (eventNumber == 11) {
        return fightHades();

    }
    else if (eventNumber == 98) {

        takeExcalibur();
        return 1;
    }
    else if (eventNumber == 99) {
        return fightUltimecia();
    }

    else if (eventNumber <= 97){
        takeMinorItems(eventNumber);
        return 1;
    }
    else {
        takePhoenixdown(eventNumber - 110);
        return true;
    }
    return false;
}

bool ArmyKnights::fightMinor(int eventOrder, int opponentType)
{
    int gilForEachOpponent[5] = {100, 150, 450, 750, 800};
    int baseDamageForEachOpponent[5] = {10, 15, 45, 75, 95};
    int opponentLevel = (eventOrder + opponentType) % 10 + 1;

    int gil = gilForEachOpponent[opponentType - 1];
    int baseDamage = baseDamageForEachOpponent[opponentType - 1];
    BaseOpponent* opponent = new BaseOpponent(opponentLevel, opponentType, gil, baseDamage);
    // cout << "\nNums: " << this->numKnights << endl;

    for (int i = this->numKnights - 1; i >= 0; i--){
        // cout << this->knightList[i]->getKnightType() << endl;
        // cout << "\nNums: " << this->numKnights << endl;
        // cout << typeid(knightList[i]).name() << endl;
        knightList[i]->fight(opponent);
        // cout << knightList[i]->getHP() << endl;

        if (knightList[i]->getHP() <= 0){
            deleteKnightWithIndex(i);
            break;
        } 
        else {
            // cout << knightList[i]->getGil()  << endl;
            // knightList[i]->setGil(knightList[i]->getGil() + gil);
            int knightGil = knightList[i]->getGil();
            if (knightGil > 999){
                knightList[i]->setGil(999);
                passGilToPreKnight(knightGil - 999, i - 1);
            }
            break;
        }
    }

    delete opponent;
    if (numKnights < 0) return 0;
    
    return 1;
}

bool ArmyKnights::fightTornbery(int eventOrder)
{
    int opponentLevel = (eventOrder + 6) % 10 + 1;
    // cout << opponentLevel << endl;
    BaseOpponent* opponent = new BaseOpponent(opponentLevel, 6, 0, 0);

    for(int i = numKnights - 1; i >= 0; i--){
        knightList[i]->fight(opponent);
        // cout << knightList[i]->getHP();
        if (knightList[i]->getHP() <= 0) {
            deleteKnightWithIndex(i);
            break;
            // cout << "Torn: " << (knightList[0] == nullptr);
        }
        else { break; }
    }
    
    delete opponent;
    if (numKnights < 0) return 0;
    return 1;
}

bool ArmyKnights::fightQueenOfCards(int eventOrder)
{
    int opponentLevel = (eventOrder + 7) % 10 + 1;
    BaseOpponent* opponent = new BaseOpponent(opponentLevel, 7, 0, 0);
    BaseKnight* knight = this->lastKnight();
    
    knight->fight(opponent);
    
    int gil = knight->getGil();

    if (gil > 999) {
        knight->setGil(999);
        passGilToPreKnight(gil - 999, numKnights - 2);
    }

    delete opponent;

    return 1;
}

void ArmyKnights::meetNina()
{
    // cout << "Nina\n";
    for (int i = 0; i < numKnights; i++){
        // cout << (knightList[0] == NULL) << endl;
        BaseKnight* knight = knightList[i];
        // cout << numKnights << endl;
        // cout  << (knight == nullptr) << endl;
        int currGil = knight->getGil();
            // cout << "Nina loop\n";
        int currHP = knight->getHP();
        int maxHP = knight->getMaxHP();

        // cout << knight->getKnightType() << endl;
        if (knight->getKnightType() == PALADIN && currHP < (maxHP / 3)){
            knight->setHP(currHP + maxHP / 5);

        }
        else if (currGil >= 50 && currHP < (maxHP / 3)){
            knight->setGil(currGil - 50);
            knight->setHP(currHP + maxHP / 5);
        }

    }
}

void ArmyKnights::meetDurianGarden()
{
    for (int i = 0; i < numKnights; i++){
        BaseKnight* knight = knightList[i];
        knight->setHP(knight->getMaxHP());
    }
}

bool ArmyKnights::fightOmegaWeapon()
{
    if (equipments.hasDefeatedByOmega) return 1;

    for (int i = numKnights - 1; i >= 0; i--){
        bool cond = (knightList[i]->getKnightType() == DRAGON) 
                    || ((knightList[i]->getLevel() == 10) && (knightList[i]->getHP() == knightList[i]->getMaxHP()));
        if (cond) {
            equipments.hasDefeatedByOmega = true;
            knightList[i]->setLevel(10);
            knightList[i]->setGil(999);
            return 1;
        }
        else {
            knightList[i]->setHP(0);
            knightList[i]->checkConditionForHp();
            if (knightList[i]->getHP() <= 0){
                deleteKnightWithIndex(i);
                break;
            } 
            else return 1;
        }

        if (numKnights == 0) return 0;
    }
    return true;
}

bool ArmyKnights::fightHades()
{
    if (equipments.hasDefeatedByHades) return 1;

    for (int i = numKnights - 1; i >= 0; i--){
        bool cond = knightList[i]->getLevel() == 10 
                    || knightList[i]->getKnightType() == PALADIN
                    && knightList[i]->getLevel() > 7;
        if (cond) {
            equipments.hasDefeatedByHades = true;
            equipments.hasShield = true;
            return 1;
        }
        else {
            knightList[i]->setHP(0);
            knightList[i]->checkConditionForHp();
            if (knightList[i]->getHP() <= 0){
                deleteKnightWithIndex(i);
                break;
            } 
            else return 1;
        }

        if (numKnights == 0) return 0;
    }
    return true;
}

bool ArmyKnights::fightUltimecia()
{
    if (equipments.hasSword) return 1;
    if (!hasPaladinShield() || !hasLancelotSpear() || !hasGuinevereHair())
        return 0;

    int initHP = 5000;
    for (int i = numKnights - 1; i >= 0; i--){
        if (knightList[i]->getKnightType() == NORMAL){
            int damage = knightList[i]->getLevel() * knightList[i]->getHP() * knightList[i]->baseDamageMultiplier;
            initHP -= damage;

            if (initHP <= 0) return 0;
            deleteKnightWithIndex(i);
        }
    }
    return false;
}

void ArmyKnights::takePhoenixdown(int phoenixType)
{
    BaseItem* item = new Phoenix(phoenixType);

    for (int i = numKnights - 1; i >= 0; i--){
        if (knightList[i]->getBag()->insertFirst(item)) return;
    }

    delete item;
    return;
}

void ArmyKnights::takeMinorItems(int eventNumber)
{
    if (eventNumber == 95){
        equipments.hasShield = 1;
        return;
    }
    else if (eventNumber == 96){
        equipments.hasSpear = 1;
        return;
    }
    else if (eventNumber == 97){
        equipments.hasHair = 1;
        return;
    }
}

void ArmyKnights::takeExcalibur()
{
    equipments.hasSword = equipments.hasShield && equipments.hasSpear && equipments.hasHair;
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
            id = knightIndex + 1;
            hp = knightParams[0];
            maxhp = knightParams[0];
            level = knightParams[1];
            phoenixdownI = knightParams[2];
            gil = knightParams[3];
            antidote = knightParams[4];
            // cout << id << " " << hp << " " << maxhp << " " << level << " " << phoenixdownI << " " << gil << " " << antidote << endl;
            this->knightList[knightIndex] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
            // cout << (knightList[knightIndex] == nullptr) << endl;
            // cout << this->knightList[0]->getID() << endl;
            knightIndex++;
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
    this->knightList = NULL;
    this->numKnights = 0;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{

    return false;
}

bool ArmyKnights::adventure(Events *events)
{
    int numEvents = events->count();

    // cout << "Knight list: " << (this->knightList[0] != nullptr);
    for (int i = 0; i < numEvents; i++) {
        int eventCode = events->get(i);
        bool res = this->handleEvent(i, eventCode);

        this->printInfo();
        if (res) {
        }
        else return 0;
        // (res == NULL)? this->printInfo() : return 0;
    }
    // this->printInfo();
    return 1;
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
    return equipments.hasShield; 
}

bool ArmyKnights::hasLancelotSpear() const
{
    return equipments.hasSpear;
}

bool ArmyKnights::hasGuinevereHair() const
{
    return equipments.hasHair; 
}

bool ArmyKnights::hasExcaliburSword() const
{
    return equipments.hasSword;
}

/* * * END implementation of class ArmyKnights * * */


/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    // cout << "KnightAdventure";
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
    // cout << "Loading";
    this->armyKnights = new ArmyKnights(file_armyknights);
    // cout << "Count: " << this->armyKnights->count();
}

void KnightAdventure::loadEvents(const string &file_events)
{
    // cout << "Loading events";
    this->events = new Events(file_events);
}

// void KnightAdventure::startCombat(int eventOrder)
// {
//     int eventCode = events->get(eventOrder);
//     // cout << eventOrder << endl;
//     cout << this->armyKnights->lastKnight()->getMaxHP() << ' ' << armyKnights->lastKnight()->getLevel() << ' ';
//     cout << armyKnights->lastKnight()->getHP() << ' ' << armyKnights->lastKnight()->getGil() << endl;
//     switch (eventCode)
//     {
//     case 1:
//     {
//         MadBear *opponent = new MadBear(eventOrder, this->events->get(eventOrder), this->armyKnights);
//         // cout << "---- " << eventOrder << ' ' << this->events->get(eventOrder) << endl;
//         opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
//     }
//     break;
//     case 2:
//     {
//         Bandit *opponent = new Bandit(eventOrder, events->get(eventOrder), this->armyKnights);
//         opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
//     }
//     break;
//     case 3:
//     {
//         LordLupin *opponent = new LordLupin(eventOrder, events->get(eventOrder), this->armyKnights);
//         opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
//     }
//         break;
//     case 4:
//     {
//         Elf *opponent = new Elf(eventOrder, events->get(eventOrder), this->armyKnights);
//         opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
//     }
//         break;
//     case 5:
//     {
//         Troll *opponent = new Troll(eventOrder, events->get(eventOrder), this->armyKnights);
//         opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
//     }
//         break;
//     case 6:
//     {
//         Tornbery *opponent = new Tornbery(eventOrder, events->get(eventOrder), this->armyKnights);
//         opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
//     }
//         break;
//     case 7:
//     {
//         QueenOfCards* opponent = new QueenOfCards(eventOrder, events->get(eventOrder), this->armyKnights);
//         opponent->tradeDame(armyKnights->lastKnight()->getHP(), armyKnights->lastKnight()->getLevel(), armyKnights->lastKnight()->getGil());
//     }
//         break;
//     case 8:
        
//         break;
//     case 9:
//         /* code */
//         break;
//     case 10:
//         /* code */
//         break;
//     case 11:
//         /* code */
//         break;
//     case 112:
//         /* code */
//         break;
//     case 113:
//         /* code */
//         break;
//     case 114:
//         /* code */
//         break;
//     case 95:
//         /* code */
//         break;
//     case 96:
//         /* code */
//         break;
//     case 97:
//         /* code */
//         break;
//     case 98:
//         /* code */
//         break;
//     case 99:
//         /* code */
//         break;
//     default:
//         break;
//     }
// }

void KnightAdventure::run()
{
    // for (int event_index = 0; event_index < this->events->count(); event_index++){
    //     // int eventCode = this->events->get(event_index);
    //     this->startCombat(event_index);
    //     this->armyKnights->printInfo();
    // }
    // cout << "Here";
    if (armyKnights && events){
        bool result = this->armyKnights->adventure(events);
        armyKnights->printResult(result);
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
    this->bag = new BaseBag(phoenixdownI, antidote);
    this->knightType = PALADIN;
    this->baseDamageMultiplier = 0.06;
}

void PaladinKnight::fight(BaseOpponent *opponent)
{
    int opponentType = opponent->getTypeOfOpponent();
    if (opponentType <= 5){
        winningWithMinor(opponent);
    }
    else if (this->level >= opponent->getLevel()) {
        if (opponentType == 6) winningWithTornbery();
        else winningWithQueen();
    }
    else if (opponentType == 6){
        losingWithTornbery();
    }
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
    this->bag = new BaseBag(phoenixdownI, antidote, 16);
    this->knightType = LANCELOT;
    this->baseDamageMultiplier = 0.06;
}

void LancelotKnight::fight(BaseOpponent *opponent)
{
    int opponentType = opponent->getTypeOfOpponent();
    if (opponentType <= 5){
        winningWithMinor(opponent);
    }
    else if (this->level >= opponent->getLevel()) {
        if (opponentType == 6) winningWithTornbery();
        else winningWithQueen();
    }
    else if (opponentType == 6){
        losingWithTornbery();
    }
    else losingWithQueen();
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
    this->bag = new BaseBag(phoenixdownI, antidote, 14);
    this->knightType = DRAGON;
    this->baseDamageMultiplier = 0.075;
}

void DragonKnight::fight(BaseOpponent *opponent)
{
    int opponentType = opponent->getTypeOfOpponent();
    if (this->level >= opponent->getLevel()) {
        if (opponentType == 6) winningWithTornbery();
        else if (opponentType == 5) winningWithMinor(opponent);
        else winningWithQueen();
    }
    else if (opponentType <= 5){
        losingWithMinor(opponent);
    }
    else if (opponentType == 7){
        losingWithQueen();
    }
    // else losingWithQueen();
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
    this->bag = new BaseBag(phoenixdownI, antidote, 19);
    this->knightType = NORMAL;
    this->baseDamageMultiplier = 0;
}

void NormalKnight::fight(BaseOpponent *opponent)
{
    int opponentType = opponent->getTypeOfOpponent();
        // cout << "Normal Knight\n";
    if (this->level >= opponent->getLevel()) {
        if (opponentType <= 5) winningWithMinor(opponent);
        else if (opponentType == 6) winningWithTornbery();
        else winningWithQueen();
    }
    else if (opponentType <= 5){
        losingWithMinor(opponent);
    }
    else if (opponentType == 7){
        losingWithQueen();
    }
    else losingWithTornbery();
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
BaseOpponent::BaseOpponent(int level, int numOfType, int gil, int baseDamage)
{
    this->level = level;
    this->typeOfOpponent = numOfType;
    this->gil = gil;
    this->baseDamage = baseDamage;
}

// MadBear::MadBear(int eventOrder, int eventCode, ArmyKnights *knights)
// {
//     this->gil = 100;
//     this->baseDamage = 10;
//     this->eventOrder = eventOrder;
//     this->eventCode = eventCode;
//     this->knights = knights;
// }
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

// Bandit::Bandit(int, int, ArmyKnights *knights)
// {
//     this->gil = 150;
//     this->baseDamage = 15;
//     this->eventOrder = eventOrder;
//     this->eventCode = eventCode;
//     this->knights = knights;
// }

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

// Tornbery::Tornbery(int, int, ArmyKnights *)
// {
//     this->gil = 0;
//     this->baseDamage = 0;
//     this->eventOrder = eventOrder;
//     this->eventCode = eventCode;
//     this->knights = knights;
// }
// /* * * END implementation of Opponents classes * * */

// QueenOfCards::QueenOfCards(int, int, ArmyKnights *)
// {
//     this->gil = 0;
//     this->baseDamage = 0;
//     this->eventOrder = eventOrder;
//     this->eventCode = eventCode;
//     this->knights = knights;
// }

// LordLupin::LordLupin(int, int, ArmyKnights *)
// {
//     this->gil = 0;
//     this->baseDamage = 0;
//     this->eventOrder = eventOrder;
//     this->eventCode = eventCode;
//     this->knights = knights;
// }

// Elf::Elf(int, int, ArmyKnights *)
// {
//     this->gil = 0;
//     this->baseDamage = 0;
//     this->eventOrder = eventOrder;
//     this->eventCode = eventCode;
//     this->knights = knights;
// }

// Troll::Troll(int, int, ArmyKnights *)
// {
//     this->gil = 0;
//     this->baseDamage = 0;
//     this->eventOrder = eventOrder;
//     this->eventCode = eventCode;
//     this->knights = knights;
// }

void ArmyKnights::passGilToPreKnight(int numOfGils, int startIndex)
{
    while (startIndex > 0 && numOfGils > 0){
        int currGil = knightList[startIndex]->getGil();
        currGil += numOfGils;
        numOfGils = 0;

        if (currGil > 999){
            numOfGils = currGil - 999;
            currGil = 999;
        }
        knightList[startIndex]->setGil(currGil);
        startIndex--;
    }
}

/* * * BEGIN implementation of Phoenix classes * * */
bool Phoenix::canUse(BaseKnight *knight)
{
    int hp = knight->getHP();
    int maxHP = knight->getMaxHP();

    if (this->phoenixType == 1){
        if (hp <= 0) return 1;
        return 0;
    }
    else if (this->phoenixType == 2){
        if (hp < (maxHP / 4)) return 1;
        return 0;
    }
    else if (this->phoenixType == 3){
        if (hp < (maxHP / 3)) return 1;
        return 0;
    }
    else if (this->phoenixType == 4){
        if (hp < (maxHP / 2)) return 1;
        return 0;
    }

    return false;
}
void Phoenix::use(BaseKnight *knight)
{
    int hp = knight->getHP();
    int maxHP = knight->getMaxHP();

    if (this->phoenixType == 1){
        if (hp <= 0) knight->setHP(maxHP);
    }
    else if (this->phoenixType == 2){
        if (hp < maxHP / 4) knight->setHP(maxHP);
        return;
    }
    else if (this->phoenixType == 3){
        if (hp < maxHP / 3){
            if (hp <= 0) knight->setHP(maxHP / 3);
            else knight->setHP((maxHP / 4) + hp);
        }
        return;
    }
    else if (this->phoenixType == 4){
        if (hp < maxHP / 2){
            if (hp <= 0) knight->setHP(maxHP / 2);
            else knight->setHP((maxHP / 5) + hp);
        }
        return;
    }

}
/* * * END implementation of Phoenix classes * * */

BaseBag::BagNode::BagNode(BaseItem *item, BagNode *ptrNext)
{
    baseItem = item;
    next = ptrNext;
}

BaseBag::BagNode::~BagNode()
{
    if (baseItem)
        delete baseItem;
}

Antidote::Antidote()
{
    this->itemType = ANTIDOTE;
}

Antidote::~Antidote()
{
}

bool Antidote::canUse(BaseKnight *knight)
{
    return 1;
}

void Antidote::use(BaseKnight *knight)
{
    return;
}
