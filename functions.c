#include "functions.h"

void makeDeposit(SCustomer *customer, double amount) {}
int withdraw(SCustomer *customer, double amount) { return 0; }
int transfer(SCustomer *from, SCustomer *to, double amount) { return 0; }

int canChangeBalanceBy(const SCustomer *customer, double amount) { return 0; }
/* ------------ */

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
int findInDb(SCustomer *found, const void *target, int (*isThatIt)(const SCustomer *cust, const void *target))
{
    FILE *fp;
    fp = fopen(DB_FILENAME, "rb");
    if (!fp)
        return -1;
    int result = 0;
    while (fread(found, sizeof(SCustomer), 1, fp) == 1)
    {
        if (isThatIt(found, target))
        {
            result = 1;
            break;
        }
    }
    fclose(fp);
    return result;
}

int nameFind(const SCustomer *cust, const void *target)
{
    return strcmp(cust->name, (const char *)target) == 0;
}
int surnameFind(const SCustomer *cust, const void *target)
{
    return strcmp(cust->surname, (const char *)target) == 0;
}
int addressFind(const SCustomer *cust, const void *target)
{
    return strcmp(cust->address, (const char *)target) == 0;
}
int PESELFind(const SCustomer *cust, const void *target)
{
    return strcmp(cust->PESEL, (const char *)target) == 0;
}
int accNumFind(const SCustomer *cust, const void *target)
{
    return strcmp(cust->accountNumber, (const char *)target) == 0;
}

int alreadyExists(const SCustomer *cust)
{
    SCustomer dummy;
    return findInDb(&dummy, cust->accountNumber, accNumFind) == 1;
}

int saveNewCustomer(const SCustomer *customer)
{
    if (alreadyExists(customer))
        return CUSTOMER_ALREADY_EXISTS;
    FILE *fp;
    fp = fopen(DB_FILENAME, "ab");
    if (!fp)
    {
        perror("Error during initialization of database file.");
        return 0;
    }
    int result = fwrite(customer, sizeof(SCustomer), 1, fp);
    fclose(fp);
    return result;
}

void listAll()
{
    FILE *fp;
    fp = fopen(DB_FILENAME, "rb");
    if (!fp)
        return;
    SCustomer custFromFile;
    int custNum = 1;
    while (fread(&custFromFile, sizeof(SCustomer), 1, fp) == 1)
    {
        printf("%d\t", custNum);
        printCustomer(&custFromFile);
        printf("\n");
        custNum++;
    }
    fclose(fp);
}

void printHeader()
{
    printf("N\tNAME\tSURNAME\tADDRESS\tPESEL\t\tACCOUNT NUMBER\n");
}

void printCustomer(const SCustomer *customer)
{
    printf("%s\t%s\t%s\t%s\t%s",
           customer->name,
           customer->surname,
           customer->address,
           customer->PESEL,
           customer->accountNumber);
}

void enterSearchMode()
{
}