#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <windows.h>

using namespace std;

bool moveToStartOfLine(ifstream& fs) {
    fs.seekg(-1, ios_base::cur);
    for(long i = fs.tellg(); i > 0; i--) {
        if(fs.peek() == '\n') {
            fs.get();
            return true;
        }
        fs.seekg(i, ios_base::beg);
    }
    return false;
}

string getLastLineInFile(ifstream& fs) {
    // Go to the last character before EOF
    fs.seekg(-1, ios_base::end);
    if (!moveToStartOfLine(fs))
        return "";
    string lastline = "";
    getline(fs, lastline);
    return lastline;
}

string pobierzOstatniaLiniePlikuTxt(string filename) {
    ifstream fs;
    fs.open(filename.c_str(), fstream::in);
    if(!fs.is_open()) {
        return  "Could not open file";
    }
    return getLastLineInFile(fs);
}

int pobierzIdZPierwszejLinijki(string filename) {

    string wers;
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt", ios::in);

    string separator="|";
    int pozycja;

    getline(ksiazkaAdresowa,wers);
    pozycja=wers.find(separator);
    string napisID;
    for(int i=0; i<pozycja; i++) {
        napisID+=wers[i];
    }
    int id=atoi(napisID.c_str());
    ksiazkaAdresowa.close();
    return id;
}

int pobierzIdAdresata(string wers, string filename) {
    int id;
    if(wers=="Could not open file") return 0;
    else if (wers=="") {
        id=pobierzIdZPierwszejLinijki(filename);
        return id;
    } else {
        string separator="|";
        int pozycja;
        pozycja=wers.find(separator);
        string napisID;
        for(int i=0; i<pozycja; i++) {
            napisID+=wers[i];
        }
        id=atoi(napisID.c_str());
        return id;
    }

}

struct Uzytkownik {
    int id;
    string login, haslo;
};

