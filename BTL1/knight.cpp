#include "knight.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
int i=1;
int b=i%10;
int levelO=i > 6?(b > 5?b : 5) : b;

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
    string line;
    string str;
    while (getline(file_input, str))
    {
        stringstream ss(str);
        while (ss >> line)
        {
        }
    }
}

void round0()
{
    
}

void round1()
{ int i=1;
  int b=i%10;
  int levelO=i > 6?(b > 5?b : 5) : b;
  
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

    readFile(file_input, knight_param, event_param, file_param);
    HP = knight_param[0];


    cout << "Function isn't implemented" << endl;
}