#include <stdio.h>
#include "trainermag.h"

struct Trainer trainers[MAX_TRAINERS];
int trainerCount = 0;

void addTrainer()
{
    if (trainerCount >= MAX_TRAINERS)
    {
        printf("\n!!! He thong day - Khong the them HLV! !!!\n");
        return;
    }

    struct Trainer newTrainer;

    // Auto-generate ID in format TRNXXX (TRN001, TRN002, etc.)
    sprintf(newTrainer.id, "TRN%03d", trainerCount + 1);

    printf("\n--- THEM HLV MOI ---\n");
    printf("Nhap ten HLV: ");
    fgets(newTrainer.name, MAX_NAME, stdin);
    newTrainer.name[strcspn(newTrainer.name, "\n")] = 0;

    printf("Nhap chuyen mon: ");
    fgets(newTrainer.specialty, MAX_SPEC, stdin);
    newTrainer.specialty[strcspn(newTrainer.specialty, "\n")] = 0;

    printf("Nhap luong (VND): ");
    scanf("%f", &newTrainer.salary);
    getchar(); // Clear newline

    // Initialize member list
    newTrainer.memberCount = 0;

    trainers[trainerCount++] = newTrainer;
    printf("\n[OK] HLV da duoc them thanh cong! (ID: %s)\n", newTrainer.id);
}

void displayAllTrainers()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    printf("\n============================================ DANH SACH TAT CA HLV ============================================\n");
    printf("%-8s %-20s %-20s %-15s\n", "ID", "Ten", "Chuyen Mon", "Luong");
    printf("==========================================================================================================\n");

    for (int i = 0; i < trainerCount; i++)
    {
        printf("%-8s %-20s %-20s %-15.0f\n",
               trainers[i].id,
               trainers[i].name,
               trainers[i].specialty,
               trainers[i].salary);
    }
    printf("==========================================================================================================\n");
}

void searchTrainerById()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    char searchId[10];
    printf("\nNhap ID HLV can tim (vi du: TRN001): ");
    fgets(searchId, 10, stdin);
    searchId[strcspn(searchId, "\n")] = 0;

    for (int i = 0; i < trainerCount; i++)
    {
        if (strcmp(trainers[i].id, searchId) == 0)
        {
            printf("\n========== THONG TIN HLV ==========\n");
            printf("ID: %s\n", trainers[i].id);
            printf("Ten: %s\n", trainers[i].name);
            printf("Chuyen Mon: %s\n", trainers[i].specialty);
            printf("Luong: %.0f VND\n", trainers[i].salary);
            printf("===================================\n");
            return;
        }
    }
    printf("\n!!! Khong tim thay HLV co ID: %s !!!\n", searchId);
}

void searchTrainerByName()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    char searchName[MAX_NAME];
    printf("\nNhap ten HLV can tim: ");
    fgets(searchName, MAX_NAME, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int found = 0;
    printf("\n========== KET QUA TIM KIEM ==========\n");
    printf("%-8s %-20s %-20s %-15s\n", "ID", "Ten", "Chuyen Mon", "Luong");
    printf("======================================================================================================\n");

    for (int i = 0; i < trainerCount; i++)
    {
        if (strstr(trainers[i].name, searchName) != NULL)
        {
            printf("%-8s %-20s %-20s %-15.0f\n",
                   trainers[i].id,
                   trainers[i].name,
                   trainers[i].specialty,
                   trainers[i].salary);
            found = 1;
        }
    }

    if (!found)
    {
        printf("!!! Khong tim thay HLV: %s !!!\n", searchName);
    }
    printf("======================================================================================================\n");
}

void editTrainer()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    char editId[10];
    printf("\nNhap ID HLV can chinh sua (vi du: TRN001): ");
    fgets(editId, 10, stdin);
    editId[strcspn(editId, "\n")] = 0;

    for (int i = 0; i < trainerCount; i++)
    {
        if (strcmp(trainers[i].id, editId) == 0)
        {
            printf("\n--- CHINH SUA THONG TIN HLV ---\n");
            printf("1. Chinh sua ten (Hien tai: %s): ", trainers[i].name);
            char temp[MAX_NAME];
            fgets(temp, MAX_NAME, stdin);
            if (strlen(temp) > 1)
            {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(trainers[i].name, temp);
            }
            getchar();

            printf("2. Chinh sua chuyen mon (Hien tai: %s): ", trainers[i].specialty);
            fgets(temp, MAX_NAME, stdin);
            if (strlen(temp) > 1)
            {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(trainers[i].specialty, temp);
            }

            printf("3. Chinh sua luong (Hien tai: %.0f): ", trainers[i].salary);
            float tempSalary;
            if (scanf("%f", &tempSalary) == 1)
            {
                trainers[i].salary = tempSalary;
            }
            getchar();

            printf("\n[OK] HLV da duoc cap nhat thanh cong!\n");
            return;
        }
    }
    printf("\n!!! Khong tim thay HLV co ID: %s !!!\n", editId);
}

