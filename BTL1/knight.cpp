#include "knight.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>

void readFile(string fileName)
{
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
void round0(){

    }
int levelO[];
for(int i=1;i<=5;i++){}
    void round1(){

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
    cout << "Function isn't implemented" << endl;
}