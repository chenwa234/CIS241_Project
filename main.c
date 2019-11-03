#include <stdio.h>
#include <stdlib.h>


int main()
{
    int test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int file_counter = 9;
    int stores[10000];
    int slot = 0, i;

    while(file_counter != 1) {
        slot = 0;
        for(i = 0; i <= file_counter - 1; i++) {
            printf("%d\t", test[i]);
        }
        puts("");

        for(i = 0; i <= file_counter - 2; i+=2) {
            test[slot] = test[i] + test[i+1];
            slot++;
        }

        if(file_counter % 2 == 1) {
            test[slot] = test[file_counter-1];
        }

        test[slot] = test[file_counter-1];
        for(i = slot + 1; i <= file_counter - 1; i++) {
            //s[i] = NULL;
        }
        file_counter = file_counter/2 + file_counter%2;

    }




    return 0;
}
