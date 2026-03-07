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

// Function declarations
void tm_addTrainer();                                             // Add a new trainer
void tm_displayAllTrainers();                                     // Display all trainers
void tm_searchTrainerById();                                      // Search trainer by ID
void tm_searchTrainerByName();                                    // Search trainer by name
void tm_editTrainer();                                            // Edit trainer information
void tm_deleteTrainer();                                          // Delete a trainer
void tm_displayMenu();                                            // Display trainer management menu
void tm_trainerManagementMenu();                                  // Main menu loop for trainer management
void tm_assignMemberToTrainer();                                  // Assign a member to a trainer
void tm_removeMemberFromTrainer();                                // Remove a member from a trainer
void tm_displayTrainerMembers();                                  // Display members assigned to a trainer
void tm_saveTrainersToFile(struct Trainer trainers[], int count); // Save trainers to file
int tm_loadTrainersFromFile(struct Trainer trainers[]);           // Load trainers from file
void tm_sortTrainersByName(struct Trainer trainers[], int count); // Sort trainers by name

// Globals (defined in trainer.c)
extern struct Trainer *trainers;
extern int trainerCount;
extern int currentCapacity;

#endif