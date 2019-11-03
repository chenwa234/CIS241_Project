#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* switch_test(char *);

int main()
{
    char *test;
    test = switch_test("C:\\Users\\Ronald\\CIS241\\Project_Convert_Slash");
    //printf("\n%s\n", test);
    return 0;
}

char* switch_test(char *test) {
    char fixed[50];
    int index = 0;

    strcpy(fixed, test);

    while(fixed[index]) {
        if(fixed[index] == '\\'){
            fixed[index] = '/';
        }
        index++;
    }
    printf("\n%s\n", fixed);
    return fixed;
}
