#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    int t = uptime();
    printf("uptime: %d\n", t);
    exit(0);
}