#ifndef MEMBERMANAGEMENT_H
#define MEMBERMANAGEMENT_H
#include "member.h"

typedef struct 
{
	int count;
	Member *members;
	
}MemberManager;

void mm_AddMember(MemberManager *mb_manager, Member member_info);
// Use to add member into a MemberManager directly from a copy of member_info

void mm_RemoveMember(MemberManager *mb_manager, int member_index);
// Use to remove member from a MemberManager directly by the index of that member

void mm_DisplayAllMembers(MemberManager *mb_manager);
// Display all members as a grid board


void mm_SearchMember(MemberManager *mb_manager, char *id, Member **selector);
// Use to search a member by input an ID


void mm_MemberManagement();

#endif