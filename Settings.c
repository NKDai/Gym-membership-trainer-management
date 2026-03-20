#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Settings.h"
#include "MemberManagement.h"
#include "trainermag.h"

#include "GlobalFunctions.h"

char *theme_codes[] = {
    "Classic Dark.0f",
    "Light Theme.f0",
    "Matrix Style.0a",
    "Cyberpunk.0d",
    "Navy Blue.1f",
    "Blood Moon.0c",
    "Gold Edition.06",
    "Communism.4e"
};
int number_of_themes = 8;

char *auto_save_mode_names[] = {
    "Off", "On"
};

char *sort_mode_names[] = {
    "Just Sort", "Sort & Save"
};

void st_DarkTheme()
{
    system("color 0f");
}

void st_LightTheme()
{
    system("color f0");
}

void st_ChangeAutoSaveMode(Settings *settings)
{
    settings->current_auto_save_mode += 1;
    if(settings->current_auto_save_mode > 1)
    {
        settings->current_auto_save_mode = 0;
    }
}

void st_ChangeSortMode(Settings *settings)
{
    (*settings).current_sort_mode += 1;
    if(settings->current_sort_mode > 1)
    {
        settings->current_sort_mode = 0;
    }
}

void st_DefaultSettings(Settings *settings)
{
    (*settings).current_theme = 0;
    (*settings).current_auto_save_mode = 1;
    (*settings).current_sort_mode = 0;

    st_DarkTheme();
}

void st_DeleteAllData(MemberManager *member_manager, TrainerManager *trainer_manager) {
    free(member_manager->members);
    free(trainer_manager->trainers);

    member_manager->members = NULL;
    member_manager->count = 0;
    
    trainer_manager->trainers = NULL;
    trainer_manager->count = 0;
}

void st_SaveSettings(Settings *settings)
{
    FILE *f = fopen(SETTINGS_FILE_NAME, "wb");

    if(f == NULL)
    {
        printf("Cannot open settings file!\n");
        return;
    }

    fwrite(settings, sizeof(Settings), 1, f);

    fclose(f);
}

void st_LoadSettings(Settings *settings)
{
    FILE *f = fopen(SETTINGS_FILE_NAME, "rb");

    if(f == NULL)
    {
        settings->current_theme = 0;
        settings->current_auto_save_mode = 1;
        settings->current_sort_mode = 0;
        return;
    }

    fread(settings, sizeof(Settings), 1, f);

    fclose(f);
}

void st_GetThemeCode(int theme, char *code)
{
    char *temp = strdup(theme_codes[theme]); 
    strtok(temp, ".");          
    strcpy(code, strtok(NULL, ".")); // Copy trực tiếp kết quả strtok vào code
    free(temp); // Chỉ cần free temp là đủ
}


void st_GetThemeName(int theme, char *name)
{
    char *temp = strdup(theme_codes[theme]);
    strcpy(name, strtok(temp, "."));
    free(temp);
}

void st_ChangeTheme(Settings *settings)
{
    settings->current_theme += 1;
    if(settings->current_theme >= number_of_themes)
    {
        settings->current_theme = 0;
    }
}

void st_SetTheme(int theme)
{
    char final_code[20];
    if(theme >= 0 && theme < number_of_themes)
    {
        char code[10];
        st_GetThemeCode(theme, code);
        sprintf(final_code, "color %s", code);
        system(final_code);
    }
    else
    {
        system("color 0f");		
    }
}

void st_SetSettings(Settings *settings)
{
    st_LoadSettings(settings);
    st_SetTheme(settings->current_theme);
}

void st_Settings_Menu(Settings *settings)
{
    char theme_name[20];
    st_GetThemeName(settings->current_theme, theme_name);
    
    printf("----------- SETTINGS -----------\n");
    printf("[1] Theme       - Current : %s\n", theme_name);
    printf("[2] Auto Save   - Current : %s\n", auto_save_mode_names[settings->current_auto_save_mode]);
    printf("[3] Sort Mode   - Current : %s\n", sort_mode_names[settings->current_sort_mode]);

    printf("--------------------------------\n");
    printf("[4] Default Settings\n");
    printf("[5] Delete All Data\n");
    printf("--------------------------------\n");
    printf("[0] Save and Back\n");
    printf("--------------------------------\n");
}

void st_Settings_Management(Settings *settings, MemberManager *member_manager, TrainerManager *trainer_manager)
{
    int choice;

    do
    {
        Clear();
        st_Settings_Menu(settings);

        choice = InputIntValue("Enter your choice: ");

        switch(choice)
        {
            case 1:
            {
                st_ChangeTheme(settings);
                st_SetTheme(settings->current_theme);
                st_SaveSettings(settings);
                break;
            }

            case 2:
            {
                st_ChangeAutoSaveMode(settings);
                st_SaveSettings(settings);
                break;
            }

            case 3:
            {
                st_ChangeSortMode(settings);
                st_SaveSettings(settings);
                break;
            }

            case 4:
            {
                st_DefaultSettings(settings);
                Clear();
                Noti("Set as default settings successfully!");
                st_SaveSettings(settings);
                break;
            }
            
            case 5:
            	printf("Are you sure you want to delete all data?\n");
            	printf("[1] - Yes, [0] - No\n");
            	int action = InputIntValue("Enter your choice: ");
				do{
					if(action==1 && action!=0)
					{
						st_DeleteAllData(member_manager, trainer_manager);
						action = 0;
					}
					else
					{
						Clear();
						Noti("Invalid choice!");
					}
				}while(action!=0);
			
            case 0:
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);

    st_SaveSettings(settings);
}
