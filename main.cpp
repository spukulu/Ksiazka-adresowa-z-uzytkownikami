#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Uzytkownik {
    int id;
    string login, haslo;
};

string wczytajLinie() {
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

int LiczUzytkownikow(vector <Uzytkownik> uzytkownicy) {
    vector<Uzytkownik>::iterator itr=uzytkownicy.begin();
    int LiczbaUzytkownikow=0;
    for(itr; itr!=uzytkownicy.end(); ++itr) {
        LiczbaUzytkownikow++;
    }
    return LiczbaUzytkownikow;
}

vector <Uzytkownik> wczytajUzytkownikow(vector <Uzytkownik> uzytkownicy ) {

    string wers;
    fstream Nadawcy;
    Nadawcy.open("Uzytkownicy.txt", ios::in);
    if(Nadawcy.good()==false) return uzytkownicy;
    else {
        string separator="|";
        int pozycja;
        while(!Nadawcy.eof()) {
            getline(Nadawcy,wers);
            pozycja=wers.find(separator);
            Uzytkownik *Nadawca=new Uzytkownik;

            string napisID;
            for(int i=0; i<pozycja; i++) {
                napisID+=wers[i];
            }
            Nadawca->id=atoi(napisID.c_str());
            wers.erase(0,pozycja+1);

            pozycja=wers.find(separator);
            for(int i=0; i<pozycja; i++) {
                Nadawca->login+=wers[i];
            }
            wers.erase(0,pozycja+1);

            pozycja=wers.find(separator);
            for(int i=0; i<pozycja; i++) {
                Nadawca->haslo+=wers[i];
            }
            wers.erase(0,pozycja+1);


            uzytkownicy.push_back(*Nadawca);
            delete Nadawca;
        }
    }
    Nadawcy.close();
    return uzytkownicy;
}

vector<Uzytkownik> dodajUzytkownika(vector<Uzytkownik> uzytkownicy, int liczbaUzytkownikow) {
    system("cls");
    Uzytkownik Nadawca;
    Uzytkownik OstatniNadawca=uzytkownicy.at(liczbaUzytkownikow-1);
    string login, haslo;

    cout<<"Podaj login: ";
    login=wczytajLinie();
    vector<Uzytkownik>::iterator itr=uzytkownicy.begin();

    for(itr; itr!=uzytkownicy.end(); ++itr) {
        Uzytkownik *Nadawca=new Uzytkownik;
        *Nadawca=*itr;
        if(Nadawca->login==login)
        {
            cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>login;
            itr=uzytkownicy.begin();
        }
    }

    cout<<"Podaj haslo: ";
    haslo=wczytajLinie();

    Nadawca.login=login;
    Nadawca.haslo=haslo;

    Nadawca.id=OstatniNadawca.id+1;
    uzytkownicy.push_back(Nadawca);

    fstream Nadawcy;
    Nadawcy.open("Uzytkownicy.txt",ios::out | ios::app);

    if (Nadawcy.good() == true) {
        Nadawcy<<endl<<Nadawca.id<<"|";
        Nadawcy<<Nadawca.login<<"|";
        Nadawcy<<Nadawca.haslo<<"|";

        Nadawcy.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    cout << endl << "Rejestracja przebiegla pomyslnie. Zaloguj sie" << endl;
    system("pause");

    return uzytkownicy;
}

int main() {
    vector <Uzytkownik> uzytkownicy;

    int liczbaUzytkownikow;
    int idZalogowanegoUzytkownika=0;
    int iloscUzytkownikow=0;
    char wybor;

    uzytkownicy=wczytajUzytkownikow(uzytkownicy);


    while(true) {
        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin>>wybor;

            switch(wybor) {
            case '1': {
                liczbaUzytkownikow=LiczUzytkownikow(uzytkownicy);
                uzytkownicy=dodajUzytkownika(uzytkownicy, liczbaUzytkownikow);
                break;
            }
            case '2': {
                //idZalogowanegoUzytkownika=logowanie(uzytkownicy, iloscUzytkownikow);
                break;
            }
            case '9': {
                exit(0);
                break;
            }
            }
        }
    }
}
