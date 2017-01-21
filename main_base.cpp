#include "bases.cpp"

using namespace std;

int main(){
    prepareDatabase* index = NULL;                                              // Main base file container
    vector <string> headers, tempBeforePush, singleRow;                         // Containers to keep returned rows, and pushing vector
    vector < vector <string>> toPush, searchResult;                             // Vector containing search results (obv)
    vector <Database*> file;                                                    // vector of files in base
    string temp, temp2, tempName, name;                                         // Temporal strings
    char answer, toI;                                                           // Answer variables
    int a = 1, freeUse, cFI = -1, kurwa;                                               // cFI = Current File Index, a = switch variable, freeUse = just a free var
    while(a != 0){
    int *swNumber = new int;                                                    // Dynamic number catching
    int *error = new int;                                                       // Dynamic error catching number
    if(cFI != -1)                                                               // If base open, then display its name
        cout << "\tAktualny plik: " << file[cFI]->getName() << endl;
    cout << "\tCo chcesz robic?" << endl;
    cout << "\t1. Wczytac baze" << endl;
    cout << "\t2. Stworzyc nowa baze" << endl;
    cout << "\t3. Wyswietlic plik" << endl;
    cout << "\t4. Edytowac plik" << endl;
    cout << "\t5. Usuwanie linii" << endl;
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
                        index->openBaseFiles(&file);
                        for(int i = 0; i < file.size(); i++)
                            cout << file[i]->getName() << endl;
                        cFI = 0;
                        if((freeUse = file[cFI]->readFile()) == 0)
                            cout << "Blad odczytu pliku z danymi " << endl;
                        else if (freeUse == 2)
                            cout << "Otworzono co najmniej jeden pusty plik" << endl;
                        else if (freeUse != 0){
                            headers = file[cFI]->getHeaders();
                            cout << "Wczytano poprawnie, baza gotowa do dalszych operacji" << endl;
                        }

                    }
            }
            else{
                cout << "Baza jest juz otwarta, czy chcesz ja zamknac aby otworzyc nowa? t\\n \n";
                answer = tolower(getch());
                if(answer == 't'){
                    answer = ' ';
                    cout << "Czy chcesz zapisac zmiany?" << endl;
                    answer = tolower(getch());
                    if(answer == 't'){
                        for(int i = 0; i < file.size(); i++)
                            file[cFI]->saveFile(file[cFI]->getName());
                        index->saveBase();
                        cout << "Zapisano zmiany" << endl;
                    }
                    else
                        cout << "Usunieto poprzednia baze, bez zapisania zmian" << endl;
                    headers.clear();
                    for(vector <Database*>::iterator it = file.begin(); it != file.end(); ++it)
                        delete (*it);
                    file.clear();
                    delete index;
                    cout << "Podaj nazwe pliku glownego: ";
                    cin >> tempName;
                    index = new prepareDatabase(tempName);
                    if(index->fileRead() == 1){
                        cout << "Blad otwarcia pliku, sprobuj jeszcze raz" << endl;
                        delete index;
                    }
                    else{
                        index->openBaseFiles(&file);
                        cout << "tutaj" << endl;
                        for(int i = 0; i < file.size(); i++)
                            cout << file[i]->getName() << endl;
                        cFI = 0;
                        cout << "A tu nie " << endl;
                        if((freeUse = file[cFI]->readFile()) == 0)
                            cout << "Blad odczytu pliku z danymi " << endl;
                        else if (freeUse == 2)
                            cout << "Otworzono co najmniej jede pusty plik" << endl;
                        else if (freeUse != 0){
                            headers = file[cFI]->getHeaders();
                            cout << "Wczytano poprawnie, baza gotowa do dalszych operacji" << endl;
                        }

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
                cout << "Aktualnie otwarta jest baza, czy chcesz ja zamknac?" << endl;
                answer = tolower(getch());
                if(answer == 't'){
                    for(int i = 0; i < file.size(); i++)
                        file[cFI]->saveFile(file[cFI]->getName());
                    index->saveBase();
                    headers.clear();
                    for(vector <Database*>::iterator it = file.begin(); it != file.end(); ++it)
                        delete (*it);
                    file.clear();
                    delete index;
                }
                else{
                    cout << "Anulowano otwieranie nowej bazy" << endl;
                    system("pause");
                    break;
                }
            }
            cout << "Podaj nazwe pliku glownego: ";
            cin >> name;
            index = new prepareDatabase(name + ".txt");
            cout << "Podaj nazwe pierwszego pliku ";
            cin >> name;
            file.push_back(new Database(name + ".txt"));
            cFI = 0;
            index->addFilesToBase(name + ".txt");
            file[cFI]->saveFile(name + ".txt");
            index->saveBase();
            system("pause");
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
            if(file.size() == 0)
                cout << "Nie utworzony bazy, nie ma co wyswietlic" << endl;
            else if (file[cFI]->getNumRows() == 0)
                cout << "Baza jest pusta, nie ma co wyswietlic" << endl;
            else if (freeUse == 1){
                system("cls");
                    headers = file[cFI]->getHeaders();
                    if(headers.size() == 0)
                        cout << "Blad odczytu danych lub baza jest pusta" << endl;
                    else
                        for(int i = 0; i < headers.size(); i++)
                            cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << headers[i];
                        cout << endl;
                        singleRow = file[cFI]->getOneRow('f');
                        do{
                            for(int i = 0; i < singleRow.size(); i++)
                                cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << singleRow[i];
                            cout << endl;
                            singleRow = file[cFI]->getOneRow('n');
                            if(singleRow.empty()){
                                file[cFI]->resetRRC();
                                break;
                            }
                        }while(true);
            }
            else if (freeUse == 2){
                if(headers.size() == 0)
                    cout << "Blad odczytu danych lub baza jest pusta" << endl;
                else{
                    singleRow = file[cFI]->getOneRow('f');
                    while(true){
                        for(int i = 0; i < headers.size(); i++)
                            cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << headers[i];
                        cout << endl;
                        int z = 0;
                        for(int i = 0; i < singleRow.size(); i++)
                            cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << singleRow[i];
                        cout << endl;
                        switch((z = getch())){
                        case UP:
                            singleRow.clear();
                            singleRow = file[cFI]->getOneRow('p');
                            break;
                        case DOWN:
                            singleRow.clear();
                            singleRow = file[cFI]->getOneRow('n');
                            break;
                        }
                        if(singleRow.empty()){
                            cout << "Nacisnij enter aby zakonczyc, w przeciwnym razie program wraca do poczatku" << endl;
                            z = getch();
                            if(z == ENTER)
                                break;
                            else
                                file[cFI]->resetRRC();
                        }
                        system("cls");
                    }
                    file[cFI]->resetRRC();
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
                    tempBeforePush.push_back(to_string(file[cFI]->getLastID()));
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
                    file[cFI]->addRow(toPush);
                    tempBeforePush.clear();
                    toPush.clear();
                    break;
                }
                case '2':{
                    do{
                        //file[cFI]->addRow();
                        cout << "Chcesz dodac nastepna linie? (t/n)";
                        *tempSwitch = getch();
                        if(tolower(*tempSwitch) != 't' && tolower(*tempSwitch) != 'n')
                            cout << "Odpowiedz nie rozpoznana, konczenie pracy" << endl;
                    }while(tolower(*tempSwitch) == 't');
                    break;
                }
                case '3':{system("cls");
                    cout << "Wiersz: ";
                    for(int i = 0; i < headers.size(); i++)
                        cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << headers[i];
                    cout << endl;
                    singleRow = file[cFI]->getOneRow('f');
                    int *rowCount = new int;
                    *rowCount = 1;
                    do{
                        cout << *rowCount << ".      ";
                        *rowCount = *rowCount + 1;
                        for(int i = 0; i < singleRow.size(); i++)
                            cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << singleRow[i];
                        cout << endl;
                        singleRow = file[cFI]->getOneRow('n');
                        if(singleRow.empty()){
                            file[cFI]->resetRRC();
                        }
                    }while(!singleRow.empty());
                    error = new int;
                    do{
                    cout << "Ktora linie chcesz usunac?: " << endl;
                    cin >> freeUse;
                    if(freeUse < 0)
                        break;
                    *error = file[cFI]->removeRow(freeUse);
                    }while(freeUse <= 1 && *error != 0);
                    delete error;
                    system("cls");
                    headers = file[cFI]->getHeaders();
                    if(headers.size() == 0)
                        cout << "Blad odczytu danych lub baza jest pusta" << endl;
                    else{
                        for(int i = 0; i < headers.size(); i++)
                            cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << headers[i];
                        cout << endl;
                        singleRow = file[cFI]->getOneRow('f');
                        do{
                            for(int i = 0; i < singleRow.size(); i++)
                                cout << "|" << setw(file[cFI]->columnWidth[i] + 1) << singleRow[i];
                            cout << endl;
                            singleRow = file[cFI]->getOneRow('n');
                            if(singleRow.empty()){
                                file[cFI]->resetRRC();
                            }
                        }while(!singleRow.empty());
                    }
                system("pause");
                }
            }
            getch();
            delete tempSwitch;
            break;
        }
        case 5: {

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
                    error = new int;
                    *error = file[cFI]->saveFile(file[cFI]->getName());
                    if(*error == 0)
                        cout << "Zapis udany" << endl;
                    else if (*error == 1)
                        cout << "Blad otwarcia, nie zapisano nic";
                    else if(*error == -1)
                        cout << "Nie wprowadzono zmian do bazy, zaniechano zapisu" << endl;
                    delete error;
                    system("pause");
                    break;
                case 2: cout << "Podaj nazwe pliku i rozszerzenie: ";
                    cin >> tempName;
                    *error = file[cFI]->saveFile(tempName);
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
                        freeUse = file[cFI]->readFile();
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
                    if(cFI < file.size()){
                        cFI++;
                        freeUse = file[cFI]->readFile();
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
                    cout << "\tPodaj indeks pliku z zakresu pomiedzy 0 a " << file.size() - 1<< " : ";
                    cin >> freeUse;
                    if(freeUse < 0 || freeUse >= file.size())
                        cout << "Nie poprawny indeks, podaj jeszcze raz" << endl;
                    }while(freeUse < 0 || freeUse >= file.size());
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
                freeUse = file[cFI]->sortFileBy(temp);
                if(freeUse == 0){
                    system("cls");
                    headers = file[cFI]->getHeaders();
                    for(int i = 0; i < headers.size(); i++)
                        cout << "|" << setw(file[cFI]->columnWidth[i]) << headers[i];
                    cout << endl;
                    singleRow = file[cFI]->getOneRow('f');
                    do{
                        for(int i = 0; i < singleRow.size(); i++)
                            cout << "|" << setw(file[cFI]->columnWidth[i]) << singleRow[i];
                        cout << endl;
                        singleRow = file[cFI]->getOneRow('n');
                        if(singleRow.size() == 0){
                            file[cFI]->resetRRC();
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
            searchResult = file[cFI] -> searchFor(temp, temp2,1);
            if(searchResult.size() == 1){
                cout << "\tNie znaleziono wartosci" << endl;
                system("pause");
            }
            else{
                for(int i = 0; i < searchResult.size(); i++){
                    for(int y = 0; y < searchResult[0].size(); y++)
                        cout << '|' << setw(file[cFI]->columnWidth[y] + 1) << searchResult[i][y];
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
    for(vector <Database*>::iterator it = file.begin(); it != file.end(); ++it)
        delete (*it);
    file.clear();
    delete index;
    return 1;
}
