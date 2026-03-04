#ifndef MEMBER_H
#define MEMBER_H

#define MAX_NAME_LENGTH  100
#define MAX_ID_LENGTH  7

typedef struct // DATE TIME STRUCT
{
	int day;
	int month;
	int year;
} Date;

typedef struct // MEMBER INFORMATION
{
	char name[MAX_NAME_LENGTH];
	char id[MAX_ID_LENGTH];
	
	int membership_type; 
	int birth_year;
	
	char trainer_id[MAX_ID_LENGTH]; // id cua trainer
	
	int removed;
	
	Date registration_date;

}Member;

extern int number_of_membership_types;
extern char *membership_types[];

// --------------------------------------------------------------------
void mb_SetName(Member *member, char name[]);
// Set member.name = name by using strcmp

void mb_SetID(Member *member, char id[]);
// Set member.ID = ID using strcmp

void mb_SetMembershipType(Member *member, int membership_type);
// Set member.membership_type = membership_type

void mb_SetTrainerID(Member *member, char trainer_id[]);
// Set member.trainer_id = trainer_id using strcmp

void mb_SetRegistrationDate(Member *member);
// Set member.registration_date = today using <time.h>

void mb_SetBirthYear(Member *member, int birth_year);
// Set member.birth_year = birth_year

// --------------------------------------------------------------------
void mb_StringDate(Date date, char **string_date);
// Transform from struct Date to a string as "dd/mm/yyyy" and write it to **string_date

void mb_PrintMemberInfo(Member *member);
// Print information about a member as a list information

void mb_PrintMembershipTypesList();
// Print all types of membership_type

#endif
