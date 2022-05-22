#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types.h"

char *readline();
char *rmNewline(char *line);
char *validatedInput(const char *prompt, size_t maxLen, validator valid);

// http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str);

#endif