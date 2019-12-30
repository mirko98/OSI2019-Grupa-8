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
        cout<<"Unesite komentar: ";
        getline(cin, comment, '\n');

        if ( comment == "EXIT" ){
            return;
        }

        for (int i=0;i<comment.length();i++){
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

    for (int i=0;i<niz.size();i++){
        fwrite(&niz[i], sizeof(EVENT), 1, fp);
    }

    fclose(fp);
}
