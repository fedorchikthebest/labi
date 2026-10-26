#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFER_SIZE 4096

void insert(char *buf, int pos, char goidic) {
  buf += pos;
  char a;
  for (int i = 0; i < 4096 - pos; i++) {
    a = buf[i];
    buf[i] = goidic;
	goidic = a;    
  }
}

void insert_chars(char *buf) {
		int mpos1 = 0, mpos2 = 0, pos1 = 0, pos2 = 0;
  for (int i = 1; i < 2048; i++) {
    if (isdigit(buf[i]) && isdigit(buf[i - 1]) && buf[i] > buf[i - 1]) {
      if (i == 1 || (isdigit(buf[i - 2]) && buf[i - 2] > buf[i - 1]) || !isdigit(buf[i - 2]))
        pos1 = i - 1;      
      pos2 = i;
    } else if (pos2 - pos1 > mpos2 - mpos1) {
      mpos1 = pos1;
      mpos2 = pos2;
	}
  }
  insert(buf, mpos1, '$');
  insert(buf, mpos2 + 2, '#');
}  

int main() {
  char zov[4096];
  fgets(zov, 2048, stdin);
  insert_chars(zov);
  printf("%s", zov);

  memset(zov, 0, BUFER_SIZE);

  int i = 0;
  int c = getchar();
  while (i < 2048 && c != EOF) {
    if (c == '\\') {
      c = getchar();
      if (c == '0')
        break;
      else {
        zov[i++] = '\\';        
	  }        
    }
    zov[i++] = c;
	c = getchar();
  }

  insert_chars(zov);
  printf("%s", zov);

  memset(zov, 0, BUFER_SIZE);

  FILE *fp = fopen("ZOV.txt", "r");
  i = 0;
  c = getc(fp);
  while (i < 2048 && c != EOF) {
    zov[i++] = c;
	c = getc(fp);
  }

  insert_chars(zov);
  fclose(fp);

  fp = fopen("GOIDA.txt", "w");
  fprintf(fp, "%s", zov);
  fclose(fp);
}  
