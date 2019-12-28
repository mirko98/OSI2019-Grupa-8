#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ios;
using std::max;

struct QUESTION{
    string question;
    string ans[3];
    int result;
    int user_ans;
};

void quiz(){
    /*============= 1 =============*/

    ifstream input("QUIZ.dat", ios::in | ios::binary);

    QUESTION niz[10];

    struct question_buff{
        char question[1000];
        char ans[3][1000];
        int result;
        int user_ans;
    };

    question_buff buff;
    int br = 0;

    while ( input.read((char*)&buff, sizeof(question_buff)) ){
        niz[br].question = buff.question;

        for (int i=0;i<3;i++){
            niz[br].ans[i] = buff.ans[i];
        }

        niz[br].result = buff.result;
        niz[br].user_ans = 0;
        br++;
    }

    /*============= 2 =============*/

    for (int i=0;i<10;i++){
        int maks = max(niz[i].ans[0].size(), max(niz[i].ans[1].size(), niz[i].ans[2].size()));

        for (int j=0;j<3;j++){
            int p = niz[i].ans[j].size();
            if ( maks != p ){
                for (int k=0;k<maks-p;k++){
                    niz[i].ans[j]+=" ";
                }
            }
        }
    }

    /*============= 3 =============*/

    cout<<"IGRANJE KVIZA: "<<"\n\n";

    br = 0;

    for (int i=0;i<10;i++){
        cout<<"Pitanje "<<i+1<<": "<<niz[i].question<<"\n";
        cout<<niz[i].ans[0]<<" [1]"<<"\n";
        cout<<niz[i].ans[1]<<" [2]"<<"\n";
        cout<<niz[i].ans[2]<<" [3]"<<"\n\n";

        string choise;

        do{
            cout<<"Unesite odgovor: ";
            getline(cin, choise, '\n');
            if ( choise == "EXIT" ){
                return;
            }

            if ( choise.length()  == 1 && ( choise[0] == '1' || choise[0] == '2' || choise[0] == '3' ) ){
                niz[i].user_ans = (int)(choise[0] - '0');
            }else{
                cout<<"\nNISTE UNIJELI JEDAN OD PONUDJENIH ODGOVORA!!!\nPOKUSAJTE PONOVO!!!\n\n";
            }
        }while ( choise.length() != 1 || ( choise[0] != '1' && choise[0] != '2' && choise[0] != '3' ) );

        if ( niz[i].result != (int)(choise[0] - '0') ){
            br++;
        }

        cout<<"\n";
    }

    /*============= 4 =============*/

    cout<<"Broj tacnih odgovora je: "<<10 - br<<"\n\n";

    if ( br != 0 ){
        cout<<"Odgovori na kojima ste pogrijesili: "<<"\n\n";

        for (int i=0;i<10;i++){
            if ( niz[i].result != niz[i].user_ans ){
                cout<<"Pitanje "<<i+1<<": "<<niz[i].question<<"\n";

                cout<<"Vas odgovor  : "<<niz[i].ans[niz[i].user_ans-1]<<"\n";

                cout<<"Tacan odgovor: "<<niz[i].ans[niz[i].result-1]<<"\n\n";
            }
        }
    }
}

/*
    1: 
        - Unosimo podatke iz binarne datoteke
        - buff je samo privremena promjenljiva sa odgovarajucom strukturom
        - niz je promjenljiva gdje cuvamo sve ucitane podatke
    
    2:
        - Posto odgovori mogu da budu razlicite duzine onda znak ':' koji koristimo bi bio na razlicitim pozicijama 
        - zato koristimo predstojeci kod u blokun 2 da bi sve to izjednacili
    
    3:
        - Igranje kviza
    
    4: 
        - Prikazivanje rezultata
*/
