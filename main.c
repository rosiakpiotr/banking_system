#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "types.h"
#include "utility.h"

int main()
{
	int result;
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

		result = scanf("%d", &option);
		if (result == EOF)
			break;
		else if (result != 1)
		{
			printf("Invaild input.\n");
			clrInBufScanf();
			continue;
		}

		switch (option)
		{
		case 1:
		{
			char accountNumber[20 + 1];
			char name[20 + 1];
			char surname[20 + 1];
			char address[25 + 1];
			char PESEL[11 + 1];
			printf("New account creator:\n");
			printf("Please fill customer data below.\n");
			// do
			// {
			// 	printf("Name:");
			// 	result = scanf("%20s", name);
			// 	if (!result)
			// 		clrInBufScanf();
			// } while (!validateNameSurname(name));
			validatedInput("Name", 20, name, validateNameSurname);
		}
		break;

		default:
			break;
		}

		printf("\n\n\n");
	}
	printf("Goodbye!\n");
	return 0;
}
