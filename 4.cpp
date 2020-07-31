#include <iostream>
#include <string>
using namespace std;

class StosString{ //stos na operatory
public:
    typedef string wartosc;
private:
    int counter = 0;
    struct Element{
        string val;
        Element *next;
    };
public:
    typedef Element *pozycja;
private:
    pozycja s;
public:
    StosString(){
        s = NULL;
    }

    ~StosString(){
        while(!pusty()){
            pop();
        }
    }

    bool pusty(){
        if(counter == 0){
            return true;
        } else return false;
    }

    string top(){
        if(!pusty())
            return s->val;
        else return "";
    }

    void push(string val){
        Element *pom =  new Element();
        pom->val = val;
        pom->next = s;
        s = pom;
        counter += 1;
    }

    void pop(){
        if(!pusty()){
            if(s->next != NULL){
                Element *pom = s;
                s = s->next;
                delete pom;
                pom = NULL;
            } else {
                delete s;
                s = NULL;
            }
            counter -= 1;
        }
    }
};

class StosDouble{ //stos do liczenia
public:
   typedef double wartosc;
private:
    int counter = 0;
    struct Element_dbl{
        wartosc val;
        Element_dbl *next;
    };
public:
    typedef Element_dbl *pozycja;
private:
    pozycja s;
public:
    StosDouble(){
        s = NULL;
    }

    ~StosDouble(){
        while(!pusty()){
            pop();
        }
    }

    bool pusty(){
        if(counter == 0){
            return true;
        } else return false;
    }

    double top(){
        if(!pusty())
            return s->val;
        else return 0;
    }

    void push(double val){
        Element_dbl *pom =  new Element_dbl();
        pom->val = val;
        pom->next = s;
        s = pom;
        counter += 1;
    }

    void pop(){
        if(!pusty()){
            if(s->next != NULL){
                Element_dbl *pom = s;
                s = s->next;
                delete pom;
                pom = NULL;
            } else {
                delete s;
                s = NULL;
            }
            counter -= 1;
        }
    }
};


class StosChar{ //stos na naiwasy
public:
    typedef char wartosc;
private:
    int counter = 0;
    struct Element_char{
        wartosc val;
        Element_char *next;
    };
public:
    typedef Element_char *pozycja;
private:
    pozycja s;
public:
    StosChar(){
        s = NULL;
    }

    ~StosChar(){
        while(!pusty()){
            pop();
        }
    }

    bool pusty(){
        if(counter == 0){
            return true;
        } else return false;
    }

    char top(){
        if(!pusty())
            return s->val;
        else return 0;
    }

    void push(char val){
        Element_char *pom =  new Element_char();
        pom->val = val;
        pom->next = s;
        s = pom;
        counter += 1;
    }

    void pop(){
        if(!pusty()){
            if(s->next != NULL){
                Element_char *pom = s;
                s = s->next;
                delete pom;
                pom = NULL;
            } else {
                delete s;
                s = NULL;
            }
            counter -= 1;
        }
    }
};

class Kolejka{ //kolejka na liczby
public:
    typedef string wartosc;
private:
    int counter = 0;
    struct element{
        wartosc val;
        element *poprzedni;
        element *nastepny;
    };
public:
    typedef element *pozycja;
private:
    pozycja pierwszy;
    pozycja ostatni;
public:
    Kolejka(){
        pierwszy = NULL;
        ostatni = NULL;
    }
    ~Kolejka(){
        while(!pusta()){
            usun();
        }
    }

    bool pusta(){
        if(counter == 0){
            return true;
        } else {
            return false;
        }
    }

    void dodaj(wartosc w){
        pozycja pom = new element();
        pom->val = w;

        if(pierwszy == NULL){
            pom->poprzedni = NULL;
            pom->nastepny = NULL;
            pierwszy = pom;
            ostatni = pierwszy;
        } else {
            pom->nastepny = NULL;
            pom->poprzedni = ostatni;
            ostatni->nastepny = pom;
            ostatni = pom;
        }

        counter += 1;
    }

    void usun(){
        if(!pusta()){
            if(pierwszy->nastepny == NULL){
                pierwszy = NULL;
                ostatni = NULL;
            } else {
                pierwszy->nastepny->poprzedni = NULL;
                pozycja pom = pierwszy;
                pierwszy = pierwszy->nastepny;
                delete pom;
                pom = NULL;
            }
            counter -= 1;
        }
    }

    string wartosc_pierwszego(){
        if(!pusta())
            return pierwszy->val;
        else return "";
    }

    void wyswietl(){
        if(!pusta()){
            pozycja pom = pierwszy;
            int licznik = counter;
            while(licznik != 0){
                cout << pom->val << " ";
                pom = pom->nastepny;
                licznik--;
            }
            cout << endl;
        }
    }
};

int priorytety(string znak){
    if(znak[0] == '*') return 2;
    else if(znak[0] == '/') return 2;
    else if(znak[0] == '-') return 1;
    else if(znak[0] == '+') return 1;
    else return 0;
}

bool czyLiczba(char znak){
    if((znak!='/') && (znak!='*') && (znak!='+') && (znak!='-') && (znak!='(') && (znak!=')') && (znak!='[') && (znak!=']') && (znak!='{') && (znak!='}')){
        return true;
    } else
        return false;
}

bool czyOperator(char znak){
    if((znak == '/') || (znak == '*') || (znak == '+') || (znak == '-')){
        return true;
    } else
        return false;
}

bool czyLiczbaString(string znak){
    if((znak != "+") && (znak != "-") && (znak != "/") && (znak != "*")){
        return true;
    } else return false;
}

