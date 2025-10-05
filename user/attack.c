#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"
#include "user/user.h"

bool
is_printable (char c)
{
  return (c >= 48 && c <= 57)    /* 0-9 */
      || (c >= 65 && c <= 90)   /* A-Z */
      || (c >= 97 && c <= 122); /* a-z */
}

int
main(int argc, char *argv[])
{
  int incr = 4096*1024;

  char* old_addr = sbrk (incr);
  if (! old_addr) {
    fprintf (2, "error: sbrk()\n");
    exit (1);
  }
  char* new_addr = old_addr + incr;

  //printf ("sbrk (%d)\n", incr);

  char* start = old_addr;
  char* end   = new_addr;
  for (char* c = start; c < end; c++) {
    if (! is_printable (*c)) continue;

    char *str_start = c;

    while (c < end && is_printable (*c)) {
      c++;
    }

    int len = c - str_start;
    if (c < end && len >= 4 && *c == '\0') {
      printf ("%s\n", str_start);
    }

    c--;
  }

  //printf ("Did not find data.\n");
  exit (0);
}
