#include "bases.h"
using namespace std;

Database::Database(){
    file_name = "";
    max_width = 0;
    num_columns = 0;
    counter = 0;
    editMethod = 0;
    lastSavedRecord = 0;
    size_set = false;
    width_set = false;
    file_read = false;
};
Database::Database(string name){
    file_name = name;
    max_width = 0;
    num_columns = 0;
    counter = 0;
    editMethod = 0;
    lastSavedRecord = 0;
    size_set = false;
    width_set = false;
    file_read = false;
};
int Database::giveNumColumns(){
    return num_columns;                                                 // Return number of columns
};
int Database::giveNumRows(){
    return base.size();
};
int Database::readFile(){
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
    lastSavedRecord = base.size() - 1;                                  // Mark the last saved ( read here) record
    return 1;                                                       	// Read succesful
};
int Database::saveFile(string whereTo){
    if(editMethod == 1)
        saveFileTrunc(whereTo);
    else if (editMethod == 2 && file_read)
        saveFileAdd();
    else
        saveFileTrunc(whereTo);

};
int Database::saveFileAdd(){
    saveFileAdd(file_name);
};
int Database::saveFileAdd(string name){
    ofstream output;
    output.open(name.c_str(), std::ofstream::app);
    if (!output.is_open())
        return 0;
    for(int i = lastSavedRecord; i < base.size(); i++){
        for(int y = 0; y < num_columns; y++)                            // Another loop to go through each element
            if(y == num_columns - 1)                                    // If it's not the end of a line, output element
                output << base[i][y];
            else                                                        // If it is, output element and seperator \t
                output << base[i][y] << '\t';
    }
    editMethod = 0;
    return 1;
};
int Database::saveFileTrunc(){                                          // Save file, destroying previous content in file, if any, using default file name
    saveFileTrunc(file_name);
};
int Database::saveFileTrunc(string name){                               // Save as above, but with name passed as parameter
    ofstream output;                                                    // Save file, destroying previous content in file, if any
    output.open(name.c_str(), std::ofstream::trunc);                    // Create output file
    if(!output.is_open())                                               // Check if output is open
        return 0;                                                       // If not, return 0
    else if (editMethod == 0)                                           // If file was not editted, return -1
        return -1;
    for(int i = 0; i < base.size(); i++){                               // Actual saving loop
        for(int y = 0; y < num_columns; y++)                            // Another loop to go through each element
            if(y == num_columns - 1)                                    // If it's not the end of a line, output element
                output << base[i][y];
            else                                                        // If it is, output element and seperator \t
                output << base[i][y] << '\t';
        output << endl;                                                 // Endline after each row
    }
    output.close();                                                     // Close file
    editMethod = 0;
    return 1;                                                           // Return 1, after everything went better than expected
};
bool Database::checkName(){                                             // Check if file name was set
    if(file_name == ""){
        return false;                                                   // Not set
    }
    else{
        return true;                                                    // Name set
    }
};
bool Database::checkRead(){                                             // Check if file was read
    return file_read;
};
bool Database::changeName(string name){                                 // Change file name
    file_name = name;
    return true;
};
void Database::addRow(){
    system("cls");                                                  	// Clear screen
    cout << "Przykladowy wpis: " << endl;                           	// Example database file entry
    for(int i = 0; i < 2; i++){
        for(int y = 0; y < num_columns; y++){
            cout << '|' << setw(column_width[y] + 1) << base[i][y];
        }
    cout << endl;
    }
    cout << endl << endl;                                           	// Few lines of space
    cout << base[0][0] << ": " << base.size();   	                    // Auto set id to last + 1
    ss << base.size();
    temp = ss.str();                                                    // Set id to last + 1
    row.push_back(temp);
    cout << endl;                                                       // Make it look pretty-ish
    for(int i = 1; i < num_columns; i++){                               // Prompt and read user input
        cout << base[0][i] << ":\t\t";                                  // Cosmetics
        getline(cin, temp);                                             // Save input
        row.push_back(temp);                                            // Push input to intermediary vector
    }
    cout << "Zostaly wprowadzone nastepujace dane: " << endl;
    for(int y = 0; y < num_columns; y++)                                // Make sure correct data was entered
        cout << '|' << setw(column_width[y] + 1) << base[0][y];
    cout << endl;
    for(int i = 0; i < num_columns; i++)
        cout << '|' << setw(column_width[i] + 1) << row[i];             // Print entered data
    char *answer = new char;
    cout << endl << "Dodac wprowadzone dane do bazy? (t/n) ";           // Ask for correctness of entered data
    *answer = getch();                                                  // Get answer
    *answer = tolower(*answer);                                         // Change answet to lower
    if(*answer == 't'){
        base.push_back(row);                                            // Push intermediary to base vector
        cout << "\nDane dodane do bazy." << endl;
        editMethod = 1;
    }
    else
        cout << "\nOdrzucono zmiany, nic nie zostalo dodane." << endl;  // Data not added, changes discarded
    delete answer;                                                      // Release answer
    row.clear();                                                        // Clear vector for further use
    temp = "";                                                          // Clear string for further use
};
void Database::addMultipleRows(){
    system("cls");                                                  	// Clear screen
    if (base.size() > 0){
        cout << "Przykladowy wpis: " << endl;                           // Example database entries if any available
        for(int i = 0; i < 2; i++){
            for(int y = 0; y < num_columns; y++){
                cout << '|' << setw(column_width[y] + 1) << base[i][y];
            }
        cout << endl;
        }
    cout << base[0][0] << ": " << base.size();   	                    // Auto set id to last + 1
    ss << base.size();
    temp = ss.str();                                                    // Set id to last + 1
    row.push_back(temp);
    }                                                                   // Few lines of space
    else if (base.size() == 0){
        row.push_back("id");
        column_width.push_back(2);
        cin.sync();
        cin.clear();
        do{
            temp = "";
            cout << "Podaj naglowki kolumn: (q konczy)" << endl;
            getline(cin, temp);
            if(temp != "q"){
                row.push_back(temp);
                column_width.push_back(temp.length());
            }
            else if (temp.length() == 0)
                cout << "Podano nie poprawny naglowek, sprobuj jeszcze raz" << endl;
        }while(temp != "q");
        tempStorage.push_back(row);
        num_columns = row.size();
        row.clear();
        temp = "";
    }
    do{
        cout << endl;                                                   // Make it look pretty-ish
        ss << tempStorage.size();
        temp = ss.str();
        row.push_back(temp);
        temp = "";
        ss.str("");
        for(int i = 1; i < num_columns; i++){                           // Prompt and read user input
            cout << tempStorage[0][i] << ":\t\t";                       // Cosmetics
            getline(cin, temp);
            if(temp != "q" && temp != "Q"){
                row.push_back(temp);
                if(temp.length() > column_width[i])
                    column_width[i] = temp.length();
            }
            else                                                        // Push input to intermediary vector
                do{
                    row.push_back(" ");
                    i++;
                }while(i < num_columns);
    }
    tempStorage.push_back(row);                                         // Push input row to temporal storage
    row.clear();                                                        // Clear row so it doesn't not push more data than neccessary
    }while(temp != "q" && temp != "Q");
    tempStorage.pop_back();
    for(int i = 0; i < tempStorage.size(); i++){                               // Go through each line
        for(int y = 0; y < num_columns; y++)
            cout << '|' << setw(column_width[y] + 1) << tempStorage[i][y];     // Print each field
        cout << endl;
    }

    char *answer = new char;
    cout << endl << "Dodac wprowadzone dane do bazy? (t/n) ";           // Ask for correctness of entered data
    *answer = getch();                                                  // Get answer
    *answer = tolower(*answer);                                         // Change answet to lower
    if(*answer == 't'){
        for(int i = 0; i < tempStorage.size(); i++)
            base.push_back(tempStorage[i]);
        cout << "\nDane dodane do bazy." << endl;
        editMethod = 1;
    }
    else
        cout << "\nOdrzucono zmiany, nic nie zostalo dodane." << endl;  // Data not added, changes discarded
    delete answer;                                                      // Release answer
    row.clear();                                                        // Clear vector for further use
    temp = "";                                                          // Clear string for further use

};
void Database::printOneRow(/*string which*/){
    system("cls");
    char keyboardInput = 0;
    int index = 1;
    while(keyboardInput != ESC && index < base.size()){
        for(int y = 0; y < num_columns; y++)
            cout << "|" << setw(column_width[y]) << base[0][y];
        cout << endl;
        for(int y = 0; y < num_columns; y++)
            cout << "|" << setw(column_width[y]) << base[index][y];
        if(index == base.size() - 1)
            cout << endl << "To ostatnia linia, DOWN aby skocnzyc, UP aby pokazac wczesniej" << endl;
        if((keyboardInput = getch()) != 27)
            keyboardInput = getch();
        if(keyboardInput == UP){
            if(index > 1)
                index--;
        }
        else if(keyboardInput == DOWN)
            index++;
        system("cls");
    }
    cout << "Koniec pliku" << endl;
};
void Database::printRead(){                                             // Print read content to console
    system("cls");                                                      // Clear console
    for(int i = 0; i < base.size(); i++){                               // Go through each line
        for(int y = 0; y < num_columns; y++){
            cout << '|' << setw(column_width[y] + 1) << base[i][y];     // Print each field
        }
    cout << endl;                                                       // Put endl to console
    }
    cin.get();                                                          // Wait for user input, before going further
};
void Database::gotoXY(int x, int y){                                    // Method, for changing cursor position
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
};
