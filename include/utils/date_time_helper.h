#ifndef DATE_TIME_HELPER_H
#define DATE_TIME_HELPER_H

#include <RTClib.h>

class DateTimeHandler {
    public:
        int minute_1;
        int minute_2;
        int hour_1;
        int hour_2;
        int day_1;    
        int day_2;
        int month_1;
        int month_2;
        int year_1;
        int year_2;
        int year_3;
        int year_4;

        int minutes;
        int hours;
        int day;
        int month;
        int year;

        void GetDigits(const DateTime& date);
        // Setting to zero in the initial decleration means that each parameter is optional and does not HAVE to be parsed 
        // since it will default the value to 0 
        void GetDigitsByPart(const int& mm = 0, const int& hh = 0, const int& DD = 0, const int& MM = 0, const int& YYYY = 0);
        
        void JoinDigits();
};


#endif