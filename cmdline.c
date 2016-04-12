#include "cmdline.h"

int main (int argc, char** argv) {
  FILE *in = stdin, *out = stdout;
  flag expifn = 0, expofn = 0, inf = 0, ouf = 0, enc = 0, dec = 0;
  int i, errlvl = 0;
  for (i = 1; i < argc; i++) {
    if (expifn) {
      in = fopen(argv[i], "r");
      inf = 1;
      expifn = 0;
      continue;
    }
    if (expofn) {
      out = fopen(argv[i], "w");
      ouf = 1;
      expofn = 0;
      continue;
    }
    if (strncmp(argv[i], "-e", 2) == 0) {
      enc = 1;
      continue;
    }
    if (strncmp(argv[i], "-d", 2) == 0) {
      dec = 1;
      continue;
    }
    if (strncmp(argv[i], "-i", 2) == 0) {
      expifn = 1;
      continue;
    }
    if (strncmp(argv[i], "-o", 2) == 0) {
      expofn = 1;
      continue;
    }
  }
  if (expifn || expofn) eprint(&errlvl, "Error: No file name specified.\n");
  if (!enc && !dec) eprint(&errlvl, "Error: You've chosen to neither encode nor decode.\n");

  if (errlvl > 0) exit(errlvl);

  if (enc) encode(in, out);
  else if (dec) decode(in, out);

  exit(0);
}

void eprint (int* errlvl, char* msg) {
  fprintf(stderr, "%s", msg);
  (*errlvl)++;
}
