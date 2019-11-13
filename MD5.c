#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdint.h>
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
// These vars will contain the hash
uint32_t h0, h1, h2, h3;
void md5(uint8_t *initial_msg, size_t initial_len);
int main()
{

    md5("fox",3);
    uint8_t *word = "fox ";
    size_t a= sizeof(word);
    md5(word,a);
    return 0;

}
/*
uint32_t gateOp(uint32_t x, uint32_t y, uint32_t z, char letter){
    if (letter == 'F'){
        return ((x & y) | (~x & z));
    }
    else if(letter == 'G'){
        return ((x & z) | (y & ~z));
    }
    else if (letter == 'H'){
        return (x ^ y ^ z);
    }
    else if (letter == 'I'){ // must be I
        return (y ^ ( x | ~z));
    }
    return 0;
}
*/

void md5(uint8_t *initial_msg, size_t initial_len)
{
    // some variables

    //int i;

    // Message (to prepare)

    uint8_t *msg;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
    // r specifies the per-round shift amounts

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

    // Note initial len is in length
    uint32_t new_length = (initial_len * 8); // get number of bits used excluding final'\n
    /* Note initial len is in length
    uint32_t new_length = (initial_len * 8); // get number of bits used excluding final'\n
    while (new_length > max_len)
    {
        max_len += 512;
    }
    */

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

            if (j < 16) {

                f = (b & c) | ((~b) & d);

                g = j;

            } else if (j < 32) {

                f = (d & b) | ((~d) & c);

                g = (5*j + 1) % 16;

            } else if (j < 48) {

                f = b ^ c ^ d;

                g = (3*j + 5) % 16;

            } else {

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
    }

    uint8_t *p;
    // display result

    p=(uint8_t *)&h0;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h1;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h2;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h3;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    puts("");


    free(msg);
}
