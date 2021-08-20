#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <cstdio>

using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

struct Kontakt
{
    int id;
    string imie, nazwisko, numer, email, adres;
};

int pobierzUzytkownikowZPlikuZUzytkownikami(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    Uzytkownik odczytywanyUzytkownik;
    fstream plikZUzytkownikami;
    string odczytanyFragmentTekstu;
    int numerOdczytywanegoFragmentu = 1;

    plikZUzytkownikami.open("uzytkownicy.txt",ios::in);

    if(plikZUzytkownikami.good()==false)
    {
        return 0;
    }
    else
    {
        while(getline(plikZUzytkownikami,odczytanyFragmentTekstu,'|'))
        {
            switch (numerOdczytywanegoFragmentu)
            {
            case 1:
            {
                odczytywanyUzytkownik.id = atoi(odczytanyFragmentTekstu.c_str());
                break;
            }
            case 2:
            {
                odczytywanyUzytkownik.nazwa = odczytanyFragmentTekstu;
                break;
            }
            case 3:
            {
                odczytywanyUzytkownik.haslo = odczytanyFragmentTekstu;
                iloscUzytkownikow++;
                uzytkownicy.push_back(odczytywanyUzytkownik);
                numerOdczytywanegoFragmentu = 0;
                break;
            }
            }
            numerOdczytywanegoFragmentu++;
        }
        plikZUzytkownikami.close();
        return iloscUzytkownikow;
    }
}

