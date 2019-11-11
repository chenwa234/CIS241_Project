#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void getFilename(char *filename);
void switch_slash(char *str);

#define MAX 100000

int main()
{
    FILE *fp;

    char filename[MAX];
    int userInput = 1;

    uint32_t hashValue[MAX]; // store hash value
    int fileTotal = 0; // Total number of files

    int i = 0;

    // user input for file
    while (userInput)
    {

        // get filename
        printf("Enter File Path or File name in same folder: ");
        getFilename(filename);

        if (access("test.txt",F_OK) == 0)
        {
            if (strcmp(filename, "HashMapSave.txt") == 0)
            {
                printf("This file can not be open due to save hash value.\n");
            }

            else{

                printf("Opening %s", filename);
                // file open and hash value calc//
                /******** ADD *********/
                /*** Save to hashValue Array ***/
            }
        }

        else
        {

            printf("File %s does not exist.\n", filename);
        }
    }

    // Compute Final Hash Value
    // Merkle Tree
    while (fileTotal != 1){

        int slot = 0;
        for (i = 0; i <= fileTotal - 2; i += 2){

            /*** Combine Hash Value **/ /** Use Sting cat **/
            /** Calc new Hash Value and Save **/

            slot++;
        }

        if (fileTotal % 2 == 1){

            hashValue[slot] = hashValue[fileTotal - 1];
        }

        // hashValue[slot] = hashValue[fileTotal - 1]; /** Maybe Add **/
        fileTotal = fileTotal / 2 + fileTotal % 2;
    }

    //fclose(fp);

    return 0;
}

/***** FIX ******/
void getFilename(char *filename)
{

    int i;
    char c;

    // user enter email
    for (i = 0; i < (MAX - 1); i++)
    {

        c = getchar();
        filename[i] = c;
        if (c == '\n')
        {
            break;
        }
    }
}

void switch_slash(char *str)
{

    int index = 0;
    while (str[index] != '\n')
    {

        if (str[index] == '\\')
            str[index] = '/';
        index++;
    }
}
