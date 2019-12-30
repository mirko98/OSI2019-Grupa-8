void print_event_category(const vector <EVENT> &niz, string &type){
    cout<<"DOGADJAJI KATEGORIJE "<<type<<" SU: "<<endl<<endl;
 
    vector <EVENT> buff;
    for (unsigned int i=0;i<niz.size();i++){
        EVENT new_event = niz[i];
 
        if ( new_event.type == type ){
            buff.push_back(new_event);
        }
    }
 
    if ( buff.size() != 0 ){
        print_event_all(buff);
    }
}
