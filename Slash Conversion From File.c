#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

int main()
{
    FILE *fp;
    char buff[MAX];
    int i = 0;
    int index = 0;

    fp = fopen("./test.txt", "r");

    while(!feof(fp)) {
        index  = 0;
        fgets(buff, MAX, (FILE*)fp);
        while(index != strlen(buff)) {
            if(buff[index] == '\\') {
                buff[index] = '/';
            }
            index++;
        }
        i++;
        printf("Line %d: %s\n", i, buff);
    }


    return 0;
}

