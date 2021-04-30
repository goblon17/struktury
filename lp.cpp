#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

struct element
{
    int wartosc;
    element * next = NULL;
};

void dodaj(element ** a, int w)
{
    if(*a == NULL)
    {
        *a = new element;
        (*a)->wartosc = w;
    }
    else
    {
        element * tmp = *a;
        element * tmp3;
        if(tmp->wartosc > w)
        {
            element * tmp2 = new element;
            tmp2->wartosc = w;
            tmp2->next = *a;
            *a = tmp2;
            return;
        }
        while(tmp->next != NULL && tmp->wartosc < w)
        {
            tmp3 = tmp;
            tmp = tmp->next;
        }
        if(tmp->next == NULL && tmp->wartosc < w)
        {
            element * tmp2 = new element;
            tmp2->wartosc = w;
            tmp2->next = tmp->next;
            tmp->next = tmp2;
            return;
        }
        element * tmp2 = new element;
        tmp2->wartosc = w;
        tmp2->next = tmp3->next;
        tmp3->next = tmp2;
    }
}

void iterIwypisz(element * a)
{
    printf("%d\n", a->wartosc);
    element * b;
    b = a;
    while(b->next != NULL)
    {
        b = b->next;
        printf("%d\n", b->wartosc);
    }
}

void usun(element ** a, int w)
{
    if((*a)->wartosc == w)
    {
        element * tmp = (*a)->next;
        delete *a;
        *a = tmp;
    }
    else
    {
        element * tmp = *a;
        element * tmp3;
        while(tmp->next != NULL && tmp->wartosc != w)
        {
            tmp3 = tmp;
            tmp = tmp->next;
        }
        tmp3->next = tmp->next;
        delete tmp;
    }
}

bool istnieje(element * a, int w)
{
    element * b;
    b = a;
    while(b->next != NULL && b->wartosc < w)
    {
        if(b->wartosc == w)
        {
            return true;
        }
        b = b->next;
    }
    if(b->wartosc == w)
    {
        return true;
    }
    return false;
}

int N = 100000;
string nazwa = "..\\testy\\100ktros.txt";

int main()
{
    element * Lista = NULL;
    ifstream plik;
    plik.open(nazwa);
    LARGE_INTEGER freq, T1, T2;
    QueryPerformanceFrequency(&freq);
    int tmp=0;
    QueryPerformanceCounter(&T1);
    for(int i = 0; i<N; i++)
    {
        plik>>tmp;
        dodaj(&Lista,tmp);
    }
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - wczytywanie z pliku t\n";
    QueryPerformanceCounter(&T1);
    istnieje(Lista, 0);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje min\n";
    QueryPerformanceCounter(&T1);
    istnieje(Lista, N-1);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje max\n";
    QueryPerformanceCounter(&T1);
    istnieje(Lista, N/2);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - istnieje srod\n";
    QueryPerformanceCounter(&T1);
    usun(&Lista, 0);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie min\n";
    QueryPerformanceCounter(&T1);
    usun(&Lista, N-1);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie max\n";
    QueryPerformanceCounter(&T1);
    usun(&Lista, N/2);
    QueryPerformanceCounter(&T2);
    cout<<(float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart<<"ms - usuwanie srod\n";
    return 0;
}
