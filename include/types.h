/**
 * @file types.h
 * @author Francisco Miguel Pereira Oliveira
 * @brief Domain types shared by every module: users, equipment and maintenance records.
 *
 * Keeping the data model in a single header avoids circular includes and makes it
 * obvious which structures are persisted to disk.
 */

#ifndef TYPES_H
#define TYPES_H

#define EQUIPMENT_NAME_MAX_LENGTH 50
#define EQUIPMENT_CATEGORY_MAX_LENGTH 18
#define MAINTENANCE_TYPE_MAX_LENGTH 40
#define MAINTENANCE_NOTES_MAX_LENGTH 100
#define USER_ACRONYM_MAX_LENGTH 10
#define USER_ROLE_MAX_LENGTH 40
#define USERNAME_MAX_LENGTH 50
#define CATEGORY_OPTIONS 12 // number of initialized categories to be assigned to equipment



typedef enum {
    INACTIVE, ACTIVE
} UserStatus;

typedef enum {
    OPERATIONAL = 1, UNDER_MAINTENANCE, N_OPERATIONAL, FOR_RECYCLING
} EquipmentStatus;

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int id;
} Id;

typedef struct {
    char maintenanceType[MAINTENANCE_TYPE_MAX_LENGTH];
    char notes[MAINTENANCE_NOTES_MAX_LENGTH];
    int movementNumber; // equipment maintenance movement number (must be unique)
    Date date; // equipment maintenance date
} Maintenance;

typedef struct {
    int maintenanceCount; // quantity of existing maintenance (initialized with 0)
    int maintenanceSize; // quantity of maintenance allocated (initialized with INITIAL_SIZE_MAINTENANCE)
    Maintenance *maintenance; // pointer for allocated maintenance
} MaintenanceHistory;

typedef struct {
    char equipmentName[EQUIPMENT_NAME_MAX_LENGTH]; // equipment name (must be unique)
    char category[EQUIPMENT_CATEGORY_MAX_LENGTH];
    Id equipmentId;
    Id userId; // user ID assigned to the technological equipment
    Date date; // equipment acquisition date
    EquipmentStatus equipmentStatus;
    MaintenanceHistory maintenanceHistory;
} Equipment;

typedef struct {
    int equipmentCount; // quantity of existing equipment (initialized with 0)
    int equipmentSize; // quantity of equipment allocated (initialized with INITIAL_SIZE_EQUIPMENT)
    int nextEquipmentId; // control variable for the ID of each equipment
    Equipment *equipment; // pointer for allocated equipment
} EquipmentList;

typedef struct {
    char acronym[USER_ACRONYM_MAX_LENGTH]; // user acronym (must be unique)
    char username[USERNAME_MAX_LENGTH];
    char role[USER_ROLE_MAX_LENGTH];
    Id userId;
    UserStatus userStatus;
} User;

typedef struct {
    int userCount; // quantity of existing users (initialized with 0)
    int userSize; // quantity of users allocated (initialized with INITIAL_SIZE_USERS)
    int nextUserId; // control variable for the ID of each user
    User *users; // pointer for allocated users
} UserList;

/* Numeric values stored in the status fields (kept as macros for readability in comparisons). */
#define OPERATIONAL_STATUS_VALUE 1
#define UNDER_MAINTENANCE_STATUS_VALUE 2
#define N_OPERATIONAL_STATUS_VALUE 3
#define FOR_RECYCLING_STATUS_VALUE 4
#define INACTIVE_STATUS_VALUE 0
#define ACTIVE_STATUS_VALUE 1
#define NO_USER -1 // value assigned to the equipment when it has no associated user

#endif /* TYPES_H */
