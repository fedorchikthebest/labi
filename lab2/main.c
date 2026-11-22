#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFER_SIZE 4096

int z1();
int z2();
int z3();

void *fedos_realloc(void *buf, int old_size, int new_size) {
  void *ans = malloc(new_size);
  if (ans == NULL) {
    perror("malloc");
    free(buf);
    exit(-1);
  }
  memcpy(ans, buf, old_size);
  free(buf);
  return ans;
}

void insert(char *buf, int pos, char goidic, int size) {
  for (int i = size; i >= pos; i--) {
    buf[i + 1] = buf[i];
  }
  buf[pos] = goidic;
}

int insert_chars(char *buf, int size) {
  int mpos1 = -1, mpos2 = -1, pos1 = 0, pos2 = 0, best = 0;
  for (int i = 1; i < size; i++) {
    if (isdigit((unsigned char)buf[i]) && isdigit((unsigned char)buf[i - 1]) &&
        buf[i] > buf[i - 1]) {
      if (i == 1 || !isdigit((unsigned char)buf[i - 2]) ||
          buf[i - 2] > buf[i - 1])
        pos1 = i - 1;
      pos2 = i;
      if (pos2 - pos1 > best) {
        best = pos2 - pos1;
        mpos1 = pos1;
        mpos2 = pos2;
      }
    }
  }
  if (mpos1 == -1)
    return size;
  insert(buf, mpos2 + 1, '#', size);
  size++;
  insert(buf, mpos1, '$', size);
  return size + 1;
}

int main() {
  switch (getchar()) {
  case '1':
    z2();
    break;
  case '2':
    z1();
    break;
  case '3':
    z3();
    break;
  }
  return 0;
}

int z1() {
  char *zov, *tmp;
  zov = calloc(1, 4);
  if (zov == NULL) {
    perror("malloc");
    exit(-1);
  }
  int i, c;

  i = 0;
  c = getc(stdin);
  while (c != '\n' && c != EOF) {
    zov[i++] = c;
    c = getc(stdin);
    tmp = zov;
    zov = realloc(zov, i + 5);
    if (zov == NULL) {
      free(tmp);
      perror("malloc");
      exit(-1);
    }
  }

  zov[i] = 0;
  insert_chars(zov, i);
  printf("%s", zov);
  free(zov);
  return 0;
}

int z2() {
  char *zov, *tmp;
  zov = malloc(5);
  if (zov == NULL) {
    perror("malloc");
    exit(-1);
  }
  int i, c;

  i = 0;
  c = getc(stdin);
  while (c != '\n' && c != EOF) {
    zov[i++] = c;
    c = getc(stdin);
    zov = fedos_realloc(zov, i + 1, i + 5);
  }

  zov[i] = 0;
  insert_chars(zov, i);
  printf("%s", zov);
  free(zov);
  return 0;
}

int z3() {
  char *zov, *tmp;
  zov = calloc(1, 5);
  if (zov == NULL) {
    perror("malloc");
    exit(-1);
  }
  int i, c;

  i = 0;
  c = getc(stdin);
  while (c != '\n' && c != EOF) {
    zov[i++] = c;
    c = getc(stdin);
    tmp = zov;
    zov = realloc(zov, i + 5);
    if (zov == NULL) {
      free(tmp);
      perror("malloc");
      exit(-1);
    }
  }

  zov[i] = 0;
  FILE *fp = fopen("qwe.txt", "w");
  if (fp == NULL) {
    perror("fopen");
    free(zov);
    exit(-1);
  }
  fprintf(fp, "%s", zov);
  free(zov);
  fclose(fp);

  fp = fopen("qwe.txt", "r");
  if (fp == NULL) {
    perror("fopen");
    exit(-1);
  }

  zov = calloc(1, 5);
  if (zov == NULL) {
    perror("malloc");
    fclose(fp);
    exit(-1);
  }
  i = 0;
  c = getc(fp);
  while (c != EOF) {
    zov[i++] = c;
    c = getc(fp);
    tmp = zov;
    zov = realloc(zov, i + 5);
    if (zov == NULL) {
      free(tmp);
      perror("malloc");
      fclose(fp);
      exit(-1);
    }
  }

  zov[i] = 0;
  insert_chars(zov, i);
  printf("%s", zov);
  fclose(fp);
  free(zov);
  return 0;
}
