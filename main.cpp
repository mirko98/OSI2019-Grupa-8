#include "eCity.h"

int main()
{
    vector <EVENT> niz;
    input_all(niz);

    cout<<"DOBRODOSLI U eCity"<<endl<<endl;

    BEGIN:
    cout<<"Prijava [1]"<<endl;
    cout<<"Guest   [2]"<<endl<<endl;

    string choise;
    bool flag = false;
    do{
        cout<<"Unesite redni broj: ";
        getline(cin, choise, '\n');

        if ( choise != "1" && choise != "2" ){
            print_text("\nREDNI BROJ");
        }
    }while ( choise != "1" && choise != "2" );

    if ( choise == "1" ){
        do{
            cout<<"\nPrijava: "<<endl<<endl;
            flag = admin_acess();

            if ( !flag ){
                cout<<"\n\nPRIJAVA NIJE USPJESNA.\nPOKUSAJTE PONOVO!!!\n\n";

                cout<<"Da li zelite se vratiti nazad: "<<endl;
                cout<<"     - Da [1]"<<endl;
                cout<<"     - Ne [2]"<<endl<<endl;
                string ch;
                do{
                    cout<<"Unesite redni broj: ";
                    getline(cin, ch, '\n');

                    if ( ch != "1" && ch != "2" ){
                        print_text("\nREDNI BROJ");
                    }
                }while ( ch != "1" && ch != "2" );

                if ( ch == "1" ){
                    cout<<endl;
                    goto BEGIN;
                }
            }
        }while ( !flag );
    }

    choise = "-1";
    do{
        if ( flag ) cout<<endl;

        cout<<"\n------------------ MENI -----------------"<<endl;

        cout<<"\nPregled danasnjih dogadjaja            [1]"<<endl;
        cout<<"Pregled dogadjaja odredjene kategorije [2]"<<endl;
        cout<<"Pregled svih buducih dogadjaja         [3]"<<endl;
        cout<<"Pregled dogadjaja koji su prosli       [4]"<<endl;
        cout<<"Komentarisanje dogadjaja               [5]"<<endl;
        cout<<"Igranje kviza                          [6]"<<endl;
        cout<<"HELP                                   [7]"<<endl;
        cout<<"Sortiranje dogadjaja                   [8]"<<endl;

        if ( flag ){
            cout<<"Dodavanje dogadjaja                    [9]"<<endl;
            cout<<"Brisanje dogadjaja                     [10]"<<endl;
            cout<<"Modifikacija dogadjaja                 [11]"<<endl;
            cout<<"Dodavanje kategorija                   [12]"<<endl;
            cout<<"Brisanje kategorija                    [13]"<<endl;
        }

        if ( flag ) cout<<"exit                                   [14]"<<endl;
        else cout<<"exit                                   [9]"<<endl;

        cout<<"\n-----------------------------------------"<<endl;

        cout<<endl<<"Unesite redni broj: ";
        getline(cin, choise, '\n');

        int buff = convert_string(choise);
        int flag_meni = true;
        if ( flag ){
            if ( buff < 1 || buff > 14 ){
                flag_meni = false;
                print_text("\nREDNI BROJ");
            }else if ( buff == 14 ){
                cout<<endl<<"DOVIDJENJA!!!"<<endl;
                return 0;
            }
        }else{
            if ( buff < 1 || buff > 9 ){
                flag_meni = false;
                print_text("\nREDNI BROJ");
            }else if ( buff == 9 ){
                cout<<endl<<"DOVIDJENJA!!!"<<endl;
                return 0;
            }
        }

        if ( flag_meni ){
            if ( buff == 1 ) print_event_today(niz);
            else if ( buff == 2 ) {
                FILE *fp = fopen("type_category.dat", "rb");

                char buff1[100];
                int br = 1;
                cout<<"Kategorije: "<<endl;
                while ( fread(buff1, sizeof(buff1), 1, fp) ){
                    cout<<"     - "<<buff1<<" ["<<br++<<"]"<<endl;
                }

                string category;
                do{
                    cout<<"Unesite redni broj: ";
                    getline(cin, category, '\n');

                    buff = convert_string(category);

                    if ( buff < 1 || buff >= br ){
                        print_text("\nREDNI BROJ");
                    }
                }while ( buff < 1 || buff >= br );

                fclose(fp);

                category = buff1;
                print_event_category(niz, category);
            }
            else if ( buff == 3 ) print_event_future(niz);
            else if ( buff == 4 ) print_event_past(niz);
            else if ( buff == 5 ) input_comment(niz);
            else if ( buff == 6 ) quiz();
            else if ( buff == 7 ) help();
            else if ( buff == 8 ) sort_event(niz);
            else if ( buff == 9 ){
                if ( flag ){
                    niz.erase(niz.begin(), niz.end());
                    add_event(1);
                    input_all(niz);
                }else{
                    return 0;
                }
            }else if ( buff == 10 ) delete_event(niz);
            else if ( buff == 11 ) mod_event(niz);
            else if ( buff == 12 ) add_type();
            else if ( buff == 13 ) delete_type();
            else if ( buff == 14 ) return 0;
        }

    }while ( 1 );
    return 0;
}
