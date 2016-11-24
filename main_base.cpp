#include "bases.cpp"
#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ENTER 13

using namespace std;

int main(){
    Database* baza = NULL;
    string temp, tempName;
    int x = 1, y = 2,a, freeUse;
    while(a != 7){
    int *swNumber = new int;
    int *error = new int;
    cout << "\tCo chcesz robic?" << endl;
    cout << "\t1. Wczytac plik" << endl;
    cout << "\t2. Stworzyc nowy plik" << endl;
    cout << "\t3. Wyswietlic plik" << endl;
    cout << "\t4. Edytowac plik" << endl;
    cout << "\t5. Wyswietlanie szczegolowe" << endl;
    cout << "\t6. Zapisanie pliku" << endl;
    cout << "\t7. Zakonczyc prace" << endl;
    cin >> a;
    switch(a){
        case 1: {
            if(baza == NULL){
            cout << "Podaj nazwe pliku: ";
            cin >> temp;
            baza = new Database(temp);
            baza->changeName(temp);
            }
            if(baza->readFile() == 1)
            cout << "Wczytano poprawnie" << endl;
            else{
            cout << "Blad wczytywania" << endl;
            delete baza;
            baza = new Database;
            }
            cin.get();
            cin.get();
            break;
        }
        case 2: {
            cout << "Podaj nazwe pliku i rozszerzenie: ";
            cin >> temp;
            baza = new Database(temp);
            baza->addMultipleRows();
            temp = "";
        }
        case 3: {
            system("cls");
            cout << "\t1. Wyswietlic caly plik" << endl;
            cout << "\t2. Wyswietlic pojedyncza linie" << endl;
            cin >> freeUse;
            if(baza == NULL)
                cout << "Nie utworzony bazy, nie ma co wyswietlic" << endl;
            else if (freeUse == 1)
                baza->printRead();
            else if (freeUse == 2)
                baza->printOneRow();
            else
                cout << "Nie rozpoznano komendy, powrot do glownego menu" << endl;
            cin.sync();
            cin.clear();
            cin.get();
            break;
        }
        case 4: {
            if(baza == NULL){
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
                    baza->addRow();
                    break;
                }
                case '2':{
                    do{
                        baza->addRow();
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
            cout << "\t1. Zapis do tego samego pliku z zastapieniem" << endl;
            cout << "\t2. Zapis do innego pliku" << endl;

            cin >> *swNumber;
            switch(*swNumber){
                case 1: if(baza->checkRead()){
                cout << "Zapisywanie, z zastapieniem poprzednich danych" << endl;
                *error = baza->saveFileTrunc();
                if(*error == 1)
                    cout << "Zapis udany" << endl;
                else if (*error == 0)
                    cout << "Blad otwarcia, nie zapisano nic";
                }
                else{
                    *error = baza->saveFileTrunc();
                if(*error == 1)
                    cout << "Zapis udany" << endl;
                else if (*error == 0)
                    cout << "Blad otwarcia, nie zapisano nic";
                }

                delete error;
                break;
                case 2: cout << "Podaj nazwe pliku i rozszerzenie: ";
                cin >> tempName;
                *error = baza->saveFileTrunc(tempName);
                if(*error == 1)
                    cout << "Zapis udany" << endl;
                else if (*error == 0)
                    cout << "Blad otwarcia, nie zapisano nic";
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
    delete baza;
    return 1;
}
