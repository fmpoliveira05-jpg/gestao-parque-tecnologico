/**
* @file searchs.c
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A source file that provides utility functions for searches.
*
* This source file contains a collection of functions designed to facilitate the implementation of requested features
* for research
* in a C program. Includes functions to search equipment by status and acquisition date, search by ID, search for a user by,
* acronym, search for the maintenance movement number, among others.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "users.h"
#include "equipment.h"
#include "searchs.h"
#include "lists.h"


void searchEquipmentFromStatusAndDate(EquipmentList equipment, int status, int day, int month, int year) {
    int i, results = 0;
    if (status != FOR_RECYCLING_STATUS_VALUE) {
        for (i = 0; i < equipment.equipmentCount; i++) {
            if (equipment.equipment[i].equipmentStatus == status) {
                if (equipment.equipment[i].date.day == day && equipment.equipment[i].date.month == month && equipment.equipment[i].date.year == year) {
                    results++;
                    printf("\nEquipmentId: %d;\nEquipmentName: %s;\nCategory: %s;\nDate of acquisition: %d/%d/%d;\nEquipmentStatus: %d;\nUserId affiliated: %d.\n", equipment.equipment[i].equipmentId.id, equipment.equipment[i].equipmentName, equipment.equipment[i].category, equipment.equipment[i].date.day, equipment.equipment[i].date.month, equipment.equipment[i].date.year, equipment.equipment[i].equipmentStatus, equipment.equipment[i].userId.id);
                }
            }
        }
    } else {
        puts(NOTE_FOR_RECYCLING_EQUIPMENT);
    }
    printf("\nFound %d results.", results);
}

void searchEquipment(EquipmentList equipment) {
    int status, day, month, year;
    status = getInt(OPERATIONAL_STATUS_VALUE, FOR_RECYCLING_STATUS_VALUE, MSG_GET_EQUIPMENT_STATUS);
    day = getInt(MIN_DAY, MAX_DAY, MSG_GET_ACQUISITION_DAY);
    month = getInt(MIN_MONTH, MAX_MONTH, MSG_GET_ACQUISITION_MONTH);
    year = getInt(MIN_YEAR, MAX_YEAR, MSG_GET_ACQUISITION_YEAR);
    searchEquipmentFromStatusAndDate(equipment, status, day, month, year);
}

int searchEquipmentFromId(EquipmentList equipment, int id) {
    int i;
    for (i = 0; i < equipment.equipmentCount; i++) {
        if (equipment.equipment[i].equipmentId.id == id) {
            return i;
        }
    }
    return -1;
}

int searchForMovementNumber(EquipmentList equipment, int movementNumber) {
    int i, j;
    for (i = 0; i < equipment.equipmentCount; i++) {
        for (j = 0; j < equipment.equipment[i].maintenanceHistory.maintenanceCount; j++) {
            if (equipment.equipment[i].maintenanceHistory.maintenance[j].movementNumber == movementNumber) {
                return 1;
            }
        }
    }
    return -1;
}

int searchUserFromAcronym(UserList users, char *acronym) {
    int i;
    for (i = 0; i < users.userCount; i++) {
        if (strcmp(users.users[i].acronym, acronym) == 0) {
            return 1;
        }
    }
    return -1;
}

int searchEquipmentFromName(EquipmentList equipment, char *name) {
    int i;
    for (i = 0; i < equipment.equipmentCount; i++) {
        if (strcmp(equipment.equipment[i].equipmentName, name) == 0) {
            return 1;
        }
    }
    return -1;
}

int searchUserFromId(UserList users, int id) {
    int i;
    for (i = 0; i < users.userCount; i++) {
        if (users.users[i].userId.id == id) {
            return i;
        }
    }
    return -1;
}

int searchMaxUserId(UserList users) {
    int i, aux = 0, max = users.users[0].userId.id;
    if (users.userCount == 1) {
        return max;
    }
    for (i = 0; i < users.userCount; i++) {
        if (users.users[i].userId.id < users.users[i + 1].userId.id) {
            max = users.users[i + 1].userId.id;
            aux++;
        }
    }
    if (aux != 0) {
        return max;
    }
    return -1;
}

int searchMaxEquipmentId(EquipmentList equipment) {
    int i, aux = 0, max = equipment.equipment[0].equipmentId.id;;
    if (equipment.equipmentCount == 1) {
        return max;
    }
    for (i = 0; i < equipment.equipmentCount; i++) {
        if (equipment.equipment[i].equipmentId.id < equipment.equipment[i + 1].equipmentId.id) {
            max = equipment.equipment[i + 1].equipmentId.id;
            aux++;
        }
    }
    if (aux != 0) {
        return max;
    }
    return -1;
}