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
