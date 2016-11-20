#include "bases.h"
using namespace std;

Database::Database(){
    file_name = "";
    max_width = 0;
    num_columns = 0;
    counter = 0;
    size_set = false;
    width_set = false;
    file_read = false;
};
Database::Database(string name){
    file_name = name;
    max_width = 0;
    num_columns = 0;
    counter = 0;
    size_set = false;
    width_set = false;
    file_read = false;
};
int Database::Give_num_columns(){
    return num_columns;
};
int Database::Read_file(){
    ifstream input;                                             	    // Prepare input file
    input.open(file_name.c_str());                              	    // Open input file
    if(!input.is_open())
        return 0;                                               	    // Opening failed, either non-existent file, or other error
    char *ch = new char;                                        	    // Declare and create temporal variable
    input.get(*ch);                                             	    // Get first character
    while(!input.eof()){                                        	    // While end of file is not reached
        if(*ch == '\n' || *ch == '\r'){
            if(!width_set){
                column_width.push_back(temp.length());          	    // Add columns to column_width vector
                if(temp.length() > max_width)                   	    // Finding maxa column width
                    max_width = temp.length();
                width_set = true;                               	    // Block adding any more column to column width
            }
            else{
                if (temp.length() > column_width[counter])      	    // Check last column length, save if grater
                    column_width[counter] = temp.length();
                if (temp.length() > max_width)
                    max_width = temp.length();
                counter = 0;                                    	    // Zero counter
            }
            row.push_back(temp);                                	    // Add temp to row, to push later to base
            base.push_back(row);                                	    // Push to base
            if(!size_set)
                num_columns = row.size();                       	    // Set number of columns
            row.clear();                                        	    // Clear row for further use
            temp = "";                                          	    // Clear temporary string for further use
        }
        else if (*ch == '\t'){                                  	    // Add columns to column_width vector
            if(!width_set){
                column_width.push_back(temp.length());
                if(temp.length() > max_width)
                    max_width = temp.length();
            }
            else{
                if(temp.length() > column_width[counter])       	    // Check current field length, save if greater
                    column_width[counter] = temp.length();
                if(temp.length() > max_width)
                    max_width = temp.length();
                counter++;                                      	    // Next column
            }
            row.push_back(temp);                                	    // Prepare row to push to base
            temp = "";                                          	    // Clear string for next field
        }
        else{
            temp += *ch;                                        	    // Add single read char, to string
        }
        input.get(*ch);                                             	// Read single char from file
    }
    input.close();                                                  	// Close input file
    delete ch;                                                      	// Release useless char variable
    file_read = true;                                               	// Mark file as read
    row.clear();                                                    	// Clear vector for further use
    temp = "";                                                      	// Clear string for further use
    return 1;                                                       	// Read succesful
};
int Database::Save_file_trunc(){
    ofstream output;
    output.open(file_name.c_str(), std::ofstream::trunc);
    if(!output.is_open())
        return 0;
    for(int i = 0; i < base.size(); i++){
        for(int y = 0; y < num_columns; y++)
            if(y == num_columns - 1)
                output << base[i][y];
            else
                output << base[i][y] << '\t';
        output << endl;
    }
    output.close();
    return 1;
};
int Database::Save_file_trunc(string name){
    ofstream output;
    output.open(name.c_str(), std::ofstream::trunc);
    if(!output.is_open())
        return 0;
    for(int i = 0; i < base.size(); i++){
        for(int y = 0; y < num_columns; y++)
            if(y == num_columns - 1)
                output << base[i][y];
            else
                output << base[i][y] << '\t';
        output << endl;
    }
    output.close();
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
bool Database::Check_read(){
    return file_read;
};
bool Database::Change_name(string name){
    file_name = name;
    return true;
};
void Database::Add_single_row(){
    system("cls");                                                  	// Clear screen
    cout << "Przykladowy wpis: " << endl;                           	// Example
    for(int i = 0; i < 2; i++){
        for(int y = 0; y < num_columns; y++){
            cout << '|' << setw(column_width[y] + 1) << base[i][y];
        }
    cout << endl;
    }
    cout << endl << endl;                                           	// Few lines of space
    cout << base[0][0] << ": " << base.size();   	                    // Auto set id to last + 1
    temp = to_string(base.size());                                 // Set id to last + 1
    row.push_back(temp);
    cout << endl;                                                       // Make it look pretty-ish
    for(int i = 1; i < num_columns; i++){                               // Prompt and read user input
        cout << base[0][i] << ":\t\t";                                  // Cosmetics
        getline(cin, temp);                                             // Save input
        row.push_back(temp);                                            // Push input to intermediary vector
    }
    cout << "Zostaly wprowadzone nastepujace dane: " << endl;
    for(int y = 0; y < num_columns; y++)                               // Make sure correct data was entered
        cout << '|' << setw(column_width[y] + 1) << base[0][y];
    cout << endl;
    for(int i = 0; i < num_columns; i++)
        cout << '|' << setw(column_width[i] + 1) << row[i];             // Print entered data
    char *answer = new char;
    cout << endl << "Dodac wprowadzone dane do bazy? (t/n) ";
    *answer = getch();
    *answer = tolower(*answer);
    if(*answer == 't'){
        base.push_back(row);                                            // Push intermediary to base vector
        cout << "\nDane dodane do bazy." << endl;
    }
    else
        cout << "\nOdrzucono zmiany, nic nie zostalo dodane." << endl;   // Data not added, changes discarded
    delete answer;                                                      // Release answer
    row.clear();                                                        // Clear vector for further use
    temp = "";                                                          // Clear string for further use
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
