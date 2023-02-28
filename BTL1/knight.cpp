#include "knight.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
// int i = 1;
// int b = i % 10;
// int levelO = i > 6 ? (b > 5 ? b : 5) : b;

void readFile(string fileName, int line1_param[], int line2_param[], string line3_param[])
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
        while (!ss.eof())
        {
            getline(ss, param, delimeter);
        
            // cout << delimeter << endl;
            // cout << param << endl;
            switch (line_i)
            {
            case 0:
                line1_param[line1_i] = stoi(param);
                line1_i++;
                break;
            case 1:
                line2_param[line2_i] = stoi(param);
                line2_i++;
                delimeter = ',';
                break;
            case 2:
                line3_param[line3_i] = param;
                line3_i++;
                break;
            default:
                break;
            }
        }
        line_i++;
        // cout << line_i << endl;
    }
}

void initArray(int knight_param[], int event_param[], string file_param[])
{
    for (int i = 0; i < 5; i++)
    {
        knight_param[i] = -10000;
        event_param[i] = -1;
    }

    for (int i = 0; i < 3; i++)
    {
        file_param[i] = "";
    }
}

void initKnight(int knight_param[], int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    HP = knight_param[0];
    level = knight_param[1];
    remedy = knight_param[2];
    maidenkiss = knight_param[3];
    phoenixdown = knight_param[4];
}

void eventZero(int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    rescue = 1;
    return;
}

void eventOneToFive(int event_code, int event, int maxHP, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int b = event % 10;
    int levelO = event > 6 ? (b > 5 ? b : 5) : b; // i ~ event

    // cout << b << ' ' << levelO << ' ' << level << ' ' << event << endl;
    if (level > levelO)
    {
        if (level == 10)
        {
        }
        else
        {
            level++;
        }
    }
    else if (level == levelO)
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
        // cout << damage << ' ' << levelO << baseDamage << endl;
        HP = HP - (int)damage;
        if (HP <= 0)
        {
            if (phoenixdown == 0)
            {
                rescue = 0;
                return;
            }
            else if (phoenixdown > 0)
            {
                phoenixdown--;
                HP = maxHP;
                rescue = -1;
            }
        }
    }
    // rescue = 1;
}

void eventSix(bool &is_tiny, int event, int maxHP, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int b = event % 10;
    int levelO = event > 6 ? (b > 5 ? b : 5) : b; // i ~ event
    is_tiny = false;

    // cout << b << ' ' << levelO << ' ' << level << ' ' << event << endl;
    if (level > levelO)
    {
        if (level == 10)
        {
        }
        else
        {
            level += 2;
        }
    }
    else if (level == levelO)
    {
        rescue = -1;
    }
    else
    {
        if (HP < 5) HP = 1;
        else HP = (int)(HP / 5);
        is_tiny = true;

        if (remedy >= 1){
            remedy--;
            HP = HP * 5;
            is_tiny = false;
        }
        else {
            // if (HP < 5)
            //     HP = 1;
            // else
            //     HP = (int)(HP / 5);

            // cout << "HP: " << HP << endl;
        }
        // if (HP <= 0)
        // {
        //     if (phoenixdown == 0)
        //     {
        //         rescue = 0;
        //         return;
        //     }
        //     else if (phoenixdown > 0)
        //     {
        //         phoenixdown--;
        //         HP = maxHP;
        //         rescue = -1;
        //     }
        // }
    }
}

void eventSeven(bool &is_frog, int event, int maxHP, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue){
    int b = event % 10;
    int levelO = event > 6 ? (b > 5 ? b : 5) : b; // i ~ event
    is_frog = false;

    int level_zero = level;
    // cout << b << ' ' << levelO << ' ' << level << ' ' << event << endl;
    if (level > levelO)
    {
        if (level == 10)
        {
        }
        else
        {
            level += 2;
        }
    }
    else if (level == levelO)
    {
        rescue = -1;
    }
    else {
        is_frog = true;
        level = 1;
        if (maidenkiss >= 1){
            is_frog = false;
            level = level_zero;
        }
    }
}

