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

        void GetDigits(const DateTime& date);
};


#endif