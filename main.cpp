#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Uzytkownik {
    int id;
    string login, haslo;
};

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

int main() {
    vector <Uzytkownik> uzytkownicy;

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
                //iloscUzytkownikow=rejestracja(uzytkownicy,iloscUzytkownikow);
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
