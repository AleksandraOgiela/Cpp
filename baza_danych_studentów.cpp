#include <iostream>
#include <iomanip>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int id2 = 0;

struct student
{
    int id;
    string nazwisko;
    string specjalnosc;
    float srednia;

    student(int Id, string Nazwisko,string Specjalnosc, float Srednia)
    {
        id = Id;
        nazwisko = Nazwisko;
        specjalnosc = Specjalnosc;
        srednia = Srednia;

    }

    student* nast;
    student* next;

    void wypisz();
};


student* baza_studentow = NULL;

// Funkcja dodaj¹ca studenta na pocz¹tek listy
void dodaj_pocz(student* &lista)
{

    string nazwisko2, specjalnosc2;
    float srednia2 =0.0;
    id2++;
    cout<<"Podaj nazwisko studenta: ";
    cin>>nazwisko2;
    cout<<"Podaj specjalnosc studenta: ";
    cin>>specjalnosc2;
    cout<<"Podaj srednia uzyskana przez studenta: ";
    try
    {
        cin>>srednia2;
    }

    catch(const std::invalid_argument& ia)
    {
        cout<< "Invalid argument: " << ia.what() <<endl;
        Sleep(2000);
    }

    student* wsk = new student(id2,nazwisko2,specjalnosc2,srednia2);
    wsk->nast=lista;
    lista = wsk;


}

//Funkcja dodaj¹ca studenta na koniec lity
void dodaj_kon(student* &lista)
{
    student* wl, * ne;
    string nazwisko2, specjalnosc2;
    cout<<"Podaj nazwisko studenta: ";
    cin>>nazwisko2;
    cout<<"Podaj specjalnosc studenta: ";
    cin>>specjalnosc2;
    float srednia2 =0.0;
    id2++;
    cout<<"Podaj srednia uzyskana przez studenta: ";
    cin>>srednia2;
    ne = new student(id2,nazwisko2,specjalnosc2,srednia2);
    ne->nast = NULL;
    wl = lista;
    if(wl)
    {
        while(wl->nast) wl = wl->nast;
        wl->nast = ne;
    }
    else lista = ne;
}
//Funkcja licz¹ca iloœæ wpisanych studentów
int rozmiar(student* p)
{
    int licznik = 0;

    while(p)
    {
        licznik++;
        p = p->nast;
    }
    return licznik;
}

//Funkcja wyszukuj¹ca studenów po Id, Nazwisku, Specjalnoœci, Œredniej
student* wyszukaj(student* &lista)
{
    student* sz = lista;
    int wyb, Id;
    float Srednia;
    string Nazwisko, Specjalnosc;

    int rozmiar_tmp = rozmiar(lista);

    if(rozmiar_tmp==0)
    {
        throw "Nie mozna wyszukac - lista jest pusta!";
    }

    cout<<"Wyszukaj po: "<<endl;
    cout<<"1 - Id"<<endl;
    cout<<"2 - Nazwisku"<<endl;
    cout<<"3 - Specjalnosci"<<endl;
    cout<<"4 - Sredniej"<<endl;
    cin>>wyb;

    switch(wyb)
    {
    case 1:
        cout<<"Wyszkiwanie po Id: "<<endl;
        {
            cout<<"Podaj Id: ";
            cin>>Id;
            while(sz && sz->id != Id) sz = sz->nast;
            sz->wypisz();

            Sleep(3000);
            return sz;
        }
        break;
    case 2:
        cout<<"Wyszukiwanie po nazwisku: "<<endl;
        {
            cout<<"Podaj nazwisko: ";
            cin>>Nazwisko;
            {
                while(sz && sz->nazwisko != Nazwisko) sz = sz->nast;
                sz->wypisz();
            }
            Sleep(3000);
            return sz;
        }
        break;
    case 3:
        cout<<"Wyszukiwanie po specjalnosci: "<<endl;
        {
            cout<<"Podaj specjalnosc: ";
            cin>>Specjalnosc;
            while(sz && sz->specjalnosc != Specjalnosc) sz = sz->nast;
            sz->wypisz();
            Sleep(3000);
            return sz;
        }
        break;
    case 4:
        cout<<"Wyszukiwanie po sredniej: "<<endl;
        {
            cout<<"Podaj srednia: ";
            cin>>Srednia;
            while(sz && sz->srednia!= Srednia) sz = sz->nast;
            sz->wypisz();
            Sleep(3000);
            return sz;
        }
        break;

    default:
        cout<<"Wybierz inne kryterium"<<endl;

    }



}

