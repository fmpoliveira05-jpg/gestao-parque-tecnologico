/**
* @file memory_and_files.c
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
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
#include <string.h>
#include "input.h"
#include "memory_and_files.h"

/**
 * @brief Allocates a zero-initialised block or aborts with a message (allocation failure is unrecoverable here).
 */
static void *allocOrExit(size_t count, size_t size, const char *errorMessage) {
    void *block = calloc(count, size);
    if (block == NULL) {
        puts(errorMessage);
        exit(EXIT_FAILURE);
    }
    return block;
}

/**
 * @brief Puts an EquipmentList in a valid empty state (used on first run or when the file is unreadable).
 */
static void initEmptyEquipmentList(EquipmentList *equipment) {
    equipment->equipment = allocOrExit(INITIAL_SIZE_EQUIPMENT, sizeof (Equipment), ERROR_ALLOC_EQUIPMENT);
    equipment->equipmentCount = 0;
    equipment->equipmentSize = INITIAL_SIZE_EQUIPMENT;
    equipment->nextEquipmentId = 1;
}

/**
 * @brief Puts a UserList in a valid empty state (used on first run or when the file is unreadable).
 */
static void initEmptyUserList(UserList *users) {
    users->users = allocOrExit(INITIAL_SIZE_USERS, sizeof (User), ERROR_ALLOC_USERS);
    users->userCount = 0;
    users->userSize = INITIAL_SIZE_USERS;
    users->nextUserId = 1;
}

void loadEquipment(EquipmentList *equipment, const char *filename) {
    int i, count = 0, nextId = 1;
    FILE *fp = fopen(filename, "rb");

    /* A missing or empty file simply means that the program is being used for the first time. */
    if (fp == NULL || fread(&count, sizeof (int), 1, fp) != 1 || fread(&nextId, sizeof (int), 1, fp) != 1 || count <= 0) {
        if (fp != NULL) {
            fclose(fp);
        }
        initEmptyEquipmentList(equipment);
        return;
    }

    equipment->equipmentCount = count;
    equipment->equipmentSize = count;
    equipment->nextEquipmentId = nextId;
    equipment->equipment = allocOrExit((size_t) count, sizeof (Equipment), ERROR_ALLOC_EQUIPMENT);

    for (i = 0; i < count; i++) {
        Equipment *current = &equipment->equipment[i];
        int maintenanceCount = 0;
        int capacity;

        if (fread(current, sizeof (Equipment), 1, fp) != 1 || fread(&maintenanceCount, sizeof (int), 1, fp) != 1 || maintenanceCount < 0) {
            puts(ERROR_CORRUPTED_FILE);
            equipment->equipmentCount = i;
            break;
        }
        /* The pointer stored in the file is meaningless in a new execution: allocate a fresh array
         * big enough for every saved record (previously only 3 slots were allocated, overflowing
         * whenever an equipment had more than 3 maintenance records). */
        capacity = maintenanceCount > INITIAL_SIZE_MAINTENANCE ? maintenanceCount : INITIAL_SIZE_MAINTENANCE;
        current->maintenanceHistory.maintenance = allocOrExit((size_t) capacity, sizeof (Maintenance), ERROR_ALLOC_MAINTENANCE);
        current->maintenanceHistory.maintenanceSize = capacity;
        current->maintenanceHistory.maintenanceCount = (int) fread(current->maintenanceHistory.maintenance, sizeof (Maintenance), (size_t) maintenanceCount, fp);
    }
    fclose(fp);
    puts(LOAD_EQUIPMENT_DATA);
}

void expandMaintenance(Equipment *equipment) {
    int size = equipment->maintenanceHistory.maintenanceSize == 0 ? INITIAL_SIZE_MAINTENANCE : equipment->maintenanceHistory.maintenanceSize * 2;
    Maintenance *temp = realloc(equipment->maintenanceHistory.maintenance, sizeof (Maintenance) * (size_t) size);
    if (temp == NULL) {
        puts(ERROR_REALLOC_MAINTENANCE);
        exit(EXIT_FAILURE);
    }
    /* realloc does not clear the new slots; zero them so no garbage is ever written to disk. */
    memset(temp + equipment->maintenanceHistory.maintenanceSize, 0, sizeof (Maintenance) * (size_t) (size - equipment->maintenanceHistory.maintenanceSize));
    equipment->maintenanceHistory.maintenanceSize = size;
    equipment->maintenanceHistory.maintenance = temp;
}

