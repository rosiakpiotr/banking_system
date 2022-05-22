#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

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
