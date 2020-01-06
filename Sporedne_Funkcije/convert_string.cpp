/*------------- KONVERZIJA STRING-a U INT ---------------*/
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