int rejestracja(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    Uzytkownik dodawanyUzytkownik;
    string nazwa, haslo;

    system("cls");
    cout << "Rejestracja" << endl << endl;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while (i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    dodawanyUzytkownik.nazwa = nazwa;
    dodawanyUzytkownik.haslo = haslo;
    dodawanyUzytkownik.id = iloscUzytkownikow + 1;

    uzytkownicy.push_back(dodawanyUzytkownik);

    fstream plikZUzytkownikami;

    plikZUzytkownikami.open("uzytkownicy.txt",ios::out | ios::app);
    plikZUzytkownikami << dodawanyUzytkownik.id << "|";
    plikZUzytkownikami << dodawanyUzytkownik.nazwa << "|";
    plikZUzytkownikami << dodawanyUzytkownik.haslo << "|" << endl;
    plikZUzytkownikami.close();

    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return iloscUzytkownikow + 1;
}

int logowanie(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    string nazwa, haslo;

    system("cls");
    cout << "Logowanie" << endl << endl;

    cout << "Podaj nazwe: ";
    cin >> nazwa;
    int i = 0;
    while (i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo (pozostalo prob: " << 3 - proby <<"): ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void aktualizujPlikZUzytkownikami(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    system("cls");
    fstream plikZUzytkownikami;
    plikZUzytkownikami.open("uzytkownicy.txt",ios::out);

    for(int i = 0; i < iloscUzytkownikow; i++)
    {
        plikZUzytkownikami << uzytkownicy[i].id << "|";
        plikZUzytkownikami << uzytkownicy[i].nazwa << "|";
        plikZUzytkownikami << uzytkownicy[i].haslo << "|" << endl;
    }
    plikZUzytkownikami.close();
}

void zmianaHasla(vector<Uzytkownik> &uzytkownicy,int iloscUzytkownikow,int idZalogowanegoUzytkownika)
{
    string haslo;

    system("cls");
    cout << "Zmiana hasla" << endl << endl;

    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i = 0; i < iloscUzytkownikow; i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            aktualizujPlikZUzytkownikami(uzytkownicy,iloscUzytkownikow);
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
}

int pobierzKontaktyZPlikuZKontaktami(vector<Kontakt> &kontakty, int iloscKontaktow,int idZalogowanegoUzytkownika, int &maksymalneIDAdresata)
{
    Kontakt odczytywanyKontakt;
    fstream plikZKontaktami;
    string odczytanyFragmentTekstu;
    int idUzytkownika;
    int numerOdczytywanegoFragmentu = 1;

    plikZKontaktami.open("kontakty.txt",ios::in);

    if(plikZKontaktami.good()==false)
    {
        return 0;
    }
    else
    {
        while(getline(plikZKontaktami,odczytanyFragmentTekstu,'|'))
        {
            switch (numerOdczytywanegoFragmentu)
            {
            case 1:
            {
                odczytywanyKontakt.id = atoi(odczytanyFragmentTekstu.c_str());
                maksymalneIDAdresata = odczytywanyKontakt.id;
                break;
            }
            case 2:
            {
                idUzytkownika = atoi(odczytanyFragmentTekstu.c_str());
                if (idUzytkownika != idZalogowanegoUzytkownika)
                {
                    getline(plikZKontaktami,odczytanyFragmentTekstu);
                    numerOdczytywanegoFragmentu = 0;
                }
                break;
            }
            case 3:
            {
                odczytywanyKontakt.imie = odczytanyFragmentTekstu;
                break;
            }
            case 4:
            {
                odczytywanyKontakt.nazwisko = odczytanyFragmentTekstu;
                break;
            }
            case 5:
            {
                odczytywanyKontakt.numer = odczytanyFragmentTekstu;
                break;
            }
            case 6:
            {
                odczytywanyKontakt.email = odczytanyFragmentTekstu;
                break;
            }
            case 7:
            {
                odczytywanyKontakt.adres = odczytanyFragmentTekstu;
                iloscKontaktow++;
                kontakty.push_back(odczytywanyKontakt);
                numerOdczytywanegoFragmentu = 0;
                break;
            }
            }
            numerOdczytywanegoFragmentu++;
        }
        plikZKontaktami.close();
        return iloscKontaktow;
    }
}

int dodajKontakt(vector<Kontakt> &kontakty, int iloscKontaktow, int idZalogowanegoUzytkownika, int &maksymalneIDAdresata)
{
    Kontakt dodawanyKontakt;
    string imie, nazwisko, numer, email, adres;
    system("cls");
    cout << "Dodawanie kontaktu" << endl << endl;
    cout << "Podaj imie: ";
    cin.sync();
    getline(cin,imie);
    cout << "Podaj nazwisko: ";
    getline(cin,nazwisko);
    cout << "Podaj numer telefonu: ";
    getline(cin,numer);
    cout << "Podaj adres email: ";
    getline(cin,email);
    cout << "Podaj adres zamieszkania: ";
    getline(cin,adres);

    dodawanyKontakt.id = maksymalneIDAdresata + 1;
    dodawanyKontakt.imie = imie;
    dodawanyKontakt.nazwisko = nazwisko;
    dodawanyKontakt.numer = numer;
    dodawanyKontakt.email = email;
    dodawanyKontakt.adres = adres;

    maksymalneIDAdresata++;

    kontakty.push_back(dodawanyKontakt);

    fstream plikZKontaktami;

    plikZKontaktami.open("kontakty.txt",ios::out | ios::app);
    plikZKontaktami << dodawanyKontakt.id << "|";
    plikZKontaktami << idZalogowanegoUzytkownika << "|";
    plikZKontaktami << dodawanyKontakt.imie << "|";
    plikZKontaktami << dodawanyKontakt.nazwisko << "|";
    plikZKontaktami << dodawanyKontakt.numer << "|";
    plikZKontaktami << dodawanyKontakt.email << "|";
    plikZKontaktami << dodawanyKontakt.adres << "|" << endl;
    plikZKontaktami.close();

    cout << endl << "Kontakt dodany" << endl;
    Sleep(1500);
    return iloscKontaktow + 1;
}

void wyswietlKontakt(vector<Kontakt> &kontakty, int numerKontaktu)
{
    cout << "id: " << kontakty[numerKontaktu].id << endl;
    cout << "imie: " << kontakty[numerKontaktu].imie << endl;
    cout << "nazwisko: " << kontakty[numerKontaktu].nazwisko << endl;
    cout << "numer: " << kontakty[numerKontaktu].numer << endl;
    cout << "email: " << kontakty[numerKontaktu].email << endl;
    cout << "adres: " << kontakty[numerKontaktu].adres << endl << endl;
}

void wyswietlWszystkieKontakty(vector<Kontakt> &kontakty, int iloscKontaktow)
{
    system("cls");
    cout << "Wszystkie dostepne kontakty:" << endl << endl;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        wyswietlKontakt(kontakty,i);
    }
    cout << "Nacisnij klawisz ENTER aby powrocic do menu glownego";
    cin.ignore();
    getchar();
}

void wyswietlKontaktOPodanymImieniu(vector<Kontakt> &kontakty, int iloscKontaktow, string szukaneImie)
{
    system("cls");
    cout << "Wszystkie kontakty o imieniu " << szukaneImie << " :" << endl << endl;
    int liczbaZnalezionychKontaktow = 0;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].imie == szukaneImie)
        {
            wyswietlKontakt(kontakty,i);
            liczbaZnalezionychKontaktow++;
        }
    }
    if (liczbaZnalezionychKontaktow == 0)
    {
        cout << "brak kontaktow o podanym imieniu" << endl << endl;
    }
    cout << "Nacisnij klawisz ENTER aby powrocic do menu glownego";
    cin.ignore();
    getchar();
}

