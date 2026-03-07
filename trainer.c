#include <stdio.h>
#include "trainermag.h"
#include "GlobalFunctions.h" // for clearInputBuffer, Pause, etc.

// Helper function to resize trainers array
static void resizeTrainers(TrainerManager *tm_manager, int newCapacity)
{
    if (newCapacity > MAX_TRAINERS)
        newCapacity = MAX_TRAINERS;
    tm_manager->trainers = realloc(tm_manager->trainers, newCapacity * sizeof(struct Trainer));
    if (tm_manager->trainers == NULL)
    {
        printf("!!! MEMORY ALLOCATION FAILED !!!\n");
        exit(1);
    }
    tm_manager->capacity = newCapacity;
}

// return smallest unused trainer number (1-based) or -1 if none available
static int getNextTrainerNumber(TrainerManager *tm_manager)
{
    for (int num = 1; num <= MAX_TRAINERS; num++)
    {
        char idbuf[10];
        sprintf(idbuf, "TRN%03d", num);
        int used = 0;
        for (int i = 0; i < tm_manager->capacity; i++)
        {
            if (strcmp(tm_manager->trainers[i].id, idbuf) == 0)
            {
                used = 1;
                break;
            }
        }
        if (!used)
            return num;
    }
    return -1;
}

void tm_addTrainer(TrainerManager *tm_manager)
{
    if (tm_manager->capacity == 0)
    {
        resizeTrainers(tm_manager, INITIAL_TRAINERS);
    }
    if (tm_manager->count >= tm_manager->capacity)
    {
        resizeTrainers(tm_manager, tm_manager->capacity * 2);
    }
    if (tm_manager->count >= MAX_TRAINERS)
    {
        // there may still be gaps if some entries were deleted earlier
        int freeSlot = -1;
        for (int i = 0; i < tm_manager->capacity; i++)
        {
            if (tm_manager->trainers[i].id[0] == '\0')
            {
                freeSlot = i;
                break;
            }
        }
        if (freeSlot == -1)
        {
            printf("\n!!! SYSTEM FULLED CANNOT ADD MORE TRAINERS !!!\n");
            return;
        }
        // otherwise we will reuse the hole below
    }

    struct Trainer newTrainer;

    // determine next unused numeric ID (smallest missing number)
    int nextNum = getNextTrainerNumber(tm_manager);
    if (nextNum == -1)
    {
        printf("\n!!! NO AVAILABLE TRAINER ID FOUND !!!\n");
        return;
    }
    sprintf(newTrainer.id, "TRN%03d", nextNum);

    printf("\n--- ADD NEW TRAINER ---\n");
    printf("ENTER TRAINER NAME : ");
    fgets(newTrainer.name, MAX_NAME, stdin);
    newTrainer.name[strcspn(newTrainer.name, "\n")] = 0;

    printf("ENTER SPECIALTY : ");
    fgets(newTrainer.specialty, MAX_SPEC, stdin);
    newTrainer.specialty[strcspn(newTrainer.specialty, "\n")] = 0;

    printf("ENTER SALARY (VND): ");
    {
        char buf[32];
        if (fgets(buf, sizeof(buf), stdin))
        {
            sscanf(buf, "%f", &newTrainer.salary);
        }
    }

    // Initialize member list
    newTrainer.memberCount = 0;

    // find slot to insert (reuse empty if possible)
    int slot = -1;
    for (int i = 0; i < MAX_TRAINERS; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
        {
            slot = i;
            break;
        }
    }
    if (slot == -1)
        slot = tm_manager->count; // append at end

    tm_manager->trainers[slot] = newTrainer;
    tm_manager->count++;
    printf("\n[OK] SUCCESSFULLY ADDED TRAINER (ID: %s)\n", newTrainer.id);
    tm_saveTrainersToFile(tm_manager);
}

void tm_displayAllTrainers(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    printf("\n============================================ ALL TRAINERS LIST ============================================\n");
    printf("%-8s %-20s %-20s %-15s\n", "ID", "Name", "Specialty", "Salary (VND)");
    printf("==========================================================================================================\n");

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        printf("%-8s %-20s %-20s %-15.0f\n",
               tm_manager->trainers[i].id,
               tm_manager->trainers[i].name,
               tm_manager->trainers[i].specialty,
               tm_manager->trainers[i].salary);
    }
    printf("==========================================================================================================\n");
}

