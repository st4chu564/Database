#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

class Database{
private:
    string file_name;
    vector <vector <string> > base;
    vector <string> row;
    string temp;
    vector <int> column_width;
    int counter;
    int num_columns;
    int num_rows;
    bool size_set;
    bool width_set;
public:
    Database();
    Database(string);
    int Read_file();
    bool Check_name();
    bool Change_name(string);
    void Print_read();
    void Fine_print();
    void Gotoxy(int,int);


};
