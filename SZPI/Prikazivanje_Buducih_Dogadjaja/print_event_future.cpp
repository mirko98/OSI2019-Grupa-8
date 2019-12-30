void print_event_future(const vector <EVENT> &niz){
    cout<<"DOGADJAJI KOJI CE SE DESITI: "<<endl<<endl;

    vector <EVENT> buff;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];

        int c_mi = get_minute();
        int c_h = get_hours();
        int c_day = new_event.current_day();
        int c_month = new_event.current_month();
        int c_year = new_event.current_year();

        if ( c_year < new_event.yy ){
            buff.push_back(new_event);
        }else if ( c_year == new_event.yy ){
            if ( c_month < new_event.mm ){
                buff.push_back(new_event);
            }else if ( c_month == new_event.mm ){
                if ( c_day < new_event.dd ){
                    buff.push_back(new_event);
                }else if ( c_day == new_event.dd ){
                    if ( c_h < new_event.hh ){
                        buff.push_back(new_event);
                    }else if ( c_h == new_event.hh ){
                        if ( c_mi < new_event.mi ){
                            buff.push_back(new_event);
                        }
                    }
                }
            }
        }
    }

    if ( buff.size() != 0 ){
        print_event_all(buff);
    }
}
