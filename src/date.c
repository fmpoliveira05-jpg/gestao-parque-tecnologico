/**
 * @file date.c
 * @author Francisco Miguel Pereira Oliveira
 * @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
 *
 * @brief Implementation of the date helpers declared in date.h.
 */

#include <stdio.h>
#include <time.h>
#include "date.h"
#include "input.h"

int compareDates(Date date1, Date date2) {
    if (date1.year != date2.year) {
        return date1.year < date2.year ? -1 : 1;
    }
    if (date1.month != date2.month) {
        return date1.month < date2.month ? -1 : 1;
    }
    if (date1.day != date2.day) {
        return date1.day < date2.day ? -1 : 1;
    }
    return 0;
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int isValidDate(Date date) {
    static const int daysInMonth[MAX_MONTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay;

    if (date.year < MIN_YEAR || date.month < MIN_MONTH || date.month > MAX_MONTH || date.day < MIN_DAY) {
        return 0;
    }
    maxDay = daysInMonth[date.month - 1];
    if (date.month == 2 && isLeapYear(date.year)) {
        maxDay = 29;
    }
    return date.day <= maxDay;
}

Date getCurrentDate(void) {
    Date today;
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    today.day = local->tm_mday;
    today.month = local->tm_mon + 1;
    today.year = local->tm_year + 1900;
    return today;
}

Date readDate(const char *label) {
    char prompt[80];
    Date date;
    Date today = getCurrentDate();

    do {
        snprintf(prompt, sizeof prompt, "Enter the day of %s: ", label);
        date.day = getInt(MIN_DAY, MAX_DAY, prompt);
        snprintf(prompt, sizeof prompt, "Enter the month of %s: ", label);
        date.month = getInt(MIN_MONTH, MAX_MONTH, prompt);
        snprintf(prompt, sizeof prompt, "Enter the year of %s: ", label);
        date.year = getInt(MIN_YEAR, today.year, prompt);

        if (!isValidDate(date) || compareDates(date, today) > 0) {
            puts(ERROR_INVALID_DATE);
        }
    } while (!isValidDate(date) || compareDates(date, today) > 0);

    return date;
}
