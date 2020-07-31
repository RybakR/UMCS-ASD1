using namespace std;

class Samochod{
public:
    string marka;
    long long int obroty;
    Samochod(string marka,double przebieg, int srednica){
        this->marka = marka;
        obroty = (przebieg * 100000.00) / (srednica * 3.141593 * 2.54);
    }
};

bool sprawdz(Samochod *a, Samochod *b){
    if(b == NULL){
        return true;
    }
    else if(a->obroty < b->obroty){
        return true;
    }
    else if(a->obroty == b->obroty){
        if(a->marka.compare(b->marka) < 0){
            return true;
        } else return false;
    }
    else return false;
}

int main(){
    ios_base :: sync_with_stdio(false);

    int ile;
    cin >> ile;

    Samochod *trzy[3];
    trzy[0]=NULL;
    trzy[1]=NULL;
    trzy[2]=NULL;

    for(int i = 0; i < ile; i++){

        string marka;
        string bezsens;

        getline(cin, bezsens); //cin.ignore();
        getline(cin, marka);

        double przebieg;
        cin >> przebieg;
        int srednica;
        cin >> srednica;

        Samochod *pom;
        pom = new Samochod(marka, przebieg, srednica);

       if(sprawdz(pom,trzy[0])){
            delete trzy[2];
            trzy[2] = trzy[1];
            trzy[1] = trzy[0];
            trzy[0] = pom;
        } else if(sprawdz(pom,trzy[1])){
            delete trzy[2];
            trzy[2] = trzy[1];
            trzy[1] = pom;
        } else if(sprawdz(pom,trzy[2])){
            delete trzy[2];
            trzy[2] = pom;
        } else {
            delete pom;
        }
    }

    for(int i=0; i<3; i++){
        cout << trzy[i]->marka << endl;
        cout << trzy[i]->obroty << endl;
    }
    return 0;
}