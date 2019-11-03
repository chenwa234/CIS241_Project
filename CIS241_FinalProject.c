#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fp;

    if (access("test.txt",F_OK) == 0){

        printf("File exist");
    }

    else{

        printf("File does not exist");
    }

    printf("\n\nHello World");

    return 0;
}