//Funkcja usuwaj¹ca studentów z pocz¹tku lub koñcza listy
void usun(student* &lista)
{
    int rozmiar_tmp = rozmiar(lista);

    if(rozmiar_tmp==0)
    {
        throw "Nie mozna usunac- lista jest pusta!";
    }
    cout<<"Jaki element chcesz usunac? Z poczatku listy - 1, z konca listy - 2"<<endl;
    int wybor_usuwania;
    cin>>wybor_usuwania;
    switch(wybor_usuwania)
    {
    case 1:
        cout<<"Usuwanie elemntu z poczatku listy..."<<endl;
        {
            Sleep(3000);
            student* ws;
            ws = lista;
            if(ws)
            {
                lista = ws->nast;
                delete ws;
                cout<<"Element na poczatku listy zostal usuniety"<<endl;
            }

        }
        break;

    case 2:
        cout<<"Usuwanie elementu z konca listy..."<<endl;
        Sleep(3000);
        {
            student* wk = lista;
            if(wk)
            {
                if(wk->nast)
                {
                    while(wk->nast->nast) wk = wk->nast;
                    delete wk->nast;
                    cout<<"Element na koncu listy zostal usuniety."<<endl;
                    wk->nast = NULL;
                }
                else
                {
                    delete wk;
                    cout<<"Element na koncu listy zostal usuniety."<<endl;
                    lista = NULL;
                }
            }
        }
        break;
    default:
        cout<<"Wybrales zla opcje. Wybierz jeszcze raz."<<endl;
    }
}

//Funkcja usuwaj¹ca wybranego studenta
void usun_wybrany(student* &lista)
{
    int rozmiar_tmp = rozmiar(lista);

    if(rozmiar_tmp==0)
    {
        throw "Nie mozna usunac - lista jest pusta!";
    }
    student* wy, * rp;
    rp = wyszukaj(baza_studentow);

    if(lista == rp)
    {

        wy = lista;
        if(wy)
        {
            lista = wy->nast;
            delete wy;
            cout<<"Wybrany element zostal usuniety.";
            Sleep(3000);

        }
    }
    else
    {
        wy = lista;
        while(wy->nast != rp) wy = wy->nast;
        wy->nast = rp->nast;
        delete rp;
        cout<<"Wybrany element zostal usuniety";
        Sleep(3000);
    }
}

//Funkcja edytuj¹ca rekord
void edytuj(student* lista)
{

    student* rp;
    int wyb;
    string nowe_nazwisko, nowa_spec;
    float nowa_srednia;
    cout<<"Wybierz ktory rekord chcesz edytowac"<<endl;

    rp = wyszukaj(baza_studentow);

    cout<<"Wybierz co chcesz edytowac: "<<endl;
    cout<<"1 - nazwisko"<<endl;
    cout<<"2 - specjalnosc"<<endl;
    cout<<"3 - srednia"<<endl;
    cin>>wyb;



    switch(wyb)
    {
    case 1:
    {

        cout<<"Podaj nowe nazwisko: ";
        cin>>nowe_nazwisko;

    }

    break;
    case 2:
    {
        cout<<"Podaj nowa specjalnosc: ";
        cin>>nowa_spec;
        rp->specjalnosc = nowa_spec;
    }
    break;
    case 3:
    {
        cout<<"Podaj nowa srednia: ";
        cin>>nowa_srednia;
        rp->srednia = nowa_srednia;
    }
    break;
    default:
        cout<<"Wybierz inne kryteria do edycji"<<endl;
    }

}




//Funkcja wypisuj¹ca rekor
void student::wypisz()
{
    cout<<id<<setw(15)<<nazwisko<<setw(15)<<specjalnosc<<setw(15)<<srednia<<endl;
}




//Funkcja zapisuj¹ca plik
void zapisz(student* m)
{

    ofstream plik;
    plik.open("baza.txt");
    while(m)
    {
        plik<<m->id<<setw(15)<<m->nazwisko<<setw(15)<<m->specjalnosc<<setw(15)<<m->srednia<<endl;
        m = m->nast;
    }

    plik.close();

}

//Funkcja dopisuj¹ca studenta do pliku
void dopisz_plik()
{
    string nazwisko_dop, specjalnosc_dop;
    float srednia_dop;
    id2++;

    cout<<"Podaj nazwisko dopisywanego studenta: ";
    cin>>nazwisko_dop;
    cout<<"Podaj specjalnosc dopisywanego studenta: ";
    cin>>specjalnosc_dop;
    cout<<"Podaj srednia dopisywanego studenta: ";
    cin>>srednia_dop;
    ofstream plik;
    plik.open("baza.txt",ios::app);

    plik<<id2<<setw(15)<<nazwisko_dop<<setw(15)<<specjalnosc_dop<<setw(15)<<srednia_dop<<endl;

    plik.close();

}

