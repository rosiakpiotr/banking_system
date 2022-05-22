#include "menu.h"

void menuAddNewCustomer()
{
    SCustomer newCustomer;
    getNewCustomerData(&newCustomer);
    sprintf(newCustomer.accountNumber, "%lu", hash(newCustomer.PESEL));
    newCustomer.balance = 20;
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

int menuSearch(SCustomer *found)
{
    printf("Search for a customer by:\n");
    printf("1. Name\n");
    printf("2. Surname\n");
    printf("3. Address\n");
    printf("4. PESEL(id)\n");
    printf("5. Account number\n");
    printf("6. Return\n");

    int option = getInputNumInRangeInt("Choice", 1, 6);
    int result = 0;
    switch (option)
    {
    case 1:
        result = menuSearchBy("Name", NAME_LENGTH, validateNameSurname, nameFind, found);
        break;

    case 2:
        result = menuSearchBy("Surname", SURNAME_LENGTH, validateNameSurname, surnameFind, found);
        break;

    case 3:
        result = menuSearchBy("Address", ADDRESS_LENGTH, validateAddress, addressFind, found);
        break;

    case 4:
        result = menuSearchBy("PESEL", PESEL_LENGTH, validatePESEL, PESELFind, found);
        break;

    case 5:
        result = menuSearchBy("Account number", ACCOUNT_NUMBER_LENGTH, validateAccNum, accNumFind, found);
        break;
    }

    return result;
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
        printf("Found customer:\n");
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

int confirmTransfer(const SCustomer *from, const SCustomer *to, double amount)
{
    printf("Are you sure you want to transfer %.2f?\n", amount);
    printHeader();
    printf("FROM\t");
    printCustomer(from);
    printf("\nTO\t");
    printCustomer(to);
    printf("\n\n");
    return getInputNumInRangeInt("Type 1 to confirm 0 to abort", 0, 1);
}
int confirmBalanceChange(const SCustomer *customer, double amount)
{
    printf("Are you sure you want to change balance by %.2f on this account?\n", amount);
    printHeader();
    printf("1\t");
    printCustomer(customer);
    printf("\n\n");
    return getInputNumInRangeInt("Type 1 to confirm 0 to abort", 0, 1);
}

int menuMoneyTransfer()
{
    printf("Money transfer\n");
    printf("You will be asked to search for customer FROM and TO.\n");

    SCustomer from, to;
    int result;

    printf("\n");
    printf("Select customer FROM.\n");
    result = menuSearch(&from);
    if (result != 1)
    {
        printf("Failed to select customer, aborting.\n");
        return 0;
    }

    printf("\n");
    printf("Select customer TO.\n");
    result = menuSearch(&to);
    if (result != 1)
    {
        printf("Failed to select customer, aborting.\n");
        return 0;
    }

    if (custCmp(&from, &to) == 1)
    {
        printf("Can't transfer money to the same account, aborting.\n");
        return 0;
    }

    printf("\n");
    double amount = getInputNumInRangeDouble("Amount", 0, from.balance);

    if (from.balance <= 0)
    {
        printf("Customer FROM has no money to transfer, aborting.\n");
        return 0;
    }

    printf("\n\n");

    int fail = 0;
    int confirm = confirmTransfer(&from, &to, amount);
    if (confirm)
    {
        from.balance -= amount;
        to.balance += amount;
        if (fail || updateCustomer(&from) != 1)
        {
            fail = 1;
        }
        if (fail || updateCustomer(&to) != 1)
        {
            fail = 1;
        }
    }

    if (fail)
    {
        printf("Failed to finalize transaction.\n");
        printf("Customer's balances will remain unchanged.\n");
        from.balance += amount;
        to.balance -= amount;
    }
    else
    {
        printf("Transfer succesful.\n");
    }

    printf("\nCurrent state:\n");
    printHeader();
    printf("FROM\t");
    printCustomer(&from);
    printf("\nTO\t");
    printCustomer(&to);

    return fail;
}

int menuDeposit()
{
    printf("Deposits\n");
    printf("Select customer.\n");
    SCustomer customer;
    int result;
    result = menuSearch(&customer);
    if (result != 1)
    {
        printf("Aborting.\n");
        return 0;
    }

    printf("\n");
    double amount = getInputNumInRangeDouble("Amount(0-10e15)", 0, 10e15);
    int confirm = confirmBalanceChange(&customer, amount);
    int fail = 0;
    if (confirm)
    {
        customer.balance += amount;
        fail = updateCustomer(&customer) != 1;
    }

    if (fail)
    {
        customer.balance -= amount;
        printf("Deposit failed, balance will remain unchanged\n");
    }

    printf("\nCurrent state:\n");
    printHeader();
    printf("1\t");
    printCustomer(&customer);

    return fail;
}

int menuWithdraw()
{
    printf("Withdrawals\n");
    printf("Select customer.\n");
    SCustomer customer;
    int result;
    result = menuSearch(&customer);
    if (result != 1)
    {
        printf("Aborting.\n");
        return 0;
    }

    printf("\n");
    double amount = getInputNumInRangeDouble("Amount", 0, customer.balance);
    int confirm = confirmBalanceChange(&customer, amount);
    int fail = 0;
    if (confirm)
    {
        customer.balance -= amount;
        fail = updateCustomer(&customer) != 1;
    }

    if (fail)
    {
        customer.balance += amount;
        printf("Withdraw failed, balance will remain unchanged\n");
    }

    printf("\nCurrent state:\n");
    printHeader();
    printf("1\t");
    printCustomer(&customer);

    return fail;
}