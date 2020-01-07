bool sortby_time(const EVENT &a, const EVENT &b){
    if ( a.yy == b.yy ){
        if ( a.mm == b.mm ){
            if ( a.dd == b.dd ){
                if ( a.hh == b.hh ){
                    if ( a.mi <= b.mi ){
                        return true;
                    }else{
                        return false;
                    }
                }else if ( a.hh < b.hh ){
                    return true;
                }else{
                    return false;
                }
            }else if ( a.dd < b.dd ){
                return true;
            }else{
                return false;
            }
        }else if ( a.mm < b.mm ){
            return true;
        }else{
            return false;
        }
    }else if ( a.yy < b.yy ){
        return true;
    }else{
        return false;
    }
}
