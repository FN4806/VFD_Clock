#include <Arduino.h>
#include <RTClib.h>
#include "utils/date_time_helper.h"


void DateTimeHandler::GetDigits(const DateTime& date) {
    minute_1 = floor(date.minute() / 10);
    minute_2 = date.minute() % 10;

    hour_1 = floor(date.hour() / 10);
    hour_2 = date.hour() % 10;

    day_1 = floor(date.day() / 10);
    day_2 = date.day() % 10;

    month_1 = floor(date.month()/10);
    month_2 = date.month() % 10;

    year_1 = floor(date.year()/1000);
    year_2 = floor((date.year() - (year_1*1000))/100);
    year_4 = date.year() % 10;
    year_3 = floor(((date.year()%100)-year_4)/10);
}

void DateTimeHandler::GetDigitsByPart(const int& mm, const int& hh, const int& DD, const int& MM, const int& YYYY) {
    minute_1 = floor(mm / 10);
    minute_2 = mm % 10;

    hour_1 = floor(hh / 10);
    hour_2 = hh % 10;

    day_1 = floor(DD / 10);
    day_2 = DD % 10;

    month_1 = floor(MM/10);
    month_2 = MM % 10;

    year_1 = floor(YYYY/1000);
    year_2 = floor((YYYY - (year_1*1000))/100);
    year_4 = YYYY % 10;
    year_3 = floor(((YYYY%100)-year_4)/10);
}

void DateTimeHandler::JoinDigits() {
    minutes = (minute_1 * 10) + minute_2;
    hours = (hour_1 * 10) + hour_2;
    day = (day_1 * 10) + day_2;
    month = (month_1*10) + month_2;
    year = (year_1*1000) + (year_2*100) + (year_3*10) + year_4;
}