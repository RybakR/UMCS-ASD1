#include <iostream>
#include<vector>
using namespace std;

class Wierzcholek {
public:
    vector<int> sasiedzi;
};

class Algorytm {
public:
    int n;  //punkty odbioru
    int m;  //ilosc polaczen
    int s; //punkt koncowy
    int k;  //ilosc paczek

    int ilosc_sciezek = 0;
    Wierzcholek *tablica;
    int **tab;

    bool jedz_sobie_januszu(int odebrales_paczek, int w){
      if (odebrales_paczek == k) {
        return false;
      }

      bool result = false;
      for (unsigned int i=0; i<tablica[w].sasiedzi.size(); i++){
        int sasiad = tablica[w].sasiedzi[i];

        if(tab[sasiad][odebrales_paczek+1] != -1){
            if (sasiad == s && odebrales_paczek+1 == k) {
                ilosc_sciezek++;
                tab[w][odebrales_paczek]++;
                return true;
            } 
            else if(tab[sasiad][odebrales_paczek+1]  != 0){
                ilosc_sciezek += tab[sasiad][odebrales_paczek+1];
                tab[w][odebrales_paczek]+=tab[sasiad][odebrales_paczek+1];
                result = true;
            }
            else if(jedz_sobie_januszu(odebrales_paczek+1, sasiad)) {
                tab[w][odebrales_paczek]+=tab[sasiad][odebrales_paczek+1];
                result = true;
            }
            else {
                tab[sasiad][odebrales_paczek+1] = -1;
            }
          }
      }
      return result;
    }

    int funkcja(){
        cin >> n >> m >> s >> k;

        tablica = new Wierzcholek[n];
        tab = new int*[n];

        for(int i = 0; i<n ; i++){
            tab[i] = new int[k+1];
        }

        for(int i=0;i<n;i++){
            for(int j=0; j<k+1; j++){
                tab[i][j] = 0;
            }
        }

        for (int i = 0; i<m; i++) {
            int x,y;
            cin >> x >> y;
            tablica[x].sasiedzi.push_back(y);
        }

        vector<int> sciezka;
        jedz_sobie_januszu(0, 0);

        sciezka.clear();
        for(int i = 0; i<n; i++) {
            delete[] tab[i];
        }
        delete[] tab;
        delete[] tablica;
        return ilosc_sciezek;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    int t; //zestawy danych
    cin >> t;
    for (int i=0; i<t; i++) {
        Algorytm *algorytm = new Algorytm();
        cout << algorytm->funkcja() << endl;
        delete algorytm;
    }
    return 0;
}