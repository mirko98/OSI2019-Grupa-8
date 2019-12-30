void print_event_today(const vector <EVENT> &niz){
    cout<<"DOGADJAJI KOJI SU DANAS: "<<endl<<endl;
 
    vector <EVENT> buff;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];
 
        int c_day = new_event.current_day();
        int c_month = new_event.current_month();
        int c_year = new_event.current_year();
 
        if ( new_event.dd == c_day && new_event.mm == c_month && new_event.yy == c_year ){
            buff.push_back(new_event);
        }
    }
 
    if ( buff.size() != 0 ){
        print_event_all(buff);
    }
}
