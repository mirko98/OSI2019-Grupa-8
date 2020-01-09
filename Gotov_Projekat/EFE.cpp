#include "EFE.h"

int mm_dd[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*------ INICIJALIZUJEMO TM ------*/
EVENT::EVENT(){
    time(&tt);
    TM = *localtime(&tt);
}

/*------ VRACA DANASNJU GODINU ------*/
int EVENT::current_year(){
    return (int)TM.tm_year + 1900;
}

/*------ VRACA DANASNJI MJESEC ------*/
int EVENT::current_month(){
    return (int)TM.tm_mon + 1;
}

/*------ VRACA DANASNJI DAN ------*/
int EVENT::current_day(){
    return (int)TM.tm_mday;
}

/*------ PROVJERA DANA ------*/
bool EVENT::flag_day(){
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
bool EVENT::flag_month(){
    if ( mm <= 12 && mm >= 1 ){
        return true;
    }

    return false;
}

/*------ PROVJERA GODINE ------*/
bool EVENT::flag_year(){
    if ( abs(yy-current_year()) <= 5 ){
        return true;
    }

    return false;
}

/*------ PROVJERA DATUMA(da li je datum buduci) ------*/
bool EVENT::flag_date(){
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
bool EVENT::flag_mi(){
    if ( mi >= 0 && mi <= 59 ){
        return true;
    }

    return false;
}

/*------ PROVJERA CASOVA ------*/
bool EVENT::flag_hh(){
    if ( hh >= 0 && hh <= 23 ){
        return true;
    }

    return false;
}

/*=================== SZAP ==================*/

//DODAJE KATEGORIJU
void add_type(){
    FILE *fp = fopen("type_category.dat", "rb");

    map <string, bool> flag;
    string buff1;
    char buff[100];

    while ( fread(buff, sizeof(buff), 1, fp) ){
        buff1 = buff;
        flag[buff] = true;
    }

    fclose(fp);
    string choise;
    do{
        cout<<"Unesite naziv kategorije: ";
        getline(cin, choise, '\n');

        if ( choise  == "EXIT" ){
            return;
        }
        if ( flag[choise] ){
            cout<<"\nNAZIV KATEGORIJE VEC POSTOJI.\nPOKUSAJTE PONOVO!!!"<<endl<<endl;
        }
        if ( choise.length() < 3 || choise.length() > 100 ){
            print_text("\nNAZIV KATEGORIJE");
        }
    }while ( choise.length() < 3 || choise.length() > 100 || flag[choise] );

    fp = fopen("type_category.dat", "ab");

    strcpy(buff, choise.c_str());
    fwrite(buff, sizeof(buff), 1, fp);

    cout<<"USPJESNO STE DODALI NOVU KATEGORIJU."<<endl;

    fclose(fp);
}

//BRISE KATEGORIJU
void delete_type(){
    cout<<"BRISANJE KATEGORIJE: "<<endl<<endl;

    FILE *fp = fopen("type_category.dat", "rb");

    char buff[100];
    vector <string> buff1;

    while ( fread(buff, sizeof(buff), 1, fp) ){
        buff1.push_back(buff);

        cout<<"Kategorija ["<<buff1.size()<<"] : "<<buff<<endl;
    }

    if ( !buff1.size() ){
        cout<<"POSTO NEMA NIJEDNE KATEGORIJE U DATOTECI NIJE MOGUCE NASTAVITI OPERACIJU"<<endl<<endl;
        return;
    }

    string choise;
    int broj = -1;
    do{
        cout<<"Unesite Redni Broj: ";
        getline(cin, choise, '\n');

        broj = convert_string(choise);

        if ( choise == "EXIT" ){
            return;
        }

        if ( broj == -1 || broj <= 0 || broj > (int)buff1.size() ){
            print_text("\nREDNI BROJ");
        }
    }while ( broj == -1 || broj <= 0 || broj > (int)buff1.size() );
    cout<<endl;

    cout<<"USPJESNO STE OBRISALI KATEGORIJU!!!"<<endl;

    fp = fopen("type_category.dat", "wb");

    for (int i=0;i<(int)buff1.size();i++){
        if ( i == broj - 1 ) continue;

        strcpy(buff, buff1[i].c_str());

        fwrite(&buff, sizeof(buff), 1, fp);
    }

    fclose(fp);
}

//DODAJE DOGADJAJ A MOZE SE KORISTITI ZA DIO OPERACIJA MODIFIKACIJE
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
    int br = 0;
    map <string, bool> flag;

    while ( fread(buff, sizeof(buff), 1, fp) ){
        cout<<"     - "<<buff<<endl;
        string buff1 = buff;
        flag[buff1] = true;
        br++;
    }

    if ( !br ){
        cout<<"POSTO NEMA NIJEDNE KATEGORIJE U DATOTECI NIJE MOGUCE NASTAVITI OPERACIJU"<<endl<<endl;
        new_event.dd = 9999;
        return new_event;
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

//BRISE DOGADJAJ
void delete_event(const vector <EVENT> &niz){
    cout<<"BRISANJE DOGADJAJA: "<<endl<<endl;

    print_event_all(niz);

    if ( !niz.size() ){
        cout<<"POSTO NEMA NIJEDNOG DOGADJAJA U DATOTECI NIJE MOGUCE NASTAVITI OPERACIJU"<<endl<<endl;
        return;
    }

    string choise;
    int broj = -1;
    do{
        cout<<"Unesite Redni Broj: ";
        getline(cin, choise, '\n');

        broj = convert_string(choise);

        if ( choise == "EXIT" ){
            return;
        }

        if ( broj == -1 || broj <= 0 || broj > (int)niz.size() ){
            print_text("\nREDNI BROJ");
        }
    }while ( broj == -1 || broj <= 0 || broj > (int)niz.size() );
    cout<<endl;

    cout<<"USPJESNO STE OBRISALI DOGADJAJ!!!"<<endl;

    FILE *fp = fopen("EVENT.dat", "wb");

    for (int i=0;i<(int)niz.size();i++){
        if ( i == broj - 1 ) continue;

        fwrite(&niz[i], sizeof(EVENT), 1, fp);
    }

    fclose(fp);
}

//MODIFIKACIJA DOGADJAJA
void mod_event(vector <EVENT> &niz){
    cout<<"MODIFIKACIJA DOGADJAJA: "<<endl<<endl;

    print_event_all(niz);

    if ( !niz.size() ){
        cout<<"POSTO NEMA NIJEDNOG DOGADJAJA U DATOTECI NIJE MOGUCE NASTAVITI OPERACIJU"<<endl<<endl;
        return;
    }

    string choise;
    int broj = -1;
    do{
        cout<<"Unesite Redni Broj: ";
        getline(cin, choise, '\n');

        broj = convert_string(choise);

        if ( choise == "EXIT" ){
            return;
        }

        if ( broj == -1 || broj <= 0 || broj > (int)niz.size() ){
            print_text("\nREDNI BROJ");
        }
    }while ( broj == -1 || broj <= 0 || broj > (int)niz.size() );
    cout<<endl;

    EVENT buff = add_event(0);

    // da se zna da se iz sljedbenik funkcije izaslo naredbom EXIT
    if ( buff.dd == 9999 ){
        return;
    }

    choise = buff.name;
    if ( choise != "-1" ){
        strcpy(niz[broj-1].name, buff.name);
    }

    choise = buff.location;
    if ( choise != "-1" ){
        strcpy(niz[broj-1].location, buff.location);
    }

    choise = buff.description;
    if ( choise != "-1" ){
        strcpy(niz[broj-1].description, buff.description);
    }

    choise = buff.type;
    if ( choise != "-1" ){
        strcpy(niz[broj-1].type, buff.type);
    }

    if ( buff.dd != -1 ){
        niz[broj-1].dd = buff.dd;
    }
    if ( buff.yy != -1 ){
        niz[broj-1].yy = buff.yy;
    }
    if ( buff.mm != -1 ){
        niz[broj-1].mm = buff.mm;
    }
    if ( buff.hh != -1 ){
        niz[broj-1].hh = buff.hh;
    }
    if ( buff.mi != -1 ){
        niz[broj-1].mi = buff.mi;
    }

    int i = 0;

    for (i=0;i<100;i++){
        if ( niz[broj-1].comment[i][0] == '-' && niz[broj-1].comment[i][1] == '\0' ){
            break;
        }
    }

    if ( i != 0 ){
        cout<<"Komentari dogadjaja: "<<endl;
        for (int j=0;j<i;j++){
            cout<<"     - Komentar ["<<j+1<<"]: "<<niz[broj-1].comment[j]<<endl;
        }

        int buff_broj;
        do{
            cout<<"Unesite redni broj komentara koji zelite da obrisete: ";

            getline(cin, choise, '\n');

            buff_broj = convert_string(choise);

            if ( choise == "EXIT" || choise == "-1" ){
                return;
            }

            if ( buff_broj == -1 || buff_broj <= 0 || buff_broj > (int)niz.size() ){
                print_text("\nREDNI BROJ");
            }
        }while ( buff_broj == -1 || buff_broj <= 0 || buff_broj > (int)niz.size() );

        for (int j=buff_broj-1;j<99;j++){
            strcpy(niz[broj-1].comment[j], niz[broj-1].comment[j+1]);
        }

        niz[broj-1].comment[99][0] = '-';
        niz[broj-1].comment[99][1] = '\0';
    }

    cout<<"USPJESNO STE MODIFIKOVALI DOGADJAJ DOGADJAJ!!!"<<endl;

    FILE *fp = fopen("EVENT.dat", "wb");

    for (unsigned int i=0;i<niz.size();i++){
        fwrite(&niz[i], sizeof(EVENT), 1, fp);
    }

    fclose(fp);
}

/*=================== SZAP ==================*/

/*=================== SZPI ==================*/

//ISPISUJE NIZ TIPA EVENT
void print_event_all(const vector <EVENT> &niz){
    for (unsigned int i=0;i<niz.size();i++){
        cout<<"REDNI BROJ: "<<i+1<<endl;
        cout<<"DATUM: "<<niz[i].dd<<"/"<<niz[i].mm<<"/"<<niz[i].yy<<endl;
        cout<<"VRIJEME: "<<niz[i].hh<<"/"<<niz[i].mi<<endl;
        cout<<"NAZIV: "<<niz[i].name<<endl;
        cout<<"VRSTA: "<<niz[i].type<<endl;
        cout<<"LOKACIJA: "<<niz[i].location<<endl;
        cout<<"OPIS: "<<niz[i].description<<endl;

        cout<<"KOMENTARI: "<<endl;
        for (int j=0;j<100;j++){
            if ( niz[i].comment[j][0] == '-' ) break;
            cout<<"     - Komentar "<<j+1<<": ";
            cout<<niz[i].comment[j]<<endl;
        }

        cout<<endl;
    }
}

//ISPISUJE DOGADJAJE KOJI SU SE EDSILI , POZIVA FUNKCIJA ZA ISPIS DOGADJAJA SAMO ZA NIZ SA ODGOVARAJUCIM DOGADJAJIMA
void print_event_past(const vector <EVENT> &niz){
    cout<<"DOGADJAJI KOJI SU PROSLI: "<<endl<<endl;

    vector <EVENT> buff;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];

        int c_mi = get_minute();
        int c_h = get_hours();
        int c_day = new_event.current_day();
        int c_month = new_event.current_month();
        int c_year = new_event.current_year();

        if ( c_year > new_event.yy ){
            buff.push_back(new_event);
        }else if ( c_year == new_event.yy ){
            if ( c_month > new_event.mm ){
                buff.push_back(new_event);
            }else if ( c_month == new_event.mm ){
                if ( c_day > new_event.dd ){
                    buff.push_back(new_event);
                }else if ( c_day == new_event.dd ){
                    if ( c_h > new_event.hh ){
                        buff.push_back(new_event);
                    }else if ( c_h == new_event.hh ){
                        if ( c_mi > new_event.mi ){
                            buff.push_back(new_event);
                        }
                    }
                }
            }
        }
    }

    if ( buff.size() != 0 ){
        print_event_all(buff);
    }
}

//ISPISUJE DOGADJAJE KOJE SE DANAS DOGADJAJU , POZIVA FUNKCIJA ZA ISPIS DOGADJAJA SAMO ZA NIZ SA ODGOVARAJUCIM DOGADJAJIMA
void print_event_today(const vector <EVENT> &niz){
    cout<<"DOGADJAJI KOJI SU DANAS: "<<endl<<endl;

    vector <EVENT> buff;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];

        int c_day = new_event.current_day();
        int c_month = new_event.current_month();
        int c_year = new_event.current_year();

        if ( new_event.dd == c_day && new_event.mm == c_month && new_event.yy == c_year ){
            buff.push_back(new_event);
        }
    }

    if ( buff.size() != 0 ){
        print_event_all(buff);
    }
}

