#include <stdio.h>
#include <stdlib.h>

#include "Sort.h"

#include "GlobalFunctions.h"

#include "member.h"
#include "MemberManagement.h"

#include "Settings.h"

void s_CopyMemberManager( MemberManager *source,  MemberManager *dest)
{
	if(source==NULL || source->members==NULL || source->count==0)
	{
		dest->count = 0;
		dest->members = NULL;
		return;
	}

	int count = source->count;
	
	dest->count = count;
	dest->members = malloc(sizeof(Member)*count);
	
	if(dest->members==NULL)
	{
		return;
	};
	
	for(int i=0; i<count; i++)
	{
		dest->members[i] = source->members[i];
	}
}

void s_SelectionSort(MemberManager *mb_manager, int condition_mode)
{
	if(mb_manager==NULL || mb_manager->members==NULL || mb_manager->count<=1)
	{
		return;
	}

	if(condition_mode!=0 && condition_mode!=1)
	{
		return;
	}
	
	int i; 
	int j; 
	int minIndex;
	
	int count = mb_manager->count;

	for(i = 0; i < count-1; i++)
	{
		minIndex = i;

		for( j = i+1; j < count; j++)
		{
			if(condition_mode==0)
			{
				if(mb_manager->members[j].birth_year < mb_manager->members[minIndex].birth_year)
				{                                                          
					minIndex = j;
				}
			}
			else
			{
				if(mb_manager->members[j].registration_date_value < mb_manager->members[minIndex].registration_date_value)
				{                                                          
					minIndex = j;
				}
			}
		}
		
		Member temp = mb_manager->members[i];
		mb_manager->members[i] = mb_manager->members[minIndex];
		mb_manager->members[minIndex] = temp;
	}
}

void s_SortMembersByBirthYear(MemberManager *mb_manager, Settings *settings)
{
	if(mb_manager==NULL || mb_manager->members==NULL || mb_manager->count==0)
	{
		mm_DisplayAllMembers(NULL);
		return;
	}

	MemberManager *copied_member_manager = malloc(sizeof(MemberManager));
	
	if(copied_member_manager==NULL) 
	{
		return;
	}
	
	s_CopyMemberManager(mb_manager, copied_member_manager);
	s_SelectionSort(copied_member_manager, 0);

	mm_DisplayAllMembers(copied_member_manager);
	
	if(settings->current_sort_mode==1)
	{
		free(mb_manager->members);
		mb_manager->members = copied_member_manager->members;
		mb_manager->count = copied_member_manager->count;
		free(copied_member_manager);
		Noti("Sorted & Saved successfully!");
	}
	else
	{
		free(copied_member_manager->members);
		free(copied_member_manager);
		Noti("Sorted successfully!");
	}
}

void s_SortMembersByRegistrationDate(MemberManager *mb_manager, Settings *settings)
{
	if(mb_manager==NULL || mb_manager->members==NULL || mb_manager->count==0)
	{
		mm_DisplayAllMembers(NULL);
		return;
	}

	MemberManager *copied_member_manager = malloc(sizeof(MemberManager));
	
	if(copied_member_manager==NULL) return;
	
	s_CopyMemberManager(mb_manager, copied_member_manager);
	s_SelectionSort(copied_member_manager, 1);

	mm_DisplayAllMembers(copied_member_manager);
	
	if(settings->current_sort_mode==1)
	{
		free(mb_manager->members);
		mb_manager->members = copied_member_manager->members;
		mb_manager->count = copied_member_manager->count;
		free(copied_member_manager);
		Noti("Sorted & Saved successfully!");
	}
	else
	{
		free(copied_member_manager->members);
		free(copied_member_manager);
		Noti("Sorted successfully!");
	}
}

void s_SortMenu(Settings *settings)
{
	printf("SORT MODE - [%s]\n", sort_mode_names[settings->current_sort_mode]);
	printf("----------------------------------------------------\n");
	printf("[1] Sort member by birth year\n");
	printf("[2] Sort member by registration date\n");
	printf("----------------------------------------------------\n");
	printf("[0] Back to menu\n");
	printf("----------------------------------------------------\n");
}

void s_SortManagement(MemberManager *mb_manager, Settings *settings)
{
	int action;
	
	do
	{
		Clear();
		
		s_SortMenu(settings);
		action = InputIntValue("Enter your action: ");
		
		switch(action)
		{
			case 1:
				s_SortMembersByBirthYear(mb_manager, settings);
				break;

			case 2:
				s_SortMembersByRegistrationDate(mb_manager, settings);
				break;

			case 0:
				break;
		}
	
	}while(action!=0);
}