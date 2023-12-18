#include "kernel/types.h"
// #include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[]){
  int pip_p2c[2];
  int pip_c2p[2];
  int pid;
  char buf[1];

  pipe(pip_p2c);
  pipe(pip_c2p);

  // child process
  if((pid = fork()) == 0){
    // read from parent
    read(pip_p2c[0], buf, 1);
    printf("%d: received ping\n", getpid());

    // write to parent
    write(pip_c2p[1], buf, 1);
  // parent process
  }else{
    //  write to child
    write(pip_p2c[1], "b", 1);

    // read from parent
    read(pip_c2p[0], buf, 1);
    printf("%d: received pong\n", getpid());

  }

  close(pip_p2c[0]);
  close(pip_p2c[1]);
  close(pip_c2p[0]);
  close(pip_c2p[1]);

  exit(0);
}