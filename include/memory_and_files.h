/**
* @file memory_and_files.h
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
*
* @brief A header file that provides utility functions for allocating, reallocating, and freeing memory in addition to files.
*
* This header file contains a collection of functions designed to facilitate the implementation of requested features
* for dynamic memory and files
* in a C program. Includes functions to allocate, reallocate and free memory for users, equipment and maintenance,
* as well as files to save data and retrieving data from files to the program memory.
*/

#ifndef MEMORY_AND_FILES_H
#define MEMORY_AND_FILES_H

#include "types.h"

#define INITIAL_SIZE_USERS 5 // initial quantity of users to be allocated
#define INITIAL_SIZE_EQUIPMENT 5 // initial quantity of equipment to be allocated
#define INITIAL_SIZE_MAINTENANCE 3 // initial quantity of maintenance to be allocated

#define FILENAME_USERS "users.bin" // user binary file name
#define FILENAME_EQUIPMENT "equipment.bin" // equipment binary file name
#define FILENAME_LOGS "logs.txt" // text file name recording the options chosen by the user when navigating the application menus

#define ERROR_OPEN_FILE "\nError opening the file."
#define ERROR_SAVE_FILE "\nError saving data to file."
#define ERROR_CORRUPTED_FILE "\nWarning: the data file seems to be incomplete. Only the valid records were loaded."
#define ERROR_ALLOC_EQUIPMENT "\nFailed to allocate memory for equipment."
#define ERROR_REALLOC_EQUIPMENT "\nFailed to reallocate memory for equipment."
#define ERROR_ALLOC_MAINTENANCE "\nFailed to allocate memory for maintenance."
#define ERROR_REALLOC_MAINTENANCE "\nFailed to reallocate memory for maintenance."
#define ERROR_ALLOC_USERS "\nFailed to allocate memory for users."
#define ERROR_REALLOC_USERS "\nFailed to reallocate memory for users."


/**
 * @brief Loads equipment data from a binary file into the EquipmentList structure.
 *
 * This function is used to read and load equipment and maintenance data from the file into the program memory.
 * If the file does not exist yet (first execution) or is empty, the list is initialised empty
 * instead of aborting the program.
 *
 * @param equipment A pointer to struct: EquipmentList.
 * @param filename The name of the binary file containing the equipment data.
 */
void loadEquipment(EquipmentList *equipment, const char *filename);

/**
 * @brief Expands equipment maintenance history.
 *
 * This function is used to double the memory for the maintenance history of one equipment whenever necessary.
 *
 * @param equipment The equipment whose history is full.
 */
void expandMaintenance(Equipment *equipment);

/**
 * @brief Saves equipment data, including maintenance history, to a binary file.
 *
 * This function is used to write equipment and maintenance data to a binary file.
 *
 * @param equipment A pointer to struct: EquipmentList.
 * @param filename The name of the binary file to which the equipment data will be saved.
 * @return 1 on success, 0 if the file could not be opened for writing.
 */
int saveEquipment(const EquipmentList *equipment, const char *filename);

/**
 * @brief Expands the storage space for equipment in the EquipmentList structure.
 *
 * This function is used to double the memory for equipment whenever necessary.
 *
 * @param equipment A pointer to struct: EquipmentList.
 */
void expandEquipment(EquipmentList *equipment);

/**
 * @brief Frees the memory allocated for equipment.
 *
 * This function is used to free the memory allocated for equipment at the end of the program.
 *
 * @param equipment A pointer to struct: EquipmentList.
 */
void freeEquipment(EquipmentList *equipment);

/**
 * @brief Loads user data from a binary file into the UserList structure.
 *
 * This function is used to read and load user data from the file into the program memory.
 * This function is also responsible for allocating memory for users when necessary,
 * such as when the file is empty.
 *
 * @param users A pointer to struct: UserList.
 * @param filename The name of the binary file containing user data.
 */
void loadUsers(UserList *users, const char *filename);

/**
 * @brief Saves user data from the UserList structure to a binary file.
 *
 * This function is used to write users data to a binary file.
 *
 * @param users A pointer to struct: UserList.
 * @param filename The name of the binary file where user data will be saved.
 * @return 1 on success, 0 if the file could not be opened for writing.
 */
int saveUsers(const UserList *users, const char *filename);

/**
 * @brief Expands the capacity of the users.
 *
 * This function is used to double the memory for users whenever necessary.
 *
 * @param users A pointer to struct: UserList.
 */
void expandUsers(UserList *users);

/**
 * @brief Frees the memory allocated for users.
 *
 * This function is used to free the memory allocated for users at the end of the program.
 *
 * @param users A pointer to struct: UserList.
 */
void freeUsers(UserList *users);

/**
 * @brief Frees the memory allocated for maintenance.
 *
 * This function is used to free the memory allocated for maintenance at the end of the program.
 *
 * @param equipment A pointer to struct: EquipmentList.
 */
void freeMaintenance(Equipment *equipment);

#endif /* MEMORY_AND_FILES_H */

