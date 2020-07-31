#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool sortowanko(int a, int b){
    return a > b;
}

class Algorytm{
public:
    int n; //liczba produktow
    int k; //kalorie
    int sposoby = 0;
    unsigned int rozmiar = 0;
    vector<int> tablica;

    void przejdz(int przekazana, int poczatek) {
        if(przekazana == k){
            sposoby++;
        }
        if(przekazana < k){
            for(unsigned int i=poczatek; i<rozmiar; i++)
                przejdz((przekazana+tablica[i]),i+1);
        }
    }

    int funkcja(){
        cin >> n;
        int x;
        for(int i=0; i<n; i++){
            cin >> x;
            tablica.push_back(x);
        }

        cin >> k;
        sort(tablica.begin(), tablica.end(), sortowanko);
        rozmiar = tablica.size();
        for (unsigned int i=0; i<rozmiar; i++) {
           przejdz(tablica[i], i+1);
        }
        return sposoby;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    int t; // liczba testow
    cin >> t;
    for(int i=0; i<t; i++){
        Algorytm *algorytm = new Algorytm();
        cout << algorytm->funkcja() << endl;
        delete algorytm;
        algorytm = NULL;
    }
    return 0;
}