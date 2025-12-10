#include <Arduino.h>
#include <RTClib.h>
#include "utils/date_time_helper.h"

/// @brief Checks to see if the given year is a leap year
/// @param year Positive integer, representing the year to check
/// @return Boolean value - Whether the year is a leap year or not
bool DateTimeHandler::IsLeapYear(int year) {
    // Leap year must be divisible by 4 but NOT divisible by 100, unless it is divisible by 400
    // e.g. (divisible by 4 AND NOT divisble by 100) OR (divible by 400) so:
    return ((year % 4 == 0) && !(year % 100 == 0)) || (year % 400 == 0);
}

/// @brief Gets the number of days in a given month, accounds for leap years
/// @param month The month which you would like to know the amount of days
/// @param year The year, given to account for leap years
/// @return The number of days in the given month
int DateTimeHandler::CheckDays(int month, int year) {
    bool is_leap_year = IsLeapYear(year);
    int days_in_months[12] = {31, is_leap_year ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days_in_months[month - 1];
}

/// @brief Gets the individual digits from a DateTime object, as in minute_1, minute_2, etc. Can be accessed through the initalised class 
/// @param date DateTime value
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

/// @brief Takes in regular integer values and splits them into digit variables that can be publically accessed from the class
/// @param mm Minutes e.g. 21 
/// @param hh Hours e.g. 51
/// @param DD Day of the Month e.g. 12 
/// @param MM Month e.g. 10
/// @param YYYY Year e.g. 2025
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

/// @brief Joins the digits stored in the class' variables to form full integers, can be used for the construction of DateTime objects
void DateTimeHandler::JoinDigits() {
    minutes = (minute_1 * 10) + minute_2;
    hours = (hour_1 * 10) + hour_2;
    day = (day_1 * 10) + day_2;
    month = (month_1*10) + month_2;
    year = (year_1*1000) + (year_2*100) + (year_3*10) + year_4;
}