/**
* @file lists.h
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
*
* @brief A header file that provides utility functions for listing equipment and maintenance.
*
* This header file contains a collection of functions designed to facilitate the implementation of requested features
* for equipment and maintenance listings
* in a C program. Includes functions for outputting data, such as equipment name, category, acquisition date and status,
* in addition to user name, acronym, role, among others.
*/

#ifndef LISTS_H
#define LISTS_H

#include "types.h"

#define MIN_MAINTENANCE_MOVEMENT_NUMBER_LIST 1
#define MAX_MAINTENANCE_MOVEMENT_NUMBER_LIST 1000000

#define ERROR_EMPTY_LIST ".\n..\n...\nReturning because the list is empty for now..." // message used to exit the function when there are no users/equipment
#define EMPTY_LIST "\nThe list is empty for now!"

/** @brief Names of the equipment categories, in the order shown in the menus. */
extern const char *const EQUIPMENT_CATEGORIES[CATEGORY_OPTIONS];

/**
 * @brief Converts a numeric equipment status into readable text.
 * @param status Status value (1 to 4).
 * @return A static string such as "Operational", or "Unknown" for invalid values.
 */
const char *equipmentStatusToString(int status);

/** @brief Prints the numbered list of equipment statuses, used before asking the user to choose one. */
void printStatusOptions(void);

/**
 * @brief Prints the details of a single equipment (single place for the output format).
 * @param equipment Equipment to print.
 */
void printEquipment(const Equipment *equipment);

/**
 * @brief Prints the details of a single user.
 * @param user User to print.
 */
void printUser(const User *user);

/**
 * @brief Displays a menu for listing equipment.
 *
 * This function presents an interactive menu that allows the user to choose one of 3 listings:
 * list of free equipment (grouped by category), list of equipment for recycling
 * and list of the maintenance history of a specific device (in chronological order).
 *
 * @param equipment A pointer to struct: EquipmentList.
 */
void menuForLists(EquipmentList *equipment);

/**
 * @brief Displays a list of equipment excluding those with "for recycling" statuts.
 *
 * This function print equipment in the list, excluding those with "for recycling" status.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 */
void listEquipmentExceptForRecycling(EquipmentList equipment);

/**
 * @brief Displays a list of equipment with "for recycling" statuts.
 *
 * This function just print equipment in the list with "for recycling" status.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 */
void listEquipmentForRecycling(EquipmentList equipment);

/**
 * @brief Displays a list of equipment currently "under maintenance".
 *
 * This function just print equipment in the list with "under maintenance" status.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 */
void listEquipmentUnderMaintenance(EquipmentList equipment);

/**
 * @brief Displays a list of available equipment that are not currently assigned to any user, grouped by category.
 *
 * This function print equipment in the list that does not have an associated user, grouped by category.
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 */
void listFreeEquipment(EquipmentList equipment);

/**
 * @brief Displays a list of active users.
 *
 * This function just print active users in the list.
 *
 * @param users A variable that accesses a struct: UserList.
 */
void listActiveUsers(UserList users);

/**
 * @brief Displays the maintenance history for a specific equipment, sorted by date.
 *
 * This function allows the user to choose a specific equipment in the list to view its maintenance history.
 * The maintenance of this equipment are reordered by date (from oldest to most current).
 *
 * @param equipment A variable that accesses a struct: EquipmentList.
 */
void listMaintenanceByDate(EquipmentList equipment);

#endif /* LISTS_H */

