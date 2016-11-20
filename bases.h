#include <iostream>
#include <vector>
#include <cstring>
#include <string>
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
    int max_width;
    int num_columns;
    bool size_set;
    bool width_set;
    bool file_read;
public:
    Database();
    Database(string);
    int Give_num_columns();
    int Read_file();
    int Save_file_trunc();
    int Save_file_trunc(string);
    int Seve_file_add();
    bool Check_name();
    bool Check_read();
    bool Change_name(string);
    void Add_single_row();
    void Fine_print();
    void Gotoxy(int,int);
    void Print_read();
};
