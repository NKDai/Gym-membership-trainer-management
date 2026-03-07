#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "member.h"
#include "MemberManagement.h"

#include "trainermag.h"

#include "GlobalFunctions.h"
#include "Settings.h"

void SaveData()
{
	
}

void SortMenu(MemberManager* mb_manager, Settings *settings)
{
	int action;
	do
	{
		Clear();
		printf("SORT MODE\n");
		printf("[1] Sort member by birth year\n");
		printf("[2] Sort member by registration date\n");
		action = InputIntValue("Enter your action: ");
		switch(action)
		{
			case 1:
				break;
			case 2:
				break;
		}
	
	}while(action!=0);
}

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
	Settings settings;
	st_LoadSettings(&settings);

	MemberManager member_manager = {0, NULL};
	TrainerManager trainer_manager = {0, 0, NULL};

	mm_LoadData(&member_manager);
	tm_loadTrainersFromFile(&trainer_manager);
	
	int running=1;
	int action;
	
	do
	{
		Clear();
		printf(" --------------- GYM MANAGEMENT ---------------\n");
		Menu();
		printf(" ----------------------------------------------\n");
		action = InputIntValue("Enter your choice");
		
		switch(action)
		{
			case 1:
				mm_MemberManagement(&member_manager);
				break;
			case 2:
				trainerManagementMenu(&trainer_manager);
				break;
			case 3:
				SaveData();
				break;
		}
		
	}while(running && action!=0);		
}