//ISPISUJE DOGADJAJE PO ODABRATOJ KATEGORIJI , POZIVA FUNKCIJA ZA ISPIS DOGADJAJA SAMO ZA NIZ SA ODGOVARAJOM KATEGORIJOM
void print_event_category(const vector <EVENT> &niz, string &type){
    cout<<type<<endl;
    cout<<"DOGADJAJI KATEGORIJE "<<type<<" SU: "<<endl<<endl;

    vector <EVENT> buff;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];

        if ( new_event.type == type ){
            buff.push_back(new_event);
        }
    }

    if ( buff.size() != 0 ){
        print_event_all(buff);
    }
}

//ISPISUJE DOGADJAJE BUDUCE , POZIVA FUNKCIJA ZA ISPIS DOGADJAJA SAMO ZA NIZ SA ODGOVARAJUCIM DOGADJAJIMA
void print_event_future(const vector <EVENT> &niz){
    cout<<"DOGADJAJI KOJI CE SE DESITI: "<<endl<<endl;

    vector <EVENT> buff;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];

        int c_mi = get_minute();
        int c_h = get_hours();
        int c_day = new_event.current_day();
        int c_month = new_event.current_month();
        int c_year = new_event.current_year();

        if ( c_year < new_event.yy ){
            buff.push_back(new_event);
        }else if ( c_year == new_event.yy ){
            if ( c_month < new_event.mm ){
                buff.push_back(new_event);
            }else if ( c_month == new_event.mm ){
                if ( c_day < new_event.dd ){
                    buff.push_back(new_event);
                }else if ( c_day == new_event.dd ){
                    if ( c_h < new_event.hh ){
                        buff.push_back(new_event);
                    }else if ( c_h == new_event.hh ){
                        if ( c_mi < new_event.mi ){
                            buff.push_back(new_event);
                        }
                    }
                }
            }
        }
    }

    if ( buff.size() != 0 ){
        print_event_all(buff);
    }
}

