#include "knight.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>

struct Knight {
    int HP;
    int level;
    int remedy;
    int maidenkiss;
    int phoenixdown;

    Knight(int hp, int lev, int rem, int mai, int phoe): HP(hp), level(lev), remedy(rem), maidenkiss(mai), phoenixdown(phoe) {}
};

void readFile(string fileName, int line1_param[], string& line2_param, string line3_param[], int &num_event)
{
    /* Các tham số của hàm:
        - fileName: tên file input
        - line1_param: dòng 1 trong file input - các chỉ số của hiệp sĩ
        - line2_param: dòng 2 trong file input - các sự kiện
        - line3_param: dòng 3 trong file input - các tên file thêm
        Lưu các chỉ số tách được vào các mảng tương ứng.
        Tại hàm adventureToKoopa(), khai báo 3 mảng sau đó truyền vào readFile().
        Các thông số HP, ... sẽ lấy từ mảng sau khi chạy hàm. Đã có ví dụ phía dưới.
    */

    ifstream file_input(fileName);
    // string line1, line2, line3;
    string str1, str2, str3;
    int line1_i = 0, line2_i = 0, line3_i = 0, line_i = 0;
    string line, param;
    char delimeter = ' ';

    while (getline(file_input, line))
    {
        stringstream ss(line);
        // cout << line << endl;
        while (getline(ss, param, delimeter))
        {
            // getline(ss, param, delimeter);
        
            // cout << delimeter << endl;
            // cout << "param:" << param << endl;
            switch (line_i)
            {
            case 0:
                line1_param[line1_i] = stoi(param);
                line1_i++;
                break;
            case 1:
                line2_param += param;
                line2_param += ',';
                line2_i++;
                break;
            case 2:
                line3_param[line3_i] = param;
                line3_i++;
                break;
            default:
                break;
            }
        }
        if (line_i == 1) delimeter = ',';
        line_i++;
    }
    num_event = line2_i;
    // cout << "Read file" << line2_i << endl;
}

void initEventArray(int arr[], string event, int num_event){
    stringstream ss(event);
    string word;
    int index = 0;
    while (getline(ss, word, ',')) {
        arr[index] = stoi(word);
        index++;
    }
}

void initArray(int knight_param[], string file_param[])
{
    for (int i = 0; i < 5; i++)
    {
        knight_param[i] = -10000;
    }

    for (int i = 0; i < 3; i++)
    {
        file_param[i] = "";
    }
}

void initKnight(int knight_param[], Knight &knight, int &rescue)
{
    knight.HP = knight_param[0];
    knight.level = knight_param[1];
    knight.remedy = knight_param[2];
    knight.maidenkiss = knight_param[3];
    knight.phoenixdown = knight_param[4];
}

void eventZero(Knight& knight, int &rescue)
{
    rescue = 1;
    return;
}

void eventOneToFive(int event_code, int event, int maxHP, Knight& knight, int &rescue)
{
    int b = event % 10;
    int levelO = event > 6 ? (b > 5 ? b : 5) : b; // i ~ event

    if (knight.level > levelO)
    {
        if (knight.level == 10)
        {
        }
        else
        {
            knight.level++;
        }
    }
    else if (knight.level == levelO)
    {
    }
    else
    {
        float damage, baseDamage;
        switch (event_code)
        {
        case 1:
            baseDamage = 1;
            break;
        case 2:
            baseDamage = 1.5;
            break;
        case 3:
            baseDamage = 4.5;
            break;
        case 4:
            baseDamage = 7.5;
            break;
        case 5:
            baseDamage = 9.5;
            break;
        default:
            break;
        }

        damage = baseDamage * levelO * 10;
        knight.HP = knight.HP - (int)damage;
        if (knight.HP <= 0)
        {
            if (knight.phoenixdown == 0)
            {
                rescue = 0;
                return;
            }
            else if (knight.phoenixdown > 0)
            {
                knight.phoenixdown--;
                knight.HP = maxHP;
                rescue = -1;
            }
        }
    }
    // rescue = 1;
}

