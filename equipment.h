/**
* @file equipment.h
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
* 
* @brief A header file that provides utility functions for creating the requested features for equipment such as create, edit and remove.
*
* This header file contains a collection of functions designed to facilitate the implementation of requested features for equipment
* in a C program. Includes functions for reading data, such as integers, characters and strings,
* as well as functions for editing the various equipment fields and removing equipment.
*/

#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_YEAR 1990
#define MAX_YEAR 2024

#define OPERATIONAL_STATUS_VALUE 1
#define UNDER_MAINTENANCE_STATUS_VALUE 2
#define N_OPERATIONAL_STATUS_VALUE 3
#define FOR_RECYCLING_STATUS_VALUE 4

#define EQUIPMENT_ADD "\nThe device was created successfully."
#define EQUIPMENT_DEL "\nThe device was removed successfully."
#define EQUIPMENT_UPDATE "\nThe device was updated successfully."
#define EQUIPMENT_MAINTENANCE "\nThe device was maintenanced successfully."

#define MSG_GET_ACQUISITION_DAY "Enter the day of acquisition: "
#define MSG_GET_ACQUISITION_MONTH "Enter the month of acquisition: "
#define MSG_GET_ACQUISITION_YEAR "Enter the year of acquisition: "
#define MSG_GET_MOVEMENT_NUMBER "\nEnter the movement number: "
#define MSG_GET_MAINTENANCE_DAY "Enter the day of maintenance: "
#define MSG_GET_MAINTENANCE_MONTH "Enter the month of maintenance: "
#define MSG_GET_MAINTENANCE_YEAR "Enter the year of maintenance: "
#define MSG_GET_MAINTENANCE_TYPE "Enter the maintenance type: "
#define MSG_GET_MAINTENANCE_NOTE "Enter a note: "
#define MSG_GET_EQUIPMENT_ID_TO_UPDATE_EQUIPMENT "Enter the Equipment ID to be update that equipment: "
#define MSG_GET_EQUIPMENT_ID_TO_REMOVE_EQUIPMENT "Enter the Equipment ID to be remove that equipment: "
#define MSG_GET_EQUIPMENT_ID_TO_MAINTENANCE_EQUIPMENT "\nEnter the Equipment ID to be maintenanced: "
#define MSG_GET_EQUIPMENT_NAME "Enter the equipment name: "
#define MSG_GET_EQUIPMENT_STATUS "Enter the equipment status: "

#define ERROR_EQUIPMENT_ADD "\nIt is not possible to insert a new device."
#define ERROR_EQUIPMENT_NAME "\nThere is already an equipment with the same name."
#define ERROR_EQUIPMENT_DEL "\nOnly equipment FOR RECYCLING can be removed."
#define ERROR_MOVEMENT_NUMBER "\nThe movement number entered already exists."
#define ERROR_MAINTENANCE "\nThe maintenance is only available on equipment with the UNDER MAINTENANCE status."
#define ERROR_EQUIPMENT_NOT_FOUND "\nThe device does not exist."
#define ERROR_FOR_RECYCLING_EQUIPMENT "\nIt is not possible to change the status of FOR RECYCLING equipment or affiliate an user."
#define ERROR_UPDATE_FOR_RECYCLING_EQUIPMENT ".\n..\n...\nReturning because FOR RECYCLING equipment CANNOT affiliate an user." // message used to exit the function when the equipment to be updated have FOR RECYCLING status
#define ERROR_UPDATE_DISSOCIATE_EQUIPMENT "\nThe user associated with this device has just been dissociated."
#define NOTE_FOR_RECYCLING_EQUIPMENT "\nNote: FOR RECYCLING equipment are always filtered."


/**
 * @brief Displays an interactive menu for managing equipment.
 *
 * This function presents an interactive menu allowing the user to perform various operations related to equipment.
 * Options include creating, editing, removing, and maintaining equipment.
 *
 * @param users A pointer to struct: UserList.
 * @param equipment A pointer to struct: EquipmentList.
 */
