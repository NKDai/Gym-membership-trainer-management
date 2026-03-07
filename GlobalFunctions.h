#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

void Clear();
// clear content on the console screen

void Pause();
// pause the program

void LightTheme();
// use to make font color to black and background color to white
void DarkTheme();
// use to make font color to white and background color to black

void Noti(char *notification);
// use to print notification and pause the program

int InputIntValue(char *msg);
// return integer if the input is an integer. Else -> return 999

int IsInteger(char *input);
// use to check if a string input is a integer or not

// flush any leftover characters (newlines etc.) from stdin so that
// subsequent fgets calls don't immediately return an empty line
void clearInputBuffer(void);
#endif
