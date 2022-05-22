#include "utility.h"

char *readline()
{
    char *line = NULL;
    int c;
    size_t bufsize = 0;
    size_t size = 0;

    while ((c = getchar()) != EOF)
    {
        if (size >= bufsize)
        {
            char *newbuf;
            // Determine new buffer size
            if (bufsize == 0)
                bufsize = 2;
            // Check for overflows in bufsize
            else if (bufsize <= (((size_t)-1) / 2))
                bufsize = 2 * size;
            else
            {
                free(line);
                abort();
            }

            newbuf = realloc(line, bufsize);
            if (newbuf == NULL)
            {
                free(line);
                abort();
            }
            line = newbuf;
        }

        line[size++] = c;
        if (c == '\n')
            break;
    }

    if ((c == EOF) && (size == 0))
        return NULL;

    if (size >= bufsize)
    {
        char *newbuf;
        if (size < (size_t)-1)
            bufsize = size + 1;
        else
        {
            free(line);
            abort();
        }
        newbuf = realloc(line, bufsize);
        if (newbuf == NULL)
        {
            free(line);
            abort();
        }
        line = newbuf;
    }
    line[size] = '\0';
    return line;
}

char *rmNewline(char *line)
{
    size_t length = strlen(line);
    char *buf = malloc(sizeof(char) * length - 1);
    if (buf)
    {
        memcpy(buf, line, length);
        buf[length - 1] = '\0';
    }
    free(line);
    return buf;
}

char *validatedInput(const char *prompt, size_t maxLen, int (*validator)(const char *input))
{
    char *line = NULL;
    do
    {
        printf("%s:", prompt);
        free(line);
        line = NULL;
    } while ((line = readline()) != NULL && (!validator(line)
                                             /* Subtracting newline character */
                                             || (strlen(line) - 1) > maxLen));

    return rmNewline(line);
}

unsigned long
hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return abs(hash);
}
