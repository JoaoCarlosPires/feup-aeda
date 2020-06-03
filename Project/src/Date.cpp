#include <sstream>
#include <iomanip>
#include "Date.h"

using namespace std;

Date::Date(){}
Date::Date(string date)
{

    stringstream date_info(date);
    string temp;
    vector<string> date_temp;

    while (getline(date_info, temp, '/')) {
        date_temp.push_back(temp);
    }

    day = stoi(date_temp[0]);
    month = stoi(date_temp[1]);
    year = stoi(date_temp[2]);

}

Date::Date(unsigned short day, unsigned short month, unsigned year):day(day), month(month), year(year){}

unsigned short Date::getDay() const
{
    return day;
}


unsigned short Date::getMonth() const
{
    return month;
}

unsigned Date::getYear() const
{
    return year;
}

string Date::getDate() const {
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}


void Date::setDay(unsigned short day)
{
    this->day = day;
}
void Date::setMonth(unsigned short month)
{
    this->month = month;
}
void Date::setYear(unsigned year)
{
    this->year = year;
}
bool Date::isEqualTo(const Date & date)
{
    return date.getYear() == year && date.getMonth() == month && date.getDay() == day;
}

bool Date::isAfter(const Date &date)
{
    if (year > date.year) return true;
    if (year == date.year && month > date.month) return true;
    return year == date.year && month == date.month && day > date.day;
}

bool Date::isBefore(const Date &date)
{
    if (year < date.year) return true;
    if (year == date.year && month < date.month) return true;
    return year == date.year && month == date.month && day < date.day;
}


ostream& operator<<(ostream& out, const Date &date)
{
    out << date.getDay() << '/' << date.getMonth() << '/' << date.getYear();
    return out;
}

istream& operator>>(istream& in, Date &date)
{
    int monthDays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int this_year, this_month, this_day;
    cout << "Year:";
    in >> this_year;
    in.ignore(1000,'\n');
    while (in.fail() || this_year < 0 || this_year > 9999)
    {
        if (in.fail()){
            in.clear();
            in.ignore();
            in.ignore(1000, '\n');
        }
        cout << "Not a valid number or year. Please reenter: ";
        in >> this_year;
    }
    cout << "Month:";
    in >> this_month;
    in.ignore(1000,'\n');
    while (cin.fail() || this_month < 1 || this_month > 12)
    {
        if (in.fail()){
            in.clear();
            in.ignore();
            in.ignore(1000, '\n');
        }
        cout << "Not a valid number or month. Please reenter: ";
        in >> this_month;
    }
    cout << "Day:";
    in >> this_day;
    in.ignore(1000,'\n');
    while (in.fail() || this_day < 1 || this_day > monthDays[this_month-1])
    {
        if (in.fail()){
            in.clear();
            in.ignore();
            in.ignore(1000, '\n');
        }
        cout << "Not a valid number or number. This month only have " << monthDays[this_month-1] << " days. Please reenter: ";
        in >> this_day;
    }

    date.year = this_year;
    date.month = this_month;
    date.day = this_day;

    return in;
}

int Date::daysUntil(const Date &date) const {
    int monthDays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    long int n1 = year*365 + day;

    for (int i=0; i< month - 1; i++)
        n1 += monthDays[i];

    long int n2 = date.getYear()*365 + date.getDay();

    for (int i=0; i<date.getMonth() - 1; i++)
        n2 += monthDays[i];
    return n2 - n1;
}





