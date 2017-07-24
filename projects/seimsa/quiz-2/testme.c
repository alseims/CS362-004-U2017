#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //**************************METHOD 1***********************************
    /*char availChars[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
     int n = rand() % 9;
     return availChars[n];*/
    
    //**************************METHOD 2***********************************
    /*char n = rand() % (127 - 32) + 32;
     return n;*/
    
    //**************************METHOD 3***********************************
    char availChars[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']', 0, 0};
    for(int i = 9; i < 11; i++)
    {
        availChars[i] = rand() % (127 - 32) + 32;
    }
    int n = rand() % 11;
    return availChars[n];
}

char *inputString()
{
    int n;
    static char returnString[6];
    //**************************METHOD 1***********************************
    /*char availChars[] = {'e', 'r', 's', 't'};
     for(int i = 0; i < 5; i++)
     {
     n = rand() % 4;
     returnString[i] = availChars[n];
     }*/
    
    //**************************METHOD 2***********************************
    /*for(int i = 0; i < 5; i++)
     {
     returnString[i] = rand() % (127 - 32) + 32;
     }*/
    
    //**************************METHOD 3***********************************
    char availChars[] = {'e', 'r', 's', 't', 0, 0};
    for(int j = 4; j < 6; j++)
    {
        availChars[j] = rand() % (127 - 32) + 32;
    }
    for(int i = 0; i < 5; i++)
    {
        n = rand() % 6;
        returnString[i] = availChars[n];
    }
    
    returnString[5] = '\0';
    return returnString;
}

void testme()
{
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    while (1)
    {
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
        
        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' ' && state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e'
            && s[2] == 's' && s[3] == 'e'
            && s[4] == 't' && s[5] == '\0'
            && state == 9)
        {
            printf("error ");
            exit(200);
        }
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
