#include "utility.h"

void clrInBufScanf()
{
    int c;
    do
        c = getchar();
    while (c != EOF && c != '\n');
}

void validatedInput(const char *prompt, size_t len, char *buff, int (*validator)(const char *))
{
    int result;
    char format[5];
    do
    {
        printf("%s:", prompt);
        format[0] = '%';
        sprintf(format + 1, "%ld", len);
        format[3] = 's';
        format[4] = '\0';
        result = scanf(format, buff);
        if (!result)
            clrInBufScanf();
    } while (!validator(buff));
}