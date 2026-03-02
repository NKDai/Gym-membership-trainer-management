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
	
	MemberManager member_manager = {0, NULL};
	MemberManager *member_manager_selector;
	member_manager_selector = &member_manager;
	
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
				mm_MemberManagement(member_manager_selector);
				break;
			case 2:
				trainerManagementMenu();
				break;
		}
		
	}while(running && action!=0);		
}
