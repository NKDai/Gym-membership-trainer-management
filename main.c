#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Settings.h"
#include "GlobalFunctions.h"

#include "member.h"
#include "MemberManagement.h"

#include "trainermag.h"

#include "Sort.h"

void Menu()
{
	printf(" --------------- GYM MANAGEMENT ---------------\n");
	printf("[1] Member Management                        \n");
	printf("[2] Trainer Management                       \n");
	printf("[3] Sort                                     \n");
	printf("[4] Save Data                                \n");
	printf("-----------------------------------------------\n");
	printf("[9] Settings                                 \n");
	printf("[0] Quit                                     \n");
	printf(" ----------------------------------------------\n");
}

void SaveData(TrainerManager *trainer_manager, MemberManager *member_manager)
{
	tm_saveTrainersToFile(trainer_manager);
	mm_SaveData(member_manager);
}

int main()
{	
	Settings settings;
	st_SetSettings(&settings);
	

	MemberManager member_manager = {0, NULL};
	TrainerManager trainer_manager = {0, 0, NULL};

	mm_LoadData(&member_manager);
	tm_loadTrainersFromFile(&trainer_manager);
	
	int running=1;
	int action;
	
	do
	{
		Clear();
		Menu();
		action = InputIntValue("Enter your choice");
		
		switch(action)
		{
			case 1:
				mm_MemberManagement(&member_manager, &settings);
				break;
			case 2:
				tm_trainerManagementMenu(&trainer_manager, &settings);
				break;
			case 3:
				s_SortManagement(&member_manager, &settings);
				break;
			case 4:
				SaveData(&trainer_manager, &member_manager);
				Noti("Data saved successfully!");
				break;
			case 9:
				st_Settings_Management(&settings, &member_manager, &trainer_manager);
				SaveData(&trainer_manager, &member_manager);
				break;
			case 0:
				printf("Quitting...");
				running = 0;
				break;
			default:
				Noti("Invalid action!");
		}
		
	}while(running);		
	
	if(settings.current_auto_save_mode)
	{
		SaveData(&trainer_manager, &member_manager);
	}
}