void wyswietlKontaktOPodanymNazwisku(vector<Kontakt> &kontakty, int iloscKontaktow, string szukaneNazwisko)
{
    system("cls");
    cout << "Wszystkie kontakty o nazwisku " << szukaneNazwisko << " :" << endl << endl;
    int liczbaZnalezionychKontaktow = 0;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].nazwisko == szukaneNazwisko)
        {
            wyswietlKontakt(kontakty,i);
            liczbaZnalezionychKontaktow++;
        }
    }
    if (liczbaZnalezionychKontaktow == 0)
    {
        cout << "brak kontaktow o podanym nazwisku" << endl << endl;
    }
    cout << "Nacisnij klawisz ENTER aby powrocic do menu glownego";
    cin.ignore();
    getchar();
}

int wyswietlKontaktOPodanymID(vector<Kontakt> &kontakty, int iloscKontaktow, int szukaneID)
{
    system("cls");
    cout << "Kontakt o ID " << szukaneID << " :" << endl << endl;
    int  numerIndeksuSzukanejPozycji = -1;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].id == szukaneID)
        {
            wyswietlKontakt(kontakty,i);
            numerIndeksuSzukanejPozycji = i;
            break;
        }
    }
    if (numerIndeksuSzukanejPozycji < 0)
    {
        cout << "brak kontaktow o podanym ID" << endl << endl;
        Sleep(1500);
    }
    return numerIndeksuSzukanejPozycji;
}

void aktualizujPlikZKontaktami(vector<Kontakt> &kontakty, int numerIndeksu, int szukaneID, int idZalogowanegoUzytkownika)
{
    system("cls");
    cout << "Aktualizowanie danych...";
    Sleep(1500);
    fstream plikTymczasowy;
    fstream plikZKontaktami;
    string pierwszyFragmentTekstu, drugiFragmentTekstu;
    int idAdresata;

    plikZKontaktami.open("kontakty.txt",ios::in);

    if(plikZKontaktami.good()==false)
    {
        return;
    }
    else
    {
        plikTymczasowy.open("tymczasowy.txt",ios::out);
        while(getline(plikZKontaktami,pierwszyFragmentTekstu,'|'))
        {
            idAdresata = atoi(pierwszyFragmentTekstu.c_str());
            getline(plikZKontaktami,drugiFragmentTekstu);
            if (idAdresata != szukaneID)
            {
                plikTymczasowy << pierwszyFragmentTekstu << "|";
                plikTymczasowy << drugiFragmentTekstu << endl;
            }
            else if (numerIndeksu >= 0)
            {
                plikTymczasowy << kontakty[numerIndeksu].id << "|";
                plikTymczasowy << idZalogowanegoUzytkownika << "|";
                plikTymczasowy << kontakty[numerIndeksu].imie << "|";
                plikTymczasowy << kontakty[numerIndeksu].nazwisko << "|";
                plikTymczasowy << kontakty[numerIndeksu].numer << "|";
                plikTymczasowy << kontakty[numerIndeksu].email << "|";
                plikTymczasowy << kontakty[numerIndeksu].adres << "|" << endl;
            }
        }
        plikTymczasowy.close();
        plikZKontaktami.close();
        remove("kontakty.txt");
        rename("tymczasowy.txt","kontakty.txt");
    }
}

