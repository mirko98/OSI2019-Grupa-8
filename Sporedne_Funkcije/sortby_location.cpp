bool sortby_location(const EVENT &a, const EVENT &b){
    string a1 = a.location;
    string b1 = b.location;
    if ( a1 < b1 ) return true;

    return false;
}
