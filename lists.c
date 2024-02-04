/**
* @file lists.c
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A source file that provides utility functions for listing equipment and maintenance.
*
* This source file contains a collection of functions designed to facilitate the implementation of requested features
* for equipment and maintenance listings
* in a C program. Includes functions for outputting data, such as equipment name, category, acquisition date and status,
* in addition to user name, acronym, role, among others.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "lists.h"
#include "equipment.h"
#include "users.h"
#include "searchs.h"
#include "memory_and_files.h"


void menuForLists(EquipmentList *equipment) {
    int op;
    do {
        printf("\n\n1-\tList Free Equipment");
        printf("\n2-\tList Equipment For Recycling");
        printf("\n3-\tList Equipment Maintenance History By Date");
        printf("\n0-\tGo back\n\n");
        printf(SPACER);
        op = getInt(0, 3, MSG_GET_OPTION);
        switch (op) {
            case 0:
                break;
            case 1:
                logMessage("List Free Equipment", FILENAME_LOGS);
                listFreeEquipment(*equipment);
                break;
            case 2:
                logMessage("List Equipment For Recycling", FILENAME_LOGS);
                listEquipmentForRecycling(*equipment);
                break;
            case 3:
                logMessage("List Equipment Maintenance History By Date", FILENAME_LOGS);
                listMaintenanceByDate(*equipment);
                break;
            default:
                puts(INVALID_VALUE);
                break;
        }
    } while (op != 0);
}

void listEquipmentExceptForRecycling(EquipmentList equipment) {
    int i, aux = 0;
    if (equipment.equipmentCount > 0) {
        for (i = 0; i < equipment.equipmentCount; i++) {
            if (equipment.equipment[i].equipmentStatus != FOR_RECYCLING_STATUS_VALUE) {
                aux++;
                printf("\n%d)\nEquipmentId: %d;\nEquipmentName: %s;\nCategory: %s;\nDate of acquisition: %d/%d/%d;\nEquipmentStatus: %d;\nUserId affiliated: %d.\n", i + 1, equipment.equipment[i].equipmentId.id, equipment.equipment[i].equipmentName, equipment.equipment[i].category, equipment.equipment[i].date.day, equipment.equipment[i].date.month, equipment.equipment[i].date.year, equipment.equipment[i].equipmentStatus, equipment.equipment[i].userId.id);
            }
        }
        if (aux == 0) {
            puts(EMPTY_LIST);
            return;
        }
    } else {
        puts(EMPTY_LIST);
        return;
    }
}

void listEquipmentForRecycling(EquipmentList equipment) {
    int i, aux = 0;
    if (equipment.equipmentCount > 0) {
        for (i = 0; i < equipment.equipmentCount; i++) {
            if (equipment.equipment[i].equipmentStatus == FOR_RECYCLING_STATUS_VALUE) {
                aux++;
                printf("\n%d)\nEquipmentId: %d;\nEquipmentName: %s;\nCategory: %s;\nDate of acquisition: %d/%d/%d;\nEquipmentStatus: %d;\nUserId affiliated: %d.\n", i + 1, equipment.equipment[i].equipmentId.id, equipment.equipment[i].equipmentName, equipment.equipment[i].category, equipment.equipment[i].date.day, equipment.equipment[i].date.month, equipment.equipment[i].date.year, equipment.equipment[i].equipmentStatus, equipment.equipment[i].userId.id);
            }
        }
        if (aux == 0) {
            puts(EMPTY_LIST);
        }
    } else {
        puts(EMPTY_LIST);
    }
}

void listEquipmentUnderMaintenance(EquipmentList equipment) {
    int i, aux = 0;
    if (equipment.equipmentCount > 0) {
        for (i = 0; i < equipment.equipmentCount; i++) {
            if (equipment.equipment[i].equipmentStatus == UNDER_MAINTENANCE_STATUS_VALUE) {
                aux++;
                printf("\nEquipmentId: %d;\nEquipmentName: %s;\nCategory: %s;\nDate of acquisition: %d/%d/%d;\nEquipmentStatus: %d;\nUserId affiliated: %d.\n", equipment.equipment[i].equipmentId.id, equipment.equipment[i].equipmentName, equipment.equipment[i].category, equipment.equipment[i].date.day, equipment.equipment[i].date.month, equipment.equipment[i].date.year, equipment.equipment[i].equipmentStatus, equipment.equipment[i].userId.id);
            }
        }
        if (aux == 0) {
            puts(EMPTY_LIST);
        }
    } else {
        puts(EMPTY_LIST);
    }
}

void listFreeEquipment(EquipmentList equipment) {
    int i, j, aux = 0;
    const char* categories[CATEGORY_OPTIONS] = {"Printer", "Computer", "Portable", "Monitor", "Router", "Switch", "TV", "Projector", "Access controller", "Mouse", "Accessory", "Other"};
    if (equipment.equipmentCount > 0) {
        for (j = 0; j < CATEGORY_OPTIONS; j++) {
            printf("\nCategory: %s", categories[j]);
            for (i = 0; i < equipment.equipmentCount; i++) {
                if (equipment.equipment[i].equipmentStatus != FOR_RECYCLING_STATUS_VALUE) {
                    if (equipment.equipment[i].userId.id == NO_USER && strcmp(equipment.equipment[i].category, categories[j]) == 0) {
                        aux++;
                        printf("\n\nEquipmentId: %d;\nEquipmentName: %s;\nCategory: %s;\nDate of acquisition: %d/%d/%d;\nEquipmentStatus: %d;\nUserId affiliated: %d.\n", equipment.equipment[i].equipmentId.id, equipment.equipment[i].equipmentName, equipment.equipment[i].category, equipment.equipment[i].date.day, equipment.equipment[i].date.month, equipment.equipment[i].date.year, equipment.equipment[i].equipmentStatus, equipment.equipment[i].userId.id);
                    }
                }
            }
        }
        if (aux == 0) {
            puts(EMPTY_LIST);
        }
    } else {
        puts(EMPTY_LIST);
    }
}

void listActiveUsers(UserList users) {
    int i, aux = 0;
    if (users.userCount > 0) {
        for (i = 0; i < users.userCount; i++) {
            if (users.users[i].userStatus == ACTIVE_STATUS_VALUE) {
                aux++;
                printf("\n%d)\nUserId: %d;\nAcronym: %s;\nUsername: %s;\nRole: %s;\nUserStatus: %d.\n", i + 1, users.users[i].userId.id, users.users[i].acronym, users.users[i].username, users.users[i].role, users.users[i].userStatus);
            }
        }
        if (aux == 0) {
            puts(EMPTY_LIST);
        }
    } else {
        puts(EMPTY_LIST);
    }
}

void listMaintenanceByDate(EquipmentList equipment) {
    int pos, i, j;
    if (equipment.equipmentCount == 0) {
        puts(ERROR_EMPTY_LIST);
        return;
    }
    listEquipmentExceptForRecycling(equipment);
    pos = getInt(1, equipment.equipmentCount, MSG_GET_EQUIPMENT_POSITION_TO_VIEW_HISTORY);
    if (equipment.equipment[pos - 1].equipmentStatus == FOR_RECYCLING_STATUS_VALUE) {
        puts(ERROR_VIEW_EQUIPMENT_MAINTENANCE_HISTORY);
        return;
    }
    
    /* reorder maintenance using the Bubble Sort method
     * it will compare the maintenance dates two by two and swap their positions (from lowest to highest)
     * until reaching the end of the algorithm and repeating, if necessary, until the dates are ordered chronologically
    */
    for (i = 0; i < equipment.equipment[pos - 1].maintenanceHistory.maintenanceCount - 1; i++) {
        for (j = 0; j < equipment.equipment[pos - 1].maintenanceHistory.maintenanceCount - i - 1; j++) {
            if (compareDates(equipment.equipment[pos - 1].maintenanceHistory.maintenance[j].date, equipment.equipment[pos - 1].maintenanceHistory.maintenance[j + 1].date) > 0) {
                Maintenance temp = equipment.equipment[pos - 1].maintenanceHistory.maintenance[j];
                equipment.equipment[pos - 1].maintenanceHistory.maintenance[j] = equipment.equipment[pos - 1].maintenanceHistory.maintenance[j + 1];
                equipment.equipment[pos - 1].maintenanceHistory.maintenance[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < equipment.equipment[pos - 1].maintenanceHistory.maintenanceCount; i++) {
        printf("\nMAINTENANCE %d\nMovementNumber: %d;\nMaintenance date: %d/%d/%d;\nMaintenanceType: %s;\nNotes: %s.\n", i + 1, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].movementNumber, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].date.day, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].date.month, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].date.year, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].maintenanceType, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].notes);
    }
    if (equipment.equipment[pos - 1].maintenanceHistory.maintenanceCount == 0) {
        puts(EMPTY_EQUIPMENT_MAINTENANCE_HISTORY);
    }
}