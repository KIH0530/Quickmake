// touch filename in command line in windows
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        FILE *fp = fopen(argv[1], "w");
        if (fp == NULL)
        {
            printf("Failed to create file %s!\n", argv[1]);
            return 1;
        }
        fprintf(fp, NULL);
        fclose(fp);
    }
    else
    {
        printf("No file to create!\n");
    }
    return 0;
}