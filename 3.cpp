#include <iostream>
using namespace std;

struct Para{ //stempel, ma numer seryjny (znak) oraz liczbe kontrolną (liczba)
    string znak;
    int liczba;
};

class ListaPara{ //lista ze steplem
public:
    typedef Para wartosc;
    int licznikPara = 0;
private:
    struct element{
        wartosc val;
        element *nastepny;
    };
public:
    typedef element *pozycja;
private:
    pozycja biezacy;
public:
    ListaPara(){
       biezacy = NULL;
    }

    bool pusta(){ //empty()
        if(biezacy == NULL){
            return true;
        } else
            return false;
    }

    void dodaj(wartosc w){ //push_back()
        pozycja pom = new element();
        pom->val = w;

        if(biezacy == NULL){
            pom->nastepny = pom;
        } else{
            pom->nastepny = biezacy->nastepny;
            biezacy->nastepny = pom;
        }
        biezacy = pom;

        pom = NULL;
        delete pom;

        licznikPara += 1;
    }

    void usun(){ //pop_front
        licznikPara -= 1;
        if(licznikPara == 0){
            biezacy = NULL;
            delete biezacy;
        } else if(licznikPara == 1){
            biezacy->nastepny = biezacy;
        } else if(licznikPara > 1) {
            pozycja pom = biezacy->nastepny;
            biezacy->nastepny = pom->nastepny;

            pom = NULL;
            delete pom;
        }
    }

    void obroc(int x){ //obracanie listy o okreslona wartosc
        if(!pusta()){
            if(x > 0){ //obracanie w przod
                int oile = x%licznikPara; //po obrotach rowynch liczbie elementow sekwencja sie powtarza
                while(oile != 0){
                    biezacy = biezacy->nastepny;
                    oile--;
                }
            }
            else if(x < 0){ //obracanie w tyl
                int oile = x%licznikPara;
                int stop = licznikPara + oile; //oboty w tył to lustrzane odbicie obrotow w tyl w okreslonym punkcjie
                while(stop != 0){
                    biezacy = biezacy->nastepny; //obracanie w przod powiekszone o okreslona wartosc
                    stop--;
                }
            }
        }
    }

     string zwroc1znak(){ //zwraca znak pierwszego el.
        if(!pusta()){
            return biezacy->nastepny->val.znak;
        } //else return "";
    }

     int zwroc1liczbe(){ //zwraca liczbe pierwszego el.
        if(!pusta()){
            return biezacy->nastepny->val.liczba;
        } //else return 0;
    }

    void wyswietl(){ // pomocnicze wyswietlanie od pierwszego do ostatniego elementu
        if(!pusta()){
            pozycja pom = biezacy->nastepny;
            int counter = licznikPara;
            while(counter != 0){
                cout << pom->val.znak;
                pom = pom->nastepny;
                counter--;
            }
        cout << endl;
        pom = NULL;
        delete pom;
        }
    }
};

class ListaList{ //lista przechowujca listy ze steplami
public:
    typedef ListaPara wartosc;
    int licznikList = 0;
    int liczbaPrzedObrotem = 0;
    int liczbaPoObrocie = 0;
private:
    struct element{
        wartosc val;
        element *nastepny;
    };
public:
    typedef element *pozycja;
private:
    pozycja biezacy;
    pozycja manipulator; //przechowuje która lista byla obracana - od niego rozpoczyna sie wybieranie kolejnej listy
public:
    ListaList(){
       biezacy = NULL;
       manipulator = NULL;
    }

    bool pusta(){ //empty
        if(biezacy == NULL){
            return true;
        } else
            return false;
    }

    void dodaj(wartosc *w){ //push_bacl
        pozycja pom = new element();
        pom->val = *w;

        if(biezacy == NULL){
            pom->nastepny = pom;
        } else{
            pom->nastepny = biezacy->nastepny;
            biezacy->nastepny = pom;
        }
        biezacy = pom;

        pom = NULL;
        delete pom;

        licznikList += 1;
    }

    void usunWybrany(pozycja tmp){
        if(!pusta()){
            licznikList -=1;
            pozycja pom = biezacy->nastepny;
            while(pom->nastepny != tmp){
                pom = pom->nastepny;
            }
            pom->nastepny = tmp->nastepny;

            tmp = NULL;
            delete tmp;
        }
    }

