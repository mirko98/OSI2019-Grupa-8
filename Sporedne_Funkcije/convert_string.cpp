/*------------- KONVERZIJA STRING-a U INT ---------------*/
int convert_string(string &a){
    int value = 0;
    int inc = 1;
    for (int i=a.length()-1;i>=0;i--){
        if ( !isdigit(a[i]) ){
            return -1;
        }

        value+=inc*(int)(a[i] - '0');
        inc*=10;
    }

    return value;
}
