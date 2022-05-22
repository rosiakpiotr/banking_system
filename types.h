#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

struct SCustomer;

typedef int (*validator)(const char *input);
typedef int (*isThatIt)(const struct SCustomer *c, const void *target);

typedef struct SCustomer
{
	// Char arrays have defined length for any use and
	// one additional place for NULL terminator.
	char accountNumber[ACCOUNT_NUMBER_LENGTH + 1];
	char name[NAME_LENGTH + 1];
	char surname[SURNAME_LENGTH + 1];
	char address[ADDRESS_LENGTH + 1];
	char PESEL[PESEL_LENGTH + 1];
	double balance;
} SCustomer;

#endif
