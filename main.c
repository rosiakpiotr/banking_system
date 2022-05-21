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
			char accountNumber[20 + 1];
			char name[20 + 1];
			char surname[20 + 1];
			char address[25 + 1];
			char PESEL[11 + 1];
			printf("New account creator:\n");
			printf("Please fill customer data below.\n");
			do
			{
				printf("Name:");
				free(line);
				line = NULL;
			} while ((line = readline()) != NULL && !validateNameSurname(line));
			memcpy(name, line, 20 + 1);
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
