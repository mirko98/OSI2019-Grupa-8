void print_text(string a){
    if ( a.find("VRSTA") != string::npos || a.find("GODINA") != string::npos || a.find("LOKACIJA") != string::npos ){
        a+=" KOJU STE UNIJELI NIJE VALIDNA.\nPOKUSAJTE PONOVO!!!\n\n";
    }else{
        a+=" KOJI STE UNIJELI NIJE VALIDAN.\nPOKUSAJTE PONOVO!!!\n\n";
    }

    cout<<a;
}
