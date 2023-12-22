#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define NULL 0
#define LINE_BUF_SIZE 512

char **parase_arg(int argc, char **argv, char *line_buf){
   char **total_arg = malloc(512);
   int p = 0;

   for(p = 0; p < argc; p++){
     total_arg[p] = malloc(512);
     strcpy(total_arg[p], argv[p]);
   }

   char *pre = line_buf;
   while(*pre == ' ') pre++;
   char *cur = pre;

   while (*cur != '\0') {
     if (*cur == ' ') {
       *cur = '\0';
       total_arg[p] = malloc(cur - pre + 1);
       strcpy(total_arg[p++], pre);

       cur++;
       while(*cur == ' ') cur++;
       pre = cur;
     } else {
       cur++;
     }
   }

   if (cur != pre) {
     total_arg[p] = malloc(cur - pre + 1);
     strcpy(total_arg[p++], pre);
   }

   total_arg[p] = NULL;
   return total_arg;
}

int
main(int argc, char *argv[])
{
    int fork_n = 0;
    char *cmd = argv[1];
    int cmd_argc = argc - 1;
    char **cmd_argv = argv+1;

    char line_buf[512];
    memset(line_buf, 0, sizeof(line_buf));
    int p = 0;
    char b;
    while(read(0, &b, 1) > 0){
      if (b == '\n') {
        line_buf[p] = 0;
        p = 0;

        char **total_argv = parase_arg(cmd_argc, cmd_argv, line_buf);

        fork_n++;
        if (fork() == 0){
          exec(cmd, total_argv);
        }
      } else {
        line_buf[p++] = b;
      }
    }

    if(p != 0){
        line_buf[p] = 0;
        char **total_argv = parase_arg(cmd_argc, cmd_argv, line_buf);
        
        fork_n++;
        if (fork() == 0) {
          exec(cmd, total_argv);
        }
    }

    for(int i = 0; i < fork_n; i++){
        wait(0);
    }

    exit(0);
}

