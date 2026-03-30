#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int c;
  FILE *fp;
  for (int i=1; i<argc; i++) {
    unveil(argv[i],"r");
  }
  pledge("stdio rpath", NULL);
  if(argc < 2) {
    while((c=fgetc(stdin))!=EOF){
      fputc(c,stdout);
    }
    return 0;
  }
  for (int i=1; i<argc; i++){
    fp = fopen(argv[i], "r");
    if (fp == NULL){
      printf("error: cannot open %s\n",argv[i]);
      continue;
    }
    while ((c=fgetc(fp))!=EOF) {
      fputc(c,stdout);
    }
    fclose(fp);
  }
  return 0;
}
