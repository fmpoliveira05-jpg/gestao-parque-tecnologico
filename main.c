/**
* @file main.c
* @author 8230148
* @date 04-02-2024
* @version 1
* @copyright Copyright (C) 8230148 2024. All Rights MIT Licensed.
* @note If you have any questions, contact 8230148@estg.ipp.pt.
*
* @brief This C program's main objective is can record the maintenance history of all equipment
* in the technology park of a given organization. It must also store data relating to users and equipment.
*
* The main file contains a collection of functions designed to facilitate the implementation of requested features
* in a C program. It is mainly composed of libraries created by the programmer and includes all the libraries necessary
* to execute this project, including manipulating dynamic memory ("stdlib.h") and files ("stdio.h").
*/

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "users.h"
#include "equipment.h"
#include "searchs.h"
#include "memory_and_files.h"
#include "lists.h"

/**
* @brief This function is responsible for printing the program's main menu, being an intermediary
 * for loading program data from files, allocating memory for users, equipment and maintenance
 * and freeing all allocated memory at the end.
* @return 0 upon successful execution.
*/
int main() {
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
        printf("\n0-\tSave And Exit");
        printf(SPACER);
        op = getInt(0, 5, MSG_GET_OPTION);
        switch (op) {
            case 0:
                saveUsers(&users, FILENAME_USERS);
                saveEquipment(&equipment, FILENAME_EQUIPMENT);
                puts(SAVE_DATA);
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

