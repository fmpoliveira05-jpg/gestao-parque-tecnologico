/**
* @file input.h
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
*
* @brief A header file providing utility functions for user input validation and retrieval.
*
* This header file contains a collection of functions designed to facilitate user input
* in a C program. It includes functions for obtaining integers,
* characters, and strings from the user while performing input validation to ensure
* that the entered values are within specified ranges or constraints.
*/

#ifndef INPUT_H
#define INPUT_H

#include "types.h"

#define INVALID_VALUE "The value entered is invalid." // message displayed when the number entered by the user is out of range of the function
#define LOAD_EQUIPMENT_DATA ".\n..\n...\nThe equipment data has been loaded."
#define LOAD_USERS_DATA ".\n..\n...\nThe users data has been loaded."
#define SAVE_DATA ".\n..\n..\nAll changes have been saved."
#define MSG_GET_OPTION "Choose an option: "
#define SPACER "\n-------------------------------------------------------------------------------------------------------------\n\n"



/**
* @brief This function is used to display some important additional information about the program.
*/
void additionalInformationAboutProgram();

/**
* @brief This function is used to clean the keyboard buffer.
*/
void cleanInputBuffer();

/**
* @brief This function is used to save the directory history in a file that the user scrolls through in the menus of the program.
* @param msg A custom message to prompt the user for input.
* @param filename The name of the log file.
*/
void logMessage(char *msg, char *filename);

/**
* @brief This function prompts the user to input a string and displays a custom message.
* @param string A pointer to the string to be read.
* @param size The maximum length of the string.
* @param msg A custom message to prompt the user for input.
*/
void readString(char *string, unsigned int size, char *msg);

/**
* @brief This function prompts the user to input an integer within a specified range and displays a custom message.
* @param minValue The minimum valid integer value.
* @param maxValue The maximum valid integer value.
* @param msg A custom message to prompt the user for input.
* @return the user-provided integer value within the specified range: minValue <= inputValue <= maxValue.
*/
int getInt(int minValue, int maxValue, char *msg);


/**
* @brief This function prompts the user to input an character and displays a custom message.
* @param msg A custom message to prompt the user for input.
* @return the user-provided character already validated: 'y', 'Y', 'n', 'N'.
*/
char getChar(char *msg);

#endif /* INPUT_H */

