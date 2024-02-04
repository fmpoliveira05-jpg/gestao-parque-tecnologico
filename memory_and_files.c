/**
* @file memory_and_files.c
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief A source file that provides utility functions for allocating, reallocating, and freeing memory in addition to files.
*
* This source file contains a collection of functions designed to facilitate the implementation of requested features
* for dynamic memory and files
* in a C program. Includes functions to allocate, reallocate and free memory for users, equipment and maintenance,
* as well as files to save data and retrieving data from files to the program memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "memory_and_files.h"


void loadEquipment(EquipmentList *equipment, char *filename) {
    int i, success = 0;
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        puts(ERROR_OPEN_FILE);
        exit(EXIT_FAILURE);
    }
    fread(&equipment->equipmentCount, sizeof (int), 1, fp);
    fread(&equipment->nextEquipmentId, sizeof (int), 1, fp);
    if (equipment->equipmentCount > 0) {
        equipment->equipmentSize = equipment->equipmentCount;
        equipment->equipment = (Equipment*) malloc(equipment->equipmentCount * sizeof (Equipment));
        if (equipment->equipment == NULL) {
            puts(ERROR_ALLOC_EQUIPMENT);
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < equipment->equipmentCount; i++) {
            fread(&equipment->equipment[i], sizeof (Equipment), 1, fp);
            fread(&equipment->equipment[i].maintenanceHistory.maintenanceCount, sizeof (int), 1, fp);
            equipment->equipment[i].maintenanceHistory.maintenance = (Maintenance*) calloc(INITIAL_SIZE_MAINTENANCE, sizeof (Maintenance));
            if (equipment->equipment[i].maintenanceHistory.maintenance == NULL) {
                puts(ERROR_ALLOC_MAINTENANCE);
                exit(EXIT_FAILURE);
            }
            fread(equipment->equipment[i].maintenanceHistory.maintenance, sizeof (Maintenance), equipment->equipment[i].maintenanceHistory.maintenanceCount, fp);
        }
        success = 1;
        puts(LOAD_EQUIPMENT_DATA);
    }
    fclose(fp);
    
    if (!success) {
        fp = fopen(filename, "wb");
        if (fp == NULL) {
            puts(ERROR_OPEN_FILE);
            exit(EXIT_FAILURE);
        }
        equipment->equipment = (Equipment*) malloc(INITIAL_SIZE_EQUIPMENT * sizeof(Equipment));
        if (equipment->equipment == NULL) {
            puts(ERROR_ALLOC_EQUIPMENT);
            exit(EXIT_FAILURE);
        }
        equipment->equipmentCount = 0;
        equipment->equipmentSize = INITIAL_SIZE_EQUIPMENT;
        equipment->nextEquipmentId = 1;
        fclose(fp);
    }
}

void expandMaintenance(EquipmentList *equipment) {
    int size = (equipment->equipment->maintenanceHistory.maintenanceSize) == 0 ? INITIAL_SIZE_MAINTENANCE : equipment->equipment->maintenanceHistory.maintenanceSize * 2;
    Maintenance *temp = (Maintenance*) realloc(equipment->equipment->maintenanceHistory.maintenance, sizeof (Maintenance) * (size));
    if (temp == NULL) {
        puts(ERROR_REALLOC_MAINTENANCE);
        exit(EXIT_FAILURE);
    }
    equipment->equipment->maintenanceHistory.maintenanceSize = size;
    equipment->equipment->maintenanceHistory.maintenance = temp;
}

void saveEquipment(EquipmentList *equipment, char *filename) {
    int i;
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        puts(ERROR_SAVE_FILE);
        exit(EXIT_FAILURE);
    }
    fwrite(&equipment->equipmentCount, sizeof (int), 1, fp);
    fwrite(&equipment->nextEquipmentId, sizeof (int), 1, fp);
    for (i = 0; i < equipment->equipmentCount; i++) {
        fwrite(&equipment->equipment[i], sizeof (Equipment), 1, fp);
        fwrite(&equipment->equipment[i].maintenanceHistory.maintenanceCount, sizeof (int), 1, fp);
        fwrite(equipment->equipment[i].maintenanceHistory.maintenance, sizeof (Maintenance), equipment->equipment[i].maintenanceHistory.maintenanceCount, fp);
    }
    fclose(fp);
}

void expandEquipment(EquipmentList *equipment) {
    int size = (equipment->equipmentSize) == 0 ? INITIAL_SIZE_EQUIPMENT : equipment->equipmentSize * 2;
    Equipment *temp = (Equipment*) realloc(equipment->equipment, sizeof (Equipment) * (size));
    if (equipment->equipment == NULL) {
        puts(ERROR_REALLOC_EQUIPMENT);
        exit(EXIT_FAILURE);
    }
    equipment->equipmentSize = size;
    equipment->equipment = temp;
}

void freeEquipment(EquipmentList *equipment) {
    if (equipment->equipment) {
        free(equipment->equipment);
        equipment->equipment = NULL;
    }
    equipment = NULL;
}

void loadUsers(UserList *users, char *filename) {
    int i, sucess = 0;
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        puts(ERROR_OPEN_FILE);
        exit(EXIT_FAILURE);
    }
    fread(&users->userCount, sizeof (int), 1, fp);
    fread(&users->nextUserId, sizeof (int), 1, fp);
    if (users->userCount > 0) {
        users->userSize = users->userCount;
        users->users = (User*) malloc(users->userCount * sizeof (User));
        if (users->users == NULL) {
            puts(ERROR_ALLOC_USERS);
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < users->userCount; i++) {
            fread(&users->users[i], sizeof (User), 1, fp);
        }
        sucess = 1;
        puts(LOAD_USERS_DATA);
    }
    fclose(fp);
        
    if (!sucess) {
        fp = fopen(filename, "wb");
        if (fp == NULL) {
            puts(ERROR_OPEN_FILE);
            exit(EXIT_FAILURE);
        }
        users->users = (User*) malloc(INITIAL_SIZE_USERS * sizeof (User));
        if (users->users == NULL) {
            puts(ERROR_ALLOC_USERS);
            exit(EXIT_FAILURE);
        }
        users->userCount = 0;
        users->userSize = INITIAL_SIZE_USERS;
        users->nextUserId = 1;
        fclose(fp);
    }
}

void saveUsers(UserList *users, char *filename) {
    int i;
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        puts(ERROR_SAVE_FILE);
        exit(EXIT_FAILURE);
    }
    fwrite(&users->userCount, sizeof (int), 1, fp);
    fwrite(&users->nextUserId, sizeof (int), 1, fp);
    for (i = 0; i < users->userCount; i++) {
        fwrite(&users->users[i], sizeof (User), 1, fp);
    }
    fclose(fp);
}

void expandUsers(UserList *users) {
    int size = (users->userSize) == 0 ? INITIAL_SIZE_USERS : users->userSize * 2;
    User *temp = (User*) realloc(users->users, sizeof (User) * (size));
    if (temp == NULL) {
        puts(ERROR_REALLOC_USERS);
        exit(EXIT_FAILURE);
    }
    users->userSize = size;
    users->users = temp;
}

void freeUsers(UserList *users) {
    if (users->users) {
        free(users->users);
        users->users = NULL;
    }
    users = NULL;
}

void freeMaintenance(Equipment *equipment) {
    free(equipment->maintenanceHistory.maintenance);
    equipment->maintenanceHistory.maintenance = NULL;
    equipment->maintenanceHistory.maintenanceCount = 0;
    equipment->maintenanceHistory.maintenanceSize = 0;
}