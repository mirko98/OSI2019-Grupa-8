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

    if ( buff.dd == -1 ){
        return;
    }

    cout<<"USPJESNO STE MODIFIKOVALI DOGADJAJ DOGADJAJ!!!"<<endl;

    niz[broj-1] = buff;

    FILE *fp = fopen("EVENT.dat", "wb");

    for (unsigned int i=0;i<niz.size();i++){
        fwrite(&niz[i], sizeof(EVENT), 1, fp);
    }

    fclose(fp);
}
