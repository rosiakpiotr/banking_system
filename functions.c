#include "functions.h"

void listAll() {}

char *generateAccNum() { return NULL; }

int saveAccount(const SCustomer *data) { return 0; }

// searchByAccNum(accnum);
// searchByName(name);
// searchBySurname(surname);
// searchByAddress(address);
// searchByPESEL(PESEL);

void makeDeposit(SCustomer *customer, double amount) {}
int withdraw(SCustomer *customer, double amount) { return 0; }
int transfer(SCustomer *from, SCustomer *to, double amount) { return 0; }

int canChangeBalanceBy(const SCustomer *customer, double amount) { return 0; }
/* ------------ */

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

int validateNameSurname(const char *input)
{
    if (!input)
        return 0;
    while (*input && *input != '\n')
        if (!isalpha(*input++))
            return 0;
    return 1;
}

int validateAddress(const char *input)
{
    return 1;
}

int validatePESEL(const char *input)
{
    int count = 0;
    while (*(input + count) && *(input + count) != '\n')
    {
        if (!isdigit(*(input + count)))
        {
            return 0;
        }
        ++count;
    }
    return count == 11;
}