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
    fileName = name;
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
    input.open(fileName.c_str());
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
int prepareDatabase::saveBase(){
    ofstream output;
    output.open(fileName.c_str());
    if(!output.is_open())
        return 1;
    for(int i = 0; i < baseFilesNames.size(); i++)
        output << baseFilesNames[i] << endl;
    output.close();
    return 0;
}
Database::Database(){
    file_name = "";
    maxWidth = 0;
    numColumns = 0;
    columnCounter = 0;
    editMethod = 0;
    lastSavedRecord = 0;
    rRC = 1;
    size_set = false;
    width_set = false;
    file_read = false;
};
Database::Database(string name){
    file_name = name;
    maxWidth = 0;
    numColumns = 0;
    columnCounter = 0;
    editMethod = 0;
    lastSavedRecord = 0;
    rRC = 1;
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
string Database::getName(){
    return file_name;
};
int Database::getNumColumns(){
    return numColumns;                                                 // Return number of columns
};
int Database::getNumRows(){
    return base.size();
};
int Database::readFile(){
    ifstream input;                                             	    // Prepare input file
    input.open(file_name.c_str());                              	    // Open input file
    if(!input.is_open())
        return 0;                                               	    // Opening failed, either non-existent file, or other error
    else if(input.peek() == std::ifstream::traits_type::eof())          // Check if file is empty
        return 2;
    char *ch = new char;                                        	    // Declare and create temporal variable
    input.get(*ch);                                             	    // Get first character
    while(!input.eof()){                                        	    // While end of file is not reached
        if(*ch == '\n' || *ch == '\r'){
            if(!width_set){
                columnWidth.push_back(temp.length());          	    // Add columns to columnWidth vector
                if(temp.length() > maxWidth)                   	    // Finding max column width
                    maxWidth = temp.length();
                width_set = true;                               	    // Block adding any more column to column width
            }
            else{
                if (temp.length() > columnWidth[columnCounter])      	// Check last column length, save if grater
                    columnWidth[columnCounter] = temp.length();
                if (temp.length() > maxWidth)
                    maxWidth = temp.length();
                columnCounter = 0;                                    	// Zero counter
            }
            row.push_back(temp);                                	    // Add temp to row, to push later to base
            base.push_back(row);                                	    // Push to base
            if(!size_set)
                numColumns = row.size();                       	    // Set number of columns
            row.clear();                                        	    // Clear row for further use
            temp = "";                                          	    // Clear temporary string for further use
        }
        else if (*ch == '\t'){                                  	    // Add columns to columnWidth vector
            if(!width_set){
                columnWidth.push_back(temp.length());
                if(temp.length() > maxWidth)
                    maxWidth = temp.length();
            }
            else{
                if(temp.length() > columnWidth[columnCounter])       	    // Check current field length, save if greater
                    columnWidth[columnCounter] = temp.length();
                if(temp.length() > maxWidth)
                    maxWidth = temp.length();
                columnCounter++;                                      	    // Next column
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
    lastSavedRecord = base.size();                                  // Mark the last saved ( read here) record
    return 1;                                                       	// Read succesfull
};
int Database::saveFile(string whereTo){
    if (editMethod == 2 && file_read)
        saveFileAdd(whereTo);
    else
        saveFileTrunc(whereTo);
};
int Database::saveFileAdd(string name){
    ofstream output;
    output.open(name.c_str(), std::ofstream::app);
    if (!output.is_open())
        return 1;
    for(int i = lastSavedRecord; i < base.size(); i++){
        for(int y = 0; y < numColumns; y++)
            if(y == numColumns - 1)                                     // If it's not the end of a line, output element
                output << base[i][y];
            else                                                        // If it is, output element and seperator \t
                output << base[i][y] << '\t';
        output << endl;
    }
    editMethod = 0;
    lastSavedRecord = base.size();
    return 0;
};
int Database::saveFileTrunc(string name){                               // Save as above, but with name passed as parameter
    ofstream output;                                                    // Save file, destroying previous content in file, if any
    output.open(name.c_str(), std::ofstream::trunc);                    // Create output file
    if(!output.is_open())                                               // Check if output is open
        return 1;                                                       // If not, return 0
    else if (editMethod == 0)                                           // If file was not editted, return -1
        return -1;
    for(int i = 0; i < base.size(); i++){                               // Actual saving loop
        for(int y = 0; y < numColumns; y++)                             // Another loop to go through each element
            if(y == numColumns - 1)                                     // If it's not the end of a line, output element
                output << base[i][y];
            else                                                        // If it is, output element and seperator \t
                output << base[i][y] << '\t';
        output << endl;                                                 // Endline after each row
    }
    output.close();                                                     // Close file
    editMethod = 0;
    lastSavedRecord = base.size();
    return 0;                                                           // Return 1, after everything went better than expected
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
bool Database::changeValue(string column, string val){
    int place = findRow(column);
    if(place != -1){
        base[rRC][place] = val;
        editMethod = 1;
        setWidth();
        return true;
    }
    else
        return false;
};
bool Database::setName(string name){                                    // set file name
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
vector <vector <string>> Database::searchFor(string rowName, string criteria, int choice){
    vector <vector <string>> toReturn;
    int place = findRow(rowName);
    if(place == -1)
        return toReturn;
    toReturn.push_back(base[0]);
    if(choice == 1)
        for(int i = 1; i < base.size(); i++){
            std::size_t found = base[i][place].find(criteria);
            if(found!=std::string::npos)
                toReturn.push_back(base[i]);
        }
    else if(choice == 2)
        for(int i = 1; i < base.size(); i++)
            if(base[i][place].compare(criteria) == 0)
                toReturn.push_back(base[i]);
    return toReturn;
};
void Database::setWidth(){
    if(!width_set){
        for(int i = 0; i < numColumns; i++)
            columnWidth.push_back(base[0][i].length());
        width_set = true;
    }
    for(int i = 0; i < columnWidth.size(); i++)
        columnWidth[i] = 0;
    for(int i = 0; i < base.size(); i++){
        for(int y = 0; y < numColumns; y++)
            if(columnWidth[y] < base[i][y].length())
                columnWidth[y] = base[i][y].length();
    }
};
void Database::addRow(vector <vector <string>> dataToPush){
    numColumns = dataToPush[0].size();
    for(int i = 0; i < dataToPush.size(); i++){
        base.push_back(dataToPush[i]);
    }
    setWidth();
    if(editMethod != 1)
        editMethod = 2;
};
vector <string> Database::getHeaders(){
    return base[0];                                                     // Return header row
};
vector <string> Database::getOneRow(char which){
    if(which == 'f')
        return base[rRC];                                               // Return first row
    else if(which == 'n' && rRC < base.size() - 1)
        return base[++rRC];                                             // Return next row
    else if(which == 'p' && rRC > 1)
        return base[--rRC];                                             // Return previous row
    return vector <string>();                                           // Empty if outbounds
};
void Database::resetRRC(){
rRC = 1;                                                                // Reset Row Counter
};
int Database::removeRow(int which){
    if(which > base.size() || which == 0)
        return 1;
    base.erase(base.begin() + which);
    editMethod = 1;
    return 0;
};
int Database::getLastID(){
    if(base.size() > 1)
        return stoi(base[base.size() - 1][0]) + 1;
    else
        return 1;
};
