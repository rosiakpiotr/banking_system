#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "types.h"
#include "menu.h"

int main()
{
	int option = 0;
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

		option = getInputNumInRangeInt("Option", 1, 7);
		switch (option)
		{
		case 1:
			menuAddNewCustomer();
			break;

		case 2:
			listAll();
			break;

		case 3:
			menuSearch();
			break;

		default:
			break;
		}

		printf("\n\n\n");
	}

	printf("Goodbye!\n");
	return 0;
}
