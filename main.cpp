#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <windows.h>

using namespace std;

struct Uzytkownik {
    int id;
    string login, haslo;
};

struct Kontakt {
    int id;
    string imie, nazwisko, adres, telefon, mail;
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

vector<Uzytkownik> rejestracja(vector<Uzytkownik> uzytkownicy, int liczbaUzytkownikow) {
    system("cls");
    cin.sync();
    Uzytkownik Nadawca;
    string login, haslo;

    if (liczbaUzytkownikow==0) {
        cout<<"Podaj login: ";
        login=wczytajLinie();
        cout<<"Podaj haslo: ";
        haslo=wczytajLinie();

        Nadawca.login=login;
        Nadawca.haslo=haslo;
        Nadawca.id=1;

    } else {
        Uzytkownik OstatniNadawca=uzytkownicy.at(liczbaUzytkownikow-1);

        cout<<"Podaj login: ";
        login=wczytajLinie();
        vector<Uzytkownik>::iterator itr=uzytkownicy.begin();

        for(itr; itr!=uzytkownicy.end(); ++itr) {
            Uzytkownik *Nadawca=new Uzytkownik;
            *Nadawca=*itr;
            if(Nadawca->login==login) {
                cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                cin>>login;
                itr=uzytkownicy.begin();
            }
            delete Nadawca;
        }

        cout<<"Podaj haslo: ";
        haslo=wczytajLinie();

        Nadawca.login=login;
        Nadawca.haslo=haslo;

        Nadawca.id=OstatniNadawca.id+1;
    }
    uzytkownicy.push_back(Nadawca);

    fstream Nadawcy;
    Nadawcy.open("Uzytkownicy.txt",ios::out | ios::app);

    if (Nadawcy.good() == true) {
        if(Nadawca.id!=1) Nadawcy<<endl;
        Nadawcy<<Nadawca.id<<"|";
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

int logowanie(vector <Uzytkownik> uzytkownicy) {
    system("cls");
    cin.sync();
    string login, haslo;
    cout<<"Podaj login: ";
    login=wczytajLinie();

    vector<Uzytkownik>::iterator itr=uzytkownicy.begin();

    for(itr; itr!=uzytkownicy.end(); ++itr) {
        Uzytkownik *Nadawca=new Uzytkownik;
        *Nadawca=*itr;

        if(Nadawca->login==login) {
            for(int proby=0; proby<3; proby++) {
                system("cls");
                cout<<"login: "<<login<<endl;
                cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<": ";
                haslo=wczytajLinie();
                if(Nadawca->haslo==haslo) {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return Nadawca->id;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);
    return 0;

}

int ksiazkaAdresowa(int idUzytkownika){

}

int main() {
    vector <Uzytkownik> uzytkownicy;

    int liczbaUzytkownikow;
    int idZalogowanegoUzytkownika=0;
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
                uzytkownicy=rejestracja(uzytkownicy, liczbaUzytkownikow);
                break;
            }
            case '2': {
                idZalogowanegoUzytkownika=logowanie(uzytkownicy);
                idZalogowanegoUzytkownika=ksiazkaAdresowa(idZalogowanegoUzytkownika);
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
