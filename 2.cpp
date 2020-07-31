#include <iostream>
using namespace std;

struct Uczen{
    string k;
    unsigned int d;
    float s;
    short m;
};

int porownajS(Uczen nowy, Uczen stary){
    if(nowy.s > stary.s){
        return 1;
    } else if(nowy.s == stary.s){
        return 0;
    } else {
        return -1;
    }
}
int porownajD(Uczen nowy, Uczen stary){
    if(nowy.d > stary.d){
        return 1;
    } else if(nowy.d == stary.d){
        return 0;
    } else {
        return -1;
    }
}
int porownajM(Uczen nowy, Uczen stary){
    if(nowy.m > stary.m){
        return 1;
    } else if(nowy.m == stary.m){
        return 0;
    } else {
        return -1;
    }
}

int porownaj(Uczen nowy, Uczen stary, char *kryteria, int index){
    int pom;

    if(kryteria[index] == 's'){
        pom = porownajS(nowy,stary);
    } else if(kryteria[index] == 'd'){
        pom = porownajD(nowy,stary);
    } else if(kryteria[index] == 'm'){
        pom = porownajM(nowy,stary);
    }

    if(pom > 0){
        return true;
    } else if(pom < 0){
        return false;
    }else if(pom == 0) {
        index++;
        if(index == 3){
            return false;
        }
        return porownaj(nowy,stary,kryteria,index);
    }
}

void sortuj(Uczen *tabX, Uczen *tabY, char kryteria[], int i){
    if(porownaj(tabX[i],tabX[i-1],kryteria,0)){
        int j;
        Uczen pom = tabX[i];
        for(j=i-1; (j>=0) && porownaj(pom,tabX[j],kryteria,0);j--){
            tabX[j+1] = tabX[j];
        }
        tabX[j+1] = pom;
    }
    if(porownaj(tabY[i],tabY[i-1],kryteria,0)){
        int j;
        Uczen pom = tabY[i];
        for(j=i-1; (j>=0) && porownaj(pom,tabY[j],kryteria,0);j--){
            tabY[j+1] = tabY[j];
        }
        tabY[j+1] = pom;
    }
}


int main(){
    ios_base :: sync_with_stdio(false);
   int n;
   cin >> n;

   string k;
   float s;
   unsigned int d;
   short m;

   Uczen *tabX = new Uczen[n];
   Uczen *tabY = new Uczen[n];

   char kryteria[3];
    for(int i=0;i<3;i++)
        cin >> kryteria[i];

    cin >> k;
    cin >> s;
    cin >> d;
    cin >> m;
    tabX[0].k = k;
    tabX[0].s = s;
    tabX[0].d = d;
    tabX[0].m = m;

    cin >> k;
    cin >> s;
    cin >> d;
    cin >> m;
    tabY[0].k = k;
    tabY[0].s = s;
    tabY[0].d = d;
    tabY[0].m = m;

   for(int i=1; i<n; i++){
        cin >> k;
        cin >> s;
        cin >> d;
        cin >> m;
        tabX[i].k = k;
        tabX[i].s = s;
        tabX[i].d = d;
        tabX[i].m = m;

        cin >> k;
        cin >> s;
        cin >> d;
        cin >> m;
        tabY[i].k = k;
        tabY[i].s = s;
        tabY[i].d = d;
        tabY[i].m = m;
        sortuj(tabX,tabY,kryteria,i);
   }

   for(int i=0; i<n; i++){
        cout << tabX[i].k << " " << tabY[i].k << " ";
   }

   delete[] tabX;
   delete[] tabY;
   return 0;
}