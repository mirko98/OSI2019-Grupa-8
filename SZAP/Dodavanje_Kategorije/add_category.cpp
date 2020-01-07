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
