/**
* @file main.c
* @author Francisco Miguel Pereira Oliveira
* @version 2.0
* @copyright Copyright (C) 2024 Francisco Miguel Pereira Oliveira. MIT License.
*
* @brief Technology park manager: keeps the inventory of an organisation's IT equipment,
* the users they are assigned to and the full maintenance history of every device.
*
* This file only contains the main menu; each feature lives in its own module
* (equipment, users, lists, search, date, input and memory_and_files).
*/

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "users.h"
#include "equipment.h"
#include "search.h"
#include "memory_and_files.h"
#include "lists.h"

/**
* @brief Entry point: loads the data files, shows the main menu and frees all memory on exit.
*
* Data is saved when the user leaves the program (option 0) or at any time through option 6.
* @return 0 upon successful execution.
*/
int main(void) {
    int op;
    EquipmentList equipment;
    UserList users;
    loadEquipment(&equipment, FILENAME_EQUIPMENT);
    loadUsers(&users, FILENAME_USERS);
    do {
        printf("\n\nMAIN\tMENU");
        printf("\n1-\tManage Equipment");
        printf("\n2-\tManage Users");
        printf("\n3-\tView Lists");
        printf("\n4-\tSearch Equipment");
        printf("\n5-\tView Additional Information About Program");
        printf("\n6-\tSave Data Now");
        printf("\n0-\tSave And Exit");
        printf(SPACER);
        op = getInt(0, 6, MSG_GET_OPTION);
        switch (op) {
            case 0:
            case 6:
                if (saveUsers(&users, FILENAME_USERS) && saveEquipment(&equipment, FILENAME_EQUIPMENT)) {
                    puts(SAVE_DATA);
                }
                break;
            case 1:
                logMessage("Manage Equipment", FILENAME_LOGS);
                menuForEquipment(&users, &equipment);
                break;
            case 2:
                logMessage("Manage Users", FILENAME_LOGS);
                menuForUsers(&equipment, &users);
                break;
            case 3:
                logMessage("View Lists", FILENAME_LOGS);
                menuForLists(&equipment);
                break;
            case 4:
                logMessage("Search Equipment", FILENAME_LOGS);
                searchEquipment(equipment);
                break;
            case 5:
                additionalInformationAboutProgram();
                break;
            default:
                puts(INVALID_VALUE);
                break;
        }
    } while (op != 0);
    freeEquipment(&equipment);
    freeUsers(&users);
    return (EXIT_SUCCESS);
}

