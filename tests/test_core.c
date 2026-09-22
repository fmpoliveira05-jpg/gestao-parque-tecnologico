/**
 * @file test_core.c
 * @author Francisco Miguel Pereira Oliveira
 * @brief Unit tests for the non-interactive parts of the program (dates, searches and persistence).
 *
 * The project is small, so instead of adding an external framework the tests use a tiny
 * CHECK macro. Run them with `make test`.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "search.h"
#include "memory_and_files.h"

static int failures = 0;
static int checks = 0;

#define CHECK(condition) do { \
        checks++; \
        if (!(condition)) { \
            failures++; \
            fprintf(stderr, "FAILED %s:%d: %s\n", __FILE__, __LINE__, #condition); \
        } \
    } while (0)

static Date makeDate(int day, int month, int year) {
    Date date;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

static Equipment makeEquipment(int id, const char *name, int status, Date date) {
    Equipment equipment;
    memset(&equipment, 0, sizeof equipment);
    equipment.equipmentId.id = id;
    equipment.userId.id = NO_USER;
    strcpy(equipment.equipmentName, name);
    strcpy(equipment.category, "Laptop");
    equipment.equipmentStatus = (EquipmentStatus) status;
    equipment.date = date;
    return equipment;
}

static void testCompareDates(void) {
    CHECK(compareDates(makeDate(1, 1, 2020), makeDate(2, 1, 2020)) == -1);
    CHECK(compareDates(makeDate(1, 2, 2020), makeDate(31, 1, 2020)) == 1);
    CHECK(compareDates(makeDate(31, 12, 2019), makeDate(1, 1, 2020)) == -1);
    CHECK(compareDates(makeDate(5, 5, 2021), makeDate(5, 5, 2021)) == 0);
}

static void testIsValidDate(void) {
    CHECK(isValidDate(makeDate(29, 2, 2024)));   /* leap year */
    CHECK(!isValidDate(makeDate(29, 2, 2023)));  /* not a leap year */
    CHECK(!isValidDate(makeDate(31, 4, 2023)));  /* April has 30 days */
    CHECK(isValidDate(makeDate(29, 2, 2000)));   /* divisible by 400 */
    CHECK(!isValidDate(makeDate(29, 2, 2100))); /* 2100 is not a leap year */
    CHECK(!isValidDate(makeDate(0, 1, 2020)));
    CHECK(!isValidDate(makeDate(1, 13, 2020)));
    CHECK(!isValidDate(makeDate(1, 1, MIN_YEAR - 1)));
}

static void testSearchHelpers(void) {
    Equipment laptop = makeEquipment(1, "Dell XPS 13", OPERATIONAL_STATUS_VALUE, makeDate(10, 3, 2022));

    CHECK(equipmentNameContains(&laptop, "dell"));
    CHECK(equipmentNameContains(&laptop, "XPS"));
    CHECK(equipmentNameContains(&laptop, ""));
    CHECK(!equipmentNameContains(&laptop, "Lenovo"));
    CHECK(!equipmentNameContains(&laptop, "Dell XPS 13 Plus"));

    CHECK(equipmentMatchesStatusAndDate(&laptop, OPERATIONAL_STATUS_VALUE, makeDate(10, 3, 2022)));
    CHECK(!equipmentMatchesStatusAndDate(&laptop, UNDER_MAINTENANCE_STATUS_VALUE, makeDate(10, 3, 2022)));
    CHECK(!equipmentMatchesStatusAndDate(&laptop, OPERATIONAL_STATUS_VALUE, makeDate(11, 3, 2022)));
}

