#ifndef TRAINERMAG_H
#define TRAINERMAG_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRAINERS 999
#define MAX_NAME 50
#define MAX_SPEC 50
#define MAX_MEMBERS_PER_TRAINER 50
#define TRAINERS_FILE "trainers.dat"

struct Trainer
{
    char id[10];
    char name[MAX_NAME];
    char specialty[MAX_SPEC];
    float salary;

    // Member management
    char memberIds[MAX_MEMBERS_PER_TRAINER][10];
    int memberCount;
};

// Function declarations
void addTrainer();
void displayAllTrainers();
void searchTrainerById();
void searchTrainerByName();
void editTrainer();
void deleteTrainer();
void displayMenu();
void trainerManagementMenu();
void assignMemberToTrainer();
void removeMemberFromTrainer();
void displayTrainerMembers();
void saveTrainersToFile(struct Trainer trainers[], int count);
int loadTrainersFromFile(struct Trainer trainers[]);
void sortTrainersByName(struct Trainer trainers[], int count);

#endif