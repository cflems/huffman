#include "scanner.h"

q* scan (FILE* fp) {
  int counts[256], i;
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
    q_insert(header, counts[i], t);
  }
  return header;
}
