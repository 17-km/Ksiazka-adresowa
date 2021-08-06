#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, numer, email, adres;
};

int pobierzKontaktyZplikZKontaktamiu(Kontakt kontakty[], int iloscKontaktow)
{
    int id;
    string imie, nazwisko, numer, email, adres;

    fstream plikZKontaktami;
    string oczyttanaLiniaTekstu;
    int numerOdczytywanejLinii = 1;

    plikZKontaktami.open("kontakty.txt",ios::in);

    if(plikZKontaktami.good()==false)
    {
        return 0;
    }
    else
    {
        while(getline(plikZKontaktami,oczyttanaLiniaTekstu))
        {
            switch (numerOdczytywanejLinii)
            {
            case 1:
            {
                kontakty[iloscKontaktow].id = atoi(oczyttanaLiniaTekstu.c_str());
                break;
            }
            case 2:
            {
                kontakty[iloscKontaktow].imie = oczyttanaLiniaTekstu;
                break;
            }
            case 3:
            {
                kontakty[iloscKontaktow].nazwisko = oczyttanaLiniaTekstu;
                break;
            }
            case 4:
            {
                kontakty[iloscKontaktow].numer = oczyttanaLiniaTekstu;
                break;
            }
            case 5:
            {
                kontakty[iloscKontaktow].email = oczyttanaLiniaTekstu;
                break;
            }
            case 6:
            {
                kontakty[iloscKontaktow].adres = oczyttanaLiniaTekstu;
                iloscKontaktow++;
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

    fstream plikZKontaktami;

    plikZKontaktami.open("kontakty.txt",ios::out | ios::app);
    plikZKontaktami << iloscKontaktow + 1 << endl;
    plikZKontaktami << imie << endl;
    plikZKontaktami << nazwisko << endl;
    plikZKontaktami << numer << endl;
    plikZKontaktami << email << endl;
    plikZKontaktami << adres << endl;
    plikZKontaktami.close();

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

void wyswietlWszystkieKontakty(Kontakt kontakty[], int iloscKontaktow)
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
    int numerOdczytywanejLinii = 0;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].imie == szukaneImie)
        {
            wyswietlKontakt(kontakty,i);
            numerOdczytywanejLinii++;
        }
    }
    if (numerOdczytywanejLinii == 0)
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
    int numerOdczytywanejLinii = 0;
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].nazwisko == szukaneNazwisko)
        {
            wyswietlKontakt(kontakty,i);
            numerOdczytywanejLinii++;
        }
    }
    if (numerOdczytywanejLinii == 0)
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

    iloscKontaktow = pobierzKontaktyZplikZKontaktamiu(kontakty,iloscKontaktow);

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
            wyswietlWszystkieKontakty(kontakty,iloscKontaktow);
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
