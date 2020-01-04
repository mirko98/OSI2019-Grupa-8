EVENT add_event(int type){
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

        if ( !type ){
            if ( naziv == "-1" ){
                naziv = "-1";
                break;
            }
        }

        if ( naziv.length() >= 101 || naziv.length() <= 2 ){
            print_text("\nNAZIV");
        }

        if ( naziv == "EXIT" ){
            new_event.dd = 9999;
            return new_event;
        }
    }while ( naziv.length() >= 101 || naziv.length() <= 2 );
    strcpy(new_event.name, naziv.c_str());

    /*------------ UNOSENJE OPISA DOGADJAJA ------------*/
    do{
        cout<<"Opis: ";
        getline(cin, opis, '\n');

        if ( !type ){
            if ( opis == "-1" ){
                opis = "-1";
                break;
            }
        }

        if ( opis.length() >= 1001 || opis.length() <= 9 ){
            print_text("\nOPIS");
        }

        if ( opis == "EXIT" ){
            new_event.dd = 9999;
            return new_event;
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

        if ( !type ){
            if ( vrsta == "-1" ){
                vrsta = "-1";
                break;
            }
        }

        if ( !flag[vrsta] ){
            print_text("\nVRSTA");
        }

        if ( vrsta == "EXIT" ){
            new_event.dd = 9999;
            return new_event;
        }
    }while ( vrsta.length() <= 2 || vrsta.length() >= 101 || !flag[vrsta] );
    strcpy(new_event.type, vrsta.c_str());

    /*------------ UNOSENJE LOKACIJE DOGADJAJA ------------*/
    do{
        cout<<"Lokacija: ";
        getline(cin, lokacija, '\n');

        if ( !type ){
            if ( lokacija == "-1" ){
                lokacija = "-1";
                break;
            }
        }

        if ( lokacija.length() >= 101 || lokacija.length() <= 1 ){
            print_text("\nLOKACIJA");
        }

        if ( lokacija == "EXIT" ){
            new_event.dd = 9999;
            return new_event;
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
            new_event.dd = 9999;
            return new_event;
        }
        cout<<"     - Mjesec: ";
        getline(cin, mm, '\n');
        new_event.mm = convert_string(mm);
        if ( mm == "EXIT" ){
            new_event.dd = 9999;
            return new_event;
        }
        cout<<"     - Godina: ";
        getline(cin, yy, '\n');
        new_event.yy = convert_string(yy);
        if ( yy == "EXIT" ){
            new_event.dd = 9999;
            return new_event;
        }

        if ( yy == "-1" && mm == "-1" && dd == "-1" ){
            new_event.dd = new_event.mm = new_event.yy = -1;
            break;
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
    }while ( !new_event.flag_day() || !new_event.flag_month() || !new_event.flag_year()  || !new_event.flag_date() );

    /*------------ UNOSENJE VREMENA DOGADJAJA ------------*/
    cout<<"Vrijeme: \n";
    do{
        cout<<"     - Casova: ";
        getline(cin, hh, '\n');
        new_event.hh = convert_string(hh);
        if ( hh ==  "EXIT" ){
            new_event.dd = 9999;
            return new_event;
        }
        cout<<"     - Minute: ";
        getline(cin, mi, '\n');
        new_event.mi = convert_string(mi);
        if ( mi == "EXIT" ){
            new_event.dd = 9999;
            return new_event;
        }


        if ( hh == "-1" && mi == "-1" ){
            new_event.mi = new_event.hh = -1;
            break;
        }

        if ( !new_event.flag_hh() ){
            print_text("\nCASOVE VREMENA");
        }

        if ( !new_event.flag_mi() ){
            print_text("\nMINUTE VREMENA");
        }
    }while ( !new_event.flag_hh() || !new_event.flag_mi() );

    for (int i=0;i<100;i++){
        new_event.comment[i][0] = '-';
        new_event.comment[i][1] = '\0';
    }

    /*------------ DODAVANJE DOGADJAJA U DATOTEKU ------------*/

    if ( type ){
        fp = fopen("EVENT.dat", "ab");

        cout<<"USPJESNO STE UNIJELI NOVI DOGADJAJ!!!"<<endl;

        fwrite(&new_event, sizeof(EVENT), 1, fp);
        fclose(fp);
    }

    return new_event;
}
