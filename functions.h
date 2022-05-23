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

int custCmp(const SCustomer *c1, const SCustomer *c2);

int alreadyExists(const SCustomer *cust);

int findInDb(SCustomer *found, const void *target, isThatIt comparator);
int nameFind(const SCustomer *cust, const void *target);
int surnameFind(const SCustomer *cust, const void *target);
int addressFind(const SCustomer *cust, const void *target);
int PESELFind(const SCustomer *cust, const void *target);
int accNumFind(const SCustomer *cust, const void *target);

int validateNameSurname(const char *input);
int validateAddress(const char *input);
int validatePESEL(const char *input);
int validateAccNum(const char *input);

int saveNewCustomer(const SCustomer *customer);
int updateCustomer(const SCustomer *customer);

#endif