struct Kontakt {
    int idUzytkownika, idAdresata;
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

char wczytajZnakTakLubNie() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie == "t" || wejscie == "n") {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest poprawny znak. Wpisz ponownie." << endl;
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

int LiczKontakty(vector <Kontakt> znajomi) {
    vector<Kontakt>::iterator itr=znajomi.begin();
    int LiczbaKontaktow=0;
    for(itr; itr!=znajomi.end(); ++itr) {
        LiczbaKontaktow++;
    }
    return LiczbaKontaktow;
}

void EdycjaAdresataWPlikuTxt (vector<Kontakt>znajomi, int idEdytowanegoAdresata){
    fstream ksiazkaAdresowa, ksiazkaAdresowa_tymczasowy;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt",ios::in);
    ksiazkaAdresowa_tymczasowy.open("ksiazkaAdresowa_tymczasowy.txt",ios::out);

    string wers;

    if(ksiazkaAdresowa.good()==true) {
        string separator="|";
        int pozycja;
        while(!ksiazkaAdresowa.eof()) {
            getline(ksiazkaAdresowa,wers);
            pozycja=wers.find(separator);

            string napisID="";
            for(int i=0; i<pozycja; i++) {
                napisID+=wers[i];
            }
            int idAdresata=atoi(napisID.c_str());
            if(idAdresata!=1){ksiazkaAdresowa_tymczasowy<<endl;}
            if(idAdresata!=idEdytowanegoAdresata && ksiazkaAdresowa_tymczasowy.good() == true){

                ksiazkaAdresowa_tymczasowy<<wers;
            }else{
                vector<Kontakt>::iterator itr=znajomi.begin();
                for(itr; itr!=znajomi.end(); ++itr) {
                Kontakt *Adresat=new Kontakt;
                *Adresat=*itr;
                if(Adresat->idAdresata==idEdytowanegoAdresata){
                    if (ksiazkaAdresowa_tymczasowy.good() == true) {
            ksiazkaAdresowa_tymczasowy<<Adresat->idAdresata<<"|";
            ksiazkaAdresowa_tymczasowy<<Adresat->idUzytkownika<<"|";
            ksiazkaAdresowa_tymczasowy<<Adresat->imie<<"|";
            ksiazkaAdresowa_tymczasowy<<Adresat->nazwisko<<"|";
            ksiazkaAdresowa_tymczasowy<<Adresat->telefon<<"|";
            ksiazkaAdresowa_tymczasowy<<Adresat->mail<<"|";
            ksiazkaAdresowa_tymczasowy<<Adresat->adres<<"|";
                    }
                        }
                delete Adresat;
            }
        }
    }



    ksiazkaAdresowa.close();
    remove("ksiazkaAdresowa.txt");
    ksiazkaAdresowa_tymczasowy.close();
    rename("ksiazkaAdresowa_tymczasowy.txt", "ksiazkaAdresowa.txt");

}
}

void UsuwanieAdresataWPlikuTxt(vector<Kontakt>znajomi, int idEdytowanegoAdresata){
    fstream ksiazkaAdresowa, ksiazkaAdresowa_tymczasowy;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt",ios::in);
    ksiazkaAdresowa_tymczasowy.open("ksiazkaAdresowa_tymczasowy.txt",ios::out);

    string wers;

    if(ksiazkaAdresowa.good()==true) {
        string separator="|";
        int pozycja;
        while(!ksiazkaAdresowa.eof()) {
            getline(ksiazkaAdresowa,wers);
            pozycja=wers.find(separator);

            string napisID="";
            for(int i=0; i<pozycja; i++) {
                napisID+=wers[i];
            }
            int idAdresata=atoi(napisID.c_str());

            if(idAdresata!=idEdytowanegoAdresata && ksiazkaAdresowa_tymczasowy.good() == true){

                if(idAdresata!=1){ksiazkaAdresowa_tymczasowy<<endl;}
                ksiazkaAdresowa_tymczasowy<<wers;
            }
    }
}
ksiazkaAdresowa.close();
    remove("ksiazkaAdresowa.txt");
    ksiazkaAdresowa_tymczasowy.close();
    rename("ksiazkaAdresowa_tymczasowy.txt", "ksiazkaAdresowa.txt");
}

void nadpiszPlikUzytkownicyTxt(vector<Uzytkownik>uzytkownicy) {
    fstream Uzytkownicy;
    Uzytkownicy.open("Uzytkownicy.txt",ios::trunc | ios::out);

    vector<Uzytkownik>::iterator itr=uzytkownicy.begin();
    for(itr; itr!=uzytkownicy.end(); ++itr) {
        Uzytkownik *Nadawca=new Uzytkownik;
        *Nadawca=*itr;

        if (Uzytkownicy.good() == true) {
            Uzytkownicy<<Nadawca->id<<"|";
            Uzytkownicy<<Nadawca->login<<"|";
            Uzytkownicy<<Nadawca->haslo<<"|";

            if(itr!=(uzytkownicy.end()-1)) Uzytkownicy<<endl;
        }
        delete Nadawca;
    }
    Uzytkownicy.close();
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
                login=wczytajLinie();
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
        delete Nadawca;
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);
    return 0;

}

vector <Kontakt> wczytajKontakty(vector <Kontakt> znajomi, int idUzytkownika) {

    string wers;
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt", ios::in);
    if(ksiazkaAdresowa.good()==false) return znajomi;
    else {
        string separator="|";
        int pozycja;
        while(!ksiazkaAdresowa.eof()) {
            getline(ksiazkaAdresowa,wers);
            pozycja=wers.find(separator);
            Kontakt *Adresat=new Kontakt;

            string napisID;
            for(int i=0; i<pozycja; i++) {
                napisID+=wers[i];
            }
            Adresat->idAdresata=atoi(napisID.c_str());
            wers.erase(0,pozycja+1);

            napisID="";
            for(int i=0; i<pozycja; i++) {
                napisID+=wers[i];
            }
            Adresat->idUzytkownika=atoi(napisID.c_str());
            wers.erase(0,pozycja+1);

            if(Adresat->idUzytkownika==idUzytkownika) {
                pozycja=wers.find(separator);
                for(int i=0; i<pozycja; i++) {
                    Adresat->imie+=wers[i];
                }
                wers.erase(0,pozycja+1);

                pozycja=wers.find(separator);
                for(int i=0; i<pozycja; i++) {
                    Adresat->nazwisko+=wers[i];
                }
                wers.erase(0,pozycja+1);

                pozycja=wers.find(separator);
                for(int i=0; i<pozycja; i++) {
                    Adresat->telefon+=wers[i];
                }
                wers.erase(0,pozycja+1);

                pozycja=wers.find(separator);
                for(int i=0; i<pozycja; i++) {
                    Adresat->mail+=wers[i];
                }
                wers.erase(0,pozycja+1);

                pozycja=wers.find(separator);
                for(int i=0; i<pozycja; i++) {
                    Adresat->adres+=wers[i];
                }
                wers.erase(0,pozycja+1);

                znajomi.push_back(*Adresat);
            }
            delete Adresat;
        }
    }
    ksiazkaAdresowa.close();
    return znajomi;
}

