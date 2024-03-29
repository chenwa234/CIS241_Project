#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <conio.h>
#include <stdint.h>

uint32_t h0, h1, h2, h3;

void getFilename(char *filename);
void switch_slash(char *str);
void getStr_File(char *filename, char *fileStr);
void md5(uint8_t *initial_msg, size_t initial_len);
void combineHash(char *str, uint32_t *h1, uint32_t *h2);


#define MAX 100000
#define MAX_STR 100000
#define MAX_COMB_HASH 65
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

int main()
{
    char filename[MAX_PATH] = {0};
    int userInput = 1;

    uint32_t hashValue[MAX][4]; // store hash value
    int fileTotal = 0; // Total number of files

    char fileStr[MAX_STR];
    char hashValueStr_Correct[33] = {0};

    char combine[65] = {0};

    int i = 0;
    int user_Cont = 1;
    int valid = 0;

    // user input for file
    while (userInput == 1)
    {

        // get filename
        printf("Enter File Pathname or Stop to quit input: ");

        while (strlen(filename) == 0)
            getFilename(filename);
        switch_slash(filename);

        printf("filename = %s\n", filename);

        // checking if filepath exist
        if (access(filename,F_OK) == 0)
        {
            // Making sure it is not the actual hashvalue file
            if (strcmp(filename, "HashMapSave.txt") == 0)
            {
                printf("This file can not be open due to save hash value.\n");
            }

            // None of the above calc hash value for file
            else
            {

                printf("Opening %s\n", filename);
                getStr_File(filename, fileStr);
                md5(fileStr, strlen(fileStr));

                hashValue[fileTotal][0] = h0; // saving values in an array
                hashValue[fileTotal][1] = h1;
                hashValue[fileTotal][2] = h2;
                hashValue[fileTotal][3] = h3;
                fileTotal++;
            }
        }

        else
        {

            printf("File %s does not exist.\n", filename);
        }


        while (valid == 0)
        {

            printf("Enter 0 to stop or 1 to continue: ");
            valid = scanf("%d",&user_Cont);

            if (valid == 1)
            {

                if (user_Cont == 1 || user_Cont == 0)
                {
                    valid = 1;
                    userInput = user_Cont;
                }
                else
                {

                    printf("Enter value must be 1 or 0.\n\n");
                    valid = 0;
                }
            }
            else
            {
                printf("Enter value is not an integer.\n");
            }
        }

        valid = 0;
        strcpy(filename,"\0"); // solves extermly stop issue
    }



    // Compute Final Hash Value
    // Merkle Tree
    while (fileTotal != 1)
    {

        int slot = 0;
        for (i = 0; i <= fileTotal - 2; i += 2)
        {

            combineHash(combine,hashValue[slot],hashValue[slot + 1]);
            md5(combine,strlen(combine));

            hashValue[slot][0] = h0; // saving values in an array
            hashValue[slot][1] = h1;
            hashValue[slot][2] = h2;
            hashValue[slot][3] = h3;
            slot++;

        }

        if (fileTotal % 2 == 1)
        {

            hashValue[slot][0] = hashValue[fileTotal - 1][0];
            hashValue[slot][1] = hashValue[fileTotal - 1][1];
            hashValue[slot][2] = hashValue[fileTotal - 1][2];
            hashValue[slot][3] = hashValue[fileTotal - 1][3];
        }

        // hashValue[slot] = hashValue[fileTotal - 1];
        fileTotal = fileTotal / 2 + fileTotal % 2;
    }


    uint8_t *p;

    // display result



    p=(uint8_t *)&hashValue[0][0];

    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);



    p=(uint8_t *)&hashValue[0][1];

    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);



    p=(uint8_t *)&hashValue[0][2];

    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);



    p=(uint8_t *)&hashValue[0][3];

    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    puts("");


    return 0;
}

void getFilename(char *str)
{

    int i;
    char c;

    // user enter email
    for (i = 0; i < (MAX_PATH - 1); i++)
    {

        c = getchar();
        str[i] = c;
        if (c == '\n')
        {
            break;
        }
    }
    str[i] = '\0';
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

void getStr_File(char *filename, char *fileStr)
{

    FILE *fp;
    unsigned int i = 0;

    fp = fopen(filename,"r");

    while(!feof(fp) || i == MAX_STR)
    {

        fscanf(fp,"%c", &fileStr[i]);
        i++;
    }


    fclose(fp);
}

void md5(uint8_t *initial_msg, size_t initial_len)

{

    uint8_t *msg;
    uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
                   };
    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] =

    {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391

    };

    h0 = 0x67452301; // A
    h1 = 0xefcdab89; // B
    h2 = 0x98badcfe; // C
    h3 = 0x10325476; // D

    int max_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;

    msg = calloc(max_len + 64, 1); // set full length of string
    memcpy(msg, initial_msg, initial_len); // copies over message
    msg[initial_len] = 128; // add the 1 bit at end of message and replace '\n'

    // append the length of the message

    uint32_t bit_len = 8 * initial_len; // finding the overall bits used for the string
    memcpy(msg + max_len, &bit_len, 4); // append length

    int offset;
    for(offset = 0; offset < max_len; offset += (512/8))

    {
        uint32_t *w = (uint32_t *)(msg + offset);
        uint32_t a = h0; // hash values for chunks
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        uint32_t j;
        for (j = 0; j < 64; j++)

        {

            uint32_t f,g;

            if (j < 16)
            {

                f = (b & c) | ((~b) & d);
                g = j;

            }
            else if (j < 32)
            {

                f = (d & b) | ((~d) & c);
                g = (5*j + 1) % 16;

            }
            else if (j < 48)
            {
                f = b ^ c ^ d;
                g = (3*j + 5) % 16;

            }
            else
            {
                f = c ^ (b | (~d));
                g = (7*j) % 16;
            }
            uint32_t temp = d;
            a = b + LEFTROTATE((a + f + k[j] + w[g]), s[j]);

            d = c;
            c = b;
            b = a;
            a = temp;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;



    free(msg);

    }
}

void combineHash(char *str, uint32_t *h1, uint32_t *h2){

    char combineStr[MAX_COMB_HASH] = {0};
    char part[9]= {0};
    int i;

    uint8_t *p;

    for (i = 0; i < 4; i++){

        p=(uint8_t *)&h1[i];
        sprintf(part,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
        strcat(combineStr,part);
    }

    for (i = 0; i < 4; i++){

        p=(uint8_t *)&h2[i];
        sprintf(part,"%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
        strcat(combineStr,part);
    }

    strcpy(str,combineStr);
}
