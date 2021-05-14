#include <iostream>
#include "Date.h"

using namespace std;

Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(const Date& date)
{
    day = date.day;
    month = date.month;
    year = date.year;
}

Date& Date::operator= (const Date& date)
{
    if (this == &date) return *this;
    day = date.day;
    month = date.month;
    year = date.year;
    return *this;
}


bool Date::operator==(const Date& d)
{
    return (day == d.day) && (month == d.month) && (year == d.year); 
}

//output format: 01-02-2016
ostream &operator<<(ostream& left, const Date& ob)
{
    int day_i = ob.get_day();
    string day_str = to_string(day_i);
    int month_i = ob.get_month();
    string month_str = to_string(month_i);
    int year_i = ob.get_year();
    string year_str = to_string(year_i);

    left << ((day_str.length()==1) ? "0" + day_str : day_str ) << "-" 
        << ((month_str.length()==1) ? "0" + month_str : month_str ) << "-" 
        << ((year_str.length()==1) ? "0" + year_str : year_str );
        
    return left;
}


bool Date::operator<(const Date& d)
{
    if (year < d.get_year()) {

        return true;
    }
    else if (year > d.get_year()) {
        return false;
    }
    else {  //same year
        if (month < d.get_month()) {
            return true;
        }
        else if (month > d.get_month()) {
            return false;
        }
        else { //same month
            if (day < d.get_day())
                return true;
            else 
                return false;
        }
        
    }

}


bool Date::operator>(const Date& dat)
{
    if (*this == dat)
        return false;

    if (*this < dat)
        return false;

    return true;
}


bool Date::operator>=(const Date& d)
{
    if (*this == d)
        return true;
    
    if (*this > d)
        return true;

    return false;

}


bool Date::operator<=(const Date& d)
{
    if (*this == d)
        return true;

    if (*this < d)
        return true;
        
    return false;
}



void Date::print()
{
    cout << day << "-" << month << "-" << year;
}