//IGRANJE KVIZA
void quiz(){
    ifstream input("QUIZ.dat", std::ios::in | std::ios::binary);

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

//UNOSIMO SVE DOGADJAJE IZ DATOTEKE U NIZ
void input_all(vector <EVENT> &niz){
    FILE *fp = fopen("EVENT.dat", "rb");

    EVENT buff;

    while ( fread(&buff, sizeof(EVENT), 1, fp) ){
        niz.push_back(buff);
    }

    fclose(fp);
}

//DODAVANJE KOMENTARA
void input_comment(vector <EVENT> &niz){
    cout<<"UNOS KOMENTARA DOGADJAJA: "<<endl<<endl;

    print_event_all(niz);

    string choise;
    int broj = -1;
    do{
        cout<<"Unesite Redni Broj: ";
        getline(cin, choise, '\n');

        broj = convert_string(choise);

        if ( choise == "EXIT" ){
            return;
        }

        if ( broj == -1 || broj <= 0 || broj > (int)niz.size() ){
            print_text("\nREDNI BROJ");
        }
    }while ( broj == -1 || broj <= 0 || broj > (int)niz.size() );
    cout<<endl;

    string comment;
    bool flag = false;
    do{
        flag = false;
        cout<<"Unesite komentar: ";
        getline(cin, comment, '\n');

        if ( comment == "EXIT" ){
            return;
        }

        for (unsigned int i=0;i<comment.length();i++){
            if ( comment[i] == '-' ){
                flag = true;
                break;
            }
        }

        if ( comment.length() <= 0 || comment.length() >= 101 || flag ){
            print_text("\nKOMENTAR");
        }
    }while ( comment.length() <= 0 || comment.length() >= 101 || flag );

    cout<<"USPJESNO STE DODALI KOMENTAR DOGADJAJU!!!"<<endl;

    int j = 0;
    for (j=0;j<100;j++){
        if ( niz[broj-1].comment[j][0] == '-' ){
            break;
        }
    }

    strcpy(niz[broj-1].comment[j % 100], comment.c_str());

    FILE *fp = fopen("EVENT.dat", "wb");

    for (unsigned int i=0;i<niz.size();i++){
        fwrite(&niz[i], sizeof(EVENT), 1, fp);
    }

    fclose(fp);
}

/*=================== SZPI ==================*/

/*============= SPOREDNE FUNKCIJE ===========*/

//KONVERTUJEMO STRING U BROJ UKOLIKO JE MOGUCE
int convert_string(string &a){
    int value = 0;
    int inc = 1;

    bool flag = false;
    if ( a[0] == '-' && (int)a.length() >= 2 ){
        a.erase(0, 1);
        flag = true;
    }

    for (int i=a.length()-1;i>=0;i--){
        if ( !isdigit(a[i]) ){
            return -1;
        }

        value+=inc*(int)(a[i] - '0');
        inc*=10;
    }

    if ( flag ) {
        a.insert(0, "-");
        return value * (-1);
    }
    return value;
}

//ISPISUJE ODGOVARAUCI TEKST(PORUKU)
void print_text(string a){
    if ( a.find("VRSTA") != string::npos || a.find("SIFRU") != string::npos || a.find("GODINA") != string::npos || a.find("LOKACIJA") != string::npos ){
        a+=" KOJU STE UNIJELI NIJE VALIDNA.\nPOKUSAJTE PONOVO!!!\n\n";
    }else{
        a+=" KOJI STE UNIJELI NIJE VALIDAN.\nPOKUSAJTE PONOVO!!!\n\n";
    }

    cout<<a;
}

//DOBIJAMO TERNUTNE SATE
int get_hours(){
    time_t tt;
    tm TM;
    time(&tt);
    TM = *localtime(&tt);

    return (int)TM.tm_hour;
}

//DOBIJAMO TERNUTNE MINUTE
int get_minute(){
    time_t tt;
    tm TM;
    time(&tt);
    TM = *localtime(&tt);

    return (int)TM.tm_min;
}

//ZA PRIJAVU NA SISTEM
bool admin_acess(){
    string name;
    char password[100];
    string pass_buff;
    cout<<"Unesite sljedece stavke: "<<endl;

    do{
        cout<<"     - Ime: ";
        getline(cin, name, '\n');

        if ( !check_admin_login(name) || name.length() < 3 || name.length() > 100 ){
            print_text("\nIME NALOGA");
        }
    }while ( !check_admin_login(name) || name.length() < 3 || name.length() > 100 );

    int poz = 0;
    do{
        char c;
        cout<<"     - Sifra: ";
        poz = 0;

        while (1){
            c=getch();

            if ( c == 13 ){
                break;
            }else if ( c == 8){
                putch('\b');
                putch(' ');
                putch('\b');
                poz--;
            }
            else{
                password[poz++] = c;
                putch('*');
            }
        }

        password[poz] = '\0';

        pass_buff = password;
        if ( !check_admin_login(pass_buff) || poz < 6 || poz > 100 ){
            print_text("\nSIFRU");
        }
    }while( !check_admin_login(pass_buff) || poz < 6 || poz > 100 );

    FILE *fp = fopen("ADMIN.dat", "rb");

    ADMIN buff;

    while ( fread(&buff, sizeof(ADMIN), 1, fp) ){
        string ime_k = buff.name;
        string sifra_k = buff.password;

        if ( ime_k == name && sifra_k == pass_buff ){
            return true;
        }
    }

    fclose(fp);

    return false;
}

//DA LI USERNAME I SIFRA DOBRE
bool check_admin_login(string &a){
    int br = 0;
    for (int i=0;i<(int)a.length();i++){
        if ( (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z') || (a[i] >= '0' && a[i] <= '9') ){
            br++;
        }
    }

    if ( br == (int)a.length() ){
        return true;
    }else{
        return false;
    }
}

//UKOLIKO ZELI DA VIDI OGRANICENJA I KAKO KORISTITI
void help(){
    cout<<endl<<"   POMOC PRI PRIJAVI ADMINISTRATORA NA SISTEM\n"<<endl;
    cout<<"     - Administrator mora postovati strogo definisana pravila pri prijavljivanju na sistem."<<endl;
    cout<<"     - Korisnicko ime se mora sastojati od 3 do 100 karaktera, dok se lozinka mora sastojati"<<endl;
    cout<<"       od 6 do 100 karaktera. "<<endl;
    cout<<"     - Za sifru i ime se mogu koristiti samo cifre i slova a-z(takodje vazi za velika slova)."<<endl;
    cout<<"     - Ukoliko uneseni podaci ne zadovoljaju odredjene opsege, sistem od korisnika trazi da"<<endl;
    cout<<"       ponovo unese podatke."<<endl;

    cout<<endl<<"   POMOC PRI UNOSU INFORMACIJA O DOGADJAJU\n"<<endl;
    cout<<"     - Unose se informacije o dogadjaju kao sto su naziv, opis, vrsta, lokacija i datum"<<endl;
    cout<<"       odrzavanja dogadjaja."<<endl;
    cout<<"     - Takodje se ostavlja mogucnost korisnicima da komentarisu odredjeni dogadjaj. Naziv"<<endl;
    cout<<"       dogadjaja se mora sastojati od 3 do 100 karaktera."<<endl;
    cout<<"     - Opis ogranicavamo na opseg 10-1000 karaktera."<<endl;
    cout<<"     - Pri unosu vrste i lokacije dogadjaja zahtjeva se da unos bude u opsegu 2-100"<<endl;
    cout<<"       karaktera, dok je duzina komentara ogranicena na opseg 1-1000 karaktera."<<endl;
    cout<<"     - Datum dogadjaja mora da bude validan, tj. da se navede da ce se dogadjaj dogoditi u"<<endl;
    cout<<"       buducnosti (najranije sutradan), inace ce sistem prikazivati gresku."<<endl;
    cout<<"     - Ukoliko uneseni podaci ne zadovoljaju odredjene opsege i nisu validni, sistem od"<<endl;
    cout<<"       korisnika trazi da ponovo unese podatke."<<endl;

    cout<<endl<<"   POMOC PRI IGRANJU KVIZA\n"<<endl;
    cout<<"     - Duzina pitanja mora ispostovati opseg koji iznosi 3-1000 karaktera. Na svako pitanje"<<endl;
    cout<<"       moraju biti ponudjena tri odgovora ciju duzinu takodje ogranicavamo na 3-1000"<<endl;
    cout<<"       karaktera."<<endl;
    cout<<"     - Korisnik na pitanja odgovara tako sto upise odgovarajuci indeks koji stoji uz pitanje,"<<endl;
    cout<<"       za koje smatra da je tacno. Ukoliko se ne ispostuje odredjeni opseg, sistem trazi da"<<endl;
    cout<<"       se ponovo unesu podaci."<<endl;

    cout<<endl<<"   POMOC PRILIKOM DODAVANJA KOMENTARA\n"<<endl;
    cout<<"     - Duzina komentara je ogranicena na opseg 1-1000 karaktera. Jedan dogadjaj moze imati"<<endl;
    cout<<"       maksimalno 100 komentara."<<endl;
    cout<<"     - Ako komentar predstavlja neprikladan sadrzaj, administrator ima pravo da taj"<<endl;
    cout<<"       komentar ukloni."<<endl;
    cout<<"     - Ukoliko jedan dogadjaj ima maksimalan broj komentara i korisnik zeli dodati komentar,"<<endl;
    cout<<"       taj komentar ide na mjesto najstarijeg komentara, a najstariji komentar se prethodno"<<endl;
    cout<<"       obrise."<<endl;

    cout<<endl<<"   POMOC PRI BRISANJU DOGADJAJA\n"<<endl;
    cout<<"     - Mogucnost brisanja dogadjaja imaju samo administratori sistema."<<endl;
    cout<<"     - Pri odabiru ove opcije, administratoru ce biti prikazani svi dogadjaji pri cemu ce"<<endl;
    cout<<"       kraj svakog dogadjaja biti odgovarajuci indeks (koji je za svaki dogadjaj"<<endl;
    cout<<"       jedinstven)."<<endl;
    cout<<"     - Nakon ovoga, trazice se od administratora da unese vrijednost indeksa dogadjaja"<<endl;
    cout<<"       koji zeli da obrise. "<<endl;
    cout<<"     - Ukoliko unos naredbe nije dobar, odnosno indeks nije vazeci, onda ce"<<endl;
    cout<<"       administratoru biti prikazana odgovarajuca poruka, pri cemu ce se traziti od"<<endl;
    cout<<"       administrator da ponovo unese indeks dogadjaja koji zeli da obrise."<<endl;

    cout<<endl<<"   POMOC PRI MODIFIKACIJI DOGADJAJA\n"<<endl;
    cout<<"     - Prilikom modifikacije dogadjaja, otvara se isti prozor kao prilikom unosa informacija"<<endl;
    cout<<"       o dogadjaju. Ukoliko neko polje, koje predstavlja informaciju o dogadjaju, ne zelimo"<<endl;
    cout<<"       izmijenitina to polje unosimo vrijednost -1 i sistem automatski prelazi na sljedece"<<endl;
    cout<<"       polje. "<<endl;
    cout<<"       -Izuzetak je modifikacija datuma i vremena. Ako zelimo promijeniti jedno polje, datuma"<<endl;
    cout<<"       ili vremena (minut, sat, dan, mjesec, godina) moramo sva polja ponovo popuniti"<<endl;
    cout<<"       odgovarajucim vrijednostima. Ne smijemo jedno polje promijeniti, a na ostala (koja ne"<<endl;
    cout<<"       zelimo promijeniti) unijeti -1. Tada ce sistem prikazati gresku."<<endl;
    cout<<"     - I u ovom slucaju sistem trazi da se odgovarajuci opseg ispostuje, inace sistem javlja"<<endl;
    cout<<"       gresku i trazi da se ponovo unesu podaci."<<endl;

    cout<<endl<<"   EXIT\n"<<endl;
    cout<<"     - Prilikom unosenja rijeci EXIT u bilo kojoj funkciji, osim u funkciji za prijavu"<<endl;
    cout<<"       administratora na sistem, automatski se izlazi iz funkcije i korisnika vraca na glavni"<<endl;
    cout<<"       meni."<<endl;
}

//KRITERIJUM SORTIRANJA PO NAZIVU
bool sortby_name(const EVENT &a, const EVENT &b){
    string a1 = a.name;
    string b1 = b.name;
    if ( a1 < b1 ) return true;

    return false;
}

//KRITERIJUM SORTIRANJA PO LOKACIJI
bool sortby_location(const EVENT &a, const EVENT &b){
    string a1 = a.location;
    string b1 = b.location;
    if ( a1 < b1 ) return true;

    return false;
}

//KRITERIJUM SORTIRANJA PO KATEGORIJI
bool sortby_type(const EVENT &a, const EVENT &b){
    string a1 = a.type;
    string b1 = b.type;
    if ( a1 < b1 ) return true;

    return false;
}

//KRITERIJUM SORTIRANJA PO VREMENU(URACUNAT I DATUM)
bool sortby_time(const EVENT &a, const EVENT &b){
    if ( a.yy == b.yy ){
        if ( a.mm == b.mm ){
            if ( a.dd == b.dd ){
                if ( a.hh == b.hh ){
                    if ( a.mi <= b.mi ){
                        return true;
                    }else{
                        return false;
                    }
                }else if ( a.hh < b.hh ){
                    return true;
                }else{
                    return false;
                }
            }else if ( a.dd < b.dd ){
                return true;
            }else{
                return false;
            }
        }else if ( a.mm < b.mm ){
            return true;
        }else{
            return false;
        }
    }else if ( a.yy < b.yy ){
        return true;
    }else{
        return false;
    }
}

//FUNKCIJA KOJA VRSI SORTIRANJE
void sort_event(vector <EVENT> &niz){
    cout<<"SORTIRANJE DOGADJAJA: "<<endl<<endl;

    cout<<"Po nazivu          [1]"<<endl;
    cout<<"Po Lokaciji        [2]"<<endl;
    cout<<"Po vremenu         [3]"<<endl;
    cout<<"Po vrsti dogadjaja [4]"<<endl;

    string choise;
    do{
        cout<<"Unesite redni broj: ";
        getline(cin, choise, '\n');

        if ( choise != "1" && choise != "2" && choise != "3" && choise != "4" ){
            print_text("\nREDNI BROJ");
        }
    }while ( choise != "1" && choise != "2" && choise != "3" && choise != "4" );

    if ( choise == "1" ) sort(niz.begin(), niz.end(), sortby_name);
    else if ( choise == "2" ) sort(niz.begin(), niz.end(), sortby_location);
    else if ( choise == "3" ) sort(niz.begin(), niz.end(), sortby_time);
    else sort(niz.begin(), niz.end(), sortby_type);

    cout<<"USPJESNO JE IZVRSENO SORTIRANJE PODATAKA"<<endl;
}

/*============= SPOREDNE FUNKCIJE ===========*/
