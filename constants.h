#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NAME_LENGTH 20
#define SURNAME_LENGTH 20
#define ADDRESS_LENGTH 25
#define PESEL_LENGTH 11
#define ACCOUNT_NUMBER_LENGTH 20

#define DB_FILENAME "clients.dat"

// Custom error codes
typedef enum
{
    CUSTOMER_ALREADY_EXISTS = 0x2
} ERROR_CODES;

#endif