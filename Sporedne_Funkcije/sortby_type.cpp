bool sortby_type(const EVENT &a, const EVENT &b){
    string a1 = a.type;
    string b1 = b.type;
    if ( a1 < b1 ) return true;

    return false;
}
