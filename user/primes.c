#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void logger(int n){
  printf("prime %d\n", n);
}

int
main(int argv, char *argc[]){
  // every process own two pipe, one for read and one for write
  // buf stores primer number in char format
  // prime stores every process first primer number
  int pl[2];
  int pr[2];
  char buf;
  int prime = -1;

 
  pipe(pr);  // create right pipe
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    for(int i = 2; i <= 40; i++){
      if(prime == -1){
        prime = i;
        logger(prime);
      }else if(i % prime != 0){
        buf = i;
        write(pr[1], &buf, 1); 
      }
    }

    close(pr[1]);  // close right process write port 
    wait(0);
    exit(0);
  }

  // loop quit when read nothing from left process
  while (1) {
    pl[0] = pr[0];
    pl[1] = pr[1];  // copy right process's right pipe to left pipe
    close(pl[1]);  // close left pipe write port

    if(read(pl[0], &buf, 1) == 0){
      close(pl[0]);  // close left pipe read port
      exit(0);
    }

    pipe(pr);
    if (fork() > 0) {
      close(pr[0]);  // close right pipe read port
      do {
        if (prime == -1) {
          prime = buf;
          logger(prime);
        } else if ((int)buf % prime != 0) {
          write(pr[1], &buf, 1);
        }
      } while (read(pl[0], &buf, 1)); 

      close(pl[0]); // close left pipe read port
      close(pr[1]); // close right pipe write port
      wait(0);
      exit(0);
    }
  }
  exit(0);
}