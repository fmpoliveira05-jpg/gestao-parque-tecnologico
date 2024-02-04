/**
* @file users.c
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A source file that provides utility functions for creating requested resources for users, such as create, edit, and remove.
*
* This source file contains a collection of functions designed to make it easier for users to implement requested features.
* in a C program. Includes functions for reading data such as integers, characters and strings,
* as well as functions for editing the various user fields and removing users.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "users.h"
#include "searchs.h"
#include "memory_and_files.h"
#include "lists.h"


void menuForUsers(EquipmentList *equipment, UserList *users) {
    int op;
    do {
        printf("\n\n1-\tCreate User");
        printf("\n2-\tEdit User");
        printf("\n3-\tRemove User");
        printf("\n0-\tGo back");
        printf(SPACER);
        printf("Users: %d/%d\n", users->userCount, users->userSize);
        op = getInt(0, 3, MSG_GET_OPTION);
        switch (op) {
            case 0:
                break;
            case 1:
                logMessage("Create User", FILENAME_LOGS);
                insertUsers(users);
                listActiveUsers(*users);
                break;
            case 2:
                logMessage("Edit User", FILENAME_LOGS);
                updateUsers(users, equipment);
                listActiveUsers(*users);
                break;
            case 3:
                logMessage("Remove User", FILENAME_LOGS);
                removeUsers(equipment, users);
                listActiveUsers(*users);
                break;
            default:
                puts(INVALID_VALUE);
                break;
        }
    } while (op != 0);
}

void insertUsers(UserList *users) {
    if (users->userCount == users->userSize) {
        expandUsers(users);
    }
    if (users->userCount < users->userSize) {
        if (insertUser(users) == -1) {
            puts(ERROR_USER_ACRONYM);
        }
    } else {
        puts(ERROR_USER_ADD);
    }
}

int insertUser(UserList *users) {
    char acronym[USER_ACRONYM_MAX_LENGTH];
    listActiveUsers(*users);
    readString(acronym, USER_ACRONYM_MAX_LENGTH, MSG_GET_USER_ACRONYM);
    if (searchUserFromAcronym(*users, acronym) == -1) {
        strcpy(users->users[users->userCount].acronym, acronym);
        readString(users->users[users->userCount].username, USERNAME_MAX_LENGTH, MSG_GET_USERNAME);
        readString(users->users[users->userCount].role, USER_ROLE_MAX_LENGTH, MSG_GET_USER_ROLE);
        users->users[users->userCount].userStatus = ACTIVE_STATUS_VALUE;
        puts(USER_ADD);
        users->users[users->userCount].userId.id = users->nextUserId++;
        return users->userCount++;
    }
    return -1;
}

void readUser(User *user) {
    readString(user->acronym, USER_ACRONYM_MAX_LENGTH, MSG_GET_USER_ACRONYM);
    readString(user->username, USERNAME_MAX_LENGTH, MSG_GET_USERNAME);
    readString(user->role, USER_ROLE_MAX_LENGTH, MSG_GET_USER_ROLE);
    user->userStatus = getInt(INACTIVE_STATUS_VALUE, ACTIVE_STATUS_VALUE, MSG_GET_USER_STATUS);
}

void cleanUserData(User *user) {
    user->userId.id = 0;
    strcpy(user->acronym, "");
    strcpy(user->username, "");
    strcpy(user->role, "");
    user->userStatus = INACTIVE_STATUS_VALUE;
}

void removeUsers(EquipmentList *equipment, UserList *users) {
    int i, pos, id;
    char op;
    if (users->userCount == 0) {
        puts(ERROR_EMPTY_LIST);
        return;
    }
    id = getInt(1, searchMaxUserId(*users), MSG_GET_USER_ID_TO_REMOVE_USER);
    pos = searchUserFromId(*users, id);
    if (pos != -1 && users->users[pos].userStatus == ACTIVE_STATUS_VALUE) {
        for (i = 0; i < equipment->equipmentCount; i++) {
            if (equipment->equipment[i].userId.id == users->users[pos].userId.id) {
                puts(ERROR_USER_WITHOUT_EQUIPMENT_DEL);
                op = getChar(CHANGE_STATUS_QUESTION);
                if (op == 'y' || op == 'Y') {
                    users->users[pos].userStatus = INACTIVE_STATUS_VALUE;
                    puts(ERROR_INACTIVE_USER_DISSOCIATE_USER_DEL);
                    return;
                } else if (op == 'n' || op == 'N') {
                    return;
                }
            }
        }
        for (i = pos; i < users->userCount - 1; i++) {
            users->users[i] = users->users[i + 1];
        }
        cleanUserData(&users->users[i]);
        users->userCount--;
        puts(USER_DEL);
    } 
    if (pos != -1 && users->users[pos].userStatus == INACTIVE_STATUS_VALUE) {
        puts(ERROR_INACTIVE_USER_DEL);
    }
}

void updateUsers(UserList *users, EquipmentList *equipment) {
    int i, id, pos;
    if (users->userCount == 0) {
        puts(ERROR_EMPTY_LIST);
        return;
    }
    id = getInt(1, searchMaxUserId(*users), MSG_GET_USER_ID_TO_UPDATE_USER);
    pos = searchUserFromId(*users, id);
    if (pos != -1) {
        readUser(&users->users[pos]);
        for (i = 0; i < equipment->equipmentCount; i++) {
            if (users->users[pos].userStatus == INACTIVE_STATUS_VALUE && equipment->equipment[i].userId.id == users->users[pos].userId.id) {
                equipment->equipment[i].userId.id = NO_USER;
            }
        }
        puts(USER_UPDATE);
    } else {
        puts(ERROR_USER_NOT_FOUND);
    }
}