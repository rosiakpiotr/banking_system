#ifndef TYPES_H
#define TYPES_H

#define NAME_LENGTH 20
#define SURNAME_LENGTH 20
#define ADDRESS_LENGTH 25
#define PESEL_LENGTH 11
#define ACCOUNT_NUMBER_LENGTH 20

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
