int mm_dd[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct EVENT{
    char name[100];
    char description[1000];
    char type[100];
    char location[100];
    char comment[100][1000];
    int dd;
    int mm;
    int yy;
    int mi;
    int hh;

    time_t tt;
    tm TM;

    /*------ INICIJALIZUJEMO TM ------*/
    EVENT(){
        time(&tt);
        TM = *localtime(&tt);
    }

    /*------ VRACA DANASNJU GODINU ------*/
    int current_year(){
        return (int)TM.tm_year + 1900;
    }
    
    /*------ VRACA DANASNJI MJESEC ------*/
    int current_month(){
        return (int)TM.tm_mon + 1;
    }

    /*------ VRACA DANASNJI DAN ------*/
    int current_day(){
        return (int)TM.tm_mday;
    }

    /*------ PROVJERA DANA ------*/
    bool flag_day(){
        if ( dd <= 0 ){
            return false;
        }

        if ( mm == 2 ){
            if ( ( yy % 400 == 0 ) || ( yy % 100 != 0 && yy % 4 == 0 ) ){
                if ( dd <= 29 ){
                    return true;
                }else{
                    return false;
                }
            }else{
                if ( dd <= 28 ){
                    return true;
                }else{
                    return false;
                }
            }
        }else{
            if ( dd <= mm_dd[mm-1] ){
                return true;
            }else{
                return false;
            }
        }
    }

    /*------ PROVJERA MJESECA ------*/
    bool flag_month(){
    if ( mm <= 12 && mm >= 1 ){
            return true;
        }

        return false;
    }

    /*------ PROVJERA GODINE ------*/
    bool flag_year(){
        if ( abs(yy-current_year()) <= 5 ){
            return true;
        }

        return false;
    }

    /*------ PROVJERA DATUMA(da li je datum buduci) ------*/
    bool flag_date(){
        int day = current_day();
        int month = current_month();
        int year = current_year();

        if ( year == yy ){
            if ( month == mm ){
                if ( day >= dd ){
                    return false;
                }else{
                    return true;
                }
            }else if ( month < mm ){
                return true;
            }else{
                return false;
            }
        }else if ( year > yy ){
            return false;
        }else{
            return true;
        }
    }

    /*------ PROVJERA MINUTA ------*/
    bool flag_mi(){
        if ( mi >= 0 && mi <= 59 ){
            return true;
        }

        return false;
    }

    /*------ PROVJERA CASOVA ------*/
    bool flag_hh(){
        if ( hh >= 0 && hh <= 23 ){
            return true;
        }

        return false;
    }
};
