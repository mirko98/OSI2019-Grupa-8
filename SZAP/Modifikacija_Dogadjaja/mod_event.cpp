void mod_event(vector <EVENT> &niz){
    cout<<"MODIFIKACIJA DOGADJAJA: "<<endl<<endl;

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

    EVENT buff = add_event(0);

    // da se zna da se iz sljedbenik funkcije izaslo naredbom EXIT
    if ( buff.dd == 9999 ){
        return;
    }

    if ( buff.name[0] != '-' && buff.name[1] != '1' && buff.name[2] != '\0' ){
        strcpy(niz[broj-1].name, buff.name);
    }
    if ( buff.location[0] != '-' && buff.location[1] != '1' && buff.location[2] != '\0' ){
        strcpy(niz[broj-1].location, buff.location);
    }
    if ( buff.description[0] != '-' && buff.description[1] != '1' && buff.description[2] != '\0' ){
        strcpy(niz[broj-1].description, buff.description);
    }
    if ( buff.type[0] != '-' && buff.type[1] != '1' && buff.type[2] != '\0' ){
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
            cout<<"Unesite redni broj: ";

            getline(cin, choise, '\n');

            buff_broj = convert_string(choise);

            if ( choise == "EXIT" ){
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
