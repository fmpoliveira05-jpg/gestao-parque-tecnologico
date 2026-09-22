/**
* @file search.c
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
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
#include <ctype.h>
#include "date.h"
#include "input.h"
#include "users.h"
#include "equipment.h"
#include "search.h"
#include "lists.h"


int equipmentMatchesStatusAndDate(const Equipment *equipment, int status, Date date) {
    return (int) equipment->equipmentStatus == status && compareDates(equipment->date, date) == 0;
}

int equipmentNameContains(const Equipment *equipment, const char *fragment) {
    size_t i, j, nameLength = strlen(equipment->equipmentName), fragmentLength = strlen(fragment);

    if (fragmentLength == 0) {
        return 1;
    }
    /* Case-insensitive substring search, so "dell" finds "Portátil Dell XPS". */
    for (i = 0; i + fragmentLength <= nameLength; i++) {
        for (j = 0; j < fragmentLength; j++) {
            if (tolower((unsigned char) equipment->equipmentName[i + j]) != tolower((unsigned char) fragment[j])) {
                break;
            }
        }
        if (j == fragmentLength) {
            return 1;
        }
    }
    return 0;
}

int searchEquipmentFromStatusAndDate(EquipmentList equipment, int status, Date date) {
    int i, results = 0;
    if (status == FOR_RECYCLING_STATUS_VALUE) {
        puts(NOTE_FOR_RECYCLING_EQUIPMENT);
    } else {
        for (i = 0; i < equipment.equipmentCount; i++) {
            if (equipmentMatchesStatusAndDate(&equipment.equipment[i], status, date)) {
                results++;
                printEquipment(&equipment.equipment[i]);
            }
        }
    }
    printf("\nFound %d results.\n", results);
    return results;
}

int searchEquipmentFromNameFragment(EquipmentList equipment, const char *fragment) {
    int i, results = 0;
    for (i = 0; i < equipment.equipmentCount; i++) {
        if (equipment.equipment[i].equipmentStatus != FOR_RECYCLING_STATUS_VALUE && equipmentNameContains(&equipment.equipment[i], fragment)) {
            results++;
            printEquipment(&equipment.equipment[i]);
        }
    }
    printf("\nFound %d results.\n", results);
    return results;
}

void searchEquipment(EquipmentList equipment) {
    char fragment[EQUIPMENT_NAME_MAX_LENGTH];
    int op;

    puts("\n1-\tSearch by status and acquisition date");
    puts("2-\tSearch by name (partial, case-insensitive)");
    puts("0-\tGo back");
    op = getInt(0, 2, MSG_GET_OPTION);
    if (op == 1) {
        printStatusOptions();
        int status = getInt(OPERATIONAL_STATUS_VALUE, FOR_RECYCLING_STATUS_VALUE, MSG_GET_EQUIPMENT_STATUS);
        searchEquipmentFromStatusAndDate(equipment, status, readDate("acquisition"));
    } else if (op == 2) {
        readString(fragment, EQUIPMENT_NAME_MAX_LENGTH, MSG_GET_EQUIPMENT_NAME);
        searchEquipmentFromNameFragment(equipment, fragment);
    }
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
    int i, max = 0;
    for (i = 0; i < users.userCount; i++) {
        if (users.users[i].userId.id > max) {
            max = users.users[i].userId.id;
        }
    }
    return max;
}

int searchMaxEquipmentId(EquipmentList equipment) {
    int i, max = 0;
    for (i = 0; i < equipment.equipmentCount; i++) {
        if (equipment.equipment[i].equipmentId.id > max) {
            max = equipment.equipment[i].equipmentId.id;
        }
    }
    return max;
}
