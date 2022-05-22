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

void getNewCustomerData(SCustomer *newCustomer)
{
    char *line;
    printf("New account creator:\n");
    printf("Please fill customer data below.\n");

    line = validatedInput("Name", NAME_LENGTH, validateNameSurname);
    memcpy(newCustomer->name, line, NAME_LENGTH + 1);
    free(line);
    line = NULL;

    line = validatedInput("Surname", SURNAME_LENGTH, validateNameSurname);
    memcpy(newCustomer->surname, line, SURNAME_LENGTH + 1);
    free(line);
    line = NULL;

    line = validatedInput("Address", ADDRESS_LENGTH, validateAddress);
    memcpy(newCustomer->address, line, ADDRESS_LENGTH + 1);
    free(line);
    line = NULL;

    line = validatedInput("PESEL", PESEL_LENGTH, validatePESEL);
    memcpy(newCustomer->PESEL, line, PESEL_LENGTH + 1);
    free(line);
    line = NULL;
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

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return abs(hash);
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