#include "bases.h"
using namespace std;

Database::Database(){
    file_name = "";
    num_columns = 0;
    num_rows = 0;
    counter = 0;
    size_set = false;
    width_set = false;

};
Database::Database(string name){
    file_name = name;
    num_columns = 0;
    num_rows = 0;
    counter = 0;
    size_set = false;
    width_set = false;
};
int Database::Read_file(){
    ifstream input;
    input.open(file_name.c_str());
    if(!input.is_open())
        return 0;
    int m = 0;
    char ch;
    input.get(ch);
    while(!input.eof()){
        if(ch == '\n' || ch == '\r'){
            if(!width_set){
                column_width.push_back(temp.length());
                width_set = true;
            }
            else{
                if(temp.length() > column_width[counter])
                    column_width[counter] = temp.length();
                counter = 0;
            }
            row.push_back(temp);
            base.push_back(row);
            if(!size_set)
                num_columns = row.size();
            row.clear();
            temp = "";
        }
        else if (ch == '\t'){
            if(!width_set)
                column_width.push_back(temp.length());
            else{
                if(temp.length() > column_width[counter])
                    column_width[counter] = temp.length();
                counter++;
            }
            row.push_back(temp);
            temp = "";
        }
        else{
            temp += ch;
        }
        input.get(ch);
    }
    input.close();
    return 1;
};
bool Database::Check_name(){
    if(file_name == ""){
        return false;
    }
    else{
        return true;
    }
};
bool Database::Change_name(string name){
    file_name = name;
    return true;
};
void Database::Print_read(){
    system("cls");
    for(int i = 0; i < base.size(); i++){
        for(int y = 0; y < num_columns; y++){
            cout << '|' << setw(column_width[y] + 1) << base[i][y];
        }
    cout << endl;
    }
    cin.get();
};
void Database::Gotoxy(int x, int y){
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
};