void eventSix(bool &is_tiny, int event, int& event_remain ,int maxHP, Knight& knight, int &rescue)
{
    int b = event % 10;
    int levelO = event > 6 ? (b > 5 ? b : 5) : b; // i ~ event
    is_tiny = false;

    if (knight.level > levelO)
    {
        knight.level += 2;
        if (knight.level >= 10)
        {
            knight.level = 10;
        }

    }
    else if (knight.level == levelO)
    {
        rescue = -1;
    }
    else
    {
        if (knight.HP < 5) knight.HP = 1;
        else knight.HP = (int)(knight.HP / 5);
        is_tiny = true;

        if (knight.remedy >= 1){
            knight.remedy--;
            // knight.HP = knight.HP * 5;
            knight.HP = (knight.HP * 5) > maxHP ? maxHP :  (knight.HP * 5);
            is_tiny = false;
        }
        else {}
    }
}

void eventSeven(bool &is_frog, int event, int &event_remain, int maxHP, Knight& knight, int &rescue){
    int b = event % 10;
    int levelO = event > 6 ? (b > 5 ? b : 5) : b; // i ~ event
    is_frog = false;

    int level_zero = knight.level;
    if (knight.level > levelO)
    {
        knight.level += 2;
        if (knight.level >= 10)
        {
            knight.level = 10;
        }
    }
    else if (knight.level == levelO)
    {
        rescue = -1;
    }
    else {
        is_frog = true;
        knight.level = 1;
        if (knight.maidenkiss >= 1){
            knight.maidenkiss--;
            is_frog = false;
            knight.level = level_zero;
        }
    }
}

int oddNumberSum(int n1){
    int s1 = 0;
    int count = 0;
    for (int i = 99; i >= 1; i -= 2){
        if (count == n1) break;
        s1 += i;
        count++;
    }

    return s1;
}
bool isPrime(int n){
    for (int i = 2; i < n; i++){
        if (n % i == 0){return 0;}
    }

    return 1;
}
int upToNearestPrime(int HP){
    for (int i = HP + 1; ; i++){
        if (isPrime(i)) return i;
    }
}
void eventEleven(int maxHP, Knight& knight, int & rescue){
    int n1 = ((knight.level + knight.phoenixdown) % 5 + 1) * 3;
    int s1 = oddNumberSum(n1);

    knight.HP = knight.HP + (s1 % 100);
    knight.HP = upToNearestPrime(knight.HP);
    if (knight.HP > maxHP) knight.HP = maxHP;
}

bool isFibonacci(int HP){
    int sum = 1;
    int prev_sum = 1;
    if (HP == 1) return 1;
    for (int i = 1; i < HP;){
        sum = prev_sum + i;
        if (HP == sum) return 1;
        else if (sum > HP) return 0;
        i = prev_sum;
        prev_sum = sum;
        // cout << prev_sum << " " << i << endl;
    }
    return 1;
}
int downToNearestFibonacci(int HP){
    for (int i = HP - 1; i >= 1; i--){
        // cout <<  "i: " << i << endl;
        if (isFibonacci(i)) return i;
    }

    return 1;
}
void eventTwelve(int & HP){
    if (HP > 1) HP = downToNearestFibonacci(HP);
}

