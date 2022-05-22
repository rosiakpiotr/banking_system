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
	while (option != 7)
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
			SCustomer newCustomer;
			getNewCustomerData(&newCustomer);
			sprintf(newCustomer.accountNumber, "%lu", hash(newCustomer.PESEL));
			int result = saveNewCustomer(&newCustomer);
			if (result == 1)
			{
				printf("New customer added.\n");
			}
			else if (result == CUSTOMER_ALREADY_EXISTS)
			{
				printf("Customer already exists.\n");
			}
		}
		break;

		case 2:
		{
			listAll();
		}
		break;

		case 7:
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