int oddNumberSum(int n1){
    int s1 = 0;
    for (int i = 99; i >= 1; i -= 2){
        s1 += i;
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
void eventEleven(int maxHP, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    int n1 = ((level + phoenixdown) % 5 + 1) * 3;
    int s1 = oddNumberSum(n1);

    HP = HP + (s1 % 100);
    HP = upToNearestPrime(HP);
    if (HP > maxHP) HP = maxHP;
}

bool isFibonacci(int HP){
    int sum = 1;
    if (HP = 1) return 1;
    for (int i = 1; i < HP;){
        sum += i;
        if (HP == sum) return 1;
        else if (sum > HP) return 0;
        i = sum;
    }
    return 1;
}
int downToNearestFibonacci(int HP){
    for (int i = HP - 1; i >= 1; i--){
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
        if (arr[i] > arr[maxi]) {
            maxi = i;
        }
        if (arr[i] < arr[mini])
            mini = i;
    }

    HP = HP - (maxi + mini);
}
void mushroomType2(int& HP, int arr[], int size){

}
void mushroomType3(int & HP, int arr[], int size){}
void mushroomType4(int & HP, int arr[], int size){}
void eventThirteen(string file_name, int event_code, int maxHP, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    string event_code_str = to_string(event_code);

    string line, param, number;

    ifstream file_input(file_name);

    int line_i = 0, size = 0;

    // cout << line_i << endl;
    while (getline(file_input, line))
    {
        // cout << file_name;
        stringstream ss(line);
        while (getline(ss, param, ','))
        {
            switch (line_i)
            {
            case 0:
                size = stoi(param);
                break;
            case 1:
                number += param;
                break;
            default:
                break;
            }
        }
        line_i++;
    }

    int arr[size];
    for (int i = 0; i < number.length(); i++){
        arr[i] = number[i] - '0';
    }

    for (int i = 2; i < event_code_str.length(); i++){
        switch (event_code_str[i])
        {
        case '1':
            mushroomType1(HP, arr, size);
            break;
        case '2':
            /* code */
            break;
        case '3':
            /* code */
            break;
        case '4':
            /* code */
            break;
        default:
            break;
        }

        if (HP > maxHP) HP = maxHP;
        else if (HP < 0){
            if (phoenixdown >= 1) phoenixdown--;
            else break;
        }
    }
}

void eventFifteen2Seventeen(int event_code, int & remedy, int & maidenkiss, int & phoenixdown){
    switch (event_code)
    {
    case 15:
        remedy++;
        if (remedy > 99) remedy = 99;
        break;
    case 16:
        maidenkiss++;
        if (maidenkiss > 99) maidenkiss = 99;
        break;
    case 17:
        phoenixdown++;
        if (phoenixdown > 99) phoenixdown = 99;
        break;
    default:
        break;
    }
}

void eventNineteen(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

void hpIs999(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){

}

void hpIsPrime(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){

}

void event99th(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventEighteen(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

void traverseEvent(int event_param[], string file_param[], int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int maxHP = HP;
    rescue = -1;

    bool is_event6 = false, is_tiny = false;
    bool is_event7 = false, is_frog = false;
    int event6_time = 3, event7_time = 3;

    int level_zero = 0;

    for (int event = 0; event < 5; event++)
    {
        int event_code = event_param[event];

        if (event_code == -1)
            break;

        if (event_code == 0)
        {
            eventZero(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            return;
        }
        else if (event_code == 1 || event_code == 2 || event_code == 3 || event_code == 4 || event_code == 5)
        {
            eventOneToFive(event_code, event + 1, maxHP, HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        else if (event_code == 6)
        {
            is_event6 = true;
            eventSix(is_tiny, event + 1, maxHP, HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        else if (event_code == 7){
            if (!is_event7){
                level_zero = level;
            }
            is_event7 = true;
            eventSeven(is_frog, event + 1, maxHP, HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        else if (event_code == 11){
            eventEleven(maxHP, HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        else if (event_code == 12){
            eventTwelve(HP);
        }
        else if (to_string(event_code).find("13") != string::npos){
            if (file_param[0] != "") {
            // cout << "Here\n";
                eventThirteen(file_param[0], event_code, maxHP, HP, level, remedy, maidenkiss, phoenixdown, rescue);
            }
        }

        // Sau mỗi sự kiện, nếu rescue = 0 thì hành trình dừng lại, thoát vòng lặp
        if (rescue == 0)
            return;


        if (HP <= 0)
        {
            if (phoenixdown == 0)
            {
                rescue = 0;
                return;
            }
            else if (phoenixdown > 0)
            {
                phoenixdown--;
                HP = maxHP;
                rescue = -1;
            }
        }

        if (is_event6 && event6_time > 0)
        {
            event6_time--;
        }
        else if (event6_time == 0)
        {
            if (is_tiny){
                HP = HP * 5;
                if (HP > maxHP) HP = maxHP;
            } 
            is_event6 = false;
        }

        if (is_event7 && event7_time > 0)
        {
            event7_time--;
        }
        else if (event7_time == 0)
        {
            if (is_frog){
                level = level_zero;
            } 
            is_event7 = false;
        }
    }

    if (rescue == -1)
        rescue = 1;
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
    int knight_param[5], event_param[5];
    string file_param[3];

    initArray(knight_param, event_param, file_param);
    readFile(file_input, knight_param, event_param, file_param);
    // cout << file_param[1] << endl;

    // ******* Knight parameter *********
    initKnight(knight_param, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    // ******* Đọc và thao tác với các sự kiện ******
    traverseEvent(event_param, file_param, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    // ******* In ra kết quả ******
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    // cout << "Function isn't implemented" << endl;
}
