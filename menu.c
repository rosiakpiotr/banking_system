#include "menu.h"

void menuAddNewCustomer()
{
    SCustomer newCustomer;
    getNewCustomerData(&newCustomer);
    sprintf(newCustomer.accountNumber, "%lu", hash(newCustomer.PESEL));
    int result = saveNewCustomer(&newCustomer);
    if (result == 1)
    {
        printf("New customer added.\n");
    }
    else if (result == CUSTOMER_ALREADY_EXISTS)
    {
        printf("Customer already exists.\n");
    }
}

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

void menuSearch()
{
    printf("\n\n");
    printf("Search for a customer by:\n");
    printf("1. Name\n");
    printf("2. Surname\n");
    printf("3. Address\n");
    printf("4. PESEL(id)\n");
    printf("5. Account number\n");
    printf("6. Return\n");

    int option = getInputNumInRangeInt("Choice", 1, 6);

    SCustomer customer;
    switch (option)
    {
    case 1:
        menuSearchBy("Name", NAME_LENGTH, validateNameSurname, nameFind, &customer);
        break;

    case 2:
        menuSearchBy("Surname", SURNAME_LENGTH, validateNameSurname, surnameFind, &customer);
        break;

    case 3:
        menuSearchBy("Address", ADDRESS_LENGTH, validateAddress, addressFind, &customer);
        break;

    case 4:
        menuSearchBy("PESEL", PESEL_LENGTH, validatePESEL, PESELFind, &customer);
        break;

    case 5:
        menuSearchBy("Account number", ACCOUNT_NUMBER_LENGTH, validateAccNum, accNumFind, &customer);
        break;
    }
}

int menuSearchBy(const char *byWhat, size_t maxInputLen, validator inputValidator, isThatIt searchComparator, SCustomer *found)
{
    char *line;
    int result;

    line = validatedInput(byWhat, maxInputLen, inputValidator);
    char field[maxInputLen + 1];
    memcpy(field, line, maxInputLen + 1);
    free(line);
    line = NULL;
    result = findInDb(found, field, searchComparator);
    if (result == 1)
    {
        printf("Found customer(it will be selected for next operations):\n");
        printHeader();
        printf("1\t");
        printCustomer(found);
        printf("\n");
    }
    else if (result == 0)
    {
        printf("No customer found.\n");
    }

    return result;
}

int getInputNumInRangeInt(const char *prompt, int bottom, int upper)
{
    char *line;
    int num;
    do
    {
        printf("%s: ", prompt);
        line = readline();
        if (!line)
            break;
        num = strtol(line, NULL, 10);
        free(line);
        line = NULL;
    } while (num < bottom || num > upper);
    return num;
}
double getInputNumInRangeDouble(const char *prompt, double bottom, double upper)
{
    char *line;
    double num;
    do
    {
        printf("%s: ", prompt);
        line = readline();
        if (!line)
            break;
        num = strtod(line, NULL);
        free(line);
        line = NULL;
    } while (num < bottom || num > upper);
    return num;
}