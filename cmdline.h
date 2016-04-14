#ifndef __CMDLINE_H
#define __CMDLINE_H 1
#include <stdio.h>
#include <stdlib.h>
#include "hufftree.h"
typedef int flag; // flags are booleans
#define true 1
#define false 0

int main (int, char**);
void eprint (int*, char*);
#endif
