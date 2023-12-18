#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{
  int t;

  if(argc < 2){
    fprintf(2, "Usage: sleep <times>\n");
    exit(1);
  }

  t = atoi(argv[1]);

  if(t < 0){
    fprintf(2, "sleep time should greater than 0\n");
    exit(1);
  }

  sleep(t);

  exit(0);
}