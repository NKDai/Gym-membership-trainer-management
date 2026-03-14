#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GlobalFunctions.h"

void Clear()
{
	system("cls");
}

void Pause()
{
	system("Pause");
}

void Noti(char *notification)
{
	printf("[%s]\n", notification);
	Pause();
}

int IsInteger(char *input)
{
    if (input == NULL || *input == '\0')
        return 0;

    int i = 0;

    if (input[i] == '+' || input[i] == '-')
    {
        i++;
        if (input[i] == '\0')
            return 0;
    }

    while (input[i] != '\0')
    {
        if (!isdigit((unsigned char)input[i]))
            return 0;
        i++;
    }

    return 1;
}

int InputIntValue(char *msg)
{
    char input[100];

    printf("%s: ", msg);

    if (scanf("%254s", input) != 1)
        return 999;

    if (IsInteger(input))
        return atoi(input);

    return 999;
}

void ClearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
