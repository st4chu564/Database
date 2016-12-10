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
#include <sstream>

#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ENTER 13

using namespace std;

class Database{
private:
    string file_name;
    stringstream ss;
    vector <vector <string> > base;
    vector <vector <string> > tempStorage;
    vector <string> row;
    string temp;
    vector <int> column_width;
    int counter;
    int editMethod;
    int max_width;
    int num_columns;
    int lastSavedRecord;
    bool size_set;
    bool width_set;
    bool file_read;
public:
    Database();
    Database(string);
    int giveNumColumns();
    int giveNumRows();
    int readFile();
    int saveFile(string);
    int saveFileTrunc();
    int saveFileTrunc(string);
    int saveFileAdd();
    int saveFileAdd(string);
    bool createNewFile();
    bool checkName();
    bool checkRead();
    bool changeName(string);
    void addRow();
    void addMultipleRows();
    void finePrint();
    void gotoXY(int,int);
    void printOneRow(/*string*/);
    void printRead();
};

class prepareDatabase{
private:
    string file_name;
    vector <string> baseFilesNames;
    string temp;
public:
    prepareDatabase();
    prepareDatabase(string);
    int fileRead();
    int openFile(Database*);
};
