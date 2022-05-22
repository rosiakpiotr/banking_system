#ifndef MENU_H
#define MENU_H

#include "types.h"
#include "functions.h"

void menuAddNewCustomer();

void getNewCustomerData(SCustomer *newCustomer);
int menuSearch(SCustomer *found);
int menuSearchBy(const char *byWhat, size_t maxInputLen, validator inputValidator, isThatIt searchComparator, SCustomer *found);
int menuMoneyTransfer();
int menuDeposit();
int menuWithdraw();

int confirmTransfer(const SCustomer *from, const SCustomer *to, double amount);
int confirmBalanceChange(const SCustomer *customer, double amount);

int getInputNumInRangeInt(const char *prompt, int bottom, int upper);
double getInputNumInRangeDouble(const char *prompt, double bottom, double upper);

#endif