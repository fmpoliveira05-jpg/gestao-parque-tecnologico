/**
* @file users.h
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A header file that provides utility functions for creating requested resources for users, such as create, edit, and remove.
*
* This header file contains a collection of functions designed to make it easier for users to implement requested features.
* in a C program. Includes functions for reading data such as integers, characters and strings,
* as well as functions for editing the various user fields and removing users.
*/

#ifndef USERS_H
#define USERS_H


#define INACTIVE_STATUS_VALUE 0
#define ACTIVE_STATUS_VALUE 1

#define NO_USER -1 // value assigned to the equipment when it has no associated user

#define USER_ADD "\nThe user was created successfully."
#define USER_DEL "\nThe user was removed successfully."
#define USER_UPDATE "\nThe user was updated successfully."

#define MSG_GET_USER_ID_TO_UPDATE_USER "Enter the User ID to be update that user: "
#define MSG_GET_USER_ID_TO_REMOVE_USER "Enter the User ID to be remove that user: "
#define MSG_GET_OTHER_USER "Enter the position of the User to change the user on device (enter \"-1\" for dissociate or \"0\" if you NOT change): " // referring to the user position in the listing
#define MSG_GET_USER_POSITION_TO_AGROUP "Enter the position of the User to associate: " // referring to the user position in the listing
#define MSG_GET_USER_ACRONYM "\nEnter the user acronym: "
#define MSG_GET_USERNAME "Enter the username: "
#define MSG_GET_USER_ROLE "Enter the user role: "
#define MSG_GET_USER_STATUS "Enter the user status: "

#define AGROUP_USER_QUESTION "Do you want to associate this device with a user? (y/n)  "
#define CHANGE_STATUS_QUESTION "\nDo you want to change the status of this user to INACTIVE? (y/n)  "

#define ERROR_USER_ACRONYM "\nThere is already an user with the same acronym."
#define ERROR_USER_ADD "\nIt is not possible to insert a new user."
#define ERROR_USER_AGROUP "\nAction refused. This user is INACTIVE."
#define ERROR_USERS_NOT_FOUND "\nThere are no users."
#define ERROR_USER_WITHOUT_EQUIPMENT_DEL "\nOnly users without equipment can be removed."
#define ERROR_INACTIVE_USER_DISSOCIATE_USER_DEL "The user is INACTIVE for now and all equipment associated with him has been dissociated."
#define ERROR_INACTIVE_USER_DEL "\nIt is not possible to remove INACTIVE users."


/**
 * @brief Displays a menu for user management and performs corresponding actions based on user input.
 *
 * This function presents a menu for user management with options to create, edit or remove users.
 *
 * @param equipment A pointer to struct: EquipmentList.
 * @param users A pointer to struct: UserList.
 */
void menuForUsers(EquipmentList *equipment, UserList *users);

/**
 * @brief Inserts a new user into the UserList after checking for available space and valid input.
 *
 * This function checks whether it is possible to add a new user (it is not possible to have two users with the same acronym),
 * being an intermediary to increase users' memory space, whenever necessary.
 *
 * @param users A pointer to struct: UserList.
 */
void insertUsers(UserList *users);

/**
 * @brief Inserts a new user into the user list.
 *
 * This function prompts the user to enter a new user requesting information including acronym, username and role.
 *
 * @param users A pointer to struct: UserList.
 * @return the index of the newly added user if successful;
 * -1, otherwise.
 */
int insertUser(UserList *users);

/**
 * @brief Reads and collects information for a User structure from the user through the console.
 * This function will be used to edit a user.
 *
 * This function prompts the user to input information for a User structure, including the acronym,
 * username, role, and user status.
 *
 * @param user A pointer to struct: UserList.
 */
void readUser(User *user);

/**
 * @brief Resets all data fields of an user to default values.
 *
 * This function initializes or "cleans" an user structure by resetting all of its
 * data fields to default values.
 *
 * @param user A pointer to struct: UserList.
 */
void cleanUserData(User *user);

/**
 * @brief Removes a user from the user list.
 *
 * This function allows you to remove an active user from the user list by asking for him ID.
 *
 * @param equipment A pointer to struct: EquipmentList.
 * @param users A pointer to struct: UserList.
 * 
 * @note The user is only removed if he has no equipment associated with him.
 */
void removeUsers(EquipmentList *equipment, UserList *users);

/**
 * @brief Updates an existing user in the user list.
 *
 * This function prompts the user to enter new details for an existing user, identified by the user ID.
 *
 * @param users A pointer to struct: UserList.
 * @param equipment A pointer to struct: EquipmentList.
 * 
 * @note This function unlinks an inactive user from all devices to which they are linked,
 * if the user is placed as inactive.
 */
void updateUsers(UserList *users, EquipmentList *equipment);

#endif /* USERS_H */