int saveEquipment(const EquipmentList *equipment, const char *filename) {
    int i;
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        puts(ERROR_SAVE_FILE);
        return 0;
    }
    fwrite(&equipment->equipmentCount, sizeof (int), 1, fp);
    fwrite(&equipment->nextEquipmentId, sizeof (int), 1, fp);
    for (i = 0; i < equipment->equipmentCount; i++) {
        const MaintenanceHistory *history = &equipment->equipment[i].maintenanceHistory;
        fwrite(&equipment->equipment[i], sizeof (Equipment), 1, fp);
        fwrite(&history->maintenanceCount, sizeof (int), 1, fp);
        fwrite(history->maintenance, sizeof (Maintenance), (size_t) history->maintenanceCount, fp);
    }
    fclose(fp);
    return 1;
}

void expandEquipment(EquipmentList *equipment) {
    int size = equipment->equipmentSize == 0 ? INITIAL_SIZE_EQUIPMENT : equipment->equipmentSize * 2;
    Equipment *temp = realloc(equipment->equipment, sizeof (Equipment) * (size_t) size);
    if (temp == NULL) {
        puts(ERROR_REALLOC_EQUIPMENT);
        exit(EXIT_FAILURE);
    }
    memset(temp + equipment->equipmentSize, 0, sizeof (Equipment) * (size_t) (size - equipment->equipmentSize));
    equipment->equipmentSize = size;
    equipment->equipment = temp;
}

void freeEquipment(EquipmentList *equipment) {
    int i;
    if (equipment->equipment != NULL) {
        /* Each equipment owns its own maintenance array, which must be released first. */
        for (i = 0; i < equipment->equipmentCount; i++) {
            freeMaintenance(&equipment->equipment[i]);
        }
        free(equipment->equipment);
        equipment->equipment = NULL;
    }
    equipment->equipmentCount = equipment->equipmentSize = 0;
}

void loadUsers(UserList *users, const char *filename) {
    int count = 0, nextId = 1;
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL || fread(&count, sizeof (int), 1, fp) != 1 || fread(&nextId, sizeof (int), 1, fp) != 1 || count <= 0) {
        if (fp != NULL) {
            fclose(fp);
        }
        initEmptyUserList(users);
        return;
    }

    users->users = allocOrExit((size_t) count, sizeof (User), ERROR_ALLOC_USERS);
    users->userSize = count;
    users->nextUserId = nextId;
    users->userCount = (int) fread(users->users, sizeof (User), (size_t) count, fp);
    if (users->userCount != count) {
        puts(ERROR_CORRUPTED_FILE);
    }
    fclose(fp);
    puts(LOAD_USERS_DATA);
}

int saveUsers(const UserList *users, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        puts(ERROR_SAVE_FILE);
        return 0;
    }
    fwrite(&users->userCount, sizeof (int), 1, fp);
    fwrite(&users->nextUserId, sizeof (int), 1, fp);
    fwrite(users->users, sizeof (User), (size_t) users->userCount, fp);
    fclose(fp);
    return 1;
}

void expandUsers(UserList *users) {
    int size = users->userSize == 0 ? INITIAL_SIZE_USERS : users->userSize * 2;
    User *temp = realloc(users->users, sizeof (User) * (size_t) size);
    if (temp == NULL) {
        puts(ERROR_REALLOC_USERS);
        exit(EXIT_FAILURE);
    }
    memset(temp + users->userSize, 0, sizeof (User) * (size_t) (size - users->userSize));
    users->userSize = size;
    users->users = temp;
}

void freeUsers(UserList *users) {
    free(users->users);
    users->users = NULL;
    users->userCount = users->userSize = 0;
}

void freeMaintenance(Equipment *equipment) {
    free(equipment->maintenanceHistory.maintenance);
    equipment->maintenanceHistory.maintenance = NULL;
    equipment->maintenanceHistory.maintenanceCount = 0;
    equipment->maintenanceHistory.maintenanceSize = 0;
}