    void usun1Elementy(){
        if(!pusta()){
            if(licznikList == 1){
                biezacy->val.usun();
            }
            else if(licznikList > 1){
                pozycja pom = biezacy->nastepny;
                int licznik = licznikList;

                while(licznik != 0){
                    if(!pom->val.pusta()){
                        pom->val.usun();
                    }
                    if(pom->val.licznikPara == 0){ // z tym zla w 3, bez zla w 2,5,6
                        usunWybrany(pom);
                        }
                    pom = pom->nastepny;
                    licznik--;
                }

                pom = NULL;
                delete pom;
            }
        }
    }

    void multipop(){
        if(!pusta()){
            pozycja pom = biezacy->nastepny;
            int licznik = licznikList;

            while(licznik != 0){
                if(!pom->val.pusta()){
                    pom->val.usun();
                }
                pom = pom->nastepny;
                licznik--;
                }

            pom = NULL;
            delete pom;
        }
     }

   void obroc(int ileManipulator, int ileLista){
        if(!pusta()){
            pozycja pom;
            if(manipulator == NULL){
                pom = biezacy->nastepny;
            } else {
                  if(!manipulator->val.pusta()){
                    pom = manipulator;
                } else
                    pom = biezacy->nastepny;
            }

            if(ileManipulator > 0){
                int obrotyP = ileManipulator%licznikList;
                while(obrotyP != 0){
                    pom = pom->nastepny;
                    obrotyP--;
                }
            } else if(ileManipulator < 0){
                int obrotyM = ileManipulator%licznikList;
                int stop = obrotyM + licznikList;
                while(stop != 0){
                    pom = pom->nastepny;
                    stop--;
                }
            }

            liczbaPrzedObrotem = pom->val.zwroc1liczbe();
            pom->val.obroc(ileLista);
            manipulator = pom;
            liczbaPoObrocie = manipulator->val.zwroc1liczbe();

            pom = NULL;
            delete pom;
        }
    }

   void wyswietl1Znaki(){
        if(!pusta()){
            if(licznikList == 1){
                cout << biezacy->nastepny->val.zwroc1znak();

            } else if(licznikList > 1){
                pozycja pom = biezacy->nastepny;
                int licznk = licznikList;

                while(licznk != 0){
                    if(!pom->val.pusta()){
                        cout << pom->val.zwroc1znak();
                    }
                    pom = pom->nastepny;
                    licznk--;
                }

                pom = NULL;
                delete pom;
            }
        }
    }

    int zroc1Sume(){
        if(!pusta()){
            if(licznikList == 1){
                int suma = 0;
                suma = biezacy->nastepny->val.zwroc1liczbe();
                return suma;

            } else if(licznikList > 1){
                pozycja pom = biezacy->nastepny;
                int licznk = licznikList;
                int suma = 0;

                while(licznk != 0){
                    if(!pom->val.pusta()){
                        suma = suma + pom->val.zwroc1liczbe();
                    }
                    pom = pom->nastepny;
                    licznk--;
                }

                pom = NULL;
                delete pom;
                return suma;
            }
        }
    }

    int zwrocLiczbePrzedObr(){
        return liczbaPrzedObrotem;
    }

    int zwrocLiczbePoObr(){
        return liczbaPoObrocie;
    }

    void wyswietl(){
        if(!pusta()){
            pozycja pom = biezacy->nastepny;
            int counter = licznikList;
            while(counter != 0){
                pom->val.wyswietl();
                pom = pom->nastepny;
                counter--;
            }
        cout << endl;
        pom = NULL;
        delete pom;
        }
    }
};

class ListaSum{ //lista przechowujaca sumy
public:
    typedef int wartosc;
    int licznikSum = 0;
private:
    struct element{
        wartosc val;
        element *nastepny;
    };
public:
    typedef element *pozycja;
private:
    pozycja biezacy;
public:
    ListaSum(){
       biezacy = NULL;
    }

    bool pusta(){ //empty()
        if(biezacy == NULL){
            return true;
        } else
            return false;
    }

    void dodaj(wartosc w){ //push_back()
        pozycja pom = new element();
        pom->val = w;

        if(biezacy == NULL){
            pom->nastepny = pom;
        } else{
            pom->nastepny = biezacy->nastepny;
            biezacy->nastepny = pom;
        }
        biezacy = pom;

        pom = NULL;
        delete pom;

        licznikSum += 1;
    }

