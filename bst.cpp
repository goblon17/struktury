#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

struct element
{
    int wartosc;
    element * lewo = NULL;
    element * prawo = NULL;
};

void dodaj(element ** a, int w)
{
    if((*a) == NULL)
    {
        element * tmp = new element;
        tmp->wartosc = w;
        *a = tmp;
    }
    else
    {
        element * tmp = *a;
        while(true)
        {
            if(tmp->wartosc > w && tmp->lewo == NULL)
            {
                element * tmp2 = new element;
                tmp2->wartosc = w;
                tmp->lewo = tmp2;
                break;
            }
            else if(tmp->wartosc > w)
            {
                tmp = tmp->lewo;
            }
            if(tmp->wartosc < w && tmp->prawo == NULL)
            {
                element * tmp2 = new element;
                tmp2->wartosc = w;
                tmp->prawo = tmp2;
                break;
            }
            else if(tmp->wartosc < w)
            {
                tmp = tmp->prawo;
            }
        }
    }
}

void zgleb(element * a)
{
    if(a->lewo != NULL)
    {
        zgleb(a->lewo);
    }
    printf("%d\n", a->wartosc);
    if(a->prawo != NULL)
    {
        zgleb(a->prawo);
    }
}

void wypisz(element * a)
{
    zgleb(a);
}

bool istnieje(element * a, int w)
{
    if(a->wartosc == w)
    {
        return true;
    }
    element * tmp = a;
    while(true)
    {
        if(tmp->wartosc < w)
        {
            tmp = tmp->prawo;
        }
        else if(tmp->wartosc > w)
        {
            tmp = tmp->lewo;
        }
        if(tmp == NULL)
        {
            return false;
        }
        if(tmp->wartosc == w)
        {
            return true;
        }
    }
}

element * znajdz(element * a, int w)
{
    if(a->wartosc == w)
    {
        return a;
    }
    element * tmp = a;
    while(true)
    {
        if(tmp->wartosc < w)
        {
            tmp = tmp->prawo;
        }
        else if(tmp->wartosc > w)
        {
            tmp = tmp->lewo;
        }
        if(tmp == NULL)
        {
            return NULL;
        }
        if(tmp->wartosc == w)
        {
            return tmp;
        }
    }
}

element * mini(element * a)
{
    element * tmp = a;
    while (tmp->lewo != NULL)
        tmp = tmp->lewo;
    return tmp;
}

element * usun(element * a, int w)
{
    if (a == NULL)
        return a;
    if (w < a->wartosc)
        a->lewo = usun(a->lewo, w);
    else if (w > a->wartosc)
        a->prawo = usun(a->prawo, w);
    else
    {
        if (a->lewo == NULL && a->prawo == NULL)
            return NULL;
        else if (a->lewo == NULL)
        {
            element * tmp = a->prawo;
            delete a;
            return tmp;
        }
        else if (a->lewo == NULL)
        {
            element * tmp = a->lewo;
            delete a;
            return tmp;
        }
        element * tmp = mini(a->prawo);
        a->wartosc = tmp->wartosc;
        a->prawo = usun(a->prawo, tmp->wartosc);
    }
    return a;
}

int N = 100000;
string nazwa = "..\\testy\\100ktros.txt";

int main()
{
    element * drzewko = NULL;
    ifstream plik;
    plik.open(nazwa);
    LARGE_INTEGER freq, T1, T2;
    QueryPerformanceFrequency(&freq);
    int tmp=0;
    QueryPerformanceCounter(&T1);
    for(int i = 0; i<N; i++)
    {
        plik>>tmp;
        dodaj(&drzewko,tmp);
    }
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - wczytywanie z pliku t\n";
    QueryPerformanceCounter(&T1);
    istnieje(drzewko, 0);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje min\n";
    QueryPerformanceCounter(&T1);
    istnieje(drzewko, N-1);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje max\n";
    QueryPerformanceCounter(&T1);
    istnieje(drzewko, N/2);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje srod\n";
    QueryPerformanceCounter(&T1);
    drzewko = usun(drzewko, 0);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie min\n";
    QueryPerformanceCounter(&T1);
    drzewko = usun(drzewko, N-1);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie max\n";
    QueryPerformanceCounter(&T1);
    drzewko = usun(drzewko, N/2);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie srod\n";
    return 0;
}
