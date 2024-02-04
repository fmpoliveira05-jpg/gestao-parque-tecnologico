/**
* @file input.c
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A source file providing utility functions for user input validation and retrieval.
*
* This source file contains a collection of functions designed to facilitate user input
* in a C program. It includes functions for obtaining integers,
* characters, and strings from the user while performing input validation to ensure
* that the entered values are within specified ranges or constraints.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "input.h"
#include "users.h"
#include "equipment.h"


void additionalInformationAboutProgram() {
    puts("\nADDITIONAL INFORMATION:");
    puts("\n- By default, the equipment are OPERATIONAL and users are ACTIVE;");
    puts("- Only equipment UNDER MAINTENANCE can be maintained;");
    puts("- INACTIVE users are NOT included in lists;");
    puts("- INACTIVE users mustn't be removed;");
    printf("Press \"ENTER\" to continue...  ");
    cleanInputBuffer();
    
    puts("\n- INACTIVE users are automatically disconnected from their devices;");
    puts("- There mustn't be 2 users with the same acronym;");
    puts("- There mustn't be 2 equipment with the same name;");
    puts("- It is not possible to change the status of FOR RECYCLING equipment.");
}

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void logMessage(char *msg, char *filename) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d - %s\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, msg);
    fclose(fp);
}

void readString(char *string, unsigned int size, char *msg) {
    do {
        printf(msg);
        if (fgets(string, size, stdin) != NULL) {
            unsigned int len = strlen(string) - 1;
            if (string[len] == '\n') {
                string[len] = '\0';
            } else {
                cleanInputBuffer();
            }
        }
        if (strlen(string) == 0) {
            puts("\nRequired field.");
        }
    } while (strlen(string) == 0);
}

int getInt(int minValue, int maxValue, char *msg) {
    int value;
    printf(msg);
    while (scanf("%d", &value) != 1 || value < minValue || value > maxValue) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return value;
}

int compareDates(Date date1, Date date2) {
    if (date1.year < date2.year) {
        return -1;
    } else if (date1.year > date2.year) {
        return 1;
    } else {
        if (date1.month < date2.month) {
            return -1;
        } else if (date1.month > date2.month) {
            return 1;
        } else {
            if (date1.day < date2.day) {
                return -1;
            } else if (date1.day > date2.day) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

char getChar(char *msg) {
    char value;
    do {
        printf(msg);
        value = getchar();
        cleanInputBuffer();
        if (value != 'n' && value != 'N' && value != 'y' && value != 'Y') {
            puts("\nInvalid input.");
        }
    } while (value != 'n' && value != 'N' && value != 'y' && value != 'Y');
    return value;
}