static void testMaxIds(void) {
    Equipment items[3];
    EquipmentList list;

    list.equipment = items;
    list.equipmentCount = 0;
    CHECK(searchMaxEquipmentId(list) == 0);

    /* IDs are not necessarily ordered after removals: the old implementation got this wrong. */
    items[0] = makeEquipment(7, "A", OPERATIONAL_STATUS_VALUE, makeDate(1, 1, 2020));
    items[1] = makeEquipment(3, "B", OPERATIONAL_STATUS_VALUE, makeDate(1, 1, 2020));
    items[2] = makeEquipment(5, "C", OPERATIONAL_STATUS_VALUE, makeDate(1, 1, 2020));
    list.equipmentCount = 3;
    CHECK(searchMaxEquipmentId(list) == 7);
    CHECK(searchEquipmentFromId(list, 5) == 2);
    CHECK(searchEquipmentFromId(list, 42) == -1);
}

/* Regression test: equipment with more than INITIAL_SIZE_MAINTENANCE records used to overflow on load. */
static void testPersistenceRoundTrip(void) {
    const char *file = "test_equipment.bin";
    const int records = INITIAL_SIZE_MAINTENANCE * 3;
    EquipmentList saved, loaded;
    int i;

    loadEquipment(&saved, "file-that-does-not-exist.bin");
    CHECK(saved.equipmentCount == 0);
    CHECK(saved.nextEquipmentId == 1);

    saved.equipment[0] = makeEquipment(1, "Router Cisco", UNDER_MAINTENANCE_STATUS_VALUE, makeDate(2, 2, 2021));
    saved.equipment[0].maintenanceHistory.maintenance = calloc(INITIAL_SIZE_MAINTENANCE, sizeof (Maintenance));
    saved.equipment[0].maintenanceHistory.maintenanceSize = INITIAL_SIZE_MAINTENANCE;
    saved.equipmentCount = 1;
    saved.nextEquipmentId = 2;

    for (i = 0; i < records; i++) {
        MaintenanceHistory *history = &saved.equipment[0].maintenanceHistory;
        if (history->maintenanceCount >= history->maintenanceSize) {
            expandMaintenance(&saved.equipment[0]);
        }
        history->maintenance[history->maintenanceCount].movementNumber = 100 + i;
        history->maintenance[history->maintenanceCount].date = makeDate(1 + i, 1, 2023);
        strcpy(history->maintenance[history->maintenanceCount].maintenanceType, "Firmware update");
        history->maintenanceCount++;
    }

    CHECK(saveEquipment(&saved, file));
    loadEquipment(&loaded, file);

    CHECK(loaded.equipmentCount == 1);
    CHECK(loaded.nextEquipmentId == 2);
    CHECK(strcmp(loaded.equipment[0].equipmentName, "Router Cisco") == 0);
    CHECK(loaded.equipment[0].maintenanceHistory.maintenanceCount == records);
    CHECK(loaded.equipment[0].maintenanceHistory.maintenanceSize >= records);
    CHECK(loaded.equipment[0].maintenanceHistory.maintenance[records - 1].movementNumber == 100 + records - 1);

    freeEquipment(&saved);
    freeEquipment(&loaded);
    remove(file);
}

static void testUsersPersistence(void) {
    const char *file = "test_users.bin";
    UserList saved, loaded;

    loadUsers(&saved, "file-that-does-not-exist.bin");
    CHECK(saved.userCount == 0);

    memset(&saved.users[0], 0, sizeof (User));
    saved.users[0].userId.id = 1;
    strcpy(saved.users[0].acronym, "FMO");
    strcpy(saved.users[0].username, "Francisco");
    strcpy(saved.users[0].role, "Developer");
    saved.users[0].userStatus = ACTIVE;
    saved.userCount = 1;
    saved.nextUserId = 2;

    CHECK(saveUsers(&saved, file));
    loadUsers(&loaded, file);
    CHECK(loaded.userCount == 1);
    CHECK(loaded.nextUserId == 2);
    CHECK(strcmp(loaded.users[0].acronym, "FMO") == 0);
    CHECK(searchUserFromId(loaded, 1) == 0);

    freeUsers(&saved);
    freeUsers(&loaded);
    remove(file);
}

int main(void) {
    testCompareDates();
    testIsValidDate();
    testSearchHelpers();
    testMaxIds();
    testPersistenceRoundTrip();
    testUsersPersistence();

    printf("\n%d checks, %d failed\n", checks, failures);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