void tm_searchTrainerById(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    char searchId[10];
    printf("\nENTER TRAINER ID TO SEARCH (e.g., TRN001): ");
    fgets(searchId, 10, stdin);
    searchId[strcspn(searchId, "\n")] = 0;

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        if (strcmp(tm_manager->trainers[i].id, searchId) == 0)
        {
            printf("\n========== TRAINER INFORMATION ==========\n");
            printf("ID: %s\n", tm_manager->trainers[i].id);
            printf("Name: %s\n", tm_manager->trainers[i].name);
            printf("Specialty: %s\n", tm_manager->trainers[i].specialty);
            printf("Salary: %.0f VND\n", tm_manager->trainers[i].salary);
            printf("===================================\n");
            return;
        }
    }
    printf("\n!!! NO TRAINER FOUND WITH ID: %s !!!\n", searchId);
}

void tm_searchTrainerByName(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    char searchName[MAX_NAME];
    printf("\nENTER TRAINER NAME TO SEARCH: ");
    fgets(searchName, MAX_NAME, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int found = 0;
    printf("\n========== SEARCH RESULTS ==========\n");
    printf("%-8s %-20s %-20s %-15s\n", "ID", "Name", "Specialty", "Salary (VND)");
    printf("======================================================================================================\n");

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        if (strstr(tm_manager->trainers[i].name, searchName) != NULL)
        {
            printf("%-8s %-20s %-20s %-15.0f\n",
                   tm_manager->trainers[i].id,
                   tm_manager->trainers[i].name,
                   tm_manager->trainers[i].specialty,
                   tm_manager->trainers[i].salary);
            found = 1;
        }
    }

    if (!found)
    {
        printf("!!! NO TRAINER FOUND WITH NAME: %s !!!\n", searchName);
    }
    printf("======================================================================================================\n");
}

void tm_editTrainer(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    char editId[10];
    printf("\nENTER TRAINER ID TO EDIT (e.g., TRN001): ");
    fgets(editId, 10, stdin);
    editId[strcspn(editId, "\n")] = 0;

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        if (strcmp(tm_manager->trainers[i].id, editId) == 0)
        {
            printf("--- EDITING TRAINER INFORMATION ---\n");

            printf("1. Edit name (Current: %s): ", tm_manager->trainers[i].name);
            char temp[MAX_NAME];
            if (fgets(temp, MAX_NAME, stdin) && temp[0] != '\n')
            {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(tm_manager->trainers[i].name, temp);
            }

            printf("2. Edit specialty (Current: %s): ", tm_manager->trainers[i].specialty);
            if (fgets(temp, MAX_NAME, stdin) && temp[0] != '\n')
            {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(tm_manager->trainers[i].specialty, temp);
            }

            printf("3. Edit salary (Current: %.0f): ", tm_manager->trainers[i].salary);
            {
                char buf[32];
                if (fgets(buf, sizeof(buf), stdin))
                {
                    float tempSalary;
                    if (sscanf(buf, "%f", &tempSalary) == 1)
                    {
                        tm_manager->trainers[i].salary = tempSalary;
                    }
                }
            }

            printf("\n[OK] Trainer information updated successfully!\n");
            tm_saveTrainersToFile(tm_manager);
            return;
        }
    }
    printf("\n!!! NO TRAINER FOUND WITH ID: %s !!!\n", editId);
}

void tm_deleteTrainer(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    char deleteId[10];
    printf("\nENTER TRAINER ID TO DELETE (e.g., TRN001): ");
    fgets(deleteId, 10, stdin);
    deleteId[strcspn(deleteId, "\n")] = 0;

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        if (strcmp(tm_manager->trainers[i].id, deleteId) == 0)
        {
            printf("Are you sure you want to delete trainer '%s'? (y/n): ", tm_manager->trainers[i].name);
            char confirm_buf[4];
            if (fgets(confirm_buf, sizeof(confirm_buf), stdin))
            {
                char confirm = confirm_buf[0];
                if (confirm == 'y' || confirm == 'Y')
                {
                    // mark slot empty but keep other entries in place; this leaves a hole
                    tm_manager->trainers[i].id[0] = '\0';
                    tm_manager->trainers[i].name[0] = '\0';
                    tm_manager->trainers[i].specialty[0] = '\0';
                    tm_manager->trainers[i].salary = 0;
                    tm_manager->trainers[i].memberCount = 0;
                    tm_manager->count--;
                    printf("[OK] Trainer deleted successfully!\n");
                    tm_saveTrainersToFile(tm_manager);
                }
                else
                {
                    printf("Delete operation cancelled.\n");
                }
            }
            return;
        }
    }
    printf("\n!!! NO TRAINER FOUND WITH ID: %s !!!\n", deleteId);
}

