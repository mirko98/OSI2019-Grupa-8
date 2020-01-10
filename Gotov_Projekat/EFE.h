#pragma once
#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>
#include <ctime>
#include <fstream>
#include <map>
#include <conio.h>
#include <algorithm>

using std::cin;
using std::string;
using std::endl;
using std::cout;
using std::vector;
using std::map;
using std::ifstream;
using std::max;

/*=================== STRUKTURE ==================*/

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
    EVENT();

    /*------ VRACA DANASNJU GODINU ------*/
    int current_year();

    /*------ VRACA DANASNJI MJESEC ------*/
    int current_month();

    /*------ VRACA DANASNJI DAN ------*/
    int current_day();

    /*------ PROVJERA DANA ------*/
    bool flag_day();

    /*------ PROVJERA MJESECA ------*/
    bool flag_month();

    /*------ PROVJERA GODINE ------*/
    bool flag_year();

    /*------ PROVJERA DATUMA(da li je datum buduci) ------*/
    bool flag_date();

    /*------ PROVJERA MINUTA ------*/
    bool flag_mi();

    /*------ PROVJERA CASOVA ------*/
    bool flag_hh();
};


struct QUESTION{
    string question;
    string ans[3];
    int result;
    int user_ans;
};

struct ADMIN{
    char name[100];
    char password[100];
};

/*============= SPOREDNE FUNKCIJE ===========*/

bool sortby_time(const EVENT &, const EVENT &);
bool sortby_name(const EVENT &, const EVENT &);
bool sortby_location(const EVENT &, const EVENT &);
bool sortby_type(const EVENT &, const EVENT &);

void sort_event(vector <EVENT> &);

void help();

int convert_string(string &);

void print_text(string );

int get_minute();

int get_hours();

bool check_admin_login(string &);

bool admin_acess();

/*

new_event.dd = 9999 da znam da je iz add_event izaslo na EXIT nacin i da mod_event treba da se vrati na main

*/

/*=================== SZAP ==================*/

EVENT add_event(int);
void mod_event(vector <EVENT> &);
void delete_event(const vector <EVENT> &);
void add_type();
void delete_type();

/*=================== SZPI ==================*/

void input_all(vector <EVENT> &);
void quiz();
void input_comment(vector <EVENT> &);
void print_event_all(const vector <EVENT> &);
void print_event_past(const vector <EVENT> &);
void print_event_today(const vector <EVENT> &);
void print_event_category(const vector <EVENT> &, string &);
void print_event_future(const vector <EVENT> &);