void mushroomType1(int & HP, int arr[], int size) {
    int mini = 0, maxi = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= arr[maxi]) {
            maxi = i;
        }
        if (arr[i] <= arr[mini])
            mini = i;
    }
    // cout <<HP << " " << maxi << ' ' << mini << endl;
    HP = HP - (maxi + mini);
}
bool isMountainArray(int arr[], int size, int& mtx, int& mti){
    int climb = 0;

    while (climb < size - 1 && arr[climb] < arr[climb + 1]) {
        climb++;
    }
    
    //Kiểm tra núi đỉnh cuối
    if (climb == size - 1){
        mtx = arr[size - 1];
        mti = size - 1;
        return true;
    }

    // Kiểm tra núi đỉnh 0
    if (climb == 0){
        int climb_down = 0;
        while (climb_down < size - 1 && arr[climb_down] > arr[climb_down + 1]) {
            climb_down++;
        }
        if (climb_down == size - 1) {
            mtx = arr[0];
            mti = 0;
            return true;
        }
        else return false;
    } 

    climb = 0;
    while (climb < size - 1 && arr[climb] < arr[climb + 1]){
        climb++;
    }

    mti = climb; mtx = arr[climb];

    while (climb < size - 1 && arr[climb] > arr[climb + 1]){
        climb++;
    }
    
    if (climb == size - 1) return true;
    else {
        mtx = -2; mti = -3;
        return false;    
    }
    return false;
}
void mushroomType2(int& HP, int arr[], int size){
    int mtx = -2, mti = -3;
    isMountainArray(arr, size, mtx, mti);
    // cout << mtx << ' ' << mti << endl;
    HP = HP - (mtx + mti);
}
void mushroomType3(int & HP, int arr[], int size){
    for (int i = 0; i < size; i++){
        if (arr[i] < 0) arr[i] = -arr[i];
        arr[i] = (17 * arr[i] + 9) % 257;
    }

    int mini = 0, maxi = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] > arr[maxi]) {
            maxi = i;
        }
        if (arr[i] < arr[mini])
            mini = i;
    }

    // cout << maxi << " " << mini << endl;
    HP = HP - (maxi + mini);
}
void mushroomType4(int & HP, int arr[], int size){
    for (int i = 0; i < size; i++){
        if (arr[i] < 0) arr[i] = -arr[i];
        arr[i] = (17 * arr[i] + 9) % 257;
    }

    int max2_3x = -5, max2_3i = -7;
    int largest_i = 0;
    if (size > 2){
        for (int i = 1; i < 3; i++){
            if (arr[i] > arr[largest_i]) largest_i = i;
        }

        for (int i = 0; i < 3; i++){
            if (arr[i] != arr[largest_i]) {
                if (max2_3i == - 7)
                    max2_3i = i;
                else if (arr[i] > arr[max2_3i])
                    max2_3i = i;
            }
        }
    }
    else if (size == 2){
        if (arr[0] > arr[1]) {
            max2_3i = 1;
        }
        else if (arr[0] < arr[1])
            max2_3i = 0;
    }

    if (max2_3i >= 0) max2_3x = arr[max2_3i];
    // cout << max2_3x << ' ' << max2_3i << endl;
    HP = HP - (max2_3x + max2_3i);
}
void revertToRootArray(int root_array[], int used_array[], int size){
    for (int i = 0; i < size; i++) {
        used_array[i] = root_array[i];
    }
}
void printArray(int array[], int size){
    for (int i = 0; i < size; i++){
        cout << array[i] << ' ';
    }
    cout << endl;
}
void eventThirteen(string file_name, int event_code, int maxHP, Knight& knight, int & rescue){
    string event_code_str = to_string(event_code);

    string line, param, number;

    ifstream file_input(file_name);

    int line_i = 0, size = 0;

    getline(file_input, line);
    stringstream ss(line);
    getline(ss, param);
    size = stoi(param);
    // cout << "size: " << size << endl;

    int arr1[size];

    while (getline(file_input, line))
    {
        // cout << file_name;
        stringstream ss(line);
        while (getline(ss, param, ','))
        {
            arr1[line_i] = stoi(param);
            // cout << arr1[line_i] << endl;
            line_i++;
        }
    }

    int arr2[size], arr3[size], arr4[size];
    for (int i = 0; i < size; i++){
        // cout <<number[i] << ' ';
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
    }

    for (int i = 2; i < event_code_str.length(); i++){
        switch (event_code_str[i])
        {
        case '1':
            // printArray(arr1, size);
            mushroomType1(knight.HP, arr1, size);
            // cout << "Type 1 " << knight.HP << endl;
            break;
        case '2':
            // printArray(arr2, size);
            mushroomType2(knight.HP, arr2, size);
            // cout << "Type 2 " << knight.HP << endl;
            break;
        case '3':
            revertToRootArray(arr1, arr3, size);
            // printArray(arr3, size);
            mushroomType3(knight.HP, arr3, size);
            // printArray(arr3, size);
            // cout << "Type 3 " << knight.HP << endl;
            break;
        case '4':
            revertToRootArray(arr1, arr4, size);
            // printArray(arr4, size);
            mushroomType4(knight.HP, arr4, size);
            // printArray(arr4, size);
            // cout << "Type 4 " << knight.HP << endl;
            break;
        default:
            break;
        }

        if (knight.HP > maxHP) knight.HP = maxHP;
        else if (knight.HP <= 0){
            if (knight.phoenixdown >= 1){
                knight.phoenixdown--;
                knight.HP = maxHP;
            } 
            else break;
        }
    }
}

