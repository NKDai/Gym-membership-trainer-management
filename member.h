#ifndef MEMBER_H
#define MEMBER_H

#define MAX_NAME_LENGTH  100
#define MAX_ID_LENGTH  7

typedef struct // DATE TIME STRUCT
{
	int day;
	int month;
	int year;
} RegistrationDate;

typedef struct // MEMBER INFORMATION
{
	char name[MAX_NAME_LENGTH];
	char id[MAX_ID_LENGTH];
	int membership_type; 
	char trainer_id[MAX_ID_LENGTH]; // id cua trainer
		
	int removed;
	
	RegistrationDate registration_date;

}Member;

extern int number_of_membership_types;
extern char *membership_types[];


void mb_SetName(Member *member, char name[]);
void mb_SetID(Member *member, char id[]);
void mb_SetMembershipType(Member *member, int membership_type);
void mb_SetTrainerID(Member *member, char trainer_id[]);
void mb_SetRegistrationDate(Member *member);

void mb_StringDate(RegistrationDate date, char **string_date);
void mb_PrintMemberInfo(Member *member);
void mb_PrintMembershipList();

#endif
