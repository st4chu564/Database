#include "bases.cpp"

using namespace std;

int main(){
    prepareDatabase* index = NULL;
    vector <string> fileIndex, headers, tempBeforePush, singleRow;
    vector < vector <string>> toPush, searchResult;
    vector <Database*> entry;
    string temp, temp2, tempName, name;
    char answer, toI;
    int x = 1, y = 2,a = 1, freeUse, cFI = -1;
    while(a != 0){
    int *swNumber = new int;
    int *error = new int;
    if(cFI != -1)
        cout << "\tAktualny plik: " << entry[cFI]->getName() << endl;
    cout << "\tCo chcesz robic?" << endl;
    cout << "\t1. Wczytac baze" << endl;
    cout << "\t2. Stworzyc nowa baze" << endl;
    cout << "\t3. Wyswietlic plik" << endl;
    cout << "\t4. Edytowac plik" << endl;
    cout << "\t5. Wyswietlanie szczegolowe" << endl;
    cout << "\t6. Zapisanie pliku" << endl;
    cout << "\t7. Zmienic plik" << endl;
    cout << "\t8. Sortowanie" << endl;
    cout << "\t9. Wyszukiwanie" << endl;
    cout << "\t0. Zakonczyc prace" << endl;
    a = (toI = getch()) - '0';
    switch(a){
        case 1: {
            if(index == NULL){
                cout << "Podaj nazwe pliku glownego: ";
                cin >> tempName;
                index = new prepareDatabase(tempName);
                if(index->fileRead() == 1){
                    cout << "Blad otwarcia pliku, sprobuj jeszcze raz" << endl;
                    delete index;
                    index = NULL;
                }
                else{
                    cout << "Wczytano poprawnie, baza gotowa do dalszych operacji" << endl;
                    index->openBaseFiles(&entry);
                    for(int i = 0; i < entry.size(); i++)
                        cout << entry[i]->getName() << endl;
                    cFI = 0;
                    if(entry[cFI]->readFile() != 0)
                        headers = entry[cFI]->getHeaders();
                    else
                        cout << "Blad odczytu pliku z danymi " << endl;
                }
            }
            else{
                cout << "Baza jest juz otwarta, czy chcesz ja zamknac aby otworzyc nowa? t\\n \n";
                answer = tolower(getch());
                if(answer == 't'){
                    for(vector <Database*>::iterator it = entry.begin(); it != entry.end(); ++it)
                        delete (*it);
                    entry.clear();
                    delete index;
                    cout << "Usunieto poprzednia baze, bez zapisania zmian" << endl;
                    cout << "Podaj nazwe pliku glownego: ";
                    cin >> tempName;
                    index = new prepareDatabase(tempName);
                    if(index->fileRead() == 1){
                        cout << "Blad otwarcia pliku, sprobuj jeszcze raz" << endl;
                        delete index;
                    }
                    else{
                        cout << "Wczytano poprawnie, baza gotowa do dalszych operacji" << endl;
                        index->openBaseFiles(&entry);
                        for(int i = 0; i < entry.size(); i++)
                            cout << entry[i]->getName() << endl;
                        cFI = 0;
                        if(entry[cFI]->readFile() != 0)
                            headers = entry[cFI]->getHeaders();
                        else
                            cout << "Blad odczytu pliku z danymi " << endl;
                    }
                }
                else{
                    cout << "Anulowano otwieranie bazy." << endl;
                }
            }
            system("pause");
            break;
        }
        case 2: {
            if(index != NULL){
                cout << "Baza jest juz otwarta, nie mozna tworzyc nowej" << endl;
                system("pause");
                break;
            }
            cout << "Podaj nazwe pliku glownego: ";
            cin >> name;
            index = new prepareDatabase(name);

            entry.push_back(new Database(name));
            system("pause");
            cFI = 0;
            break;
        }
        case 3: {
            if(index == NULL){
                cout << "\tNie otworzono bazy.\n\t";
                system("pause");
                break;
            }
            system("cls");
            cout << "\t1. Wyswietlic caly plik" << endl;
            cout << "\t2. Wyswietlic pojedyncza linie" << endl;
            cin >> freeUse;
            if(entry.size() == 0)
                cout << "Nie utworzony bazy, nie ma co wyswietlic" << endl;
            else if (freeUse == 1){
                system("cls");
                    headers = entry[cFI]->getHeaders();
                    for(int i = 0; i < headers.size(); i++)
                        cout << "|" << setw(entry[cFI]->column_width[i]) << headers[i];
                    cout << endl;
                    singleRow = entry[cFI]->getOneRow('f');
                    do{
                        for(int i = 0; i < singleRow.size(); i++)
                            cout << "|" << setw(entry[cFI]->column_width[i]) << singleRow[i];
                        cout << endl;
                        singleRow = entry[cFI]->getOneRow('n');
                        if(singleRow.size() == 0){
                            entry[cFI]->resetRRC();
                            break;
                        }
                    }while(true);
            }
            else if (freeUse == 2){
                if(headers.size() == 0)
                    cout << "Blad odczytu danych" << endl;
                else{
                    for(int i = 0; i < headers.size(); i++)
                        cout << "|" << setw(entry[cFI]->column_width[i]) << headers[i];
                    cout << endl;
                    singleRow = entry[cFI]->getOneRow('f');
                    for(int i = 0; i < singleRow.size(); i++)
                        cout << "|" << setw(entry[cFI]->column_width[i]) << singleRow[i];
                    cout << endl;
                    /*while(){

                    }*/

                }

            }
            else
                cout << "Nie rozpoznano komendy, powrot do glownego menu" << endl;
            cin.sync();
            cin.clear();
            system("pause");
            break;
        }
        case 4: {
            if(index == NULL){
                cout << "\tNie otworzono bazy.\n\t";
                system("pause");
                break;
            }
            cout << "\t\t\t Edytowanie" << endl;
            system("cls");
            fflush(stdin);
            cout << "\t\t 1. Dodaj pojedynczy rekord" << endl;
            cout << "\t\t 2. Dodaj wiele rekordow" << endl;
            cout << "\t\t 3. Usun rekord" << endl;
            cout << "\t\t 3. Powrot do glownego menu" << endl;
            char* tempSwitch = new char;
            cin >> *tempSwitch;
            cin.ignore();
            switch(*tempSwitch){
                case '1':{
                    if(headers.size() == 0){
                        cout << "Baza jest pusta, podaj naglowki ( id dodawane automatycznie, q aby przerwaæ)" << endl;
                        tempBeforePush.push_back("id");
                        do{
                            cout << "Podaj nazwe kolumny: ";
                            cin >> temp;
                            if(temp != "q" && temp != "Q" && temp != "id" && temp != "ID")
                                tempBeforePush.push_back(temp);
                        }while(temp != "q" && temp != "Q");
                        toPush.push_back(tempBeforePush);
                        headers = tempBeforePush;
                        tempBeforePush.clear();
                    }
                    temp = "";
                    tempBeforePush.push_back(to_string(entry[cFI]->getNumRows() + 1));
                    for(int i = 1; i < headers.size(); i++){
                        if (temp != "q" && temp != "Q"){
                            cout << headers[i] << " : ";
                            cin >> temp;
                            if (temp != "q" && temp != "Q"){
                                tempBeforePush.push_back(temp);
                                temp = "";
                            }
                            else
                                tempBeforePush.push_back(" ");
                        }
                        else
                            tempBeforePush.push_back(" ");
                    }
                    toPush.push_back(tempBeforePush);
                    entry[cFI]->addRow(toPush);
                    tempBeforePush.clear();
                    toPush.clear();
                    break;
                }
                case '2':{
                    do{
                        //entry[cFI]->addRow();
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
            if(index == NULL){
                cout << "\tNie otworzono bazy.\n\t";
                system("pause");
                break;
            }
            cout << "Wyswietlanie" << endl;
            cin.get();
            cin.get();
            break;
        }
        case 6: {
            if(index == NULL){
                cout << "\tNie otworzono bazy.\n\t";
                system("pause");
                break;
            }
            system("cls");
            cout << "\t1. Zapis do tego samego pliku" << endl;
            cout << "\t2. Zapis do innego pliku" << endl;
            cin >> *swNumber;
            switch(*swNumber){
                case 1:
                    if(!entry[cFI]->checkName()){
                        cout << "Podaj nazwe pliku: ";
                        cin >> name;
                        entry[cFI]->setName(name);
                    }
                    else if(entry[cFI]->checkRead())
                        cout << "Zapisywanie, z zastapieniem poprzednich danych" << endl;
                    *error = entry[cFI]->saveFileTrunc();
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
                    *error = entry[cFI]->saveFile(tempName);
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
        case 7: {
            if(index == NULL){
                cout << "\tNie otworzono bazy.\n\t";
                system("pause");
                break;
            }
            system("cls");
            cout << "\t1. Poprzedni plik" << endl;
            cout << "\t2. Nastepny plik" << endl;
            cout << "\t3. Wpisac numer pliku" << endl;
            cin >> freeUse;
            switch(freeUse){
                case 1:
                    if(cFI > 0){
                        cFI--;
                        freeUse = entry[cFI]->readFile();
                        if(freeUse == 0)
                            cout << "Blad odczytu pliku";
                        else
                            cout << "Wczytano poprawnie";
                        system("pause");
                    }
                    else
                        cout << "Nie da sie zmniejszyc indeksu" << endl;
                    break;
                case 2:
                    if(cFI < entry.size()){
                        cFI++;
                        freeUse = entry[cFI]->readFile();
                        if(freeUse == 0)
                            cout << "Blad odczytu pliku";
                        else
                            cout << "Wczytano poprawnie";
                        system("pause");
                    }
                    else
                        cout << "Nie da sie wiekszyc indeksu" << endl;
                    break;
                case 3:
                    do{
                    cout << "\tPodaj indeks pliku z zakresu pomiedzy 0 a " << entry.size() - 1<< " : ";
                    cin >> freeUse;
                    if(freeUse < 0 || freeUse >= entry.size())
                        cout << "Nie poprawny indeks, podaj jeszcze raz" << endl;
                    }while(freeUse < 0 || freeUse >= entry.size());
                    break;
                }
            break;
        }
        case 8: {
            if(index == NULL){
                cout << "\tNie otworzono bazy.\n\t";
                system("pause");
                break;
            }
            while(true){
                system("cls");
                cout << "\tPodaj nazwe kolumny wg ktorej sortowac: ";
                cin >> temp;
                freeUse = entry[cFI]->sortFileBy(temp);
                if(freeUse == 0){
                    system("cls");
                    headers = entry[cFI]->getHeaders();
                    for(int i = 0; i < headers.size(); i++)
                        cout << "|" << setw(entry[cFI]->column_width[i]) << headers[i];
                    cout << endl;
                    singleRow = entry[cFI]->getOneRow('f');
                    do{
                        for(int i = 0; i < singleRow.size(); i++)
                            cout << "|" << setw(entry[cFI]->column_width[i]) << singleRow[i];
                        cout << endl;
                        singleRow = entry[cFI]->getOneRow('n');
                        if(singleRow.size() == 0){
                            entry[cFI]->resetRRC();
                            break;
                        }
                    }while(true);
                    system("pause");
                    break;
                }
                else if (freeUse == -1){
                    cout << "Nie ma takiej kolumny, sprobuj jeszcze raz" << endl;
                    system("pause");
                }
            }
            break;
        }
        case 9: {
            if(index == NULL){
                cout << "\tNie otworzono bazy.\n\t";
                system("pause");
                break;
            }
            system("cls");
            cout << "\tNazwa kolumny: ";
            cin >> temp;
            cin.clear();
            cin.sync();
            cout << "\tZawartosc: ";
            getline(cin, temp2);
            searchResult = entry[cFI] -> searchFor(temp, temp2,1);
            if(searchResult.size() == 1){
                cout << "\tNie znaleziono wartosci" << endl;
                system("pause");
            }
            else{
                for(int i = 0; i < searchResult.size(); i++){
                    for(int y = 0; y < searchResult[0].size(); y++)
                        cout << '|' << setw(entry[cFI]->column_width[y] + 1) << searchResult[i][y];
                    cout << endl;
                }
                system("pause");
            }
        };
        case 0: exit;
            break;
        default: {
            cout << "Nie poprawna opcja, podaj jeszcze raz" << endl;
            system("pause");
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
