#ifndef MEMBERMANAGEMENT_H
#define MEMBERMANAGEMENT_H

#define MAX_MEMBERS 999
#define MEMBER_SAVE_FILE_NAME "members.dat"

#include "member.h"

// ---------------------------------------------------------------------------------------------------------------------- STRUCT

struct Settings;

typedef struct MemberManager{
	
	int count;
	Member *members;	
	
}MemberManager;

// ---------------------------------------------------------------------------------------------------------------------- CORE FUNCTIONS
void mm_AddMember(MemberManager *mb_manager,  Member Member_info);
// Use to add Member into a MemberManager directly from a copy of Member_info

void mm_RemoveMember(MemberManager *mb_manager, int Member_index);
// Use to remove Member from a MemberManager directly by the index of that Member

void mm_DisplayAllMembers(MemberManager *mb_manager);
// Display all Members as a grid board

Member* mm_SearchMemberByID(MemberManager *mb_manager, char id[]);
// Use to search a Member by input an ID

void mm_SearchMemberByName(MemberManager *mb_manager, char *name, MemberManager *selectors);
// Use to search a Member by input any string or char

// ---------------------------------------------------------------------------------------------------------------------- COMPLETED FUNCTIONS

void mm_MemberManagement_AddingMember(MemberManager *mb_Member_manager);
// Clear screen
// Let user input Member fullname, Membership type and generate new Member
// Then make sure Member's information is correct or not
// If correct -> save Member to data -> show notification and back to menu
// If not correct -> show notification and back to menu
// This function use mm_AddMember as core to add Member

void mm_MemberManagement_RemovingMember(MemberManager *mb_manager);
// Clear screen
// Let user input Member ID and check if ID is valid
// Print out the information of selected Member
// Then ask user if they really want to remove this Member of not
// If sure -> remove Member from data -> show notification and back to menu
// If not sure -> show notification and back to menu
// This function use mm_RemoveMember as core to remove Member

void mm_MemberManagement_DisplayingAllMembers(MemberManager *mb_manager);
// Clear screen
// Then use mm_DisplayAllMembers to show all Member
// Last, pause program before back to menu

void mm_MemberManagement_SearchingMemberByID(MemberManager *mb_manager);
// Clear screen
// Use to let user enter Member ID, check ID valid
// Print out the information about selected Member
// Pause program before back to menu

void mm_MemberManagement_SearchingMemberByName(MemberManager *mb_manager);
// Clear screen
// Use to let user enter Member fullname
// Print out the information of all Members have the same fullname
// Pause program before back to menu

void mm_MemberManagement_ChangingMemberInfo(MemberManager *mb_manager);
// Clear screen
// Let user select mode : [1] change member's fullname, [2] change member's membership type or [0] to quit
// As user choice action -> ask user for member ID, check ID valid and show member information before change
// Then, let user change the fullname or membership type as their selected action
// Last, change member information, show notification and back to menu

// ---------------------------------------------------------------------------------------------------------------------- CALCULATOR FUNCTIONS
void mm_GenerateNewID(MemberManager *mb_manager, char *id);
// Pick a non-used ID from GYM000 to GYM999 and write it into *id
// If all of the IDs are used -> write "NULL" into *id

void mm_InputMemberID(char *msg, char *id);
// Use to input and check if the ID selected is correct
// If correct -> write it into *id
// If not correct -> type again
// *msg is use to show what user must do

int mm_InputMembershipType(char *msg);
// Use to input and check if the membership type is valid
// If correct -> return the value as int
// If not correct -> let user type again
// *msg is use to show guide

int mm_InputBirthYear(char *msg);
// Use to input and check if the birth year is valid
// If correct -> return the value as int
// if not correct -> let user type again
// *msg is use to show guide
// Main function of MemberManagement
// This function show Menu and give user action to use other sub-function about member management.

int mm_GetMemberIndex(MemberManager *mb_manager, char id[]);
// Return member index in member list by using ID to find

// ---------------------------------------------------------------------------------------------------------------------- MENU FUNCTIONS
void mm_MemberManagement_Menu();
// Member management main menu

void mm_MemberManagement_CorrectDataMenu();
// Use to correct data before add member

void mm_MemberManagement_MakeSureMenu();
// Use to make sure before remove member

void mm_MemberManagement_InfoListMenu();
// The menu that show options in ChangingMemberInfo
// [1] change fullname, [2] change membership type, [0] quit


// ---------------------------------------------------------------------------------------------------------------------- DATA WORKING
void mm_LoadData(MemberManager *mb_manager);
// Get data from file and write it to mb_manager

void mm_SaveData(MemberManager *mb_manager);
// Write data to file from mb_manager's data

// ----------------------------------------------------------------------- MAIN

void mm_MemberManagement(MemberManager *mb_manager, struct Settings *settings);
// Main controll member management's functions

#endif