void tm_saveTrainersToFile(TrainerManager *tm_manager)
{
    FILE *file = fopen(TRAINERS_FILE, "wb");
    if (file == NULL)
    {
        printf("!!! ERROR: Cannot open file for saving data! !!!\n");
        return;
    }

    // write only non-empty trainers
    int actual = 0;
    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] != '\0')
            actual++;
    }
    fwrite(&actual, sizeof(int), 1, file);
    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] != '\0')
        {
            fwrite(&tm_manager->trainers[i], sizeof(struct Trainer), 1, file);
        }
    }
    fclose(file);
    printf("[OK] DATA SAVED SUCCESSFULLY!\n");
}

int tm_loadTrainersFromFile(TrainerManager *tm_manager)
{
    FILE *file = fopen(TRAINERS_FILE, "rb");
    if (file == NULL)
    {
        return 0;
    }

    int count;
    fread(&count, sizeof(int), 1, file);
    resizeTrainers(tm_manager, count);
    // compact the data into the beginning of array
    for (int i = 0; i < count; i++)
    {
        fread(&tm_manager->trainers[i], sizeof(struct Trainer), 1, file);
    }
    fclose(file);

    tm_manager->count = count; // Set count directly in the struct
    return count;
}

void tm_displayTrainerMembers(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    // clear newline left by menu input
    clearInputBuffer();

    char searchId[10];
    printf("\nENTER TRAINER ID TO VIEW MEMBER LIST (e.g., TRN001): ");
    fgets(searchId, 10, stdin);
    searchId[strcspn(searchId, "\n")] = 0;

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        if (strcmp(tm_manager->trainers[i].id, searchId) == 0)
        {
            printf("\n========== MEMBER LIST OF TRAINER %s =========\n", tm_manager->trainers[i].name);
            if (tm_manager->trainers[i].memberCount == 0)
            {
                printf("No members assigned to this trainer.\n");
            }
            else
            {
                printf("Total members: %d\n", tm_manager->trainers[i].memberCount);
                printf("\nAssigned members:\n");
                for (int j = 0; j < tm_manager->trainers[i].memberCount; j++)
                {
                    printf("%d. %s\n", j + 1, tm_manager->trainers[i].memberIds[j]);
                }
            }
            printf("===============================================\n");
            return;
        }
    }
    printf("\n!!! NO TRAINER FOUND WITH ID: %s !!!\n", searchId);
}

void tm_assignMemberToTrainer(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    // clear newline from previous menu choice
    clearInputBuffer();

    char trainerId[10];
    printf("\nENTER TRAINER ID TO ASSIGN MEMBER (e.g., TRN001): ");
    fgets(trainerId, 10, stdin);
    trainerId[strcspn(trainerId, "\n")] = 0;

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        if (strcmp(tm_manager->trainers[i].id, trainerId) == 0)
        {
            if (tm_manager->trainers[i].memberCount >= MAX_MEMBERS_PER_TRAINER)
            {
                printf("\n!!! TRAINER '%s' HAS REACHED MAXIMUM MEMBER COUNT (%d)! !!!\n", tm_manager->trainers[i].name, MAX_MEMBERS_PER_TRAINER);
                return;
            }

            char memberId[10];
            printf("ENTER MEMBER ID TO ASSIGN (e.g., GYM001): ");
            fgets(memberId, 10, stdin);
            memberId[strcspn(memberId, "\n")] = 0;

            // Check if member already assigned
            for (int j = 0; j < tm_manager->trainers[i].memberCount; j++)
            {
                if (strcmp(tm_manager->trainers[i].memberIds[j], memberId) == 0)
                {
                    printf("\n!!! Member '%s' already assigned to this trainer! !!!\n", memberId);
                    return;
                }
            }

            // Add member
            strcpy(tm_manager->trainers[i].memberIds[tm_manager->trainers[i].memberCount], memberId);
            tm_manager->trainers[i].memberCount++;
            printf("\n[OK] Member '%s' assigned to trainer '%s' successfully!\n", memberId, tm_manager->trainers[i].name);
            tm_saveTrainersToFile(tm_manager);
            return;
        }
    }
    printf("\n!!! NO TRAINER FOUND WITH ID: %s !!!\n", trainerId);
}

