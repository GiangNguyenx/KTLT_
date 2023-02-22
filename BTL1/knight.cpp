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
    string line1, line2, line3;
    string str1, str2, str3;
    int line1_i = 0, line2_i = 0, line3_i = 0, line_i = 0;
    string line, param;

    while (getline(file_input, line))
    {
        stringstream str(line);
        while (str >> param)
        {
            switch (line_i)
            {
            case 0:
                line1_param[line1_i] = stoi(param);
                line1_i++;
                break;
            case 1:
                line2_param[line2_i] = stoi(param);
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
        line_i++;
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
        cout << damage << ' ' << levelO << baseDamage << endl;
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
                if (event < 4)
                    rescue = -1;
                else rescue = 1;
            }
        }
    }
    // rescue = 1;
}

void traverseEvent(int event_param[], int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    int maxHP = HP;
    bool is_rescued = false;
    rescue = -1;

    for (int event = 0; event < 5; event++)
    {
        int event_code = event_param[event];
        if (event_code == -1) break;
        if (event_code == 0)
        {
            eventZero(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            return;
        }
        else if (event_code == 1 || event_code == 2 || event_code == 3 || event_code == 4 || event_code == 5)
        {
            eventOneToFive(event_code, event + 1, maxHP, HP, level, remedy, maidenkiss, phoenixdown, rescue);
            if (rescue == -1)
                return;
        }
        //
    }

    // if (is_rescued) rescue = 1;
    // else if (!is_rescued) rescue = -1;
    // else rescue = 0;
}

void round0(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    rescue = 1;
}

void round1(int i, int b, int levelO, int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    // int i = 1, basedamage=1, damage;
    // int b = i % 10;
    // int levelO = i > 6 ? (b > 5 ? b : 5) : b;
    // if (level > levelO){
    //     if(level<10) level+=1;
    // }
    // else if (level == levelO)
    //     level+=0;
    // else
    // {
    //     damage = basedamage * levelO * 10;
    //     HP = HP - damage;
    // }
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
    traverseEvent(event_param, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    // ******* In ra kết quả ******
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    // cout << "Function isn't implemented" << endl;
}



#include "knight.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>

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
    string line1, line2, line3;
    string str1, str2, str3;
    int line1_i = 0, line2_i = 0, line3_i = 0, line_i = 0;
    string line, param;
        
        while (getline(file_input, line)){
            stringstream str(line);
            while (str >> param){
                switch (line_i)
                {
                    case 0:
                        line1_param[line1_i] = stoi(param);
                        line1_i++;
                        break;
                    case 1:
                        line2_param[line2_i] = stoi(param);
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
            line_i++;
        }
   
}

void initArray(int knight_param[], int event_param[], string file_param[]){
    for(int i = 0; i < 5; i++){
        knight_param[i] = -10000;
        event_param[i] = -1;
    }

    for(int i = 0; i < 3; i++){
        file_param[i] = "";
    }
}

void initKnight(int knight_param[], int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    HP = knight_param[0];
    level = knight_param[1];
    remedy = knight_param[2];
    maidenkiss = knight_param[3];
    phoenixdown = knight_param[4];
}

void eventZero(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    return;
}
    
void traverseEvent(int event_param[], int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    for (int event = 0; event < 5; event++){
        if (event_param[event] == 0) {
            eventZero(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            return;
        }
        else if (event == 1 || event == 2 || event == 3 || event == 4 || event == 5) {
            eventOneToFive(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
    
        // 
    }
}   

void eventOneToFive(int i, int b, int levelO,int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue ){
    int basedamage, damage;
    int maxHP=HP;
    for(int event=1; event<=5;event++ ){
        if(event==1) basedamage=1;
        else if(event==2) basedamage=1.5;
        else if(event==3) basedamage=4.5;
        else if(event==4) basedamage=7.5;
        else if(event==5) basedamage=9.5;
    i=event;
    b = i % 10;
    levelO = i > 6 ? (b > 5 ? b : 5) : b;    
    if (level > levelO){
        if(level<10) level+=1;
    }
    else if (level == levelO)
        level+=0;
    else
    {
        damage = basedamage * levelO * 10;
        HP = HP - damage;
    }
}
if(HP<0 && phoenixdown==0) return;
else if(HP<0 && phoenixdown!=0){
    phoenixdown-=1;
    HP=maxHP;
    }
}


void eventSix(int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue){
    int i = 6, miniHP;
    int b = i % 10;
    int levelO = i > 6 ? (b > 5 ? b : 5) : b;
    int maxHP=HP;
    if (level > levelO){
        if(level<10) level+=2;
    }
    else if (level == levelO)
        level+=0;
    else
    {HP=HP/5;
    miniHP=HP;
    }



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
    // cout << phoenixdown << endl;

    // ******* Knight parameter *********
    initKnight(knight_param, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    // ******* Đọc và thao tác với các sự kiện ******
    traverseEvent(event_param, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    // ******* In ra kết quả ******
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    // cout << "Function isn't implemented" << endl;
}