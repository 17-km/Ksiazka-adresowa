#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, numer, email, adres;
};

int pobierzKontaktyZplikZKontaktamiu(vector<Kontakt> &kontakty, int iloscKontaktow)
{
    Kontakt odczytywanyKontakt;
    fstream plikZKontaktami;
    string odczytanaLiniaTekstu;
    int numerOdczytywanejLinii = 1;

    plikZKontaktami.open("kontakty.txt",ios::in);

    if(plikZKontaktami.good()==false)
    {
        return 0;
    }
    else
    {
        while(getline(plikZKontaktami,odczytanaLiniaTekstu,'|'))
        {
            switch (numerOdczytywanejLinii)
            {
            case 1:
            {
                odczytywanyKontakt.id = atoi(odczytanaLiniaTekstu.c_str());
                break;
            }
            case 2:
            {
                odczytywanyKontakt.imie = odczytanaLiniaTekstu;
                break;
            }
            case 3:
            {
                odczytywanyKontakt.nazwisko = odczytanaLiniaTekstu;
                break;
            }
            case 4:
            {
                odczytywanyKontakt.numer = odczytanaLiniaTekstu;
                break;
            }
            case 5:
            {
                odczytywanyKontakt.email = odczytanaLiniaTekstu;
                break;
            }
            case 6:
            {
                odczytywanyKontakt.adres = odczytanaLiniaTekstu;
                iloscKontaktow++;
                kontakty.push_back(odczytywanyKontakt);
                numerOdczytywanejLinii = 0;
                break;
            }
            }
            numerOdczytywanejLinii++;
        }
        plikZKontaktami.close();
        return iloscKontaktow;
    }
}

int dodajKontakt(vector<Kontakt> &kontakty, int iloscKontaktow)
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

    int najwiekszaWartoscID;
    if (iloscKontaktow == 0)
        najwiekszaWartoscID = 0;
    else
        najwiekszaWartoscID = kontakty[iloscKontaktow - 1].id;

    dodawanyKontakt.id = najwiekszaWartoscID + 1;
    dodawanyKontakt.imie = imie;
    dodawanyKontakt.nazwisko = nazwisko;
    dodawanyKontakt.numer = numer;
    dodawanyKontakt.email = email;
    dodawanyKontakt.adres = adres;

    kontakty.push_back(dodawanyKontakt);

    fstream plikZKontaktami;

    plikZKontaktami.open("kontakty.txt",ios::out | ios::app);
    plikZKontaktami << dodawanyKontakt.id << "|";
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
    }
    return numerIndeksuSzukanejPozycji;
}

void aktualizujPlikZKontaktami(vector<Kontakt> &kontakty, int iloscKontaktow)
{
    system("cls");
    cout << "Aktualizowanie danych...";
    Sleep(1500);
    fstream plikZKontaktami;
    plikZKontaktami.open("kontakty.txt",ios::out);

    for(int i = 0; i < iloscKontaktow; i++)
    {
        plikZKontaktami << kontakty[i].id << "|";
        plikZKontaktami << kontakty[i].imie << "|";
        plikZKontaktami << kontakty[i].nazwisko << "|";
        plikZKontaktami << kontakty[i].numer << "|";
        plikZKontaktami << kontakty[i].email << "|";
        plikZKontaktami << kontakty[i].adres << "|" << endl;
    }
}

int usunKontakt(vector<Kontakt> &kontakty, int iloscKontaktow, int szukaneID)
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
            aktualizujPlikZKontaktami(kontakty,iloscKontaktow);
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

void edytujKontakt(vector<Kontakt> &kontakty, int iloscKontaktow, int szukaneID)
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
            aktualizujPlikZKontaktami(kontakty,iloscKontaktow);
            break;
        }
        case '2':
        {
            cout << "Obecne nazwisko: " << kontakty[numerIndeksuPozycjiDoEdycji].nazwisko << endl;
            cout << "Podaj nowe nazwisko: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].nazwisko = wprowadzoneDane;
            aktualizujPlikZKontaktami(kontakty,iloscKontaktow);
            break;
        }
        case '3':
        {
            cout << "Obecny numer: " << kontakty[numerIndeksuPozycjiDoEdycji].numer << endl;
            cout << "Podaj nowy numer: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].numer = wprowadzoneDane;
            aktualizujPlikZKontaktami(kontakty,iloscKontaktow);
            break;
        }
        case '4':
        {
            cout << "Obecny numer: " << kontakty[numerIndeksuPozycjiDoEdycji].email << endl;
            cout << "Podaj nowy email: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].email = wprowadzoneDane;
            aktualizujPlikZKontaktami(kontakty,iloscKontaktow);
            break;
        }
        case '5':
        {
            cout << "Obecny numer: " << kontakty[numerIndeksuPozycjiDoEdycji].adres << endl;
            cout << "Podaj nowy adres: ";
            cin.sync();
            getline(cin,wprowadzoneDane);
            kontakty[numerIndeksuPozycjiDoEdycji].adres = wprowadzoneDane;
            aktualizujPlikZKontaktami(kontakty,iloscKontaktow);
            break;
        }
        case '6':
        {
            cout << "Edycja anulowana";
            break;
        }
        }
        Sleep(1500);
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
    vector<Kontakt> kontakty;
    int iloscKontaktow = 0;

    string szukaneImie;
    string szukaneNazwisko;
    int szukaneID;

    iloscKontaktow = pobierzKontaktyZplikZKontaktamiu(kontakty,iloscKontaktow);

    char wybor;

    while (true)
    {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;

        cin >> wybor;

        switch(wybor)
        {
        case '1':
        {
            iloscKontaktow = dodajKontakt(kontakty,iloscKontaktow);
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
                iloscKontaktow = usunKontakt(kontakty,iloscKontaktow,szukaneID);
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
                edytujKontakt(kontakty,iloscKontaktow,szukaneID);
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


    return 0;
}
