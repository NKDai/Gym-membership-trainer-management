#ifndef SORT_H
#define SORT_H

#include "MemberManagement.h"
#include "Settings.h"

void s_SortMembersByBirthYear(MemberManager *mb_manager, Settings *settings);
// Use to copy member_manager -> sort it by birth year -> print it -> check setting -> save or not

void s_SortMembersByRegistrationDate( MemberManager *mb_manager,  Settings *settings);
// Use to copy member_manager -> sort it by registration date -> print it -> check setting -> save or not

void s_SortManagement( MemberManager *mb_manager,  Settings *settings);
// Use to manage all types of sort

void s_SelectionSort( MemberManager *mb_manager, int condition_mode);
// Use selection sort to sort member_manager with the condition about birth_year or registration_date

void s_CopyMemberManager( MemberManager *source,  MemberManager *dest);
// Copy a source of member_manager to dest 


#endif
