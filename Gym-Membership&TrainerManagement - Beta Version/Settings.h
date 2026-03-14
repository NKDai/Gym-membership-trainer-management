#ifndef SETTINGS_H
#define SETTINGS_H

#define SETTINGS_FILE_NAME "settings.dat"

#include "MemberManagement.h" 
#include "trainermag.h"

typedef struct Settings
{
	int current_theme; // 0->1->2-> ... ->0
	int current_auto_save_mode;//0, 1
	int current_sort_mode;//0, 1
	
}Settings;

// --------------------------------------------------------------------

extern char *theme_codes[]; 
// Name of themes. E.g : Dark Theme, Light Theme (you can see it in settings menu)
extern int number_of_themes;
// Number of themes : current is 2 (Dark theme and Light theme but future can add more)

extern char *sort_mode_names[];
// Name of sort_mode. E.g : Sort, Sort & Save 

extern char *auto_save_mode_names[];
// Off, On

// --------------------------------------------------------------------

void st_ChangeTheme(Settings *settings);
// Change current theme - 0 : dark theme, 1 : light theme

void st_ChangeAutoSaveMode(Settings *settings);
// Change current auto save mode - 1 : On, 0 :  Off

void st_ChangeSortMode(Settings *settings);
// Change current sort mode - 0 : show sorted list, 1 : show sorted list and save it into data

void st_DeleteAllData(struct MemberManager *member_manager,struct TrainerManager *trainer_manager);
// Clear all data in members.dat & trainers.dat

void st_DefaultSettings(Settings *settings);
// Change all settings back to default, theme=0, auto_save=0, sort_mode=0

void st_GetThemeCode(int theme, char code[]);
// split theme code and write the code of theme into char "code" using strcpy

void st_GetThemeName(int theme, char name[]);
// split theme code and write the name of theme into char "name" using strcpy

void st_SetTheme(int theme);
// Find theme code and active it

void st_SetSettings(Settings *settings);
// Load settings data & set theme

// --------------------------------------------------------------------
void st_LoadSettings(Settings *settings);
// load settings
void st_SaveSettings(Settings *settings);
// Save settings
// --------------------------------------------------------------------

void st_Settings_Menu(Settings *settings);
// Show all settings can be changed and these current value
// Example settings menu: 
// ---------------- SETTINGS ---------------------
// [1] Theme             - Current : Dark Theme
// [2] Auto Save         - Current : On
// [3] Sort Mode         - Current : Sort & Save
// -----------------------------------------------
// [4] Default Settings
// [5] Delete All Members & Trainers Data
// -----------------------------------------------
// [0] Save and Back
// -----------------------------------------------
// Enter your choice : 

void st_Settings_Management(Settings *settings,struct MemberManager *member_manager,struct TrainerManager *trainer_manager);
// Main function that shows menu, manages & controls all settings

// case choice=1 -> Change theme to the next theme in list.
// E.g: If the list of themes has 4 different themes the current_theme will be changed 0->1->2->3->0

// case choice=2 -> Change auto save mode from 0->1 or 1->0
// case choice=3 -> Change sort mode from 0->1 or 1->0

// case choice=4 -> Ask to ensure -> Set settings as default 
// case choice=5 -> Ask to ensure -> Delete all data
#endif