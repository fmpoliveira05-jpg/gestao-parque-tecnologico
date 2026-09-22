/**
* @file search.h
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
*
* @brief A header file that provides utility functions for searches.
*
* This header file contains a collection of functions designed to facilitate the implementation of requested features
* for research
* in a C program. Includes functions to search equipment by status and acquisition date, search by ID, search for a user by,
* acronym, search for the maintenance movement number, among others.
*/

#ifndef SEARCH_H
#define SEARCH_H

#include "types.h"

#define MSG_GET_EQUIPMENT_POSITION_TO_VIEW_HISTORY "Enter the position of the Equipment to view its maintenance history: " // // referring to the equipment position in the listing

#define ERROR_VIEW_EQUIPMENT_MAINTENANCE_HISTORY "\nIt is not possible to list the maintenance history of FOR RECYCLING equipment."
#define ERROR_USER_NOT_FOUND "\nThe user does not exist."
#define EMPTY_EQUIPMENT_MAINTENANCE_HISTORY "\nThe history is empty for now!"


/**
 * @brief Checks whether an equipment has the given status and acquisition date (pure function, no output).
 * @param equipment Equipment to test.
 * @param status Status value (see EquipmentStatus).
 * @param date Acquisition date to match.
 * @return 1 if both criteria match, 0 otherwise.
 */
int equipmentMatchesStatusAndDate(const Equipment *equipment, int status, Date date);

/**
 * @brief Checks whether the equipment name contains a text fragment, ignoring upper/lower case.
 * @param equipment Equipment to test.
 * @param fragment Text to look for (an empty fragment matches everything).
 * @return 1 if the name contains the fragment, 0 otherwise.
 */
int equipmentNameContains(const Equipment *equipment, const char *fragment);

/**
 * @brief Search criterion 1: prints every equipment with the given status and acquisition date.
 *
 * Equipment FOR RECYCLING is never shown, as required by the project brief.
 *
 * @param equipment The equipment list.
 * @param status Status to look for.
 * @param date Acquisition date to look for.
 * @return Number of results found.
 */
int searchEquipmentFromStatusAndDate(EquipmentList equipment, int status, Date date);

/**
 * @brief Search criterion 2: prints every equipment whose name contains the given fragment.
 *
 * Equipment FOR RECYCLING is never shown, as required by the project brief.
 *
 * @param equipment The equipment list.
 * @param fragment Part of the name to look for.
 * @return Number of results found.
 */
int searchEquipmentFromNameFragment(EquipmentList equipment, const char *fragment);

/**
 * @brief Search menu: lets the user choose between the two available search criteria.
 *
 * @param equipment The equipment list.
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
 * @return the highest user ID, or 0 if the list is empty.
 */
int searchMaxUserId(UserList users);

/**
 * @brief Searches for the maximum equipment ID in the EquipmentList.
 *
 * This function is used to check among existing equipment which equipment ID is the highest.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 *
 * @return the highest equipment ID, or 0 if the list is empty.
 */
int searchMaxEquipmentId(EquipmentList equipment);

#endif /* SEARCH_H */

