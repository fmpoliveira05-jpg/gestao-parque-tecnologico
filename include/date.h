/**
 * @file date.h
 * @author Francisco Miguel Pereira Oliveira
 * @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
 *
 * @brief Date helpers: validation, comparison and interactive reading.
 *
 * Dates were previously read field by field in several places, and impossible
 * dates such as 31/02 were accepted. Centralising the logic here keeps the
 * validation rules in a single spot.
 */

#ifndef DATE_H
#define DATE_H

#include "types.h"

#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_YEAR 1990

#define ERROR_INVALID_DATE "\nThat date does not exist or is in the future. Please try again."

/**
 * @brief Compares two dates chronologically.
 * @param date1 First date.
 * @param date2 Second date.
 * @return -1 if date1 < date2, 1 if date1 > date2, 0 if they are equal.
 */
int compareDates(Date date1, Date date2);

/**
 * @brief Tells whether a year is a leap year in the Gregorian calendar.
 * @param year Year to check.
 * @return 1 if it is a leap year, 0 otherwise.
 */
int isLeapYear(int year);

/**
 * @brief Checks whether a date exists in the calendar (e.g. rejects 31/04 and 29/02/2023).
 * @param date Date to validate.
 * @return 1 if the date is valid, 0 otherwise.
 */
int isValidDate(Date date);

/**
 * @brief Returns today's date according to the system clock.
 * @return The current date.
 */
Date getCurrentDate(void);

/**
 * @brief Reads a date from the keyboard, repeating until it is valid and not in the future.
 * @param label Word used in the prompts (e.g. "acquisition" or "maintenance").
 * @return The date typed by the user.
 */
Date readDate(const char *label);

#endif /* DATE_H */
