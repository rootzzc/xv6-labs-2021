#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void my_strcat(char *des, const char *src){
  int i = 0;
  int j = 0;
  while(des[i] != '\0')
    i++;
  while(src[j] != '\0')
    des[i++] = src[j++];
  des[i] = '\0';
}

void logger(char *path){
  printf("%s\n", path);
}

void dir_dfs(char *path, char *target){
  int fd;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }
  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }
  if(st.type != T_DIR){
    close(fd);
    return;
  }

  struct dirent de;
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;

    char *buf = malloc(512);
    strcpy(buf, path);
    my_strcat(buf, "/");
    my_strcat(buf, de.name);

    // logger(buf);
    logger(de.name);

    int cfd;
    struct stat cst;
    if ((cfd = open(buf, 0)) < 0) {
      fprintf(2, "find: cannot open %s\n", path);
      return;
    }
    if (fstat(cfd, &cst) < 0) {
      fprintf(2, "find: cannot stat %s\n", path);
      return;
    }

    if(cst.type == T_DIR){
      dir_dfs(buf, target);
    }else if(cst.type == T_FILE && strcmp(de.name, target) == 0){
      // logger(buf);
    }

    close(cfd);
    free(buf);
  }
  close(fd);
}

int main(int argc, char *argv[]){
  if(argc < 3){
    fprintf(2, "find: usage find <dir_path> <file_name>\n");
    exit(0);
  }
  char *dir_path = argv[1];
  char *file_name = argv[2];

  dir_dfs(dir_path, file_name);

  exit(0);
 }