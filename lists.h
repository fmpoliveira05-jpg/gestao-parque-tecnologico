/**
* @file lists.h
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
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

#define MIN_MAINTENANCE_MOVEMENT_NUMBER_LIST 1
#define MAX_MAINTENANCE_MOVEMENT_NUMBER_LIST 1000000

#define ERROR_EMPTY_LIST ".\n..\n...\nReturning because the list is empty for now..." // message used to exit the function when there are no users/equipment
#define EMPTY_LIST "\nThe list is empty for now!"

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

