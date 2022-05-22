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
    char *line;
    int option;

    printf("\n\n");
    printf("Search for a customer by:\n");
    printf("1. Name\n");
    printf("2. Surname\n");
    printf("3. Address\n");
    printf("4. PESEL(id)\n");
    printf("5. Account number\n");
    printf("6. Return\n");

    do
    {
        printf("Choice: ");
        line = readline();
        if (!line)
            break;
        option = strtol(line, NULL, 10);
        free(line);
        line = NULL;
    } while (option < 1 || option > 6);
    free(line);
    line = NULL;

    SCustomer customer;
    int result;
    switch (option)
    {
    case 1:
    {
        line = validatedInput("Name", NAME_LENGTH, validateNameSurname);
        char name[NAME_LENGTH + 1];
        memcpy(name, line, NAME_LENGTH + 1);
        free(line);
        line = NULL;
        result = findInDb(&customer, name, nameFind);
        if (result == 1)
        {
            printf("Customer:\n");
            printHeader();
            printf("1\t");
            printCustomer(&customer);
            printf("\n");
        }
    }
    }

    free(line);
}