void deleteTrainer()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    char deleteId[10];
    printf("\nNhap ID HLV can xoa (vi du: TRN001): ");
    fgets(deleteId, 10, stdin);
    deleteId[strcspn(deleteId, "\n")] = 0;

    for (int i = 0; i < trainerCount; i++)
    {
        if (strcmp(trainers[i].id, deleteId) == 0)
        {
            printf("Ban co chac chan muon xoa HLV '%s'? (y/n): ", trainers[i].name);
            char confirm;
            scanf("%c", &confirm);
            getchar();

            if (confirm == 'y' || confirm == 'Y')
            {
                for (int j = i; j < trainerCount - 1; j++)
                {
                    trainers[j] = trainers[j + 1];
                }
                trainerCount--;
                printf("[OK] HLV da duoc xoa thanh cong!\n");
            }
            else
            {
                printf("Huy thi hanh xoa.\n");
            }
            return;
        }
    }
    printf("\n!!! Khong tim thay HLV co ID: %s !!!\n", deleteId);
}

void saveTrainersToFile(struct Trainer trainers[], int count)
{
    FILE *file = fopen(TRAINERS_FILE, "wb");
    if (file == NULL)
    {
        printf("!!! Loi: Khong the mo file de luu du lieu! !!!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(trainers, sizeof(struct Trainer), count, file);
    fclose(file);
    printf("[OK] Du lieu da duoc luu thanh cong!\n");
}

int loadTrainersFromFile(struct Trainer trainers[])
{
    FILE *file = fopen(TRAINERS_FILE, "rb");
    if (file == NULL)
    {
        return 0;
    }

    int count;
    fread(&count, sizeof(int), 1, file);
    fread(trainers, sizeof(struct Trainer), count, file);
    fclose(file);

    return count;
}

void displayTrainerMembers()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    char searchId[10];
    printf("\nNhap ID HLV can xem danh sach member (vi du: TRN001): ");
    fgets(searchId, 10, stdin);
    searchId[strcspn(searchId, "\n")] = 0;

    for (int i = 0; i < trainerCount; i++)
    {
        if (strcmp(trainers[i].id, searchId) == 0)
        {
            printf("\n========== DANH SACH MEMBER CUA HLV %s =========\n", trainers[i].name);
            if (trainers[i].memberCount == 0)
            {
                printf("Chua co member nao duoc gan cho HLV nay!\n");
            }
            else
            {
                printf("Tong member: %d\n", trainers[i].memberCount);
                printf("\nCac member da gan:\n");
                for (int j = 0; j < trainers[i].memberCount; j++)
                {
                    printf("%d. %s\n", j + 1, trainers[i].memberIds[j]);
                }
            }
            printf("===============================================\n");
            return;
        }
    }
    printf("\n!!! Khong tim thay HLV co ID: %s !!!\n", searchId);
}

void assignMemberToTrainer()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    char trainerId[10];
    printf("\nNhap ID HLV can gan member (vi du: TRN001): ");
    fgets(trainerId, 10, stdin);
    trainerId[strcspn(trainerId, "\n")] = 0;

    for (int i = 0; i < trainerCount; i++)
    {
        if (strcmp(trainers[i].id, trainerId) == 0)
        {
            if (trainers[i].memberCount >= MAX_MEMBERS_PER_TRAINER)
            {
                printf("\n!!! HLV nay da dat toi da so luong member (%d)! !!!\n", MAX_MEMBERS_PER_TRAINER);
                return;
            }

            char memberId[10];
            printf("Nhap ID member can gan (vi du: GYM001): ");
            fgets(memberId, 10, stdin);
            memberId[strcspn(memberId, "\n")] = 0;

            // Check if member already assigned
            for (int j = 0; j < trainers[i].memberCount; j++)
            {
                if (strcmp(trainers[i].memberIds[j], memberId) == 0)
                {
                    printf("\n!!! Member '%s' da duoc gan cho HLV nay! !!!\n", memberId);
                    return;
                }
            }

            // Add member
            strcpy(trainers[i].memberIds[trainers[i].memberCount], memberId);
            trainers[i].memberCount++;
            printf("\n[OK] Member '%s' da duoc gan cho HLV '%s'!\n", memberId, trainers[i].name);
            return;
        }
    }
    printf("\n!!! Khong tim thay HLV co ID: %s !!!\n", trainerId);
}

