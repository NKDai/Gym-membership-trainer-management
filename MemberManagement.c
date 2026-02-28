#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "MemberManagement.h"
#include "member.h"
#include "GlobalFunctions.h"



int mm_InputMembershipType(char *msg)
{
	int membership_type=-9;
	printf("------------------------\n");
	do{
		mb_PrintMembershipList();
		printf("------------------------\n");
		membership_type = InputIntValue(msg);
	}while(membership_type<0 || membership_type >= number_of_membership_types);
	
	return membership_type;
}
void mm_InputMemberID(char *msg, char *id)
{
	printf("%s :", msg);
	scanf("%s", id);
}


void mm_AddMember(MemberManager *mb_manager, Member member_info){
	
	int new_count = mb_manager->count+1;
	Member* new_members = realloc(mb_manager->members, new_count*sizeof(Member));
	
	if(new_members==NULL) return;
	
	
	mb_manager->members = new_members;
	mb_manager->members[new_count-1] = member_info;
	mb_manager->count = new_count;
	
		
}

void mm_DisplayAllMembers(MemberManager *mb_manager)
{
    printf(" ______________________________________________MEMBER_LIST__________________________________________________ \n");
    printf("| %-3s | %-25s | %-7s | %-20s | %-12s | %-23s |\n",
           "No.", "Full-name", "ID", "Membership type", "Trainer ID", "Registration date");
    printf("|-----------------------------------------------------------------------------------------------------------|\n");
    
	int i;
    for (i = 0; i < mb_manager->count; i++)
    {
        Member *current_member = &mb_manager->members[i];
        
        char *registration_date;
        mb_StringDate(current_member->registration_date, &registration_date);

        printf("| %-3d | %-25s | %-7s | %-20s | %-12s | %-23s |\n",
               i+1,
               current_member->name,
               current_member->id,
               membership_types[current_member->membership_type],
               current_member->trainer_id,
			   registration_date);
    }
    if(i==0)
    {
    printf("|                                              No member here...                                            | \n");
	}
    
    printf("|___________________________________________________________________________________________________________| \n");
}

void mm_MemberManagement_CorrectDataMenu()
{
	printf("[1] The information is correct \n");
	printf("[0] Cancel the process\n");
}

void mm_GenerateNewID(MemberManager *mb_manager, char *id)
{
    for(int i=0; i<999; i++)
    {
        snprintf(id, 7, "GYM%03d", i);

        int exist = 0;

        for(int j=0; j<mb_manager->count; j++)
        {
            if(strcmp(mb_manager->members[j].id, id) == 0)
            {
                exist = 1;
                break;
            }
        }

        if(!exist) return;  
		  	 
    }

    id = "NULL";
}

void mm_MemberManagement_AddingMember(MemberManager *mb_member_manager)
{
	char id[7];
	char name[255];
	int membership_type;
	
	Member new_member;
	Member *point_to_new_member = &new_member;
	
	mm_GenerateNewID(mb_member_manager, id);
	
	Clear();
	if(strcmp(id, "NULL")==0)
	{
		Noti("Member list is full, you can not add new member!");
		return;
	}
	
	printf("ADDING MEMBER MODE\n");
	printf("Enter member full-name: ");
	scanf(" %[^\n]s", &name);
	membership_type = mm_InputMembershipType("Enter membership type");
	
	mb_SetID(point_to_new_member, id);
	mb_SetName(point_to_new_member, name);
	mb_SetMembershipType(point_to_new_member, membership_type);
	mb_SetTrainerID(point_to_new_member, "NULL");
	mb_SetRegistrationDate(point_to_new_member);
	
	int correct=0;
	do
	{
		Clear();
		printf("CHECK MEMBER INFOMATION AGAIN\n");
		printf("----------------------------------------\n");
		mb_PrintMemberInfo(point_to_new_member);
		printf("----------------------------------------\n");
		mm_MemberManagement_CorrectDataMenu();
		printf("----------------------------------------\n");
		correct = InputIntValue("Enter your choice");
	}while(correct!=1 && correct!=0);
	
	if(correct == 1)
	{	
		mm_AddMember(mb_member_manager, new_member);
		Noti("Added member successfully!");
	}
	else
	{
		Noti("Cancelled... ");
	}
	
}

void mm_MemberManagement_Menu()
{
	printf("----------- MEMBER MANAGEMENT ------------ \n");
	printf("[1] List of all members \n");
	printf("[2] Add new member \n");
	printf("[3] Remove member\n");
	printf("[4] Search member information\n");
	printf("[5] Change member information\n");
	printf("[0] Back to menu \n");
	printf("------------------------------------------ \n");
}

void mm_MemberManagement_DisplayingAllMembers(MemberManager *mb_manager)
{
	Clear();
	mm_DisplayAllMembers(mb_manager);
	Pause();
}

void mm_MemberManagement_SearchingMember(MemberManager *mb_manager)
{
	Clear();
	
	char id[7];
	Member *selector;
	
	printf("SEARCHING MEMBER MODE\n");
	mm_InputMemberID("Enter member ID", id);
	printf("---------------------------\n");
	
	mm_SearchMember(mb_manager, id, &selector);
	
	if(selector!=NULL)
	{
		printf("MEMBER INFORMATION\n");
		printf("---------------------------\n");
		mb_PrintMemberInfo(selector);
		printf("---------------------------\n");
		Pause();
	}
	else
	{
		Noti("Member not found...");
	}
}

