/*---------- TRENUTNI BROJ SATI -----------*/
int get_hours(){
    time_t tt;
    tm TM;
    time(&tt);
    TM = *localtime(&tt);

    return (int)TM.tm_hour;
}
