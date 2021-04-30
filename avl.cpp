#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

#define max(x,y) (x > y)? x : y

struct element
{
    int wartosc;
    element * lewo = NULL;
    element * prawo = NULL;
    int wysokosc = 1;
};


int wys(element * a)
{
    if (a == NULL)
        return 0;
    return a->wysokosc;
}

int wywarzenie(element * a)
{
    if (a == NULL)
        return 0;
    return wys(a->lewo) - wys(a->prawo);
}

element * rotacjaP(element * a)
{
    element * b = a->lewo;
    element * T2 = b->prawo;
    b->prawo = a;
    a->lewo = T2;
    a->wysokosc = max(wys(a->lewo), wys(a->prawo)) + 1;
    b->wysokosc = max(wys(b->lewo), wys(b->prawo)) + 1;
    return b;
}

element * rotacjaL(element * a)
{
    element * b = a->prawo;
    element * T2 = b->lewo;
    b->lewo = a;
    a->prawo = T2;
    a->wysokosc = max(wys(a->lewo), wys(a->prawo)) + 1;
    b->wysokosc = max(wys(b->lewo), wys(b->prawo)) + 1;
    return b;
}

element * stworzelement(int w)
{
    element * a = new element;
    a->wartosc = w;
    return a;
}

element * dodaj(element * a, int w)
{
    if(a == NULL)
    {
        return stworzelement(w);
    }
    if(w < a->wartosc)
    {
        a->lewo = dodaj(a->lewo,w);
    }
    else if(w > a->wartosc)
    {
        a->prawo = dodaj(a->prawo,w);
    }
    a->wysokosc = max(wys(a->lewo), wys(a->prawo)) + 1;
    int b = wywarzenie(a);
    if(b > 1 && w < a->lewo->wartosc)
    {
        return rotacjaP(a);
    }
    if(b < -1 && w > a->prawo->wartosc)
    {
        return rotacjaL(a);
    }
    if(b > 1 && w > a->lewo->wartosc)
    {
        a->lewo = rotacjaL(a->lewo);
        return rotacjaP(a);
    }
    if(b < -1 && w < a->prawo->wartosc)
    {
        a->prawo = rotacjaP(a);
        return rotacjaL(a);
    }
    return a;
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

element * mini(element * a)
{
    element * tmp = a;
    while (tmp->lewo != NULL)
        tmp = tmp->lewo;
    return tmp;
}

element * usun(element * a, int w)
{
    if(a == NULL)
    {
        return a;
    }
    if(w < a->wartosc)
    {
        a->lewo = usun(a->lewo, w);
    }
    else if(w > a->wartosc)
    {
        a->prawo = usun(a->prawo, w);
    }
    else
    {
        if((a->lewo == NULL) || (a->prawo == NULL))
        {
            element * tmp;
            if(a->lewo == NULL)
            {
                tmp = a->prawo;
            }
            else
            {
                tmp = a->lewo;
            }
            if(tmp == NULL)
            {
                tmp = a;
                a = NULL;
            }
            else
            {
                *a = *tmp;
            }
            delete tmp;
        }
        else
        {
            element * tmp = mini(a->prawo);
            a->wartosc = tmp->wartosc;
            a->prawo = usun(a->prawo,tmp->wartosc);
        }
    }
    if(a == NULL)
    {
        return a;
    }
    a->wysokosc = max(wys(a->lewo),wys(a->prawo)) + 1;
    int b = wywarzenie(a);
    if(b > 1 && w < a->lewo->wartosc)
    {
        return rotacjaP(a);
    }
    if(b < -1 && w > a->prawo->wartosc)
    {
        return rotacjaL(a);
    }
    if(b > 1 && w > a->lewo->wartosc)
    {
        a->lewo = rotacjaL(a->lewo);
        return rotacjaP(a);
    }
    if(b < -1 && w < a->prawo->wartosc)
    {
        a->prawo = rotacjaP(a);
        return rotacjaL(a);
    }
    return a;
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

int N = 100000;
string nazwa = "..\\testy\\100ktros.txt";

int main()
{
    element * AVL = NULL;
    ifstream plik;
    plik.open(nazwa);
    LARGE_INTEGER freq, T1, T2;
    QueryPerformanceFrequency(&freq);
    int tmp=0;
    QueryPerformanceCounter(&T1);
    for(int i = 0; i<N; i++)
    {
        plik>>tmp;
        AVL = dodaj(AVL,tmp);
    }
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - wczytywanie z pliku t\n";
    QueryPerformanceCounter(&T1);
    istnieje(AVL, 0);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje min\n";
    QueryPerformanceCounter(&T1);
    istnieje(AVL, N-1);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje max\n";
    QueryPerformanceCounter(&T1);
    istnieje(AVL, N/2);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje srod\n";
    QueryPerformanceCounter(&T1);
    AVL = usun(AVL, 0);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie min\n";
    QueryPerformanceCounter(&T1);
    AVL = usun(AVL, N-1);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie max\n";
    QueryPerformanceCounter(&T1);
    AVL = usun(AVL, N/2);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie srod\n";
    return 0;
}
