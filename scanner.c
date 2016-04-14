#include "scanner.h"

// take the character frequencies from a file
// and produce a priority queue
q* scan (FILE* fp) {
  int counts[256], i;

  // characters can range from 0x00 to 0xff
  for (i = 0; i < 256; i++) counts[i] = 0;
  while (!feof(fp)) {
    int c = fgetc(fp);
    if (c >= 0) counts[c]++;
  }
  q* header = q_create();
  for (i = 0; i < 256; i++) {
    if (counts[i] <= 0) continue;
    tree* t = calloc(1, sizeof(tree));
    t->value = i;
    q_insert(header, counts[i], t); // insert each character and its count
                                    // as a leaf for the upcoming tree
  }
  return header;
}
