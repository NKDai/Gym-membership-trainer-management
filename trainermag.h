#ifndef TRAINERMAG_H
#define TRAINERMAG_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_TRAINERS 10
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

// Trainer Manager struct
typedef struct
{
    int count;
    int capacity;
    struct Trainer *trainers;
} TrainerManager;

// Function declarations
void tm_addTrainer(TrainerManager *tm_manager);                   // Add a new trainer
void tm_displayAllTrainers(TrainerManager *tm_manager);           // Display all trainers
void tm_searchTrainerById(TrainerManager *tm_manager);            // Search trainer by ID
void tm_searchTrainerByName(TrainerManager *tm_manager);          // Search trainer by name
void tm_editTrainer(TrainerManager *tm_manager);                  // Edit trainer information
void tm_deleteTrainer(TrainerManager *tm_manager);                // Delete a trainer
void tm_displayMenu();                                            // Display trainer management menu
void tm_trainerManagementMenu(TrainerManager *tm_manager);        // Main menu loop for trainer management
void tm_assignMemberToTrainer(TrainerManager *tm_manager);        // Assign a member to a trainer
void tm_removeMemberFromTrainer(TrainerManager *tm_manager);      // Remove a member from a trainer
void tm_displayTrainerMembers(TrainerManager *tm_manager);        // Display members assigned to a trainer
void tm_saveTrainersToFile(TrainerManager *tm_manager);           // Save trainers to file
int tm_loadTrainersFromFile(TrainerManager *tm_manager);          // Load trainers from file
void tm_sortTrainersByName(struct Trainer trainers[], int count); // Sort trainers by name

#endif