void tm_removeMemberFromTrainer(TrainerManager *tm_manager)
{
    if (tm_manager->count == 0)
    {
        printf("\n*** NO TRAINERS IN SYSTEM ***\n");
        return;
    }

    // flush newline left by menu
    clearInputBuffer();

    char trainerId[10];
    printf("\nENTER TRAINER ID TO REMOVE MEMBER (e.g., TRN001): ");
    fgets(trainerId, 10, stdin);
    trainerId[strcspn(trainerId, "\n")] = 0;

    for (int i = 0; i < tm_manager->capacity; i++)
    {
        if (tm_manager->trainers[i].id[0] == '\0')
            continue;
        if (strcmp(tm_manager->trainers[i].id, trainerId) == 0)
        {
            if (tm_manager->trainers[i].memberCount == 0)
            {
                printf("\n*** TRAINER HAS NO MEMBERS! ***\n");
                return;
            }

            printf("\nAssigned members:\n");
            for (int j = 0; j < tm_manager->trainers[i].memberCount; j++)
            {
                printf("%d. %s\n", j + 1, tm_manager->trainers[i].memberIds[j]);
            }

            char memberId[10];
            printf("ENTER MEMBER ID TO REMOVE: ");
            fgets(memberId, 10, stdin);
            memberId[strcspn(memberId, "\n")] = 0;

            for (int j = 0; j < tm_manager->trainers[i].memberCount; j++)
            {
                if (strcmp(tm_manager->trainers[i].memberIds[j], memberId) == 0)
                {
                    // Remove member by shifting array
                    for (int k = j; k < tm_manager->trainers[i].memberCount - 1; k++)
                    {
                        strcpy(tm_manager->trainers[i].memberIds[k], tm_manager->trainers[i].memberIds[k + 1]);
                    }
                    tm_manager->trainers[i].memberCount--;
                    printf("\n[OK] Member '%s' removed from trainer '%s' successfully!\n", memberId, tm_manager->trainers[i].name);
                    tm_saveTrainersToFile(tm_manager);
                    return;
                }
            }
            printf("\n!!! Member '%s' not found in trainer's list! !!!\n", memberId);
            return;
        }
    }
    printf("\n!!! NO TRAINER FOUND WITH ID: %s !!!\n", trainerId);
}

void tm_sortTrainersByName(struct Trainer trainers[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(trainers[j].name, trainers[j + 1].name) > 0)
            {
                struct Trainer temp = trainers[j];
                trainers[j] = trainers[j + 1];
                trainers[j + 1] = temp;
            }
        }
    }
    printf("\n[OK] Trainers sorted by name successfully!\n");
}

void tm_displayMenu()
{
    printf("\n");
    printf("========== TRAINER MANAGEMENT =========\n");
    printf("1. ADD NEW TRAINER\n");
    printf("2. DISPLAY ALL TRAINERS\n");
    printf("3. SEARCH TRAINER BY ID\n");
    printf("4. SEARCH TRAINER BY NAME\n");
    printf("5. EDIT TRAINER INFO\n");
    printf("6. DELETE TRAINER\n");
    printf("7. SORT TRAINERS BY NAME\n");
    printf("\n--- MANAGEMENT MEMBER OF TRAINER ---\n");
    printf("8. VIEW TRAINER MEMBERS\n");
    printf("9. ASSIGN MEMBER TO TRAINER\n");
    printf("10. REMOVE MEMBER FROM TRAINER\n");
    printf("0. RETURN TO MAIN MENU\n");
    printf("================================\n");
    printf("OPTION: ");
}

void tm_trainerManagementMenu(TrainerManager *tm_manager)
{
    int choice;

    while (1)
    {
        Clear();
        tm_displayMenu();
        
        choice = InputIntValue("Enter your choice");
        clearInputBuffer();

        Clear(); // Clear screen after selecting option

        switch (choice)
        {
        case 1:
            tm_addTrainer(tm_manager);
            Pause();
            break;
        case 2:
            tm_displayAllTrainers(tm_manager);
            Pause();
            break;
        case 3:
            tm_searchTrainerById(tm_manager);
            Pause();
            break;
        case 4:
            tm_searchTrainerByName(tm_manager);
            Pause();
            break;
        case 5:
            tm_editTrainer(tm_manager);
            Pause();
            break;
        case 6:
            tm_deleteTrainer(tm_manager);
            Pause();
            break;
        case 7:
            tm_sortTrainersByName(tm_manager->trainers, tm_manager->count);
            Pause();
            break;
        case 8:
            tm_displayTrainerMembers(tm_manager);
            Pause();
            break;
        case 9:
            tm_assignMemberToTrainer(tm_manager);
            Pause();
            break;
        case 10:
            tm_removeMemberFromTrainer(tm_manager);
            Pause();
            break;
        case 0:
            printf("\n[OK] RETURN TO MAIN MENU!\n");
            return; // Return to main menu
        default:
            printf("!!! INVALID OPTION !!!\n");
            Pause();
        }
    }
}
