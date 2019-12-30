/*------------ TRENUTNI BROJ MINUTA -------------*/
int get_minute(){
    time_t tt;
    tm TM;
    time(&tt);
    TM = *localtime(&tt);

    return (int)TM.tm_min;
}
