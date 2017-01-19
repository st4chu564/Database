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
    string file_name;                                           // Name of the opened file
    stringstream ss;                                            // Used in to_string conversion
    vector <vector <string> > base;                             // Main vector keeping records from file
    vector <string> row;                                        // Var keeping read for a file row to push to main vector
    string temp;                                                // Same as above, but contains only a single cell rather than whole row
    int rRC;                                                    // returnRowCounter used to keep track of returned rows
    int columnCounter;                                          // Used in setting column width while reading
    int editMethod;                                             // Changes save method
    int maxWidth;                                               // Keeps track of cell width, then it goes to vector if needed
    int numColumns;                                             //
    int lastSavedRecord;
    bool size_set;
    bool width_set;
    bool file_read;
    int findRow(string);
public:
    Database();
    Database(string);
    vector <int> columnWidth;
    string getName();
    int getNumColumns();
    int getNumRows();
    int readFile();
    vector< string> getHeaders();
    int saveFile(string);
    int saveFileTrunc(string);
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
    string fileName;
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
    int saveBase();
};
