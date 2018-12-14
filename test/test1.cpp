#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
volatile void Sort(char part[][20], int n)
{
    int i, j;
    char tmp[100] = {0};
    for (j = 0; j < n - 1; j++)
        for (i = 1; i < n - j; i++) {
            if (strcmp(part[i - 1], part[i]) > 0) {
                strcpy(tmp, part[i - 1]);
                strcpy(part[i - 1], part[i]);
                strcpy(part[i], tmp);
            }
        }
}

int main()
{
    char ss[8][20] = {"asdfdf",
                      "dfefrdf",
                      "regfrrv",
                      "odgfpds",
                      "hguhx",
                      "sdffsdf",
                      "tggf",
                      "gtgffg"};
    int i;
    for (i = 0; i < 8; i++)
        printf("%s\n", ss[i]);
    printf("分隔符\n");
    Sort(ss, 8);
    for (i = 0; i < 8; i++)
        printf("%s\n", ss[i]);
    printf("分隔符\n");
    return 0;
}
