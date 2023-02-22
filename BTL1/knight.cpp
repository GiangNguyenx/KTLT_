#include "knight.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
int i = 1;
int b = i % 10;
int levelO = i > 6 ? (b > 5 ? b : 5) : b;

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
    
}

void eventZero(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){

}
    
        

void round0(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue){
    rescue=1;
}

void round1(int i, int b, int levelO,int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue )
{
    int i = 1, basedamage=1, damage;
    int b = i % 10;
    int levelO = i > 6 ? (b > 5 ? b : 5) : b;
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

    // Knight parameter
    HP = knight_param[0];
    level = knight_param[1];
    remedy = knight_param[2];
    maidenkiss = knight_param[3];
    phoenixdown = knight_param[4];

    // Event parameter

    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    // cout << phoenixdown << endl;
    // cout << "Function isn't implemented" << endl;
}