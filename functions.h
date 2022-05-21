#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utility.h"
#include "types.h"

/* MODEL OPERATIONS */
void listAll();

char *generateAccNum();

int saveAccount(const SCustomer *data);

// searchByAccNum(accnum);
// searchByName(name);
// searchBySurname(surname);
// searchByAddress(address);
// searchByPESEL(PESEL);

void makeDeposit(SCustomer *customer, double amount);
int withdraw(SCustomer *customer, double amount);
int transfer(SCustomer *from, SCustomer *to, double amount);

int canChangeBalanceBy(const SCustomer *customer, double amount);
/* ------------ */

char *rmNewline(char *line);
char *validatedInput(const char *prompt, size_t maxLen, int (*validator)(const char *input));

int validateNameSurname(const char *input);
int validateAddress(const char *input);
int validatePESEL(const char *input);

#endif