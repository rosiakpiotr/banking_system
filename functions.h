#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utility.h"
#include "types.h"
#include "constants.h"

void listAll();
void printHeader();
void printCustomer(const SCustomer *customer);

int alreadyExists(const SCustomer *cust);

// account number, name, surname, address,
// identification number
int findInDb(SCustomer *found, const void *target, int (*isThatIt)(const SCustomer *cust, const void *target));
int nameFind(const SCustomer *cust, const void *target);
int surnameFind(const SCustomer *cust, const void *target);
int addressFind(const SCustomer *cust, const void *target);
int PESELFind(const SCustomer *cust, const void *target);
int accNumFind(const SCustomer *cust, const void *target);

void makeDeposit(SCustomer *customer, double amount);
int withdraw(SCustomer *customer, double amount);
int transfer(SCustomer *from, SCustomer *to, double amount);

int canChangeBalanceBy(const SCustomer *customer, double amount);

int validateNameSurname(const char *input);
int validateAddress(const char *input);
int validatePESEL(const char *input);

int saveNewCustomer(const SCustomer *customer);

#endif