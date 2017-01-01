#include "bases.cpp"

using namespace std;

int main(){
    prepareDatabase* index = NULL;
    vector <string> fileIndex, toPush, tempBeforePush;
    vector <Database*> entry;
    string temp, tempName, name;
    int x = 1, y = 2,a, freeUse, currentFileIndex = -1;
    while(a != 7){
    int *swNumber = new int;
    int *error = new int;
    if(currentFileIndex != -1)
        cout << "\tAktualny plik: " << entry[currentFileIndex]->returnName() << endl;
    cout << "\tCo chcesz robic?" << endl;
    cout << "\t1. Wczytac baze" << endl;
    cout << "\t2. Stworzyc nowy baze" << endl;
    cout << "\t3. Wyswietlic plik" << endl;
    cout << "\t4. Edytowac plik" << endl;
    cout << "\t5. Wyswietlanie szczegolowe" << endl;
    cout << "\t6. Zapisanie pliku" << endl;
    cout << "\t7. Zakonczyc prace" << endl;
    cin >> a;
    switch(a){
        case 1: {
            cout << "Podaj nazwe pliku glownego: ";
            cin >> tempName;
            index = new prepareDatabase(tempName);
            if(index->fileRead() == 1){
                cout << "Blad otwarcia pliku, sprobuj jeszcze raz" << endl;
                delete index;
            }
            else{
                cout << "Wczytano poprawnie, baza gotowa do dalszych operacji" << endl;
                //*entry = index->openBaseFiles();
                index->openBaseFiles(&entry);
                for(int i = 0; i < entry.size(); i++)
                    cout << entry[i]->returnName() << endl;
                currentFileIndex = 0;
                entry[currentFileIndex]->readFile();

            }
            system("pause");
            break;
        }
        case 2: {
            if(entry.size() > 0){
                cout << "Baza jest juz otwarta, nie mozna tworzyc nowej" << endl;
                system("pause");
                break;
            }
            cout << "Podaj nazwe pliku : ";
            cin >> name;
            entry.push_back(new Database(name));
            system("pause");
            currentFileIndex = 0;
            entry[currentFileIndex]->addMultipleRows();
            break;
        }
        case 3: {
            system("cls");
            cout << "\t1. Wyswietlic caly plik" << endl;
            cout << "\t2. Wyswietlic pojedyncza linie" << endl;
            cin >> freeUse;
            if(entry.size() == 0)
                cout << "Nie utworzony bazy, nie ma co wyswietlic" << endl;
            else if (freeUse == 1)
                entry[currentFileIndex]->printRead();
            else if (freeUse == 2)
                entry[currentFileIndex]->printOneRow();
            else
                cout << "Nie rozpoznano komendy, powrot do glownego menu" << endl;
            cin.sync();
            cin.clear();
            cin.get();
            break;
        }
        case 4: {
            if(entry.size() == 0){
                cout << "Nie utworzono bazy, nie mozna edytowac" << endl;
                cin.sync();
                cin.clear();
                cin.get();
                break;
            }
            cout << "\t\t\t Edytowanie" << endl;
            system("cls");
            fflush(stdin);
            cout << "\t\t 1. Dodaj pojedynczy rekord" << endl;
            cout << "\t\t 2. Dodaj wiele rekordow" << endl;
            cout << "\t\t 3. Powrot do glownego menu" << endl;
            char* tempSwitch = new char;
            cin >> *tempSwitch;
            cin.ignore();
            switch(*tempSwitch){
                case '1':{
                    if(entry[currentFileIndex]->returnHeaders(&tempBeforePush) != 0){
                        cout << "Baza jest pusta, podaj naglowki ( id dodawane automatycznie, q aby przerwaæ)" << endl;
                        toPush.push_back("id");
                        do{
                            cout << "Podaj nazwe kolumny: ";
                            cin >> temp;
                            if(tolower(temp.c_str() != "q"))
                                toPush.push_back(temp);
                        }while(tolower(temp.c_str() != "q"));
                        entry[currentFileIndex]->addRow(toPush);
                        toPush.clear();
                    }
                    for(int i = 0; i < tempBeforePush.size(); i++){
                        if(tolower(temp.c_str() != "q") && i > 0){
                            cout << tempBeforePush[i] << " : ";
                            cin >> temp;
                        }
                        else if (i == 0){
                            cout << tempBeforePush[i] << " : " << i + 1 << endl;
                            toPush.push_back(to_string(i));
                        }
                        //else
                    }
                    //entry[currentFileIndex]->addRow();
                    break;
                }
                case '2':{
                    do{
                        //entry[currentFileIndex]->addRow();
                        cout << "Chcesz dodac nastepna linie? (t/n)";
                        *tempSwitch = getch();
                        if(tolower(*tempSwitch) != 't' && tolower(*tempSwitch) != 'n')
                            cout << "Odpowiedz nie rozpoznana, konczenie pracy" << endl;
                    }while(tolower(*tempSwitch) == 't');
                    break;
                }
                case '3':{
                    cout << "Powrot do glownego menu" << endl;
                    break;
                }
            }
            getch();
            delete tempSwitch;
            break;
        }
        case 5: {
            cout << "Wyswietlanie" << endl;
            cin.get();
            cin.get();
            break;
        }
        case 6: {
            system("cls");
            cout << "\t1. Zapis do tego samego pliku" << endl;
            cout << "\t2. Zapis do innego pliku" << endl;

            cin >> *swNumber;
            switch(*swNumber){
                case 1:
                    if(!entry[currentFileIndex]->checkName()){
                        cout << "Podaj nazwe pliku: ";
                        cin >> name;
                        entry[currentFileIndex]->changeName(name);
                    }
                    else if(entry[currentFileIndex]->checkRead())
                        cout << "Zapisywanie, z zastapieniem poprzednich danych" << endl;
                    *error = entry[currentFileIndex]->saveFileTrunc();
                    if(*error == 1)
                        cout << "Zapis udany" << endl;
                    else if (*error == 0)
                        cout << "Blad otwarcia, nie zapisano nic";

                    else if(*error == -1)
                        cout << "Nie wprowadzono zmian do bazy, zaniechano zapisu" << endl;
                    delete error;
                    system("pause");
                    break;
                case 2: cout << "Podaj nazwe pliku i rozszerzenie: ";
                    cin >> tempName;
                    *error = entry[currentFileIndex]->saveFile(tempName);
                    if(*error == 1)
                        cout << "Zapis udany" << endl;
                    else if (*error == 0)
                        cout << "Blad otwarcia, nie zapisano nic";
                    else if (*error == -1)
                        cout << "Nie wprowadzono zmian w pliku, zaniechano zapisu" << endl;
                    cin.clear();
                    cin.sync();
                    cin.get();
                break;
                cin.get();

            }
            break;
        }
        case 7: exit;
        break;
        default: {
            cout << "Nie poprawna opcja, podaj jeszcze raz" << endl;
            cin.get();
            cin.get();
            break;
        }
    }
        cin.clear();
        cin.sync();
        system("cls");
    }
    for(vector <Database*>::iterator it = entry.begin(); it != entry.end(); ++it)
        delete (*it);
    entry.clear();
    delete index;
    return 1;
}
