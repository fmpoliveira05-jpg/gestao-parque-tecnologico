/**
* @file input.h
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
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

#define EQUIPMENT_NAME_MAX_LENGTH 50
#define EQUIPMENT_CATEGORY_MAX_LENGTH 18
#define MAINTENANCE_TYPE_MAX_LENGTH 40
#define MAINTENANCE_NOTES_MAX_LENGTH 100
#define USER_ACRONYM_MAX_LENGTH 10
#define USER_ROLE_MAX_LENGTH 40
#define USERNAME_MAX_LENGTH 50
#define CATEGORY_OPTIONS 12 // number of initialized categories to be assigned to equipment

#define INVALID_VALUE "The value entered is invalid." // message displayed when the number entered by the user is out of range of the function

#define LOAD_EQUIPMENT_DATA ".\n..\n...\nThe equipment data has been loaded."
#define LOAD_USERS_DATA ".\n..\n...\nThe users data has been loaded."
#define SAVE_DATA ".\n..\n..\nAll changes have been saved."

#define MSG_GET_OPTION "Choose an option: "
#define SPACER "\n-------------------------------------------------------------------------------------------------------------\n\n"


typedef enum {
    INACTIVE, ACTIVE
} UserStatus;

typedef enum {
    OPERATIONAL = 1, UNDER_MAINTENANCE, N_OPERATIONAL, FOR_RECYCLING
} EquipmentStatus;

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int id;
} Id;

typedef struct {
    char maintenanceType[MAINTENANCE_TYPE_MAX_LENGTH];
    char notes[MAINTENANCE_NOTES_MAX_LENGTH];
    int movementNumber; // equipment maintenance movement number (must be unique)
    Date date; // equipment maintenance date
} Maintenance;

typedef struct {
    int maintenanceCount; // quantity of existing maintenance (initialized with 0)
    int maintenanceSize; // quantity of maintenance allocated (initialized with INITIAL_SIZE_MAINTENANCE)
    Maintenance *maintenance; // pointer for allocated maintenance
} MaintenanceHistory;

typedef struct {
    char equipmentName[EQUIPMENT_NAME_MAX_LENGTH]; // equipment name (must be unique)
    char category[EQUIPMENT_CATEGORY_MAX_LENGTH];
    Id equipmentId;
    Id userId; // user ID assigned to the technological equipment
    Date date; // equipment acquisition date
    EquipmentStatus equipmentStatus;
    MaintenanceHistory maintenanceHistory;
} Equipment;

typedef struct {
    int equipmentCount; // quantity of existing equipment (initialized with 0)
    int equipmentSize; // quantity of equipment allocated (initialized with INITIAL_SIZE_EQUIPMENT)
    int nextEquipmentId; // control variable for the ID of each equipment
    Equipment *equipment; // pointer for allocated equipment
} EquipmentList;

typedef struct {
    char acronym[USER_ACRONYM_MAX_LENGTH]; // user acronym (must be unique)
    char username[USERNAME_MAX_LENGTH];
    char role[USER_ROLE_MAX_LENGTH];
    Id userId;
    UserStatus userStatus;
} User;

typedef struct {
    int userCount; // quantity of existing users (initialized with 0)
    int userSize; // quantity of users allocated (initialized with INITIAL_SIZE_USERS)
    int nextUserId; // control variable for the ID of each user
    User *users; // pointer for allocated users
} UserList;


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
* @brief This function prompts the user to input two dates and compare them.
* @param date1 Variable that saves the first date.
* @param date2 Variable that saves the second date.
* @return -1 if date1 < date2, 1 if date1 > date2, 0 if date1 == date2.
*/
int compareDates(Date date1, Date date2);

/**
* @brief This function prompts the user to input an character and displays a custom message.
* @param msg A custom message to prompt the user for input.
* @return the user-provided character already validated: 'y', 'Y', 'n', 'N'.
*/
char getChar(char *msg);

#endif /* INPUT_H */

