
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Date {
    int day;
    string month;
    int year;
};

int IsYearLeap(int y) {
    bool c1 = y % 400 == 0;
    bool c2 = (y % 4 == 0) && (y % 100 != 0);
    if (c1 || c2) {
        return 1;
    } else {
        return 0;
    }
}

int NumberOfLeapYears(int y) {
    int leaps = (y - 1980) / 4;
    if (IsYearLeap(y)) {
        return leaps;
    } else if (y == 2100) {
        return leaps;
    }
    return leaps+1;
}


int GetNumberOfDaysFromTheStartOfTheYear(const Date& d) {
    if (d.month == "January") {
        return d.day;
    } else if ( d.month == "February") {
        return d.day + 31;
    }
    else if ( d.month == "March") {
        return d.day + 59 + IsYearLeap(d.year);
    } 
    else if ( d.month == "April") {
        return d.day + 90 + IsYearLeap(d.year);
    } 
    else if ( d.month == "May") {
        return d.day + 120 + IsYearLeap(d.year);
    } 
    else if ( d.month == "June") {
        return d.day + 151 + IsYearLeap(d.year);
    } 
    else if ( d.month == "July") {
        return d.day + 181 + IsYearLeap(d.year);
    } 
    else if ( d.month == "August") {
        return d.day + 212 + IsYearLeap(d.year);
    }
    else if ( d.month == "September") {
        return d.day + 243 + IsYearLeap(d.year);
    }
    else if ( d.month == "October") {
        return d.day + 273 + IsYearLeap(d.year);
    } 
    else if ( d.month == "November") {
        return d.day + 304 + IsYearLeap(d.year);
    } 
    else if ( d.month == "December") {
        return d.day + 334 + IsYearLeap(d.year);
    } 
    else {
        return 0;
    }
}

int DaysFromStart(const Date d) {
    int ys = d.year - 1980;
    if (d.year == 1980) {
        return GetNumberOfDaysFromTheStartOfTheYear(d);
    } 
    return ys * 365 + NumberOfLeapYears(d.year) + GetNumberOfDaysFromTheStartOfTheYear(d);
}

string GetNameOfTheDay(int d) {
    switch(d % 7) {
        case 0: {
            return "Monday";
        } case 1: {
            return "Tuesday";
        } case 2: {
            return "Wednesday";
        } case 3: {
            return "Thursday";
        } case 4: {
            return "Friday";
        } case 5: {
            return "Saturday";
        } case 6: {
            return "Sunday";
        } default: {
            return "Monday";
        }
    }
}

int main(int argc, char const *argv[]){
    ifstream in("input.txt");
    ofstream out("output.txt");
    int iters;
    in >> iters;
    for (int i = 0; i < iters; i++) {
        Date d;
        in >> d.day >> d.month >> d.year;
        out << GetNameOfTheDay(DaysFromStart(d)) << endl;
    }
    return 0;
}