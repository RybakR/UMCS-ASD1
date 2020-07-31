#include <iostream>
#include <vector>

using namespace std;

class Drzewo{
public:
    Drzewo *ojciec;
    vector <Drzewo *> dzieci;
    int numerDrogi;
    bool kamera = false;
    int odleglosc = 0;
};

void preorder(Drzewo *root, int m){
    unsigned int rozmiar = root->dzieci.size();

    if(root->kamera == true){
        bool tylkoroot;
    }

    else if(root->ojciec->kamera == false){
        if(rozmiar+1 >= m){
            root->kamera = true;
            root->odleglosc = 0;

        } else {
            root->odleglosc = root->ojciec->odleglosc+1;

            if(root->odleglosc == 3){
                root->kamera = true;
                root->odleglosc = 0;
            }
        }
    }

    for(unsigned int i=0; i<rozmiar; i++){
        preorder(root->dzieci[i],m);
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    int n;
    int m;
    int a;
    int b;

    cin >> n;
    cin >> m;

    Drzewo** tablica = new Drzewo*[n];

    tablica[0] = new Drzewo();
    tablica[0]->numerDrogi = 1;
    tablica[0]->kamera = true;

    for(int i = 1; i < n; i++){
        tablica[i] = new Drzewo();
        tablica[i]->numerDrogi = i+1;
    }

    for(int i = 0; i< (n-1); i++){
        cin >> a;
        cin >> b;

        tablica[a-1]->dzieci.push_back(tablica[b-1]);
        tablica[b-1]->ojciec = tablica[a-1];
    }

    preorder(tablica[0],m);

    for(int i = 0; i < n; i++){
        if(tablica[i]->kamera == true){
            cout << tablica[i]->numerDrogi << " ";
        }
    }
    return 0;
}