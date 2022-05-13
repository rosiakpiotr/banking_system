#ifndef TYPES_H
#define TYPES_H

struct SCustomer
{
	// Char arrays have defined length for any use and 
	// one additional place for NULL terminator.
	char name[20+1];
	char surname[20+1];
	char address[25+1];
	char PESEL[11+1];
};

#endif
