#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

int main()
{
    char str[MAX] = {'\0'};
    char fin_str[MAX] = {'\0'};
    int counter = 0;

    printf("Please enter a file path or Stop to quit input.\n");
    do {
        gets(str);
        strcat(fin_str, str);
        counter++;
    } while(strcmp(str,"Stop"));

    printf("The total amount of files inputed : %d\n", counter-1);

    int i = 0;

    for(i = 0; i < strlen(fin_str) - 4; i++) {
        printf("%c", fin_str[i]);
    }


    return 0;
}
