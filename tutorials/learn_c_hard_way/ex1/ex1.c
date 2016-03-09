
#include <stdio.h>

int get_days_in_month( int month, int year ) {
    if ( month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ) {
        return 31;
    } else if ( month == 4 || month == 6 || month == 9 || month == 11 ) {
        return 30;
    } else if ( month == 2 && year % 4 == 0 ) {
        return 29;
    } else if ( month == 2 && year % 4 != 0 ) {
        return 28;
    } else {
        return -1;
    }
}

int main( int argc, char* argv[] ) {
    int year, month, day;
    int day_of_week = 4;
    for ( year=1994; year<=1995; year++ ) {
        for ( month=1; month<=12; month++ ) {
            for ( day=1; day<=get_days_in_month( month, year ); day++ ) {
                if ( day == 1 ) {
                    int tab;
                    for ( tab=1; tab<day_of_week-1; tab++ ) {
                        printf( "   " );
                    }
                }
                printf("%.2i ", day );
                if ( day_of_week > 7 ) {
                    day_of_week = 1;
                    printf("\n");
                }
                day_of_week++;
            }
            printf("\n\n");
        }
    }
    return 0;
}
