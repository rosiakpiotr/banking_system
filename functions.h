#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utility.h"
#include "types.h"
#include "constants.h"

void listAll();
void printCustomer(const SCustomer *customer);

int custCmp(const SCustomer *c1, const SCustomer *c2);
int alreadyExists(const SCustomer *cust);
int findByName(const char *name, SCustomer *found);

void makeDeposit(SCustomer *customer, double amount);
int withdraw(SCustomer *customer, double amount);
int transfer(SCustomer *from, SCustomer *to, double amount);

int canChangeBalanceBy(const SCustomer *customer, double amount);

void getNewCustomerData(SCustomer *newCustomer);

char *rmNewline(char *line);
char *validatedInput(const char *prompt, size_t maxLen, int (*validator)(const char *input));

// http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str);

int validateNameSurname(const char *input);
int validateAddress(const char *input);
int validatePESEL(const char *input);

int saveNewCustomer(const SCustomer *customer);

#endif