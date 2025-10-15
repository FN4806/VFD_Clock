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
    year_3 = floor((date.year()%100)-year_4);
}