#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "member.h"
#include "MemberManagement.h"

#include "trainermag.h"

#include "GlobalFunctions.h"

void Menu()
{
	printf("[1] Member Management                        \n");
	printf("[2] Trainer Management                       \n");
	printf("[3] Sort                                     \n");
	printf("[4] Save Data                                \n");
	printf("-----------------------------------------------\n");
	printf("[9] Settings                                 \n");
	printf("[0] Quit                                     \n");
}
int main()
{

	LightTheme();

	// Load trainer data
	trainerCount = tm_loadTrainersFromFile(trainers);

	MemberManager member_manager = {0, NULL};
	MemberManager *member_manager_selector;
	member_manager_selector = &member_manager;

	// Load member data
	mm_LoadMembersFromFile(&member_manager);

	int running = 1;
	int action;

	do
	{
		Clear();
		Menu();
		printf(" ----------------------------------------------\n");
		action = InputIntValue("Enter your choice");

		switch (action)
		{
		case 1:
			mm_MemberManagement(member_manager_selector);
			break;
		case 2:
			tm_trainerManagementMenu();
			break;
		}

	} while (running && action != 0);
}
