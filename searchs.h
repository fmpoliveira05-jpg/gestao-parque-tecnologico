/**
* @file searchs.h
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A header file that provides utility functions for searches.
*
* This header file contains a collection of functions designed to facilitate the implementation of requested features
* for research
* in a C program. Includes functions to search equipment by status and acquisition date, search by ID, search for a user by,
* acronym, search for the maintenance movement number, among others.
*/

#ifndef SEARCHS_H
#define SEARCHS_H

#define MSG_GET_EQUIPMENT_POSITION_TO_VIEW_HISTORY "Enter the position of the Equipment to view its maintenance history: " // // referring to the equipment position in the listing

#define ERROR_VIEW_EQUIPMENT_MAINTENANCE_HISTORY "\nIt is not possible to list the maintenance history of FOR RECYCLING equipment."
#define ERROR_USER_NOT_FOUND "\nThe user does not exist."
#define EMPTY_EQUIPMENT_MAINTENANCE_HISTORY "\nThe history is empty for now!"


/**
 * @brief Searches and displays equipment based on its status and acquisition date.
 *
 * This function is used to search for equipment by status and date of acquisition and prints the number of results found.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 * @param status A variable to search for the status of equipment.
 * @param day A variable to search for the day of acquisition of equipment.
 * @param month A variable to search for the month of acquisition of equipment.
 * @param year A variable to search for the year of acquisition of equipment.
 */
void searchEquipmentFromStatusAndDate(EquipmentList equipment, int status, int day, int month, int year);

/**
 * @brief Initiates a search for equipment based on user-provided criteria.
 *
 * This function is used to read the status and acquisition date of a certain equipment, in order to be searched
 * in the "searchEquipmentFromStatusAndDate" function.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 */
void searchEquipment(EquipmentList equipment);

/**
 * @brief Searches for equipment in the EquipmentList based on the provided equipment ID.
 *
 * This function is used to check whether there is any equipment with the ID entered by the user.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 * @param id The equipment ID to search for in the equipment list.
 *
 * @return the index of the equipment if a matching equipment ID is found;
 * -1 to indicate that no matching equipment was found, otherwise.
 */
int searchEquipmentFromId(EquipmentList equipment, int id);

/**
 * @brief Searches for a specific movement number in the maintenance history of all equipment.
 *
 * This function is used to check whether there is any maintenance with the movement number entered by the user.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 * @param movementNumber The movement number to search for in the maintenance history.
 *
 * @return 1 if a matching movement number is found;
 * -1 to indicate that no matching movement number was found, otherwise.
 */
int searchForMovementNumber(EquipmentList equipment, int movementNumber);

/**
 * @brief Searches for a user in the UserList based on the provided acronym.
 *
 * This function is used to check if there is a user with the acronym entered by the user.
 *
 * @param users A variable that accesses a struct: UserList.
 * @param acronym The user acronym to search for in the user list.
 *
 * @return 1 if a matching user acronym is found;
 * -1 to indicate that no matching user was found, otherwise.
 */
int searchUserFromAcronym(UserList users, char* acronym);

/**
 * @brief Searches for equipment with a specified name in the equipment list.
 *
 * This function is used to check whether there is any equipment with the name entered by the user.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 * @param name The equipment name to search for in the equipment list.
 * @return 1 if equipment with the specified name is found;
 * -1 to indicate that no matching equipment was found, otherwise.
 */
int searchEquipmentFromName(EquipmentList equipment, char *name);

/**
 * @brief Searches for a user in the UserList based on the provided user ID.
 *
 * This function is used to check whether there is any user with the ID entered by the user.
 *
 * @param users A variable that accesses a struct: UserList.
 * @param id The user ID to search for in the user list.
 *
 * @return the index of the user in the list, if a matching user ID is found;
 * -1 to indicate that no matching user was found, otherwise.
 */
int searchUserFromId(UserList users, int id);

/**
 * @brief Searches for the maximum user ID in the UserList.
 *
 * This function is used to check among existing users which user ID is the highest.
 *
 * @param users A variable that accesses a struct: UserList.
 *
 * @return the maximum user ID, if the user list is not empty;
 * that user's ID, if there is only one user;
 * -1 to indicate that no matching user ID was found, if the user list is empty.
 */
int searchMaxUserId(UserList users);

/**
 * @brief Searches for the maximum equipment ID in the EquipmentList.
 *
 * This function is used to check among existing equipment which equipment ID is the highest.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 *
 * @return the maximum equipment ID, if the equipment list is not empty;
 * that equipment's ID, if there is only one equipment;
 * -1 to indicate that no matching equipment ID was found, if the equipment list is empty.
 */
int searchMaxEquipmentId(EquipmentList equipment);

#endif /* SEARCHS_H */

