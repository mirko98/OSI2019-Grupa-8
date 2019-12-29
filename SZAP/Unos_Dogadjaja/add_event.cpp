int mm_dd[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct EVENT{
    char name[100];
    char description[1000];
    char type[100];
    char location[100];
    char comment[100][1000];
    int dd;
    int mm;
    int yy;
    int mi;
    int hh;

    time_t tt;
    tm TM;

    /*------ INICIJALIZUJEMO TM ------*/
    EVENT(){
        time(&tt);
        TM = *localtime(&tt);
    }

    /*------ VRACA DANASNJU GODINU ------*/
    int current_year(){
        return (int)TM.tm_year + 1900;
    }

    /*------ VRACA DANASNJI MJESEC ------*/
    int current_month(){
        return (int)TM.tm_mon + 1;
    }

    /*------ VRACA DANASNJI DAN ------*/
    int current_day(){
        return (int)TM.tm_mday;
    }

    /*------ PROVJERA DANA ------*/
    bool flag_day(){
        if ( dd <= 0 ){
            return false;
        }

        if ( mm == 2 ){
            if ( ( yy % 400 == 0 ) || ( yy % 100 != 0 && yy % 4 == 0 ) ){
                if ( dd <= 29 ){
                    return true;
                }else{
                    return false;
                }
            }else{
                if ( dd <= 28 ){
                    return true;
                }else{
                    return false;
                }
            }
        }else{
            if ( dd <= mm_dd[mm-1] ){
                return true;
            }else{
                return false;
            }
        }
    }

    /*------ PROVJERA MJESECA ------*/
    bool flag_month(){
        if ( mm <= 12 && mm >= 1 ){
            return true;
        }

        return false;
    }

    /*------ PROVJERA GODINE ------*/
    bool flag_year(){
        if ( abs(yy-current_year()) <= 5 ){
            return true;
        }

        return false;
    }

    /*------ PROVJERA DATUMA(da li je datum buduci) ------*/
    bool flag_date(){
        int day = current_day();
        int month = current_month();
        int year = current_year();

        if ( year == yy ){
            if ( month == mm ){
                if ( day >= dd ){
                    return false;
                }else{
                    return true;
                }
            }else if ( month < mm ){
                return true;
            }else{
                return false;
            }
        }else if ( year > yy ){
            return false;
        }else{
            return true;
        }
    }

    /*------ PROVJERA MINUTA ------*/
    bool flag_mi(){
        if ( mi >= 0 && mi <= 59 ){
            return true;
        }

        return false;
    }

    /*------ PROVJERA CASOVA ------*/
    bool flag_hh(){
        if ( hh >= 0 && hh <= 23 ){
            return true;
        }

        return false;
    }
};

/*------------- KONVERZIJA STRING-A U INT ---------------*/

int convert_string(string &a){
    int value = 0;
    int inc = 1;
    for (int i=a.length()-1;i>=0;i--){
        if ( !isdigit(a[i]) ){
            return -1;
        }

        value+=inc*(int)(a[i] - '0');
        inc*=10;
    }

    return value;
}

/*------ ISPISUJE PORUKU ZA GRESKU(zavisno gdje je greska napravita) ------*/

void print_text(string a){
    if ( a.find("VRSTA") != string::npos || a.find("GODINA") != string::npos || a.find("LOKACIJA") != string::npos ){
        a+=" KOJU STE UNIJELI NIJE VALIDNA.\nPOKUSAJTE PONOVO!!!\n\n";
    }else{
        a+=" KOJI STE UNIJELI NIJE VALIDAN.\nPOKUSAJTE PONOVO!!!\n\n";
    }

    cout<<a;
}

void add_event(){
    /*------------ DEF. PROMJELJIVIH ------------*/
    string hh, mi;
    string dd, mm, yy;
    string opis, naziv, vrsta, lokacija;
    EVENT new_event;
    cout<<"Unesite sljedece stavke: "<<endl<<endl;

    /*------------ UNOSENJE NAZIVA DOGADJAJA ------------*/
    do{
        cout<<"Naziv: ";
        getline(cin, naziv, '\n');

        if ( naziv.length() >= 101 || naziv.length() <= 2 ){
            print_text("\nNAZIV");
        }

        if ( naziv == "EXIT" ){
            return;
        }
    }while ( naziv.length() >= 101 || naziv.length() <= 2 );
    strcpy(new_event.name, naziv.c_str());

    /*------------ UNOSENJE OPISA DOGADJAJA ------------*/
    do{
        cout<<"Opis: ";
        getline(cin, opis, '\n');
        if ( opis.length() >= 1001 || opis.length() <= 9 ){
            print_text("\nOPIS");
        }

        if ( opis == "EXIT" ){
            return;
        }
    }while ( opis.length() >= 1001 || opis.length() <= 9 );
    strcpy(new_event.description, opis.c_str());

    /*------------ PRIKAZIVANJE VRSTA KATEGORIJA KOJE SU DEF. U DATOTECI ------------*/
    cout<<"Vrste Kategorija: "<<endl;

    FILE *fp = fopen("type_category.dat", "rb");

    char buff[100];
    map <string, bool> flag;

    while ( fread(buff, sizeof(buff), 1, fp) ){
        cout<<"     - "<<buff<<endl;
        string buff1 = buff;
        flag[buff1] = true;
    }

    fclose(fp);

    /*------------ UNOSENJE VRSTE DOGADJAJA ------------*/
    cout<<endl;
    do{
        cout<<"     - Unesite vrstu: ";
        getline(cin, vrsta, '\n');

        if ( !flag[vrsta] ){
            print_text("\nVRSTA");
        }

        if ( vrsta == "EXIT" ){
            return;
        }
    }while ( vrsta.length() <= 2 || vrsta.length() >= 101 || !flag[vrsta] );
    strcpy(new_event.type, vrsta.c_str());

    /*------------ UNOSENJE LOKACIJE DOGADJAJA ------------*/
    do{
        cout<<"Lokacija: ";
        getline(cin, lokacija, '\n');
        if ( lokacija.length() >= 101 || lokacija.length() <= 1 ){
            print_text("\nLOKACIJA");
        }

        if ( lokacija == "EXIT" ){
            return;
        }
    }while ( lokacija.length() >= 101 || lokacija.length() <= 1 );
    strcpy(new_event.location, lokacija.c_str());

    /*------------ UNOSENJE DATUMA DOGADJAJA ------------*/
    cout<<"Datum: \n";
    do{

        cout<<"     - Dan   : ";
        getline(cin, dd, '\n');
        new_event.dd = convert_string(dd);
        if ( dd == "EXIT" ){
            return;
        }
        cout<<"     - Mjesec: ";
        getline(cin, mm, '\n');
        new_event.mm = convert_string(mm);
        if ( mm == "EXIT" ){
            return;
        }
        cout<<"     - Godina: ";
        getline(cin, yy, '\n');
        new_event.yy = convert_string(yy);
        if ( yy == "EXIT" ){
            return;
        }

        if ( !new_event.flag_day() ){
            print_text("\nDAN DATUMA");
        }

        if ( !new_event.flag_month() ){
            print_text("\nMJESEC DATUMA");
        }

        if ( !new_event.flag_year() ){
            print_text("\nGODINA DATUMA");
        }

        if ( !new_event.flag_date() ){
            print_text("\nDATUM");
        }
    }while ( !new_event.flag_day() || !new_event.flag_month() || !new_event.flag_year() || !new_event.flag_date() );

    /*------------ UNOSENJE VREMENA DOGADJAJA ------------*/
    cout<<"Vrijeme: \n";
    do{
        cout<<"     - Casova: ";
        getline(cin, hh, '\n');
        new_event.hh = convert_string(hh);
        if ( hh ==  "EXIT" ){
            return;
        }
        cout<<"     - Minute: ";
        getline(cin, mi, '\n');
        new_event.mi = convert_string(mi);
        if ( mi == "EXIT" ){
            return;
        }

        if ( !new_event.flag_hh() ){
            print_text("\nCASOVE VREMENA");
        }

        if ( !new_event.flag_mi() ){
            print_text("\nMINUTE VREMENA");
        }
    }while ( !new_event.flag_hh() || !new_event.flag_mi() );

    /*------------ DODAVANJE DOGADJAJA U DATOTEKU ------------*/
    fp = fopen("EVENT.dat", "ab");

    cout<<"USPJESNO STE UNIJELI NOVI DOGADJAJ!!!"<<endl;
    fwrite(&new_event, sizeof(EVENT), 1, fp);

    fclose(fp);
}
