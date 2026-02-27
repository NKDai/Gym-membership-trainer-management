#include <ctype.h>
#include "GlobalFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Clear()
{
	system("cls");
}

void Pause()
{
	system("Pause");
}

void DarkTheme()
{
	system("color 0f");
}

void WhiteTheme()
{
	system("color f0");
}

void Noti(char *notification)
{
	printf("[%s]\n", notification);
	Pause();
}

int InputIntValue(char *msg)
{
	char input[255];
	
	printf("%s :", msg);
	scanf("%s", &input);
	
	if(IsDigit(input))
    {
    	return atoi(input);
	}
	else
	{
		return 999;
	}
}

int IsDigit(char *input)
{
    int i = 0;
    while (input[i] != '\0')
    {
        if (!isdigit(input[i]))
            return 0;
        i++;
    }
    return 1;
}