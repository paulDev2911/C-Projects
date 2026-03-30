#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void list_dir(char *path){
  DIR *dir = opendir(path);
  if(dir==NULL){
    printf("error: cannot open %s\n", path);
    return;
  }
  struct dirent *entry;
  while((entry=readdir(dir))!=NULL){
    if(strcmp(entry->d_name, ".")==0)continue;
    if(strcmp(entry->d_name, "..")==0)continue;
    printf("%s\n",entry->d_name);
  }
  closedir(dir);
}

int main(int argc, char *argv[]){
  if (argc<2){
    unveil(".","r");
    unveil(NULL,NULL);
    pledge("stdio rpath",NULL);
    list_dir(".");
    return 0;
  }
  for(int i=1; i<argc;i++){
    unveil(argv[i], "r");
  }
  unveil(NULL,NULL);
  pledge("stdio rpath", NULL);
  for (int i=1;i<argc;i++){
    list_dir(argv[i]);
  }
  return 0;
}

