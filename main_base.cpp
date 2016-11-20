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
        case 1: if(!baza->Check_name()){
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
        case 2: baza->Print_read();
            cin.get();
            break;
        case 3: cout << "Edytowanie" << endl;
            baza->Print_read();
            baza->Gotoxy(x,y);
            do{
                get_temp = getch();
                if(get_temp == 224)
                    get_temp = getch();
                if(get_temp == UP && y > 1){
                    y--;
                    baza->Gotoxy(x,y);
                }
                else if(get_temp == DOWN && y < 100){
                    y++;
                    baza->Gotoxy(x,y);
                }
                else if(get_temp == LEFT && x > 1){
                    x--;
                    baza->Gotoxy(x,y);
                }
                else if(get_temp == RIGHT && x < 100){
                    x++;
                    baza->Gotoxy(x,y);
                }
                else{
                    cout << cin.get();
                    cin.clear();
                    cin.sync();
                }
            }while(get_temp != ESC);
            cin.get();
            cin.get();
            break;
        case 4: cout << "Wyswietlanie" << endl;
            cin.get();
            cin.get();
            break;
        case 5: system("cls");
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
        case 6: exit;
        break;
        default: cout << "Nie poprawna opcja, podaj jeszcze raz" << endl;
            cin.get();
            cin.get();
            break;
    }
        cin.clear();
        cin.sync();
        system("cls");
    }
    delete baza;
    return 1;
}
