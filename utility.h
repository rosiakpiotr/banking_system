#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>

// Clear input buffer for next scanf call
void clrInBufScanf();

void validatedInput(const char *prompt, size_t len, char *buff, int (*validator)(const char *));

#endif