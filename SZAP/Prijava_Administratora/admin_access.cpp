bool admin_acess(){
    string name;
    char password[100];
    string pass_buff;
    cout<<"Unesite sljedece stavke: "<<endl;
 
    do{
        cout<<"     - Ime: ";
        getline(cin, name, '\n');
 
        if ( !check_admin_login(name) ){
            print_text("\nIME NALOGA");
        }
    }while ( !check_admin_login(name) );
 
    do{
        char c;
        int poz = 0;
        cout<<"     - Sifra: ";
 
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
        if ( !check_admin_login(pass_buff) ){
            print_text("\nSIFRU");
        }
    }while( !check_admin_login(pass_buff) );
 
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