int usunKontakt(vector<Kontakt> &kontakty, int iloscKontaktow, int szukaneID, int idZalogowanegoUzytkownika)
{
    int numerIndeksuPozycjiDoUsuniecia;
    numerIndeksuPozycjiDoUsuniecia = wyswietlKontaktOPodanymID(kontakty,iloscKontaktow,szukaneID);

    if (numerIndeksuPozycjiDoUsuniecia >= 0)
    {
        cout << "Czy na pewno usunac kontakt o ID " << szukaneID << " ?" << endl;
        cout << "Aby potwierdzic nacisnij 't'" << endl;
        char decyzja;
        cin >> decyzja;

        if (decyzja == 't')
        {
            kontakty.erase(kontakty.begin() + numerIndeksuPozycjiDoUsuniecia);
            iloscKontaktow --;
            aktualizujPlikZKontaktami(kontakty,-1,szukaneID,idZalogowanegoUzytkownika);
            system("cls");
            cout << "Kontakt usuniety" << endl;
        }
        else
        {
            system("cls");
            cout << "Usuwanie anulowane" << endl;
        }
    }
    Sleep(1500);
    return iloscKontaktow;
}

void edytujKontakt(vector<Kontakt> &kontakty, int iloscKontaktow, int szukaneID, int idZalogowanegoUzytkownika)
{
    int numerIndeksuPozycjiDoEdycji;
    numerIndeksuPozycjiDoEdycji = wyswietlKontaktOPodanymID(kontakty,iloscKontaktow,szukaneID);

    if (numerIndeksuPozycjiDoEdycji >= 0)
    {
        cout << "1 - imie" << endl;
        cout << "2 - nazwisko" << endl;
        cout << "3 - numer telefonu " << endl;
        cout << "4 - email" << endl;
        cout << "5 - adres" << endl;
        cout << "6 - powrot do menu" << endl;

        char wybor;
        string wprowadzoneDane;

        cin >> wybor;

        system("cls");

        switch(wybor)
        {
        case '1':
        {
            cout << "Obecne imie: " << kontakty[numerIndeksuPozycjiDoEdycji].imie << endl;
            cout << "Podaj nowe imie: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].imie = wprowadzoneDane;
            break;
        }
        case '2':
        {
            cout << "Obecne nazwisko: " << kontakty[numerIndeksuPozycjiDoEdycji].nazwisko << endl;
            cout << "Podaj nowe nazwisko: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].nazwisko = wprowadzoneDane;
            break;
        }
        case '3':
        {
            cout << "Obecny numer: " << kontakty[numerIndeksuPozycjiDoEdycji].numer << endl;
            cout << "Podaj nowy numer: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].numer = wprowadzoneDane;
            break;
        }
        case '4':
        {
            cout << "Obecny numer: " << kontakty[numerIndeksuPozycjiDoEdycji].email << endl;
            cout << "Podaj nowy email: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].email = wprowadzoneDane;
            break;
        }
        case '5':
        {
            cout << "Obecny numer: " << kontakty[numerIndeksuPozycjiDoEdycji].adres << endl;
            cout << "Podaj nowy adres: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].adres = wprowadzoneDane;
            break;
        }
        case '6':
        {
            cout << "Edycja anulowana";
            Sleep(1500);
            return;
        }
        }
        aktualizujPlikZKontaktami(kontakty,numerIndeksuPozycjiDoEdycji,szukaneID,idZalogowanegoUzytkownika);
    }
}