void eventFifteen2Seventeen(int event_code, Knight& knight){
    switch (event_code)
    {
    case 15:
        knight.remedy++;
        if (knight.remedy > 99) knight.remedy = 99;
        break;
    case 16:
        knight.maidenkiss++;
        if (knight.maidenkiss > 99) knight.maidenkiss = 99;
        break;
    case 17:
        knight.phoenixdown++;
        if (knight.phoenixdown > 99) knight.phoenixdown = 99;
        break;
    default:
        break;
    }
}

void eventNineteen(string file_name, Knight& knight, int & rescue, bool &isTiny, bool &isFrog){
    
    string line, param, number;

    ifstream file_input(file_name);

    int line_i = 0, r1 = 0, c1 = 0;

    int numDrug = 0, drug;

    // cout << file_name << endl;
    while (getline(file_input, line))
    {
        stringstream ss(line);
        // cout << line << endl;
        while (getline(ss, param, ' '))
        {
            // cout << param << endl;
            switch (line_i)
            {
            case 0:
                r1 = stoi(param);
                break;
            case 1:
                c1 = stoi(param);
                break;
            default:
                drug = stoi(param);
                // cout << "drug: " << drug << endl;
                if ((drug == 16 || drug == 17 || drug == 18) && numDrug < 3){
                    if (drug == 16){
                        knight.remedy++;
                        numDrug++;
                    } 
                    else if (drug == 17){
                        knight.maidenkiss++;
                        numDrug++;
                    } 
                    else if (drug == 18){
                        knight.phoenixdown++;
                        numDrug++;
                    }
                }
                if (knight.remedy > 99)
                    knight.remedy = 99;

                if (knight.maidenkiss > 99)
                    knight.maidenkiss = 99;

                if (knight.phoenixdown > 99)
                    knight.phoenixdown = 99;
                // cout << "Remedy: " << knight.remedy << endl 
                //     << "maidenkiss: " << knight.maidenkiss << endl 
                //     << "phoenixdown: " << knight.phoenixdown << endl;
                break;
            }
        }
        numDrug = 0;
        line_i++;
    }

    if (isTiny){isTiny = 0;}
    if (isFrog){isFrog = 0;}
}

void hpIs999(int event_code, Knight &knight, int & rescue){
    if (event_code >= 1 && event_code <= 5){
        knight.level++;
        if (knight.level >= 10) knight.level = 10;
    }
    else if (event_code == 6){
        knight.level += 2;
        if (knight.level >= 10)
            knight.level = 10;
    }
    else if (event_code == 7){
        knight.level += 2;
        if (knight.level >= 10)
            knight.level = 10;
    }
    else if (event_code == 99){}
}

