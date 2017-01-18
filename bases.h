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
#include <algorithm>

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
    int rRC;
    int counter;
    int editMethod;
    int max_width;
    int num_columns;
    int lastSavedRecord;
    bool size_set;
    bool width_set;
    bool file_read;
    int findRow(string);
public:
    Database();
    Database(string);
    vector <int> column_width;
    string getName();
    int getNumColumns();
    int getNumRows();
    int readFile();
    vector< string> getHeaders();
    int saveFile(string);
    int saveFileTrunc();
    int saveFileTrunc(string);
    int saveFileAdd();
    int saveFileAdd(string);
    bool createNewFile();
    bool checkName();
    bool checkRead();
    bool setName(string);
    int sortFileBy(string);
    void resetRRC();
    void setWidth();
    void addRow (vector <vector <string>>);
    void finePrint();
    void gotoXY(int,int);
    vector <string> getOneRow(char);
    vector <vector <string>> searchFor(string, string, int);
};

class prepareDatabase{
private:
    bool read;
    string file_name;
    vector <string> baseFilesNames;
    string temp;
public:
    prepareDatabase();
    prepareDatabase(string);
    int addFilesToBase(string);
    int checkNameCorrectness();
    int openBaseFiles(vector <Database*>* create);
    bool checkRead();
    int fileRead();
    int saveBase(string);
    int openFile(Database*);
};
