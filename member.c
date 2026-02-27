#include "member.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int number_of_membership_types = 4;
char *membership_types[] = {"broze", "silver", "gold", "platinum"};

void mb_StringDate(RegistrationDate date, char **string_date)
{
	int size_of_date = 11; // 00/00/0000 +'\0'= 11
	
	*string_date = malloc(size_of_date); 
	if(*string_date==NULL) return;
	
		
	snprintf(*string_date, size_of_date, "%02d/%02d/%04d", date.day, date.month, date.year);
}

void mb_PrintMembershipList()
{
	for(int i=0; i<number_of_membership_types; i++)
	{
		printf("%-3d - %s\n", i, membership_types[i]);
	}
}

void mb_PrintMemberInfo(Member *member)
{
	if(member==NULL) 
	{
		printf("[Member not found...]\n");
		return;	
	}
	char *registration_date = NULL;
	
	mb_StringDate(member->registration_date, &registration_date);
	
	printf("%-20s : %s\n"
       "%-20s : %s\n"
       "%-20s : %s\n"
       "%-20s : %s\n"
       "%-20s : %s\n",
       "Member full name", member->name,
       "Member ID",        member->id,
       "Membership type", membership_types[member->membership_type],
       "Registration date", registration_date,
	   "Trainer ID", member->trainer_id);
	 
	free(registration_date);
}

void mb_SetName(Member *member, char name[])
{
	strcpy(member->name, name);
}


void mb_SetID(Member *member, char id[])
{
	strcpy(member->id, id);
}

void mb_SetMembershipType(Member *member, int membership_type)
{
	member->membership_type= membership_type;
}

void mb_SetTrainerID(Member *member, char *trainer_id)
{
    strcpy(member->trainer_id, trainer_id);
}

void mb_SetRegistrationDate(Member *member)
{
	member->removed=0;
	
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    member->registration_date.day   = t->tm_mday;
    member->registration_date.month = t->tm_mon + 1;
    member->registration_date.year  = t->tm_year + 1900;
}