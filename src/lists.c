/**
* @file lists.c
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
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
#include "search.h"
#include "memory_and_files.h"
#include "date.h"


const char *const EQUIPMENT_CATEGORIES[CATEGORY_OPTIONS] = {
    "Printer", "Computer", "Laptop", "Monitor", "Router", "Switch", "TV",
    "Projector", "Access controller", "Mouse", "Accessory", "Other"
};

const char *equipmentStatusToString(int status) {
    switch (status) {
        case OPERATIONAL_STATUS_VALUE: return "Operational";
        case UNDER_MAINTENANCE_STATUS_VALUE: return "Under maintenance";
        case N_OPERATIONAL_STATUS_VALUE: return "Not operational";
        case FOR_RECYCLING_STATUS_VALUE: return "For recycling";
        default: return "Unknown";
    }
}

void printStatusOptions(void) {
    int status;
    putchar('\n');
    for (status = OPERATIONAL_STATUS_VALUE; status <= FOR_RECYCLING_STATUS_VALUE; status++) {
        printf("%d - %s\n", status, equipmentStatusToString(status));
    }
}

void printEquipment(const Equipment *equipment) {
    printf("\nEquipment ID: %d\nName: %s\nCategory: %s\nAcquired on: %02d/%02d/%04d\nStatus: %s\n",
            equipment->equipmentId.id, equipment->equipmentName, equipment->category,
            equipment->date.day, equipment->date.month, equipment->date.year,
            equipmentStatusToString((int) equipment->equipmentStatus));
    if (equipment->userId.id == NO_USER) {
        puts("Assigned user: (none)");
    } else {
        printf("Assigned user ID: %d\n", equipment->userId.id);
    }
}

void printUser(const User *user) {
    printf("\nUser ID: %d\nAcronym: %s\nName: %s\nRole: %s\nStatus: %s\n",
            user->userId.id, user->acronym, user->username, user->role,
            user->userStatus == ACTIVE_STATUS_VALUE ? "Active" : "Inactive");
}

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
                printf("\n%d)", i + 1);
                printEquipment(&equipment.equipment[i]);
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
                printf("\n%d)", i + 1);
                printEquipment(&equipment.equipment[i]);
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
                printEquipment(&equipment.equipment[i]);
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
    if (equipment.equipmentCount > 0) {
        for (j = 0; j < CATEGORY_OPTIONS; j++) {
            printf("\nCategory: %s", EQUIPMENT_CATEGORIES[j]);
            for (i = 0; i < equipment.equipmentCount; i++) {
                if (equipment.equipment[i].equipmentStatus != FOR_RECYCLING_STATUS_VALUE) {
                    if (equipment.equipment[i].userId.id == NO_USER && strcmp(equipment.equipment[i].category, EQUIPMENT_CATEGORIES[j]) == 0) {
                        aux++;
                        printEquipment(&equipment.equipment[i]);
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
                printf("\n%d)", i + 1);
                printUser(&users.users[i]);
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
        printf("\nMAINTENANCE %d\nMovement number: %d\nDate: %02d/%02d/%04d\nType: %s\nNotes: %s\n", i + 1, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].movementNumber, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].date.day, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].date.month, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].date.year, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].maintenanceType, equipment.equipment[pos - 1].maintenanceHistory.maintenance[i].notes);
    }
    if (equipment.equipment[pos - 1].maintenanceHistory.maintenanceCount == 0) {
        puts(EMPTY_EQUIPMENT_MAINTENANCE_HISTORY);
    }
}