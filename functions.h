#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* MODEL OPERATIONS */
void listAll();

generateAccNum();

createAcconut(data...);

searchByAccNum(accnum);
searchByName(name);
searchBySurname(surname);
searchByAddress(address);
searchByPESEL(PESEL);

makeDeposit(amount);
withdraw(amount);
bool transfer(from, to, amount);

canChangeBalanceBy(customer,amount);
/* ------------ */

int validateNameSurname(input);
int validateAddress(input);
int validatePESEL(input);

#endif FUNCTIONS_H