bool isMerlin(string name){
    bool is_M = 0, is_E = 0, is_R = 0, is_L = 0, is_I = 0, is_N = 0;

    for (int i = 0; i < name.length(); i++)
    {
        if (name[i] == 'm' || name[i] == 'M')
            is_M = true;

        else if (name[i] == 'e' || name[i] == 'E')
            is_E = true;

        else if (name[i] == 'r' || name[i] == 'R')
            is_R = true;

        else if (name[i] == 'l' || name[i] == 'L')
            is_L = 1;

        else if (name[i] == 'i' || name[i] == 'I')
            is_I = 1;

        else if (name[i] == 'n' || name[i] == 'N')
            is_N = 1;
    }

    // cout << is_M << is_E << is_R << is_L << is_I << is_N << endl;
    if (is_M && is_E && is_R && is_L && is_I && is_N)
        return true;

    return false;
}
void eventEighteen(string file_name, int maxHP, int &HP){
    string line, param, number;

    ifstream file_input(file_name);

    int line_i = 0, n9 = 0;

    int line_len = 0;

    bool fullMerlin = false;
    while (getline(file_input, line))
    {
        stringstream ss(line);
        if (line_i == 0){
            line_i++;
            continue;
        }

        size_t merlinPos = line.find("merlin");
        size_t merlinUpPos = line.find("Merlin");

        if ((merlinPos != string::npos) || (merlinUpPos != string::npos)) {
            HP += 3;
            // cout << "+3\n";
            fullMerlin = true;
        }

        if (isMerlin(line) && !fullMerlin){
            // cout << "Merlin: " << line << "+2\n";
            HP += 2;
        }
        if (HP > maxHP) HP = maxHP;
        line_i++;
        fullMerlin = false;
    }
    // cout << "Merlin HP: " << HP << endl;
}

