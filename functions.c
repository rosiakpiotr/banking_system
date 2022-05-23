#include "functions.h"

int custCmp(const SCustomer *c1, const SCustomer *c2)
{
    return strcmp(c1->accountNumber, c2->accountNumber) == 0;
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

int validateAccNum(const char *input)
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
    return count;
}

int findInDb(SCustomer *found, const void *target, isThatIt comparator)
{
    FILE *fp;
    fp = fopen(DB_FILENAME, "rb");
    if (!fp)
        return -1;
    int result = 0;
    while (fread(found, sizeof(SCustomer), 1, fp) == 1)
    {
        if (comparator(found, target))
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

int updateCustomer(const SCustomer *customer)
{
    if (!alreadyExists(customer))
        return 0;

    FILE *fp;
    fp = fopen(DB_FILENAME, "rb+");
    if (!fp)
    {
        perror("Error during initialization of database file.");
        return 0;
    }
    SCustomer custFromFile;
    int pos = 0, result = 0;
    while (fread(&custFromFile, sizeof(SCustomer), 1, fp) == 1)
    {
        if (custCmp(customer, &custFromFile))
        {
            if (fseek(fp, pos * sizeof(SCustomer), SEEK_SET) == 0)
            {
                result = fwrite(customer, sizeof(SCustomer), 1, fp);
            }
            else
            {
                perror("Error seeking into database file.");
            }
            break;
        }
        ++pos;
    }
    fclose(fp);
    return result;
}

void listAll()
{
    FILE *fp;
    fp = fopen(DB_FILENAME, "rb");
    if (!fp)
        return;

    printHeader();
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
    printf("N\tNAME\tSURNAME\tADDRESS\tPESEL\t\tACCOUNT NUMBER\tBALANCE\n");
}

void printCustomer(const SCustomer *customer)
{
    printf("%s\t%s\t%s\t%s\t%s\t%.2f",
           customer->name,
           customer->surname,
           customer->address,
           customer->PESEL,
           customer->accountNumber,
           customer->balance);
}