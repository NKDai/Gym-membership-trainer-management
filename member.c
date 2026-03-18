#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "member.h"

int number_of_membership_types = 4;
char *membership_types[] = {"bronze", "silver", "gold", "platinum"};

long mb_TodayToValue()
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    struct tm date = {0};
    date.tm_mday = t->tm_mday;
    date.tm_mon  = t->tm_mon;
    date.tm_year = t->tm_year;
    date.tm_hour = 12;

    time_t seconds = mktime(&date);

    return seconds / 86400;
}

void mb_StringDate(Date date, char string_date[])
{
    snprintf(string_date, 11, "%02d/%02d/%04d",
             date.day, date.month, date.year);
}

void mb_PrintMembershipTypesList()
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

	char registration_date[11];

	mb_StringDate(member->registration_date, registration_date);
	
	printf("%-20s : %s\n"
       "%-20s : %d\n"
       "%-20s : %s\n"
       "%-20s : %s\n"
       "%-20s : %s\n"
       "%-20s : %s\n",
       "Member full name", member->name,
       "Member birth year", member->birth_year,
       "Member ID",        member->id,
       "Membership type", membership_types[member->membership_type],
       "Registration date", registration_date,
	   "Trainer ID", member->trainer_id);
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

void mb_SetBirthYear(Member *member, int birth_year)
{
	member->birth_year= birth_year;
}

int mb_IsAssigned(Member *member)
{
	if(strcmp(member->trainer_id,"NULL")!=0)
	{
		return 1;
	}
	return 0;
}

int mb_IsAssignedBy(Member *member, char *trainer_id)
{
	if(!mb_IsAssigned(member))
	{
		return 0;
	}
	
	if(strcmp(member->trainer_id, trainer_id)==0)
	{
		return 1;
	}
	return 0;
}

void mb_SetTrainerID(Member *member, char *trainer_id)
{
    strcpy(member->trainer_id, trainer_id);
}

void mb_RemoveTrainer(Member *member)
{
	mb_SetTrainerID(member, "NULL");
}

void mb_SetRegistrationDate(Member *member)
{
	member->removed=0;
	
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    member->registration_date.day   = t->tm_mday;
    member->registration_date.month = t->tm_mon + 1;
    member->registration_date.year  = t->tm_year + 1900;
    
    member->registration_date_value = mb_TodayToValue();
}