void traverseEvent(int event_param[], int num_events, string file_param[], Knight &knight, int &rescue)
{
    int maxHP = knight.HP;
    rescue = -1;

    bool is_event6 = false, is_tiny = false;
    bool is_event7 = false, is_frog = false;
    bool is_event18 = false, is_event19 = false;
    int event6_time = 3, event7_time = 3;

    bool event_continue = true;
    int level_zero = 0;

    // cout << num_events << endl;
    for (int event = 0; event < num_events; event++)
    {
        event_continue = true;
        int event_code = event_param[event];

        if (event_code == -1)
            break;

        if (event_code == 0)
        {
            eventZero(knight, rescue);
            event_continue = false;
            break;
        }
        else if (event_code == 1 || event_code == 2 || event_code == 3 || event_code == 4 || event_code == 5)
        {
            if (maxHP == 999 || isPrime(maxHP)) hpIs999(event_code, knight, rescue);
            else eventOneToFive(event_code, event + 1, maxHP, knight, rescue);
        }
        else if (event_code == 6)
        {
            if (maxHP == 999 || isPrime(maxHP)) hpIs999(event_code, knight, rescue);

            else {
                if (is_tiny || is_frog) {}
                
                else
                {
                    is_event6 = true;
                    event6_time = 3;
                    eventSix(is_tiny, event + 1, event6_time, maxHP, knight, rescue);
                }
            }

        }
        else if (event_code == 7)
        {
            if (maxHP == 999 || isPrime(maxHP)) hpIs999(event_code, knight, rescue);

            else
            {
                if (!is_event7)
                {
                    level_zero = knight.level;
                }

                if (is_tiny || is_frog)
                {
                }
                else
                {
                    is_event7 = true;
                    event7_time = 7;
                    eventSeven(is_frog, event + 1, event7_time, maxHP, knight, rescue);
                }
            }
        }
        else if (event_code == 11)
        {
            eventEleven(maxHP, knight, rescue);
        }
        else if (event_code == 12)
        {
            eventTwelve(knight.HP);
        }
        else if (to_string(event_code).find("13") != string::npos)
        {
            if (file_param[0] != "")
            {
                eventThirteen(file_param[0], event_code, maxHP, knight, rescue);
            }
        }
        else if (event_code == 16 || event_code == 17 || event_code == 15)
        {
            eventFifteen2Seventeen(event_code, knight);
        }
        else if (event_code == 19)
        {
            if (file_param[1] != "" && !is_event19)
            {
                // cout << "Event 19\n";
                eventNineteen(file_param[1], knight, rescue, is_tiny, is_frog);
                is_event19 = true;
            }
        }
        else if (event_code == 99)
        {
            if (maxHP == 999 || (isPrime(maxHP) && knight.level >= 8) || knight.level >= 10)
                knight.level = 10;
            else
            {
                rescue = 0;
                break;
            }
        }
        else if (event_code == 18)
        {
            if (file_param[2] != "" && !is_event18)
            {
                eventEighteen(file_param[2], maxHP, knight.HP);
                is_event18 = true;
            }
        }

        // Sau mỗi sự kiện, nếu rescue = 0 thì hành trình dừng lại, thoát vòng lặp
        if (rescue == 0){
            display(knight.HP, knight.level, knight.remedy, knight.maidenkiss, knight.phoenixdown, rescue);
            return;
        }


        if (knight.HP <= 0)
        {
            if (knight.phoenixdown == 0)
            {
                rescue = 0;
                display(knight.HP, knight.level, knight.remedy, knight.maidenkiss, knight.phoenixdown, rescue);
                return;
            }
            else if (knight.phoenixdown > 0)
            {
                knight.phoenixdown--;
                knight.HP = maxHP;
                rescue = -1;
            }
        }

        // Trong trường hợp nhặt được remedy -> sử dụng cho sự kiện 6: Hóa nhỏ
        if (knight.remedy > 0 && is_tiny){
            is_event6 = false;
            is_tiny = false;
            knight.HP = (knight.HP * 5) > maxHP ? maxHP :  (knight.HP * 5);
            event6_time = 0;
            knight.remedy--;
        }

        // Trong trường hợp nhặt được maidenkiss -> sử dụng cho sự kiện 7: Hóa ếch
        if (knight.maidenkiss > 0 && is_frog){
            is_event7 = false;
            is_frog = false;
            knight.level = level_zero;
            event7_time = 0;
            knight.maidenkiss--;

        }

        // Không có remedy cho sự kiện 6, xét số sự kiện đã trải qua tại sự kiện đang đứng
        if (is_event6)
        {
            if (event6_time > 0)
                event6_time--;
            else if (is_event6 && event6_time == 0)
            {
                if (is_tiny){
                    knight.HP = knight.HP * 5;
                    if (knight.HP > maxHP) knight.HP = maxHP;
                } 
                is_event6 = false;
            }
        }

        // Không có maidenkiss cho sự kiện 7, xét số sự kiện đã trải qua tại sự kiện đang đứng
        if (is_event7)
        {
            if (event7_time > 0)
                event7_time--;
            else if (event7_time == 0)
            {
                if (is_frog){
                    knight.level = level_zero;
                } 
                is_event7 = false;
            }
        }

        if (event < num_events - 1){
            event_continue = true;
        } 
        else event_continue = false;

        if (event_continue){
            display(knight.HP, knight.level, knight.remedy, knight.maidenkiss, knight.phoenixdown, rescue);
        }
    }

    if (rescue == -1)
        rescue = 1;

    display(knight.HP, knight.level, knight.remedy, knight.maidenkiss, knight.phoenixdown, rescue);
}

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int knight_param[5];
    string file_param[3];
    string event_string;
    int num_events;

    Knight knight = Knight(HP, level, remedy, maidenkiss, phoenixdown);

    initArray(knight_param, file_param);
    readFile(file_input, knight_param, event_string, file_param, num_events);

    int event_param[num_events];
    initEventArray(event_param, event_string, num_events);

    // ******* Knight parameter *********
    initKnight(knight_param, knight, rescue);

    // ******* Đọc và thao tác với các sự kiện ******
    traverseEvent(event_param, num_events, file_param, knight, rescue);

}