void removeMemberFromTrainer()
{
    if (trainerCount == 0)
    {
        printf("\n*** Khong co HLV nao trong he thong! ***\n");
        return;
    }

    char trainerId[10];
    printf("\nNhap ID HLV (vi du: TRN001): ");
    fgets(trainerId, 10, stdin);
    trainerId[strcspn(trainerId, "\n")] = 0;

    for (int i = 0; i < trainerCount; i++)
    {
        if (strcmp(trainers[i].id, trainerId) == 0)
        {
            if (trainers[i].memberCount == 0)
            {
                printf("\n*** HLV nay khong co member nao! ***\n");
                return;
            }

            printf("\nCac member hien tai:\n");
            for (int j = 0; j < trainers[i].memberCount; j++)
            {
                printf("%d. %s\n", j + 1, trainers[i].memberIds[j]);
            }

            char memberId[10];
            printf("Nhap ID member can xoa: ");
            fgets(memberId, 10, stdin);
            memberId[strcspn(memberId, "\n")] = 0;

            for (int j = 0; j < trainers[i].memberCount; j++)
            {
                if (strcmp(trainers[i].memberIds[j], memberId) == 0)
                {
                    // Remove member by shifting array
                    for (int k = j; k < trainers[i].memberCount - 1; k++)
                    {
                        strcpy(trainers[i].memberIds[k], trainers[i].memberIds[k + 1]);
                    }
                    trainers[i].memberCount--;
                    printf("\n[OK] Member '%s' da duoc xoa khoi HLV!\n", memberId);
                    return;
                }
            }
            printf("\n!!! Khong tim thay member '%s' trong danh sach! !!!\n", memberId);
            return;
        }
    }
    printf("\n!!! Khong tim thay HLV co ID: %s !!!\n", trainerId);
}

void sortTrainersByName(struct Trainer trainers[], int count)
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
    printf("\n[OK] HLV da duoc sap xep theo ten!\n");
}

void displayMenu()
{
    printf("\n");
    printf("========== QUAN LY HLV =========\n");
    printf("1. Them HLV moi\n");
    printf("2. Xem tat ca HLV\n");
    printf("3. Tim HLV theo ID\n");
    printf("4. Tim HLV theo ten\n");
    printf("5. Chinh sua thong tin HLV\n");
    printf("6. Xoa HLV\n");
    printf("7. Sap xep HLV theo ten\n");
    printf("8. Luu du lieu\n");
    printf("\n--- QUAN LY MEMBER CUA HLV ---\n");
    printf("9. Xem danh sach member cua HLV\n");
    printf("10. Gan member cho HLV\n");
    printf("11. Xoa member khoi HLV\n");
    printf("0. Quay lai menu chinh\n");
    printf("================================\n");
    printf("Lua chon: ");
}

void trainerManagementMenu()
{
    int choice;

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addTrainer();
            break;
        case 2:
            displayAllTrainers();
            break;
        case 3:
            searchTrainerById();
            break;
        case 4:
            searchTrainerByName();
            break;
        case 5:
            editTrainer();
            break;
        case 6:
            deleteTrainer();
            break;
        case 7:
            sortTrainersByName(trainers, trainerCount);
            break;
        case 8:
            saveTrainersToFile(trainers, trainerCount);
            break;
        case 9:
            displayTrainerMembers();
            break;
        case 10:
            assignMemberToTrainer();
            break;
        case 11:
            removeMemberFromTrainer();
            break;
        case 0:
            printf("\n[OK] Quay lai menu chinh!\n");
            return; // Return to main menu
        default:
            printf("!!! Lua chon khong hop le! Vui long nhap lai! !!!\n");
        }
    }
}