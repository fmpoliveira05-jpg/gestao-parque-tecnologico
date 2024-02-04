/**
* @file equipment.c
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A source file that provides utility functions for creating the requested features for equipment such as create, edit and remove.
*
* This source file contains a collection of functions designed to facilitate the implementation of requested features for equipment
* in a C program. Includes functions for reading data, such as integers, characters and strings,
* as well as functions for editing the various equipment fields and removing equipment.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "searchs.h"
#include "users.h"
#include "equipment.h"
#include "memory_and_files.h"
#include "lists.h"


void menuForEquipment(UserList *users, EquipmentList *equipment) {
    int op;
    do {
        printf("\n\n1-\tCreate Equipment");
        printf("\n2-\tEdit Equipment");
        printf("\n3-\tRemove Equipment");
        printf("\n4-\tMaintain Equipment");
        printf("\n0-\tGo back");
        printf(SPACER);
        printf("Equipment: %d/%d\n", equipment->equipmentCount, equipment->equipmentSize);
        op = getInt(0, 4, MSG_GET_OPTION);
        switch (op) {
            case 0:
                break;
            case 1:
                logMessage("Create Equipment", FILENAME_LOGS);
                insertEquipment(users, equipment);
                listEquipmentExceptForRecycling(*equipment);
                break;
            case 2:
                logMessage("Edit Equipment", FILENAME_LOGS);
                updateEquipment(equipment, users);
                listEquipmentExceptForRecycling(*equipment);
                break;
            case 3:
                logMessage("Remove Equipment", FILENAME_LOGS);
                removeEquipment(equipment);
                listEquipmentExceptForRecycling(*equipment);
                break;
            case 4:
                logMessage("Maintain Equipment", FILENAME_LOGS);
                insertEquipmentMaintenance(equipment);
                listEquipmentExceptForRecycling(*equipment);
                break;
            default:
                puts(INVALID_VALUE);
                break;
        }
    } while (op != 0);
}

void readEquipmentMaintenance(Equipment *equipment, int movementNumber) {
    equipment->maintenanceHistory.maintenance[equipment->maintenanceHistory.maintenanceCount].movementNumber = movementNumber;
    equipment->maintenanceHistory.maintenance[equipment->maintenanceHistory.maintenanceCount].date.day = getInt(MIN_DAY, MAX_DAY, MSG_GET_MAINTENANCE_DAY);
    equipment->maintenanceHistory.maintenance[equipment->maintenanceHistory.maintenanceCount].date.month = getInt(MIN_MONTH, MAX_MONTH, MSG_GET_MAINTENANCE_MONTH);
    equipment->maintenanceHistory.maintenance[equipment->maintenanceHistory.maintenanceCount].date.year = getInt(MIN_YEAR, MAX_YEAR, MSG_GET_MAINTENANCE_YEAR);
    readString(equipment->maintenanceHistory.maintenance[equipment->maintenanceHistory.maintenanceCount].maintenanceType, MAINTENANCE_TYPE_MAX_LENGTH, MSG_GET_MAINTENANCE_TYPE);
    readString(equipment->maintenanceHistory.maintenance[equipment->maintenanceHistory.maintenanceCount].notes, MAINTENANCE_NOTES_MAX_LENGTH, MSG_GET_MAINTENANCE_NOTE);
}

void cleanEquipmentData(Equipment *equipment) {
    int i;
    equipment->equipmentId.id = 0;
    equipment->userId.id = NO_USER;
    strcpy(equipment->equipmentName, "");
    strcpy(equipment->category, "");
    equipment->date.day = 0;
    equipment->date.month = 0;
    equipment->date.year = 0;
    equipment->equipmentStatus = 0;
    for (i = 0; i < equipment->maintenanceHistory.maintenanceCount; i++) {
        equipment->maintenanceHistory.maintenance[i].movementNumber = 0;
        equipment->maintenanceHistory.maintenance[i].date.day = 0;
        equipment->maintenanceHistory.maintenance[i].date.month = 0;
        equipment->maintenanceHistory.maintenance[i].date.year = 0;
        strcpy(equipment->maintenanceHistory.maintenance[i].maintenanceType, "");
        strcpy(equipment->maintenanceHistory.maintenance[i].notes, "");
    }
    equipment->maintenanceHistory.maintenanceCount = equipment->maintenanceHistory.maintenanceSize = 0;
}

void insertUserIntoEquipment(UserList *users, EquipmentList *equipment) {
    int pos;
    char op;
    op = getChar(AGROUP_USER_QUESTION);
    if (op == 'y' || op == 'Y') {
        if (users->userCount > 0) {
            listActiveUsers(*users);
            pos = getInt(1, users->userCount, MSG_GET_USER_POSITION_TO_AGROUP);
            if (users->users[pos - 1].userStatus  == ACTIVE_STATUS_VALUE) {
                equipment->equipment[equipment->equipmentCount].userId.id = users->users[pos - 1].userId.id;
            } else {
                puts(ERROR_USER_AGROUP);
                equipment->equipment[equipment->equipmentCount].userId.id = NO_USER;
            }
        } else {
            puts(ERROR_USERS_NOT_FOUND);
            equipment->equipment[equipment->equipmentCount].userId.id = NO_USER;
        }
    } else if (op == 'n' || op == 'N') {
        equipment->equipment[equipment->equipmentCount].userId.id = NO_USER;
    }
}

void insertEquipment(UserList *users, EquipmentList *equipment) {
    if (equipment->equipmentCount == equipment->equipmentSize) {
        expandEquipment(equipment);
    }
    if (equipment->equipmentCount < equipment->equipmentSize) {
        if (insert1Equipment(users, equipment) == -1) {
            puts(ERROR_EQUIPMENT_NAME);
        }
    } else {
        puts(ERROR_EQUIPMENT_ADD);
    }
}

int insert1Equipment(UserList *users, EquipmentList *equipment) {
    int i;
    char name[EQUIPMENT_NAME_MAX_LENGTH];
    const char* categories[CATEGORY_OPTIONS] = {"Printer", "Computer", "Portable", "Monitor", "Router", "Switch", "TV", "Projector", "Access controller", "Mouse", "Accessory", "Other"};
    if (equipment->equipmentCount == equipment->equipmentSize) {
        expandEquipment(equipment);
    }
    if (equipment->equipmentCount > equipment->equipmentSize) {
        puts(ERROR_EQUIPMENT_ADD);
    }
    equipment->equipment[equipment->equipmentCount].equipmentId.id = equipment->nextEquipmentId++;
    listEquipmentExceptForRecycling(*equipment);
    readString(name, EQUIPMENT_NAME_MAX_LENGTH, MSG_GET_EQUIPMENT_NAME);
    if (searchEquipmentFromName(*equipment, name) == -1) {
        strcpy(equipment->equipment[equipment->equipmentCount].equipmentName, name);
        putchar('\n');
        for (i = 0; i < CATEGORY_OPTIONS; i++) {
            printf("%d - %s\n", i + 1, categories[i]);
        }
        i = getInt(1, CATEGORY_OPTIONS, MSG_GET_OPTION);
        strcpy(equipment->equipment[equipment->equipmentCount].category, categories[i - 1]);
        equipment->equipment[equipment->equipmentCount].date.day = getInt(MIN_DAY, MAX_DAY, MSG_GET_ACQUISITION_DAY);
        equipment->equipment[equipment->equipmentCount].date.month = getInt(MIN_MONTH, MAX_MONTH, MSG_GET_ACQUISITION_MONTH);
        equipment->equipment[equipment->equipmentCount].date.year = getInt(MIN_YEAR, MAX_YEAR, MSG_GET_ACQUISITION_YEAR);
        equipment->equipment[equipment->equipmentCount].equipmentStatus = OPERATIONAL_STATUS_VALUE;
        insertUserIntoEquipment(users, equipment);
        equipment->equipment[equipment->equipmentCount].maintenanceHistory.maintenance = (Maintenance*) calloc(INITIAL_SIZE_MAINTENANCE, sizeof(Maintenance));
        if (equipment->equipment[equipment->equipmentCount].maintenanceHistory.maintenance == NULL) {
            puts(ERROR_ALLOC_MAINTENANCE);
            exit(EXIT_FAILURE);
        }
        equipment->equipment[equipment->equipmentCount].maintenanceHistory.maintenanceCount = 0;
        equipment->equipment[equipment->equipmentCount].maintenanceHistory.maintenanceSize = INITIAL_SIZE_MAINTENANCE;
        puts(EQUIPMENT_ADD);
        return equipment->equipmentCount++;
    }
    return -1;
}

void readStatusAndUserForEquipment(Equipment *equipment, UserList *users) {
    int i, pos;
    equipment->equipmentStatus = getInt(OPERATIONAL_STATUS_VALUE, FOR_RECYCLING_STATUS_VALUE, MSG_GET_EQUIPMENT_STATUS);
    if (equipment->equipmentStatus == FOR_RECYCLING_STATUS_VALUE) {
        puts(ERROR_UPDATE_FOR_RECYCLING_EQUIPMENT);
        for (i = 0; i < users->userCount; i++) {
            if (users->users[i].userId.id == equipment->userId.id) {
                equipment->userId.id = NO_USER;
                puts(ERROR_UPDATE_DISSOCIATE_EQUIPMENT);
            }
        }
        return;
    }
    listActiveUsers(*users);
    pos = getInt(NO_USER, users->userCount, MSG_GET_OTHER_USER);
    if (pos != -1 && pos != 0) {
        if (users->users[pos - 1].userStatus == ACTIVE_STATUS_VALUE) {
            equipment->userId.id = users->users[pos - 1].userId.id;
        } else {
            puts(ERROR_USER_AGROUP);
            return;
        }
    } 
    if (pos == -1) {
        equipment->userId.id = NO_USER;
    }
}

void updateEquipment(EquipmentList *equipment, UserList *users) {
    int pos;
    if (equipment->equipmentCount == 0) {
        puts(ERROR_EMPTY_LIST);
        return;
    }
    pos = searchEquipmentFromId(*equipment, getInt(1, searchMaxEquipmentId(*equipment), MSG_GET_EQUIPMENT_ID_TO_UPDATE_EQUIPMENT));
    if (pos != -1 && equipment->equipment[pos].equipmentStatus == FOR_RECYCLING_STATUS_VALUE) {
        puts(ERROR_FOR_RECYCLING_EQUIPMENT);
    }
    if (pos != -1 && equipment->equipment[pos].equipmentStatus != FOR_RECYCLING_STATUS_VALUE) {
        readStatusAndUserForEquipment(&equipment->equipment[pos], users);
        puts(EQUIPMENT_UPDATE);
    } 
    if (pos == -1) {
        puts(ERROR_EQUIPMENT_NOT_FOUND);
    }
}

void insertEquipmentMaintenance(EquipmentList *equipment) {
    int pos, aux, movementNumber;
    listEquipmentUnderMaintenance(*equipment);
    if (equipment->equipmentCount > 0) {
        if (equipment->equipment->maintenanceHistory.maintenanceCount == equipment->equipment->maintenanceHistory.maintenanceSize) {
            expandMaintenance(equipment);
        }
    }
    if (equipment->equipmentCount == 0) {
        puts(ERROR_EMPTY_LIST);
        return;
    }
    pos = searchEquipmentFromId(*equipment, getInt(1, searchMaxEquipmentId(*equipment), MSG_GET_EQUIPMENT_ID_TO_MAINTENANCE_EQUIPMENT));
    if (pos == -1) {
        puts(ERROR_EQUIPMENT_NOT_FOUND);
        return;
    } else if (equipment->equipment[pos].equipmentStatus != UNDER_MAINTENANCE_STATUS_VALUE) {
        puts(ERROR_MAINTENANCE);
        return;
    }
    printf("\nMaintenance: %d/%d", equipment->equipment[pos].maintenanceHistory.maintenanceCount, equipment->equipment[pos].maintenanceHistory.maintenanceSize);
    do {
        aux = 1;
        movementNumber = getInt(MIN_MAINTENANCE_MOVEMENT_NUMBER_LIST, MAX_MAINTENANCE_MOVEMENT_NUMBER_LIST, MSG_GET_MOVEMENT_NUMBER);
        if (searchForMovementNumber(*equipment, movementNumber) != -1) {
            puts(ERROR_MOVEMENT_NUMBER);
            aux = 0;
        }
    } while (aux == 0);
    readEquipmentMaintenance(&equipment->equipment[pos], movementNumber);
    equipment->equipment[pos].maintenanceHistory.maintenanceCount++;
    puts(EQUIPMENT_MAINTENANCE);
}

void removeEquipment(EquipmentList *equipment) {
    int i, pos;
    if (equipment->equipmentCount == 0) {
        puts(ERROR_EMPTY_LIST);
        return;
    }
    pos = searchEquipmentFromId(*equipment, getInt(1, searchMaxEquipmentId(*equipment), MSG_GET_EQUIPMENT_ID_TO_REMOVE_EQUIPMENT));
    if (pos == -1) {
        puts(ERROR_EQUIPMENT_NOT_FOUND);
        return;
    } else if (equipment->equipment[pos].equipmentStatus == FOR_RECYCLING_STATUS_VALUE) {
        freeMaintenance(&equipment->equipment[pos]);
        for (i = pos; i < equipment->equipmentCount - 1; i++) {
            equipment->equipment[i] = equipment->equipment[i + 1];
        }
        cleanEquipmentData(&equipment->equipment[i]);
        equipment->equipmentCount--;
        puts(EQUIPMENT_DEL);
    } else {
        puts(ERROR_EQUIPMENT_DEL);
    }
}