#include <iostream>
using namespace std;
int rozmiar;
int counter = 0;

struct Skrzynka{
    double suma;
    double *butelki;

    void pobierz(){
        butelki = new double[rozmiar];
        double pom = 0;

        for(int i=0; i<rozmiar; i++){
            cin >> butelki[i];
            pom +=butelki[i];
        }
        suma = pom;
    }
};

class Lista{ //lista przechowujaca sumy
public:
    typedef Skrzynka wartosc;
    int licznik = 0;
private:
    wartosc *tab;
    int n, rozmiar_tab;
public:
    Lista(){
        n = 0;
        rozmiar_tab = 1;
        tab = new wartosc[rozmiar_tab];
    }

    void dodaj_back(wartosc w){
        if(n == rozmiar_tab){
            rozmiar_tab = rozmiar_tab * 2;
            wartosc * pom = new wartosc[rozmiar_tab];

            for(int i = 0; i<n; i++){
                pom[i] = tab[i];
            }

            delete [] tab;
            tab = pom;
        }

        tab[n] = w;
        n++;

    }

    void sortowanie_przez_wstawianie(int pojemnosc) {
        int j, i;
        for (j=1;j<n;j++){
            wartosc pom = tab[j];
            i=j-1;
            while((i>=0)&&(pom.suma > tab[i].suma)){
                tab[i+1] = tab[i];
                i--;
            }
            tab[i+1]=pom;
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<rozmiar; j++){
                cout << tab[i].butelki[j] << " ";
            }
            counter++;
            if(counter == pojemnosc) return;
            cout << endl;
        }

    }
};

void sortowanie_kubelkowe(Skrzynka* samolot, int skrzynki, int pojemnosc){
    Lista *kubelki = new Lista[skrzynki];  //kubełki uzaleznione od liczby skrzynek / (m+1)*1000 rowniez przechodzi, (wtedy praktycznie jest po jednej wart w kubelku)

    int indeks;
    for(int i=0; i<skrzynki; i++){
        indeks = samolot[i].suma;  // (samolot[i].suma * 1000)
        kubelki[indeks].dodaj_back(samolot[i]);
    }

    for(int i=skrzynki-1; i>=0; i--){ // i=(rozmiar+1)*1000 -1
        kubelki[i].sortowanie_przez_wstawianie(pojemnosc);
        if(counter == pojemnosc) break;
    }
    delete []kubelki;
}

int main(){
    ios_base::sync_with_stdio(false);

    int skrzynki, butelki, ladownia;
    cin >> skrzynki >> butelki >> ladownia;
    rozmiar = butelki;
    Skrzynka *samolot = new Skrzynka[skrzynki];

    for(int i=0; i<skrzynki; i++){
        samolot[i].pobierz();
    }

    sortowanie_kubelkowe(samolot, skrzynki, ladownia);
    delete []samolot;
    return 0;
}