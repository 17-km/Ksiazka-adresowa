#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, numer, email, adres;
};

int pobierzKontaktyZPliku(Kontakt kontakty[], int iloscKontaktow)
{
    int id;
    string imie, nazwisko, numer, email, adres;

    fstream plik;
    string linia;
    int licznik = 1;

    plik.open("kontakty.txt",ios::in);

    if(plik.good()==false)
    {
        return 0;
    }
    else
    {
        while(getline(plik,linia))
        {
            switch (licznik)
            {
            case 1:
            {
                kontakty[iloscKontaktow].id = atoi(linia.c_str());
                break;
            }
            case 2:
            {
                kontakty[iloscKontaktow].imie = linia;
                break;
            }
            case 3:
            {
                kontakty[iloscKontaktow].nazwisko = linia;
                break;
            }
            case 4:
            {
                kontakty[iloscKontaktow].numer = linia;
                break;
            }
            case 5:
            {
                kontakty[iloscKontaktow].email = linia;
                break;
            }
            case 6:
            {
                kontakty[iloscKontaktow].adres = linia;
                iloscKontaktow++;
                licznik = 0;
                break;
            }
            }
            licznik++;
        }
        plik.close();
        return iloscKontaktow;
    }
}


int dodajKontakt(Kontakt kontakty[], int iloscKontaktow)
{
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

    kontakty[iloscKontaktow].id = iloscKontaktow + 1;
    kontakty[iloscKontaktow].imie = imie;
    kontakty[iloscKontaktow].nazwisko = nazwisko;
    kontakty[iloscKontaktow].numer = numer;
    kontakty[iloscKontaktow].email = email;
    kontakty[iloscKontaktow].adres = adres;

    fstream plik;

    plik.open("kontakty.txt",ios::out | ios::app);
    plik << iloscKontaktow + 1 << endl;
    plik << imie << endl;
    plik << nazwisko << endl;
    plik << numer << endl;
    plik << email << endl;
    plik << adres << endl;
    plik.close();

    cout << endl << "Kontakt dodany" << endl;
    Sleep(1500);
    return iloscKontaktow + 1;
}

void wyswietlKontakt(Kontakt kontakty[], int numerKontaktu)
{
    cout << "id: " << kontakty[numerKontaktu].id << endl;
    cout << "imie: " << kontakty[numerKontaktu].imie << endl;
    cout << "nazwisko: " << kontakty[numerKontaktu].nazwisko << endl;
    cout << "numer: " << kontakty[numerKontaktu].numer << endl;
    cout << "email: " << kontakty[numerKontaktu].email << endl;
    cout << "adres: " << kontakty[numerKontaktu].adres << endl << endl;
}

void wyswietlWszystkieKontakt(Kontakt kontakty[], int iloscKontaktow)
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

void wyswietlKontaktOPodanymImieniu(Kontakt kontakty[], int iloscKontaktow, string szukaneImie)
{
    system("cls");
    cout << "Wszystkie kontakty o imieniu " << szukaneImie << " :" << endl << endl;
    int licznik = 0;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].imie == szukaneImie)
        {
            wyswietlKontakt(kontakty,i);
            licznik++;
        }
    }
    if (licznik == 0)
    {
        cout << "brak kontaktow o podanym imieniu" << endl << endl;
    }
    cout << "Nacisnij klawisz ENTER aby powrocic do menu glownego";
    cin.ignore();
    getchar();
}

void wyswietlKontaktOPodanymNazwisku(Kontakt kontakty[], int iloscKontaktow, string szukaneNazwisko)
{
    system("cls");
    cout << "Wszystkie kontakty o nazwisku " << szukaneNazwisko << " :" << endl << endl;
    int licznik = 0;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].nazwisko == szukaneNazwisko)
        {
            wyswietlKontakt(kontakty,i);
            licznik++;
        }
    }
    if (licznik == 0)
    {
        cout << "brak kontaktow o podanym nazwisku" << endl << endl;
    }
    cout << "Nacisnij klawisz ENTER aby powrocic do menu glownego";
    cin.ignore();
    getchar();
}

int main()
{
    Kontakt kontakty[1000];
    int iloscKontaktow = 0;
    string szukaneImie;
    string szukaneNazwisko;

    iloscKontaktow = pobierzKontaktyZPliku(kontakty,iloscKontaktow);

    char wybor;

    while (iloscKontaktow == 0)
    {
        system("cls");
        cout << "***brak kontaktow***" << endl << endl;
        cout << "1. Dodaj kontakt" << endl;
        cout << "2. Zakoncz program" << endl;

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

    while (iloscKontaktow > 0)
    {
        system("cls");
        cout << "1. Dodaj kontakt" << endl;
        cout << "2. Wyszukaj kontakt po imieniu" << endl;
        cout << "3. Wyszukaj kontakt po nazwisku" << endl;
        cout << "4. Pokaz wszystkie kontakty" << endl;
        cout << "5. Zakoncz program" << endl;

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
            system("cls");
            cout << "Wyszykiwanie" << endl << endl << "Podaj imie: " << endl;
            cin >> szukaneImie;
            wyswietlKontaktOPodanymImieniu(kontakty,iloscKontaktow,szukaneImie);
            break;
        }
        case '3':
        {
            system("cls");
            cout << "Wyszykiwanie" << endl << endl << "Podaj nazwisko: " << endl;
            cin >> szukaneNazwisko;
            wyswietlKontaktOPodanymNazwisku(kontakty,iloscKontaktow,szukaneNazwisko);
            break;
        }
        case '4':
        {
            wyswietlWszystkieKontakt(kontakty,iloscKontaktow);
            break;
        }
        case '5':
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