bool czyNawias(char znak){
    if((znak == '(') || (znak == ')') || (znak == '[') || (znak == ']') || (znak == '{') || (znak == '}')){
        return true;
    } else return false;
}

bool czyLewyNawias(char znak){
    if((znak == '(') || (znak == '[') || (znak == '{')){
        return true;
    } else return false;
}

string charDoString(char znak){
    string y(1,znak);
    return y;
}



int main(){
  ios_base :: sync_with_stdio(false);
    int n;
    cin >> n;

    string wyrazenie;
    bool blad = false;
    double x,y,wynik;
    int liczNawiasy = 0;

    for(int i = 0; i < n; i++){
        StosChar *stosNawiasow = new StosChar();
        StosString *stos = new StosString();
        Kolejka *kolejka = new Kolejka();
        StosDouble *liczby = new StosDouble();

        cin >> wyrazenie;
        liczNawiasy = 0;

        for(unsigned int j = 0; j < wyrazenie.size(); j++){ //nieparzysta liczba nawiasow - blad
            if(czyNawias(wyrazenie[j])){
                liczNawiasy += 1;
            }
        }

        if(liczNawiasy%2 != 0){
            cout << "BLAD" << endl;
            blad = false;
        }

         else{
            blad = false;

            for(unsigned int j = 0; j < wyrazenie.size(); j++){
                if(czyLewyNawias(wyrazenie[j])){
                    stosNawiasow->push(wyrazenie[j]);
                    stos->push(charDoString(wyrazenie[j]));
                }

                else if(wyrazenie[j] == ')'){
                    if(stosNawiasow->top() != '('){
                        cout << "BLAD" << endl;
                        blad = true;

                        stosNawiasow->~StosChar();
                        delete stosNawiasow;
                        stosNawiasow = NULL;
                        break;

                    } else{
                        while(stos->top()!="("){
                            kolejka->dodaj(stos->top());
                            stos->pop();
                        }
                        stos->pop();
                        stosNawiasow->pop();
                    }
                }

                else if(wyrazenie[j] == ']'){
                   if(stosNawiasow->top() != '['){
                        cout << "BLAD" << endl;
                        blad = true;

                        stosNawiasow->~StosChar();
                        delete stosNawiasow;
                        stosNawiasow = NULL;
                        break;

                    } else{
                       while(stos->top()!="["){
                            kolejka->dodaj(stos->top());
                            stos->pop();
                        }
                        stos->pop();
                        stosNawiasow->pop();
                    }
                }

                else if(wyrazenie[j] == '}'){
                    if(stosNawiasow->top() != '{'){
                        cout << "BLAD" << endl;
                        blad = true;

                        stosNawiasow->~StosChar();
                        delete stosNawiasow;
                        stosNawiasow = NULL;
                        break;

                    } else{
                       while(stos->top()!="{"){
                            kolejka->dodaj(stos->top());
                            stos->pop();
                        }
                        stos->pop();
                        stosNawiasow->pop();
                    }
                }

                else if(czyLiczba(wyrazenie[j])){
                    string liczbaNapis(1,wyrazenie[j]);  //tworzenie stringa przechowujacego pojedynczy znak

                    while(((j+1)<wyrazenie.size()) && (czyLiczba(wyrazenie[j+1]))){ //petla dopisujaca do stringa pozostałe znaki (chcemy 12, nie 1 i 2)
                        liczbaNapis = liczbaNapis + wyrazenie[j+1];
                        j++;
                    }

                    kolejka->dodaj(liczbaNapis); // dodawanie do kolejki stringa przechowujacego liczbe, np 1 lub 12
                }

                else if(czyOperator(wyrazenie[j])){
                    if(!stos->pusty()){
                        while((priorytety(stos->top()) >= priorytety(charDoString(wyrazenie[j])))){ //po wczytaniu operatora sciagamy ze stosu wszystkie o prio mniejszym lub rownym od wczytanego
                            kolejka->dodaj(stos->top());
                            stos->pop();
                            if(stos->pusty()){
                                break;
                            }
                        }
                    }
                    stos->push(charDoString(wyrazenie[j])); //dodajemy wczytany operator na stos
                }
            }

            delete stosNawiasow;
            stosNawiasow = NULL;

            if(!blad){
                while(!stos->pusty()){ //przerzucanie pozostalosci ze stosu do kolejki
                    kolejka->dodaj(stos->top());
                    stos->pop();
                }
                delete stos;
                stos = NULL;

                while(!kolejka->pusta()){
                    if(czyLiczbaString(kolejka->wartosc_pierwszego())){
                        liczby->push(stod(kolejka->wartosc_pierwszego()));
                        kolejka->usun();
                    }

                    else if(!czyLiczbaString(kolejka->wartosc_pierwszego())){
                        x = liczby->top();
                        liczby->pop();

                        y = liczby->top();
                        liczby->pop();

                        if(kolejka->wartosc_pierwszego() == "+"){
                            wynik = y + x;
                            liczby->push(wynik);
                        }

                        else if(kolejka->wartosc_pierwszego() == "-"){
                            wynik = y - x;
                            liczby->push(wynik);
                        }

                        else if(kolejka->wartosc_pierwszego() == "*"){
                            wynik = y * x;
                            liczby->push(wynik);
                        }

                        else if(kolejka->wartosc_pierwszego() == "/"){
                            wynik = y / x;
                            liczby->push(wynik);
                        }

                        kolejka->usun();
                    }
                }
                cout << liczby->top() << endl;
                delete kolejka;
                kolejka = NULL;

                liczby->~StosDouble();
                delete liczby;
                liczby = NULL;
             }
         }
    }
    return 0;
}