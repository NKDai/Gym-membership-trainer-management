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

void DarkTheme()
{
    system("color 0f");
}

void LightTheme()
{
    system("color f0");
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
    char input[255];

    printf("%s: ", msg);
    if (fgets(input, sizeof(input), stdin) == NULL)
        return 999;

    // strip newline and any trailing whitespace
    input[strcspn(input, "\n")] = 0;

    if (IsInteger(input))
        return atoi(input);

    return 999;
}

// consume everything left in stdin until newline or EOF
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
