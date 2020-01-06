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
