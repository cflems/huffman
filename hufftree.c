#include "hufftree.h"

void encode (FILE* in, FILE* out) {
  q* queue = scan(in);
  rewind(in);
  if (queue == 0) return;
  print_q(out, queue);
  tree* htree = build_tree(queue);
  free(queue);
  int depth = tree_depth(htree);
  int blen = (depth>>3) + ((depth&0x7) > 0);
  char buff[blen], writing = 0;
  int bits = 0;
  while (!feof(in)) {
    char reading = fgetc(in);
    memset(buff, 0, blen);
    int nbits = find(htree, buff, reading), i;
    for (i = nbits-1; i >= 0; i--) {
      if (bits >= 8) {
        fprintf(out, "%c", writing);
        writing = 0;
        bits = 0;
      }
      if (((buff[i>>3])>>(7-(i&0x7)))&0x1) writing |= 1<<(7-(bits&0x7));
      bits++;
    }
  }
  if (bits < 8) fprintf(out, "%c", writing); // not done writing
  fprintf(out, "%c", (bits-1)%9);
  release_tree(htree);
  fclose(in);
  fclose(out);
}

int find (tree* haystack, char* buff, char needle) {
  if (haystack == 0) return -1;
  if (haystack->left == 0 && haystack->right == 0) {
    if (haystack->value != needle) return -1;
    return 0;
  }
  int fa = find(haystack->left, buff, needle),
      fb = find(haystack->right, buff, needle);
  if (fa >= 0) {
    return 1+fa;
  } else if (fb >= 0) {
    buff[fb>>3] |= 0x1 << (7-(fb&0x7));
    return 1+fb;
  } else return -1;
}

void print_q (FILE* out, q* queue) {
  if (queue == 0) { fprintf(out, "%c%c%c%c", 0, 0, 0, 0); return; }
  int len = htonl(queue->length);
  fprintf(out, "%c%c%c%c", (len>>24)&0xff, (len>>16)&0xff, (len>>8)&0xff, len&0xff);
  q_node* head = queue->head;
  while (head != 0) {
    int key = htonl(head->key);
    fprintf(out, "%c%c%c%c%c", head->value->value, (key >> 24)&0xff, (key >> 16)&0xff, (key >> 8)&0xff, key&0xff);
    head = head->next;
  }
}

int int_lit (FILE* in) {
  char buff[4];
  int i;
  for (i = 3; i >= 0; i--) buff[i] = fgetc(in);
  return ntohl(*((int*)buff));
}

void decode (FILE* in, FILE* out) {
  int i, qlen = int_lit(in);
  if (feof(in)) return;
  q* queue = q_create();
  for (i = 0; i < qlen; i++) {
    if (feof(in)) return;
    char c = fgetc(in);
    int num = int_lit(in);
    tree* t = calloc(1, sizeof(tree));
    t->value = c;
    q_insert(queue, num, t);
  }
  tree* htree = build_tree(queue);
  free(queue);
  long resume = ftell(in);
  fseek(in, 0L, SEEK_END);
  long lastbyte = ftell(in)-1L;
  int lastbits = fgetc(in)%9;
  fseek(in, resume, SEEK_SET);

  int bit = 0, c = fgetc(in);
  tree* root = htree;
  while (!feof(in)) {
    if (root == 0) {
      fprintf(stderr, "Error: Corrupt tree to decode.\n");
      exit(1);
    }
    if (root->left == 0 && root->right == 0) {
      fprintf(out, "%c", root->value);
      root = htree;
    }

    if (ftell(in) == lastbyte && bit > lastbits) return;
    if (bit >= 8) {
      if (feof(in)) return;
      c = fgetc(in);
      bit = 0;
    }
    if (!((c>>(7-bit))&0x01)) root = root->left;
    else root = root->right;
 
    bit++;
  }
  release_tree(htree);
  fclose(in);
  fclose(out);
}

void release_tree (tree* tree) {
  if (tree == 0) return;
  release_tree(tree->left);
  release_tree(tree->right);
  free(tree);
}

tree* build_tree (q* food) {
  q_node *n1, *n2;
  for (n1 = q_pull(food); n1 != 0; n1 = q_pull(food)) {
    n2 = q_pull(food);
    if (n2 == 0) {
      tree* rv = n1->value;
      free(n1);
      return rv;
    }
    tree* t = malloc(sizeof(tree));
    t->left = n1->value;
    t->right = n2->value;
    q_insert(food, n1->key+n2->key, t);
    free(n1);
    free(n2);
  }
  return 0;
}
