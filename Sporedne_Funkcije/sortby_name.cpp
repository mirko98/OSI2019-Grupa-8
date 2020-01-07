bool sortby_name(const EVENT &a, const EVENT &b){
    string a1 = a.name;
    string b1 = b.name;
    if ( a1 < b1 ) return true;

    return false;
}