void mm_SearchMember(MemberManager *mb_manager, char id[], Member **selector)
{
	
	int running=1;
	for(int i=0; i<mb_manager->count && running; i++)
	{
		if(strcmp(mb_manager->members[i].id, id)==0)
		{
			*selector = &mb_manager->members[i];
			running = 0;
		}
	}
	if(running==1) *selector = NULL;
}

//void mm_SwapMember(Member *A, Member *B)
//{
//	Member temp = *A;
//	*A = *B;
//	*B = temp;
//}
//
//void mm_SortMember(MemberManager *mb_manager)
//{
//	int done;
//	do{
//		done = 1;
//		for(int i=1; i<mb_manager->count; i++)
//		{
//				Member *current_member = &mb_manager->members[i];
//				Member *previous_member = &mb_manager->members[i-1];
//				
//				if(previous_member->removed || strcmp(previous_member->id, current_member->id) > 0)
//				{
//					mm_SwapMember(current_member, previous_member);
//					done = 0;
//				}
//			
//		}
//	}while(!done);
//} 

void mm_RemoveMember(MemberManager *mb_manager, int member_index)
{
    if (!mb_manager || member_index < 0 || member_index >= mb_manager->count)
        return;

    for (int i = member_index; i < mb_manager->count - 1; i++)
    {
        mb_manager->members[i] = mb_manager->members[i+1];
    }

    int new_count = mb_manager->count - 1;

    Member *tmp = realloc(mb_manager->members, new_count * sizeof(Member));
    if (tmp) mb_manager->members = tmp;

    mb_manager->count = new_count;
}

int mm_GetMemberIndex(MemberManager *mb_manager, char id[])
{
	for(int i=0; i<mb_manager->count;i++)
	{
		if(strcmp(mb_manager->members[i].id, id)==0)
		{
			return i;
		}
	}
}

void mm_MemberManagement_MakeSureMenu()
{
	printf("You must read the information and make sure you want to remove this member...\n");
	printf("[1] Yes, I want to remove\n");
	printf("[2] No, back to menu\n");
}

void mm_MemberManagement_RemovingMember(MemberManager *mb_manager)
{
	int action;
	char id[7];
	Member *selector;
	
	
	Clear();
	printf("REMOVING MEMBER MODE\n");
	printf("Enter member ID: ");
	scanf("%s", id);
	
	
	mm_SearchMember(mb_manager, id, &selector);
	if(selector!= NULL)
	{
		
		do{
			Clear();
			printf("CHECK MEMBER INFORMATION AGAIN\n");
			printf("-------------------------------------\n");
			mb_PrintMemberInfo(selector);
			printf("-------------------------------------\n");
			mm_MemberManagement_MakeSureMenu();
			printf("-------------------------------------\n");
			action = InputIntValue("Enter your choice");
			
		}while(action!=0 && action!=1);
		if(action==1)
		{
			mm_RemoveMember(mb_manager, mm_GetMemberIndex(mb_manager, id));
			Noti("Removed member successfully!");	
		}
		else
		{
			Noti("Cancelled...");
		}
		
	}
	else{
		Noti("Member not found...");
	}
}

void mm_MemberManagement_InfoListMenu()
{
	printf("[1] Change member's fullname\n");
	printf("[2] Change member's membership type\n");
	printf("[0] Back to member management menu\n");
}

void mm_MemberManagement_ChangingMemberInfo(MemberManager *mb_manager) // name/membership type
{
	int action;
	char id[7];
	char new_name[255];
	int new_membership_type;
	Member *selector;
	do
	{
		action = -1;
						
		Clear();
		printf("CHANGING MEMBER INFORMATION MODE\n");
		printf("----------------------------------------------\n");
		mm_MemberManagement_InfoListMenu();
		printf("----------------------------------------------\n");
		action = InputIntValue("Enter your choice");
	
		switch(action)
		{
			case 1:	
				mm_InputMemberID("Enter member ID", id);
				mm_SearchMember(mb_manager, id, &selector);
				if(selector!=NULL)
				{
					printf("Current name : %s\n", selector->name);
					printf("Enter new name :");
					scanf(" %[^\n]s", &new_name);
					mb_SetName(selector, new_name);
					
					Noti("Changed member's fullname successfully!");
				}
				else
				{
					Noti("Member not found...");
					continue;
				}
				break;
			case 2:
				mm_InputMemberID("Enter member ID", id);
				mm_SearchMember(mb_manager, id, &selector);
				if(selector!=NULL)
				{
					printf("Member fullname : %s\n", selector->name);
					printf("Current membership type : %s\n", membership_types[selector->membership_type]);
					new_membership_type = mm_InputMembershipType("Enter new membership type");
					mb_SetMembershipType(selector, new_membership_type);
					
					Noti("Changed member's membership type successfully!");
				}
				else
				{
					Noti("Member not found...");
					continue;
				}
				break;
			case 0:
				break;
			default:
				Noti("Invalid action, choice again...");
		}
	}while(action!=0);
}

void mm_MemberManagement(MemberManager *mb_manager)
{
    int running = 1;
    int action;

    do {
        Clear();
        mm_MemberManagement_Menu();

        action = InputIntValue("Enter your choice");

        switch(action){
            case 1:
                mm_MemberManagement_DisplayingAllMembers(mb_manager);
                break;
            case 2:
                mm_MemberManagement_AddingMember(mb_manager);
                break;
            case 3:
                mm_MemberManagement_RemovingMember(mb_manager);
                break;
            case 4:
                mm_MemberManagement_SearchingMember(mb_manager);
                break;
            case 5:
            	mm_MemberManagement_ChangingMemberInfo(mb_manager);
            	break;
            case 0:
                break;
            default:
                Noti("Invalid action, choice again!");
                break;
        }

    } while(running && action != 0);
}
