/**
* @file input.c
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
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
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * @brief Terminates the program cleanly when standard input is closed (e.g. Ctrl+D / Ctrl+Z).
 *
 * Without this check the input loops below would spin forever once stdin reaches EOF.
 */
static void exitOnEndOfInput(void) {
    if (feof(stdin)) {
        puts("\nEnd of input reached. Exiting without saving.");
        exit(EXIT_FAILURE);
    }
}

void logMessage(char *msg, char *filename) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        return; /* logging is best-effort: never abort the program because of it */
    }
    fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d - %s\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, msg);
    fclose(fp);
}

void readString(char *string, unsigned int size, char *msg) {
    do {
        fputs(msg, stdout);
        if (fgets(string, (int) size, stdin) == NULL) {
            exitOnEndOfInput();
            string[0] = '\0';
        } else {
            size_t len = strlen(string);
            if (len > 0 && string[len - 1] == '\n') {
                string[len - 1] = '\0';
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
    fputs(msg, stdout);
    while (scanf("%d", &value) != 1 || value < minValue || value > maxValue) {
        exitOnEndOfInput();
        puts(INVALID_VALUE);
        cleanInputBuffer();
        fputs(msg, stdout);
    }
    cleanInputBuffer();
    return value;
}

char getChar(char *msg) {
    int value;
    do {
        fputs(msg, stdout);
        value = getchar();
        if (value == EOF) {
            exitOnEndOfInput();
        }
        if (value != '\n') {
            cleanInputBuffer();
        }
        if (value != 'n' && value != 'N' && value != 'y' && value != 'Y') {
            puts("\nInvalid input.");
        }
    } while (value != 'n' && value != 'N' && value != 'y' && value != 'Y');
    return (char) value;
}