bool czySaJakiesKontakty(int iloscKontaktow)
{
    if (iloscKontaktow == 0)
    {
        system("cls");
        cout << "Brak kontaktow";
        Sleep(1500);
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    vector<Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;

    vector<Kontakt> kontakty;
    int iloscKontaktow = 0;

    string szukaneImie;
    string szukaneNazwisko;
    int szukaneID;

    int maksymalneIDAdresata = 0;

    char wybor;

    iloscUzytkownikow = pobierzUzytkownikowZPlikuZUzytkownikami(uzytkownicy,iloscUzytkownikow);

    while (true)
    {

        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wybor;

            switch(wybor)
            {
            case '1':
            {
                iloscUzytkownikow = rejestracja(uzytkownicy,iloscUzytkownikow);
                break;
            }
            case '2':
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy,iloscUzytkownikow);
                if (idZalogowanegoUzytkownika != 0)
                {
                    iloscKontaktow = pobierzKontaktyZPlikuZKontaktami(kontakty,iloscKontaktow,idZalogowanegoUzytkownika,maksymalneIDAdresata);
                }
                break;
            }
            case '9':
            {
                exit(0);
            }
            default:
            {
                cout << endl << "Wybrano niepoprawna opcje. Prosze wybrac dostepny numer." << endl;
                Sleep(1500);
                break;
            }
            }
        }
        else
        {
            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cin >> wybor;

            switch(wybor)
            {
            case '1':
            {
                iloscKontaktow = dodajKontakt(kontakty,iloscKontaktow,idZalogowanegoUzytkownika,maksymalneIDAdresata);
                break;
            }
            case '2':
            {
                if (czySaJakiesKontakty(iloscKontaktow))
                {
                    system("cls");
                    cout << "Wyszykiwanie" << endl << endl << "Podaj imie: " << endl;
                    cin >> szukaneImie;
                    wyswietlKontaktOPodanymImieniu(kontakty,iloscKontaktow,szukaneImie);
                }
                break;
            }
            case '3':
            {
                if (czySaJakiesKontakty(iloscKontaktow))
                {
                    system("cls");
                    cout << "Wyszykiwanie" << endl << endl << "Podaj nazwisko: " << endl;
                    cin >> szukaneNazwisko;
                    wyswietlKontaktOPodanymNazwisku(kontakty,iloscKontaktow,szukaneNazwisko);
                }
                break;
            }
            case '4':
            {
                if (czySaJakiesKontakty(iloscKontaktow))
                {
                    wyswietlWszystkieKontakty(kontakty,iloscKontaktow);
                }
                break;
            }
            case '5':
            {
                if (czySaJakiesKontakty(iloscKontaktow))
                {
                    system("cls");
                    cout << "Usuwanie kontaktu" << endl << endl << "Podaj ID kontaktu do usuniecia: " << endl;
                    cin >> szukaneID;
                    iloscKontaktow = usunKontakt(kontakty,iloscKontaktow,szukaneID,idZalogowanegoUzytkownika);
                }
                break;
            }
            case '6':
            {
                if (czySaJakiesKontakty(iloscKontaktow))
                {
                    system("cls");
                    cout << "Edycja kontaktu" << endl << endl << "Podaj ID kontaktu do edycji: " << endl;
                    cin >> szukaneID;
                    edytujKontakt(kontakty,iloscKontaktow,szukaneID,idZalogowanegoUzytkownika);
                }
                break;
            }
            case '7':
            {
                zmianaHasla(uzytkownicy,iloscUzytkownikow,idZalogowanegoUzytkownika);
                break;
            }
            case '8':
            {
                idZalogowanegoUzytkownika = 0;
                iloscKontaktow = 0;
                kontakty.clear();
                kontakty.shrink_to_fit();
                break;
            }
            default:
            {
                cout << endl << "Wybrano niepoprawna opcje. Prosze wybrac dostepny numer." << endl;
                Sleep(1500);
                break;
            }
            }
        }
    }


    return 0;
}

