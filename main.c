#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "types.h"
#include "utility.h"

int main()
{
	char *line;
	int option;
	while (1)
	{
		printf("Banking system\n");
		printf("Available operations:\n");
		printf("1. Create\n");
		printf("2. List all\n");
		printf("3. Search\n");
		printf("4. Transfer money\n");
		printf("5. Deposit\n");
		printf("6. Withdraw\n");
		printf("7. Quit\n");
		printf("Type in option number:");

		line = readline();
		if (!line)
			break;
		option = strtol(line, NULL, 10);
		free(line);
		line = NULL;
		switch (option)
		{
		case 1:
		{
			char accountNumber[ACCOUNT_NUMBER_LENGTH + 1];
			char name[NAME_LENGTH + 1];
			char surname[SURNAME_LENGTH + 1];
			char address[ADDRESS_LENGTH + 1];
			char PESEL[PESEL_LENGTH + 1];
			printf("New account creator:\n");
			printf("Please fill customer data below.\n");

			line = validatedInput("Name", NAME_LENGTH, validateNameSurname);
			memcpy(name, line, NAME_LENGTH + 1);
			free(line);
			line = NULL;

			line = validatedInput("Surname", SURNAME_LENGTH, validateNameSurname);
			memcpy(surname, line, SURNAME_LENGTH + 1);
			free(line);
			line = NULL;

			line = validatedInput("Address", ADDRESS_LENGTH, validateAddress);
			memcpy(address, line, ADDRESS_LENGTH + 1);
			free(line);
			line = NULL;

			line = validatedInput("PESEL", PESEL_LENGTH, validatePESEL);
			memcpy(PESEL, line, PESEL_LENGTH + 1);
			free(line);
			line = NULL;
		}
		break;

		default:
			printf("Invaild input.\n");
			break;
		}

		printf("\n\n\n");
	}

	free(line);
	printf("Goodbye!\n");
	return 0;
}