    void usun(){ //pop_front
        licznikSum -= 1;
        if(licznikSum == 0){
            biezacy = NULL;
            delete biezacy;
        } else if(licznikSum == 1){
            biezacy->nastepny = biezacy;
        } else {
            pozycja pom;
            pom = biezacy->nastepny;
            biezacy->nastepny = pom->nastepny;

            pom = NULL;
            delete pom;
        }
    }


    bool sprawdz(int suma){ //sprawdzene zgodnosci podanej sumy z sumami przechowywanimi w liscie
        if(!pusta()){
            int counter = licznikSum;
            while(counter != 0){
                if(biezacy->nastepny->val == suma){
                    return true;
                }
                biezacy = biezacy->nastepny;
                counter--;
            }
            return false;
        } else{
            return false;
        }
    }

    int zwrocWartosc(){ //zwrocenie pierwszej sumy z listy
        if(!pusta()){
            return biezacy->nastepny->val;
        } //else return 0;
    }

    void wyswietl(){ // pomocnicze wyswietlanie od pierwszego do ostatniego elementu
        if(!pusta()){
            pozycja pom = biezacy->nastepny;
            int counter = licznikSum;
            while(counter != 0){
                cout << pom->val;
                pom = pom->nastepny;
                counter--;
            }
        cout << endl;
        pom = NULL;
        delete pom;
        }
    }
};

int main(){
    ios_base :: sync_with_stdio(false);
    int n;   // ilosc list ze stemplami
    int m;   // liczba stempli na dysku
    int l;   // liczba num kontrolnych samochodów
    int h;   // liczba sekwencji

    cin >> n;
    if(n==0){
        return 0;
    }

    ListaList *listaMatrona = new ListaList();  //lista list przechowujaca poszczegolne listy z parami

    for(int i=0; i<n; i++){
        cin >> m;
        if(m==0){
            return 0;
        }

        ListaPara *listaSyn = new ListaPara();

        for(int j=0; j<m; j++){
            Para dysk;
            cin >> dysk.znak;
            cin >> dysk.liczba;
            listaSyn->dodaj(dysk);
        }

        listaMatrona->dodaj(listaSyn);
    }

    cin >> l;
    if(l==0){
        return 0;
    }

    ListaSum *sumy = new ListaSum();
    int sum;

    for(int i=0; i<l; i++){
        cin >> sum;
        sumy->dodaj(sum);
    }

    cin >>h;
    int tabPrzesun[h];   // tablica przesuniec manipulatora (okresla ktora liste z listyList wybrac do obracania
    int tabObrot[h]; // tab przesuneiec dysku, okresla o ile stempli obrócić dysk (o jaką wartosc obrocic liste z listyLis

    for(int i=0; i<h; i++){
        cin >> tabPrzesun[i];
        cin >> tabObrot[i];
    }

    int suma = 0;
    if(!listaMatrona->pusta()){
        suma = listaMatrona->zroc1Sume();
    }

    while(sumy->sprawdz(suma) == true){
                cout << sumy->zwrocWartosc() << " ";
                listaMatrona->wyswietl1Znaki();
                sumy->usun();
                cout << endl;
                listaMatrona->multipop();
                if(listaMatrona->licznikList == 0){
                    return 0;
                }
                suma = listaMatrona->zroc1Sume();
                if(sumy->pusta()){
                    return 0;
                }
            }

    for(int i=0; i<h; i++){
            while(sumy->sprawdz(suma) == true){
                cout << sumy->zwrocWartosc() << " ";
                listaMatrona->wyswietl1Znaki();
                sumy->usun();
                cout << endl;
                listaMatrona->usun1Elementy();
                if(listaMatrona->licznikList == 0){
                    return 0;
                }
                suma = listaMatrona->zroc1Sume();
                if(sumy->pusta()){
                    return 0;
                }
            }

            listaMatrona->obroc(tabPrzesun[i], tabObrot[i]);
            suma = suma - listaMatrona->zwrocLiczbePrzedObr() + listaMatrona->zwrocLiczbePoObr();
    }

    if(sumy->sprawdz(suma)){
            cout << sumy->zwrocWartosc() << " ";
            sumy->usun();
            listaMatrona->wyswietl1Znaki();
            listaMatrona->usun1Elementy();
            sum = listaMatrona->zroc1Sume();
    }

    return 0;
}