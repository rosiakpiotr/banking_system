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

int validateNameSurname(const char *input)
{
    if (!input)
        return 0;
    while (*input && *input != '\n')
        if (!isalpha(*input++))
            return 0;
    return 1;
}
int validateAddress(const char *input) { return 0; }
int validatePESEL(const char *input) { return 0; }