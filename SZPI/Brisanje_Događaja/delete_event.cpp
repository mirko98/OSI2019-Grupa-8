void delete_event(const vector <EVENT> &niz){
    cout<<"BRISANJE DOGADJAJA: "<<endl<<endl;

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

    cout<<"USPJESNO STE OBRISALI DOGADJAJ!!!"<<endl;

    FILE *fp = fopen("EVENT.dat", "wb");

    for (int i=0;i<(int)niz.size();i++){
        if ( i == broj - 1 ) continue;

        fwrite(&niz[i], sizeof(EVENT), 1, fp);
    }

    fclose(fp);
}
