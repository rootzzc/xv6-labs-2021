#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void print_prime(int n){
  // char output = n + '0';
  // write(1, "prime ", 6);
  // write(1, &output, 1);
  // write(1, "\n", 1);
  printf("prime %d\n", n);
}

static void pipeblock_init(int pl[2], int pr[2]){
  pl[0] = pr[0];
  pl[1] = pr[1];  // copy parent right pipe to left pipe
  close(pl[1]);  // close left process write port 
  pipe(pr);
}

static void pipeblock_loop(int pl[2], int pr[2]){
  char buf;
  int prime = -1;

  while (read(pl[0], &buf, 1) > 0) {
    int i = buf;
    if (prime == -1) {
      prime = i;
      print_prime(i);
      continue;
    }

    if (i % prime == 0) {
      continue;
    }

    buf = i;
    write(pr[1], &buf, 1);
  }
}

static void pipeblock_loop_first(int pr[2]){
  char buf;
  int prime = -1;

  for(int i = 2; i <= 35; i++){
    buf = i;
    if (prime == -1){
      prime = i;
      print_prime(i);
      continue;
    }

    if(i % prime == 0){
      continue;
    }
    
    buf = i;
    write(pr[1], &buf, 1);
  }
}

int
main(int argv, char *argc[]){
  int pl[2];
  int pr[2];

  // p0 
  pipe(pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop_first(pr);

    close(pr[1]);  // close right process write port 
    wait(0);
    exit(0);
  }

  // p1 
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p2 
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p3 
  pipeblock_init(pl, pr); 
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p4 
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }
  
  // p5
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p6
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p7 
  pipeblock_init(pl, pr); 
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p8 
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }
  
  // p9
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p10
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p11
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p12
  pipeblock_init(pl, pr); 
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p13
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }
  
  // p14
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p15
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p16
  pipeblock_init(pl, pr); 
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p17
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }
  
  // p18
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p19
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p20
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p21
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p22
  pipeblock_init(pl, pr); 
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p23
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }
  
  // p24
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p25
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p26
  pipeblock_init(pl, pr); 
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p27
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }
  
  // p28
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p29
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p30
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p31
  pipeblock_init(pl, pr); 
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p32
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr); 

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }
  
  // p33
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p34
  pipeblock_init(pl, pr);
  if(fork() > 0){
    close(pr[0]);  // close right process read port 

    pipeblock_loop(pl, pr);

    close(pl[0]);  // close left process read port
    close(pr[1]);  // close right process write port
    wait(0);
    exit(0);
  }

  // p35
  pipeblock_init(pl, pr);
  close(pr[0]); // close right process read port

  pipeblock_loop(pl, pr);

  close(pl[0]); // close left process read port
  close(pr[1]); // close right process write port
  wait(0);
  exit(0);
}