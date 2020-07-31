#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class Pole{
public:
    int wartosc;
    vector <int> sasiad;

    int rodzicCzerwony = -1;
    int rodzicZielony = -1;
    
    bool sprawdz(bool s) {
        if (s) {
            return rodzicZielony == -1;
        } else {
            return rodzicCzerwony == -1;
        }
    }

    void dodajSciezke(int rodzic, bool skoczek) {
        if (skoczek) {
            rodzicZielony = rodzic;
        } else {
            rodzicCzerwony = rodzic;
        }
    }
};

void wyswietl_sciezke(Pole wierzcholki[] , int pom ) {
        stack<int> *stos = new stack<int>;
        bool skoczek = true;

        while(pom >= 0)  {
            stos->push(pom);
            if (skoczek) {
                pom = wierzcholki[pom].rodzicCzerwony;
            } else {
                pom = wierzcholki[pom].rodzicZielony;
            }
            skoczek = !skoczek;
        }
        
        while(!stos->empty()) {
            cout << stos->top() << " ";
            stos->pop();
        }
        
        delete stos;
        stos = NULL;
    }

bool cyklicznosc(Pole wierzcholki[], char *odwiedzeni, int v){
    odwiedzeni[v] = 'c';
    
    for(unsigned int i =0; i<wierzcholki[v].sasiad.size(); i++){
        int pom = wierzcholki[v].sasiad[i];

        if(odwiedzeni[pom] == 'c')
            return true;
        if((odwiedzeni[pom] == 'z') && (cyklicznosc(wierzcholki,odwiedzeni,pom)))
            return true;
    }

    odwiedzeni[v] = 'n';
    return false;
}

void czyCykl(Pole wierzcholki[], int n){
    char *odwiedzony = new char[n]; //zielony - nieodwiedzony, czerwony -  przetwarzany, niebieski - przetworzony
    
    for(int i=0; i<n; i++){
        odwiedzony[i] = 'z';
    }
    
    for(int i=0; i<n; i++){
        if((odwiedzony[i] = 'z') && (cyklicznosc(wierzcholki,odwiedzony,i))){
            delete [] odwiedzony;
            odwiedzony = NULL;
            cout << "REMIS" << endl;
            return;
        }
    }

    delete [] odwiedzony;
    odwiedzony = NULL;
    cout << "NIE" << endl;
    return;
}


void bfs(int v, Pole wierzcholki[], int n){
    int nastepnik, pom;

    queue<pair<int,bool> >kolejka;

    kolejka.push(make_pair(v, true));
    wierzcholki[v].rodzicCzerwony = -2;

    while(!kolejka.empty()){

        pair<int, bool> pom_kolejka = kolejka.front();
        pom = pom_kolejka.first;
        bool skoczek = pom_kolejka.second;

        kolejka.pop();

        if(wierzcholki[pom].sasiad.empty() && skoczek){
            cout << "TAK" << endl;
            wyswietl_sciezke(wierzcholki, pom);
            cout << endl;
            return;
        }

        for(unsigned int i = 0; i < wierzcholki[pom].sasiad.size(); i++){
            nastepnik = wierzcholki[pom].sasiad[i];

            if(wierzcholki[nastepnik].sprawdz(skoczek)){
                wierzcholki[nastepnik].dodajSciezke(pom, skoczek);
                kolejka.push(make_pair(nastepnik, !skoczek));
            }
        }
    }
    czyCykl(wierzcholki,n);
}

int main(){
    ios_base::sync_with_stdio(false);
    int t,m,n,s,x,y;
    cin >> t;

    for(int i = 0; i < t; i++){
        cin >> n >> m >> s;
        Pole *tablica = new Pole[n];

        for(int j = 0; j < m; j++){
            cin >> x >> y;
            tablica[x].wartosc = x;
            tablica[y].wartosc = y;
            tablica[x].sasiad.push_back(tablica[y].wartosc);
        }

        for(int j = 0; j<n; j++){
            sort(tablica[j].sasiad.begin(),tablica[j].sasiad.end());
        }

        if(tablica[s].sasiad.empty()){
            cout << "TAK" << endl;
            cout << s << " ";
        } else {
           bfs(s,tablica,n);
        }

        delete [] tablica;
        tablica = NULL;
    }
    return 0;
}