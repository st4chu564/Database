#include "bases.h"
using namespace std;
template<typename T>
std::string to_string(const T& obj)
{
    std::stringstream ss;
    ss << obj;
    return ss.str();
}
prepareDatabase::prepareDatabase(string name){
    read = false;
    file_name = name;
};
int prepareDatabase::addFilesToBase(string name){
    baseFilesNames.push_back(name);
    return 1;
};
int prepareDatabase::openBaseFiles(vector <Database*>* create){
        for(int i = 0; i < baseFilesNames.size(); i++){
            create->push_back(new Database(baseFilesNames[i]));
        }
        return 1;
};
bool prepareDatabase::checkRead(){
    return read;
};
int prepareDatabase::fileRead(){
    ifstream input;
    input.open(file_name.c_str());
    if(!input.is_open()){
        return 1;
    }
    while(!input.eof()){
        input >> temp;
        baseFilesNames.push_back(temp);
        temp = "";
    }
    read = true;
    input.close();
    return 0;
};
int prepareDatabase::checkNameCorrectness(){
    for(int i = 0; i < baseFilesNames.size(); i++){
        int found = baseFilesNames[i].find(".txt");
        if(found == std::string::npos || found != (baseFilesNames[i].length() - 4))
            return 1; // Name does not have an extension
    }
    return 0; // Name does have an .txt extension, it's correct
};
int prepareDatabase::openFile(Database* base){

};
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
int Database::findRow(string criteria){
        for(int i = 0; i < base[0].size(); i++)
            if(base[0][i].compare(criteria) == 0)
                return i;
    return -1;
};
string Database::returnName(){
    return file_name;
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
    return saveFileTrunc(file_name);
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
int Database::sortFileBy(string criteria){
    int place = findRow(criteria);
    if(place == -1)
        return -1;
    sort(base.begin() + 1, base.end(),
            [&place](const std::vector<string>& a, const std::vector<string>& b) {
    return a[place] < b[place];
});
return 0;
};
vector <vector <string>> Database::searchFor(string rowName, string criteria){
    vector <vector <string>> toReturn;
    int place = findRow(rowName);
    if(place == -1)
        return toReturn;
    toReturn.push_back(base[0]);
    for(int i = 1; i < base.size(); i++)
        if(base[i][place].compare(criteria) == 0)
            toReturn.push_back(base[i]);
    return toReturn;
};
int Database::returnHeaders(vector <string>* headerLocation){
    if(base.size() > 0)
        headerLocation = &base[0];
    else
        return 0;
};
void Database::setWidth(){
    if(!width_set){
        for(int i = 0; i < num_columns; i++)
            column_width.push_back(base[0][i].length());
        width_set = true;
    }
    for(int i = 1; i < base.size(); i++){
        for(int y = 0; y < num_columns; y++)
            if(column_width[y] < base[i][y].length())
                column_width[y] = base[i][y].length();
    }
};
void Database::addRow(vector <vector <string>> dataToPush){
    num_columns = dataToPush[0].size();
    for(int i = 0; i < dataToPush.size(); i++){
        base.push_back(dataToPush[i]);
    }
    setWidth();
    editMethod = 1;
};
vector <int> Database::giveColumnWidth(){
    return column_width;
};
vector <string> Database::printOneRow(int which){
    return base[which];
};
/*vector <int> Database::giveWidth(){
    return column_width;
};*/
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