//Funkcja wczytuj¹ca plik
void wczytaj(student* &lista)
{
    string nazwisko2 =" ", specjalnosc2 = " ";
    float srednia2 =0.0;
    int id_zrob = 0;
    int id_temp;

    student* p;

    ifstream plik("baza.txt",ios::in);

    while(plik>>id_zrob)
    {
        int licznik = 0;
        p = lista;
        plik>>nazwisko2>>specjalnosc2>>srednia2;
        while(p)
        {
            id_temp = (*p).id;
            if(id_zrob == id_temp)
            {
                licznik++;

                cout<<"Takie Id juz istnieje na liscie: "<<endl;
                cout<<p->id<<setw(15)<<p->nazwisko<<setw(15)<<p->specjalnosc<<setw(15)<<p->srednia<<endl;
                cout<<"Rekord o tym samym Id w pliku jest postaci: "<<id_zrob<<setw(15)<<nazwisko2<<setw(15)<<specjalnosc2<<setw(15)<<srednia2<<endl;


            }
            p=p->nast;

        }

        if(licznik == 0)
        {
            student* wsk = new student(id_zrob,nazwisko2,specjalnosc2,srednia2);
            wsk->nast=lista;
            lista = wsk;
        }
    }

    plik.close();
}

//Funkcja zaamykaaj¹ca bazê
void exit()

{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<"Koniec programu"<<endl;
    Sleep(2000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int main()
{


    int wybor;

    do
    {
        system("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);

        cout << " MENU GLOWNE LISTY:"<<endl;
        cout << "---------------------------"<<endl;
        cout<<"1  - Dodaj Studenta na poczatek listy."<<endl;
        cout<<"2  - Dodaj Studenta na koniec listy."<<endl;
        cout<<"3  - Usun pierwszy lub ostatni rekord z listy studentow."<<endl;
        cout<<"4  - Usun wybrany rekord z listy studentow."<<endl;
        cout<<"5  - Edytuj rekord."<<endl;
        cout<<"6  - Wyswietl aktualny stan bazy."<<endl;
        cout<<"7  - Wyszukaj wg id, nazwiska,sredniej, specjalnosci."<<endl;
        cout<<"8  - Zapisz baze do pliku."<<endl;
        cout<<"9  - Zapisz pojedynczy rekord do pliku."<<endl;
        cout<<"10 - Wczytaj baze z pliku."<<endl;
        cout<<"11 - Zakoncz program."<<endl;
        cout<<"Wybor: ";
        cin>>wybor;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

        switch(wybor)
        {
        case 1:
            cout<<"Dodawanie rekordu na poczatek listy."<<endl;
            dodaj_pocz(baza_studentow);
            break;
        case 2:
            cout<<"Dodawanie rekordu na koniec listy"<<endl;
            dodaj_kon(baza_studentow);
            break;
        case 3:
            cout<<"Usuwanie rekordu z poczatku lub konca"<<endl;
            {
                try
                {
                    usun(baza_studentow);
                    Sleep(5000);

                }
                catch(const char *msg)
                {
                    cerr<<msg<<endl;
                    Sleep(5000);
                }

            }
            break;
        case 4:
            cout<<"Usuwanie wybranego rekordu."<<endl;
            {
                try
                {
                    usun_wybrany(baza_studentow);
                    Sleep(5000);

                }
                catch(const char *msg)
                {
                    cerr<<msg<<endl;
                    Sleep(5000);
                }

            }
            break;
        case 5:
            cout<<"Edytowanie rekordu."<<endl;
            {
                try
                {
                    edytuj(baza_studentow);

                }
                catch(const char *msg)
                {
                    cerr<<msg<<endl;
                    Sleep(5000);
                }

            }
            break;
        case 6:
            cout<<"Wyswietlanie stanu bazy:\n"<<endl;
            {
                student* t = baza_studentow;
                while(t != NULL)
                {
                    t->wypisz();
                    t=t->nast;
                }
                Sleep(8000);
            }
            break;
        case 7:
            cout<<"Wyszukiwanie."<<endl;
            wyszukaj(baza_studentow);
            break;
        case 8:
            cout<<"Zapisywanie bazy do pliku..."<<endl;
            {
                Sleep(3000);
                zapisz(baza_studentow);
                cout<<"Baza zostala zapisana do pliku."<<endl;
                Sleep(2000);
            }
            break;
        case 9:
            cout<<"Dopisywanie rekordu do pliku"<<endl;
            {
                dopisz_plik();
                cout<<"Rekord jest dopisywany..."<<endl;
                Sleep(3000);
                cout<<"Rekord zapisano"<<endl;
                Sleep(3000);
            }
            break;
        case 10:
            cout<<"Wczytywanie bazy z pliku..."<<endl;
            Sleep(3000);
            wczytaj(baza_studentow);
            break;
        case 11:
            exit();
            break;
        default:
            cout<<"Ten klawisz jest nieaktywny."<<"\nWybierz poprawna funkcjonalnosc (liczby 1-11)"<<endl;
            Sleep(3000);

            break;
        }
        system("cls");
    }
    while(wybor!=11);




    return 0;

}
