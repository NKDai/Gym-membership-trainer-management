#ifndef MEMBERMANAGEMENT_H
#define MEMBERMANAGEMENT_H
#include "member.h"
// ---------------------------------------------------------------------------------------------------------------------- STRUCT

typedef struct 
{
	int count;
	Member *members;
	
}MemberManager;

// ---------------------------------------------------------------------------------------------------------------------- CORE FUNCTIONS
void mm_AddMember(MemberManager *mb_manager, Member member_info);
// Use to add member into a MemberManager directly from a copy of member_info

void mm_RemoveMember(MemberManager *mb_manager, int member_index);
// Use to remove member from a MemberManager directly by the index of that member

void mm_DisplayAllMembers(MemberManager *mb_manager);
// Display all members as a grid board


void mm_SearchMember(MemberManager *mb_manager, char *id, Member **selector);
// Use to search a member by input an ID

// ---------------------------------------------------------------------------------------------------------------------- COMPLETED FUNCTIONS

void mm_MemberManagement_AddingMember(MemberManager *mb_member_manager);
// Clear screen
// Let user input member fullname, membership type and generate new member
// Then make sure member's information is correct or not
// If correct -> save member to data -> show notification and back to menu
// If not correct -> show notification and back to menu
// This function use mm_AddMember as core to add member

void mm_MemberManagement_RemovingMember(MemberManager *mb_manager);
// Clear screen
// Let user input member ID and check if ID is valid
// Print out the information of selected member
// Then ask user if they really want to remove this member of not
// If sure -> remove member from data -> show notification and back to menu
// If not sure -> show notification and back to menu
// This function use mm_RemoveMember as core to remove member

void mm_MemberManagement_DisplayingAllMembers(MemberManager *mb_manager);
// Clear screen
// Then use mm_DisplayAllMembers to show all member
// Last, pause program before back to menu

void mm_MemberManagement_SearchingMember(MemberManager *mb_manager);
// Clear screen
// Use to let user enter member ID, check ID valid 
// Print out the information about selected member
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
// Use to input and check if the membership type selected is correct
// If correct -> return the value as int
// If not correct -> let user type again
// *msg is use to show what user must do

void mm_MemberManagement();
// Main function of MemberManagement
// This function show Menu and give user action to use other sub-function about member management.

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
#endif