void wyswietlKontakty(vector<Kontakt> znajomi, int idUzytkownika) {

    system("cls");
    vector<Kontakt>::iterator itr=znajomi.begin();
    for(itr; itr!=znajomi.end(); ++itr) {
        Kontakt *Adresat=new Kontakt;
        *Adresat=*itr;
        if(idUzytkownika==Adresat->idUzytkownika) {
            cout<<Adresat->idAdresata<<"|";
            cout<<Adresat->imie<<"|";
            cout<<Adresat->nazwisko<<"|";
            cout<<Adresat->telefon<<"|";
            cout<<Adresat->mail<<"|";
            cout<<Adresat->adres<<"|"<<endl;
        }
        delete Adresat;
    }
    system("pause");
}

void wyszukajPoImieniu(vector<Kontakt> znajomi, int idUzytkownika) {

    string imie;

    system("cls");

    int licznikWyswietlen=0;

    cout<<"Podaj imie: ";
    imie=wczytajLinie();
    cout<<endl<<endl;

    vector<Kontakt>::iterator itr=znajomi.begin();
    for(itr; itr!=znajomi.end(); ++itr) {
        Kontakt *Adresat=new Kontakt;
        *Adresat=*itr;
        if(idUzytkownika==Adresat->idUzytkownika) {
            if(Adresat->imie==imie) {
                cout<<Adresat->imie;
                cout<<"|"<<Adresat->nazwisko;
                cout<<"|"<<Adresat->telefon;
                cout<<"|"<<Adresat->mail;
                cout<<"|"<<Adresat->adres<<endl;

                licznikWyswietlen++;
            }
            delete Adresat;
        }
    }
    if(licznikWyswietlen==0) {
        cout<<"Brak kontaktow z podanym imieniem"<<endl<<endl;
        cout<<"Nacisnij dowolny klawisz by powrocic do menu glownego"<<endl;
    }
    system("pause");
}

void wyszukajPoNazwisku(vector<Kontakt> znajomi, int idUzytkownika) {

    string nazwisko;

    system("cls");

    int licznikWyswietlen=0;

    cout<<"Podaj nazwisko: ";
    nazwisko=wczytajLinie();
    cout<<endl<<endl;

    vector<Kontakt>::iterator itr=znajomi.begin();
    for(itr; itr!=znajomi.end(); ++itr) {
        Kontakt *Adresat=new Kontakt;
        *Adresat=*itr;
        if(idUzytkownika==Adresat->idUzytkownika) {
            if(Adresat->nazwisko==nazwisko) {
                cout<<Adresat->imie;
                cout<<"|"<<Adresat->nazwisko;
                cout<<"|"<<Adresat->telefon;
                cout<<"|"<<Adresat->mail;
                cout<<"|"<<Adresat->adres<<endl;

                licznikWyswietlen++;
            }
            delete Adresat;
        }
    }
    if(licznikWyswietlen==0) {
        cout<<"Brak kontaktow z podanym nazwiskiem"<<endl<<endl;
        cout<<"Nacisnij dowolny klawisz by powrocic do menu glownego"<<endl;
    }
    system("pause");
}

vector<Kontakt> usunKontakt(vector <Kontakt> znajomi, int idUzytkownika, int id) {
    char wybor;
    system("cls");

    cout<<"Czy na pewno chcesz usunac ten kontakt?"<<endl<<"Jezeli tak, wybierz 't'. Jezeli nie, wybiez 'n'";
    cout<<endl<<"Twoj wybor: ";
    cin.sync();
    wybor=wczytajZnakTakLubNie();
    if(wybor=='t') {
        vector<Kontakt>::iterator itr=znajomi.begin();
        Kontakt *Adresat=new Kontakt;
        for(itr; itr!=znajomi.end(); ++itr) {

            *Adresat=*itr;

            if(Adresat->idAdresata==id && Adresat->idUzytkownika==idUzytkownika) {
                cin.sync();
                znajomi.erase(itr);
                cout<<endl<<endl<<"Kontakt usuniety"<<endl;
                system("pause");
                return znajomi;
            }
        }
        cout<<"Brak dostepu do kontaktu. Kontakt nie zostal usuniety"<<endl;
        Sleep(2000);
        return znajomi;
        delete Adresat;
    } else {

        return znajomi;
    }
}

