#include "bases.cpp"
#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ENTER 13

using namespace std;

int main(){
    Database* baza;
    string temp, temp_name;
    int get_temp;
    int x = 1, y = 2,a;
    baza = new Database("baza.txt");
    while(a != 6){
    int *sw_number = new int;
    int *error = new int;
    cout << "\tCo chcesz robic?" << endl;
    cout << "\t1. Wczytac plik" << endl;
    cout << "\t2. Wyswietlic plik" << endl;
    cout << "\t3. Edytowac plik" << endl;
    cout << "\t4. Wyswietlanie szczegolowe" << endl;
    cout << "\t5. Zapisanie pliku" << endl;
    cout << "\t6. Zakonczyc prace" << endl;
    cin >> a;
    switch(a){
        case 1: {
            if(!baza->Check_name()){
            cout << "Podaj nazwe pliku: ";
            cin >> temp;
            baza->Change_name(temp);
            }
            if(baza->Read_file() == 1)
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
            baza->Print_read();
            cin.get();
            break;
        }
        case 3: {
            cout << "\t\t\t Edytowanie" << endl;
            system("cls");
            fflush(stdin);
            cout << "\t\t 1. Dodaj pojedynczy rekord" << endl;
            cout << "\t\t 2. Dodaj wiele rekordow" << endl;
            cout << "\t\t 3. Powrot do glownego menu" << endl;
            int* temp_switch = new int;
            cin >> *temp_switch;
            cin.ignore();
            switch(*temp_switch){
                case 1:{
                    baza->Add_single_row();
                    break;
                }
                case 2:{
                    cout << "Placeholder, tu pojawi sie cos pozniej" << endl;
                    break;
                }
                case 3:{
                    cout << "Powrot do glownego menu" << endl;
                    break;
                }
            }
            getch();
            delete temp_switch;
            break;
        }
        case 4: {
            cout << "Wyswietlanie" << endl;
            cin.get();
            cin.get();
            break;
        }
        case 5: {
            system("cls");
            cout << "\t1. Zapis do tego samego pliku z zastapieniem" << endl;
            cout << "\t2. Zapis do innego pliku" << endl;

            cin >> *sw_number;
            switch(*sw_number){
                case 1: if(baza->Check_read()){
                cout << "Zapisywanie, z zastapieniem poprzednich danych" << endl;
                *error = baza->Save_file_trunc();
                if(*error == 1)
                    cout << "Zapis udany" << endl;
                else if (*error == 0)
                    cout << "Blad otwarcia, nie zapisano nic";
                }
                else{
                    *error = baza->Save_file_trunc();
                if(*error == 1)
                    cout << "Zapis udany" << endl;
                else if (*error == 0)
                    cout << "Blad otwarcia, nie zapisano nic";
                }

                delete error;
                break;
                case 2: cout << "Podaj nazwe pliku i rozszerzenie: ";
                cin >> temp_name;
                *error = baza->Save_file_trunc(temp_name);
                if(*error == 1)
                    cout << "Zapis udany" << endl;
                else if (*error == 0)
                    cout << "Blad otwarcia, nie zapisano nic";
                break;

            }
            break;
        }
        case 6: exit;
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
