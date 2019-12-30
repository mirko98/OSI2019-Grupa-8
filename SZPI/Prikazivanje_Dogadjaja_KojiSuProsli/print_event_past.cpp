void print_event_past(const vector <EVENT> &niz){
    cout<<"DOGADJAJI KOJI SU PROSLI: "<<endl<<endl;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];

        int c_mi = get_minute();
        int c_h = get_hours();
        int c_day = new_event.current_day();
        int c_month = new_event.current_month();
        int c_year = new_event.current_year();

        vector <EVENT> buff;
        buff.push_back(new_event);

        if ( c_year > new_event.yy ){
            print_event_all(buff);
        }else if ( c_year == new_event.yy ){
            if ( c_month > new_event.mm ){
                print_event_all(buff);
            }else if ( c_month == new_event.mm ){
                if ( c_day > new_event.dd ){
                    print_event_all(buff);
                }else if ( c_day == new_event.dd ){
                    if ( c_h > new_event.hh ){
                        print_event_all(buff);
                    }else if ( c_h == new_event.hh ){
                        if ( c_mi > new_event.mi ){
                            print_event_all(buff);
                        }
                    }
                }
            }
        }
    }
}