int pobierzIdAdresata(){
int id;
    system("cls");
    cin.sync();

    cout<<"Podaj ID kontaktu, ktory chcesz edytowac/usunac: ";
    cin>>id;
    return id;
}

vector<Kontakt> edytujKontakt(vector <Kontakt> znajomi, int idUzytkownika, int id) {
    char wybor;

    system("cls");

    cin.sync();
    vector<Kontakt>::iterator itr=znajomi.begin();
    Kontakt *Adresat=new Kontakt, AdresatPoEdycji;
    string imie, nazwisko, telefon, mail, adres;
    for(itr; itr!=znajomi.end(); ++itr) {


        *Adresat=*itr;

        if(Adresat->idAdresata==id && Adresat->idUzytkownika==idUzytkownika) {
            system("cls");
            cout<<"Wybierz pozycje do edycji"<<endl;
            cout<<"1. imie"<<endl;
            cout<<"2. nazwisko"<<endl;
            cout<<"3. numer telefonu"<<endl;
            cout<<"4. email"<<endl;
            cout<<"5. adres"<<endl;
            cout<<"6. powrot do menu"<<endl;
            cout<<endl<<"Twoj wybor: ";
            wybor=wczytajZnak();

            switch(wybor) {
            case '1': {
                cout<<"Podaj nowe imie: ";
                imie=wczytajLinie();
                AdresatPoEdycji.imie=imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.idUzytkownika=Adresat->idUzytkownika;
                AdresatPoEdycji.idAdresata=Adresat->idAdresata;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;

                break;
            }
            case '2': {
                cout<<"Podaj nowe nazwisko: ";
                nazwisko=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.idUzytkownika=Adresat->idUzytkownika;
                AdresatPoEdycji.idAdresata=Adresat->idAdresata;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;

                break;
            }
            case '3': {
                cout<<"Podaj nowy numer telefonu: ";
                telefon=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=telefon;
                AdresatPoEdycji.idUzytkownika=Adresat->idUzytkownika;
                AdresatPoEdycji.idAdresata=Adresat->idAdresata;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;
                break;
            }
            case '4': {
                cout<<"Podaj nowy e-mail: ";
                mail=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.idUzytkownika=Adresat->idUzytkownika;
                AdresatPoEdycji.idAdresata=Adresat->idAdresata;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;
                break;
            }
            case '5': {
                cout<<"Podaj nowy adres: ";
                adres=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.idUzytkownika=Adresat->idUzytkownika;
                AdresatPoEdycji.idAdresata=Adresat->idAdresata;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;
                break;
            }
            case '6': {
                return znajomi;
                break;
            }
            }
        }
    }
    cout<<"Brak dostepu do kontaktu."<<endl;
        Sleep(2000);
    return znajomi;
    delete Adresat;
}