void menuForEquipment(UserList *users, EquipmentList *equipment);

/**
 * @brief Reads maintenance information for a specific equipment.
 *
 * This function prompts the user to input a maintenance for a given equipment.
 *
 * @param equipment A pointer to struct: Equipment.
 * @param movementNumber A variable that temporarily stores the value of the maintenance movement number
 * to check if the number entered is unique.
 */
void readEquipmentMaintenance(Equipment *equipment, int movementNumber);

/**
 * @brief Resets all data fields of an equipment to default values.
 *
 * This function initializes or "cleans" an equipment structure by resetting all of its
 * data fields to default values.
 * 
 * @param equipment A pointer to struct: Equipment.
 */
void cleanEquipmentData(Equipment *equipment);

/**
 * @brief Associates a user with a specific equipment.
 *
 * This function allows the user to associate a specific user with an equipment.
 *
 * @param users A pointer to struct: UserList.
 * @param equipment A pointer to struct: EquipmentList.
 *
 * @note This function ensures that only active users are considered for association with equipment.
 */
void insertUserIntoEquipment(UserList *users, EquipmentList *equipment);

/**
 * @brief Inserts equipment into the equipment list.
 *
 * This function checks whether it is possible to add a new device (it is not possible to have two devices with the same name),
 * being an intermediary to increase the memory space to double for the devices, whenever necessary.
 *
 * @param users A pointer to struct: UserList.
 * @param equipment A pointer to struct: EquipmentList.
 */
void insertEquipment(UserList *users, EquipmentList *equipment);

/**
 * @brief Inserts a new equipment into the equipment list.
 *
 * This function adds a new equipment to the equipment list. It prompts the user to enter
 * information such as the equipment name, category, acquisition date, and associates it with a user.
 *
 * @param users A pointer to struct: UserList.
 * @param equipment A pointer to struct: EquipmentList.
 *
 * @note This funciton ensures that the equipment list is expanded if necessary, and memory allocation
 * for maintenance history is handled properly.
 * 
 * @return the equipment counter if an equipment was created successfully;
 *  -1, otherwise.
 */
int insert1Equipment(UserList *users, EquipmentList *equipment);

/**
 * @brief Reads and sets status and associated user for a specific equipment.
 * This function will be used to edit an equipment.
 *
 * This function prompts the user to enter the status of the equipment and, if applicable (i.e., whether the equipment
 * does not have "for recycling" status), associate the equipment with a user. 
 *
 * @param equipment A pointer to struct: Equipment.
 * @param users A pointer to struct: UserList.
 *
 * @note This function ensures that only active users are considered for association with equipment.
 */
void readStatusAndUserForEquipment(Equipment *equipment, UserList *users);

/**
 * @brief Updates the status and associated user for a specific equipment.
 *
 * This function allows the user to update the equipment status and, if applicable,
 * change the equipment association with another user.
 *
 * @param equipment A pointer to struct: EquipmentList.
 * @param users A pointer to struct: UserList.
 * 
 * @note For recycling equipment cannot have an associated user;
 * These devices also cannot change status.
 */
void updateEquipment(EquipmentList *equipment, UserList *users);

/**
 * @brief Inserts maintenance information for a specific equipment under maintenance.
 *
 * This function allows the user to add a maintenance for an equipment currently under maintenance.
 *
 * @param equipment A pointer to struct: EquipmentList.
 */
void insertEquipmentMaintenance(EquipmentList *equipment);

/**
 * @brief Removes an equipment from the equipment list.
 *
 * This function allows the user to remove an equipment from the list by specifying its ID.
 *
 * @param equipment A pointer to struct: EquipmentList.
 * 
 * @note Only for recycling equipment can be removed.
 */
void removeEquipment(EquipmentList *equipment);

#endif /* EQUIPMENT_H */

