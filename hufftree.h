#ifndef __HUFF_H
#define __HUFF_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "queue.h"
#include "scanner.h"

void encode (FILE*, FILE*);
int find (tree*, char*, char);
void print_q (FILE*, q*);
int int_lit (FILE*);
void decode (FILE*, FILE*);
void release_tree (tree*);
tree* build_tree (q*);

#endif
