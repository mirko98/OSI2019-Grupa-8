bool check_admin_login(string &a){
    int br = 0;
    for (int i=0;i<(int)a.length();i++){
        if ( (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z') || (a[i] >= '0' && a[i] <= '9') ){
            br++;
        }
    }
 
    if ( br == (int)a.length() ){
        return true;
    }else{
        return false;
    }
}