void dodajKontakt(int idOstatniegoAdresata, int idUzytkownika) {
    system("cls");

    string imie, nazwisko, adres, telefon, mail;
    int idAdresata=idOstatniegoAdresata+1;

    cout<<"Podaj imie: ";
    imie=wczytajLinie();
    cout<<"Podaj nazwisko: ";
    nazwisko=wczytajLinie();
    cout<<"Podaj adres e-mail: ";
    mail=wczytajLinie();
    cout<<"Podaj numer telefonu: ";
    telefon=wczytajLinie();
    cout<<"Podaj adres zamieszkania: ";
    adres=wczytajLinie();

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt",ios::out | ios::app);

    if (ksiazkaAdresowa.good() == true) {
        if (idAdresata!=1) ksiazkaAdresowa<<endl;
        ksiazkaAdresowa<<idAdresata<<"|";
        ksiazkaAdresowa<<idUzytkownika<<"|";
        ksiazkaAdresowa<<imie<<"|";
        ksiazkaAdresowa<<nazwisko<<"|";
        ksiazkaAdresowa<<telefon<<"|";
        ksiazkaAdresowa<<mail<<"|";
        ksiazkaAdresowa<<adres<<"|";
        ksiazkaAdresowa.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    cout << endl << "Osoba zostala dodana" << endl;
    system("pause");

}

vector<Uzytkownik> zmianaHasla(vector<Uzytkownik> uzytkownicy, int idUzytkownika) {
    string noweHaslo="", stareHaslo="";

    system("cls");
    cout<<endl<<"Podaj stare haslo: ";
    stareHaslo=wczytajLinie();
    vector<Uzytkownik>::iterator itr=uzytkownicy.begin();

    for(itr; itr!=uzytkownicy.end(); ++itr) {
        Uzytkownik *Nadawca=new Uzytkownik, UzytkownikPoEdycji;
        *Nadawca=*itr;
        if(Nadawca->haslo==stareHaslo && Nadawca->id==idUzytkownika) {
            cout<<"Podaj nowe haslo: ";
            noweHaslo=wczytajLinie();

            UzytkownikPoEdycji.haslo=noweHaslo;
            UzytkownikPoEdycji.id=idUzytkownika;
            UzytkownikPoEdycji.login=Nadawca->login;

            itr=uzytkownicy.insert(itr, UzytkownikPoEdycji);
            uzytkownicy.erase( itr+1);

            cout<<"Haslo zostalo zmienione"<<endl;
            system("pause");
            return uzytkownicy;

        }
        delete Nadawca;
    }

    cout<<"Haslo niepoprawne"<<endl;
    system("pause");
    return uzytkownicy;


}

int ksiazkaAdresowa(int idUzytkownika, vector <Uzytkownik> uzytkownicy, vector <Kontakt> znajomi) {
    while(true) {
        system("cls");
        cin.sync();
        int wybor, idAdresataDoEdycji, idAdresataDoUsuniecia;

        znajomi=wczytajKontakty(znajomi, idUzytkownika);

        cout<<"KSIAZKA ADRESOWA"<<endl;
        cout<<"1. Dodaj adresata"<<endl;
        cout<<"2. Wyszukaj po imieniu"<<endl;
        cout<<"3. Wyszukaj po nazwisku"<<endl;
        cout<<"4. Wyswietl wszystkich adresatow"<<endl;
        cout<<"5. Usun adresata"<<endl;
        cout<<"6. Edytuj adresata"<<endl;
        cout<<"7. Zmien haslo"<<endl;
        cout<<"9. Wyloguj sie"<<endl;
        cout<<"Twoj wybor: ";
        wybor=wczytajZnak();


        switch(wybor) {
        case '1': {
            string filename = "ksiazkaAdresowa.txt";
            string wers=pobierzOstatniaLiniePlikuTxt(filename);
            int idOstatniegoKontaktu=pobierzIdAdresata(wers, filename);
            dodajKontakt(idOstatniegoKontaktu,idUzytkownika);
            znajomi=wczytajKontakty(znajomi, idUzytkownika);
            break;
        }
        case '2': {

            wyszukajPoImieniu(znajomi, idUzytkownika);
            break;
        }
        case '3': {

            wyszukajPoNazwisku(znajomi, idUzytkownika);
            break;
        }
        case '4': {
            wyswietlKontakty(znajomi, idUzytkownika);
            break;
        }
        case '5': {
            idAdresataDoUsuniecia=pobierzIdAdresata();
            znajomi=usunKontakt(znajomi, idUzytkownika, idAdresataDoUsuniecia);
            UsuwanieAdresataWPlikuTxt(znajomi, idAdresataDoUsuniecia);
            break;
        }
        case '6': {
            idAdresataDoEdycji=pobierzIdAdresata();
            znajomi=edytujKontakt(znajomi, idUzytkownika, idAdresataDoEdycji);
            EdycjaAdresataWPlikuTxt(znajomi, idAdresataDoEdycji);
            break;

            case '7': {
                uzytkownicy=zmianaHasla(uzytkownicy, idUzytkownika);
                nadpiszPlikUzytkownicyTxt(uzytkownicy);

                break;
            }

            case '9': {
                return 0;
                break;
            }
        }
        }
    }
}

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Kontakt> znajomi;


    int liczbaUzytkownikow=0;
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
                if(idZalogowanegoUzytkownika!=0) {
                    idZalogowanegoUzytkownika=ksiazkaAdresowa(idZalogowanegoUzytkownika, uzytkownicy, znajomi);
                }
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
