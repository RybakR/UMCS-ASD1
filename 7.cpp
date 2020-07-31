#include <iostream>
#include <vector>
using namespace std;
int licznik;
int dlugosc;

class Wezel{
public:
    int wartosc;
    Wezel *lewy;
    Wezel *prawy;
};

vector<int> przejdz(Wezel *wezel) {
        vector<int> wynik, lewy, prawy;
        if (wezel->lewy != NULL) {
            lewy = przejdz(wezel->lewy);
        }
        if (wezel->prawy != NULL) {
            prawy = przejdz(wezel->prawy);
        }

        if(wezel->wartosc == dlugosc){
           licznik++;
        } else if (wezel->wartosc < dlugosc){
            wynik.push_back(wezel->wartosc);
        }

        for (unsigned int i=0; i<lewy.size(); i++) {
           for (unsigned int j=0; j<prawy.size(); j++) {
              if (lewy[i] + prawy[j] == dlugosc) {
                licznik++;
              }
           }
        }

        for (unsigned int i=0; i<lewy.size(); i++) {
           int pom = lewy[i] + wezel->wartosc;
           if (pom < dlugosc){
               wynik.push_back(pom);
           } else if (pom == dlugosc) {
             licznik++;
           }
        }

        if (!prawy.empty())
            for (unsigned int i=0; i<prawy.size(); i++) {
               int pom = prawy[i] + wezel->wartosc;
               if (pom < dlugosc){
                   wynik.push_back(pom);
               } else if (pom == dlugosc) {
                 licznik++;
               }
            }

        return wynik;
}

int main(){
    ios_base::sync_with_stdio(false);
    int liczba_testow,liczba_galezi,dlugosc_lampek;
    cin >> liczba_testow;

    for(int i=0; i<liczba_testow; i++){
        cin >> liczba_galezi >> dlugosc_lampek;
        licznik = 0;
        dlugosc = dlugosc_lampek;

        Wezel *root = new Wezel();
        root->wartosc = 0;
        root->lewy = NULL;
        root->prawy = NULL;

        vector<Wezel*> tablica;
        tablica.push_back(root);

        for(int j=1; j<(liczba_galezi+1); j++){
            Wezel *tmp = new Wezel();
            cin >> tmp->wartosc;
            tmp->lewy = NULL;
            tmp->prawy = NULL;
            tablica.push_back(tmp);

            if (j%2 == 1) {
                tablica[(j-1)/2]->lewy = tmp;
            } else {
                tablica[(j-1)/2]->prawy = tmp;
            }
        }

        przejdz(root);
        cout << licznik << endl;
        licznik = 0;

        tablica.clear();
        delete root;
        root = NULL;
    }
    return 0;
}