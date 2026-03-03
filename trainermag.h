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
void addTrainer();                                             // Add a new trainer
void displayAllTrainers();                                     // Display all trainers
void searchTrainerById();                                      // Search trainer by ID
void searchTrainerByName();                                    // Search trainer by name
void editTrainer();                                            // Edit trainer information
void deleteTrainer();                                          // Delete a trainer
void displayMenu();                                            // Display trainer management menu
void trainerManagementMenu();                                  // Main menu loop for trainer management
void assignMemberToTrainer();                                  // Assign a member to a trainer
void removeMemberFromTrainer();                                // Remove a member from a trainer
void displayTrainerMembers();                                  // Display members assigned to a trainer
void saveTrainersToFile(struct Trainer trainers[], int count); // Save trainers to file
int loadTrainersFromFile(struct Trainer trainers[]);           // Load trainers from file
void sortTrainersByName(struct Trainer trainers[], int count); // Sort trainers by name

// Globals (defined in trainer.c)
extern struct Trainer trainers[MAX_TRAINERS];
extern int trainerCount;

#endif