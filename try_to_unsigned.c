#include "to_unsigned.h"

#include <stdio.h>  /* printf. */
#include <stdint.h>  /* int64_t. */

int main(int argc, char **argv) {
  (void)argc; (void)argv;

  printf("char: %d\n", (int)sizeof(TO_UNSIGNED((char)-1)));
  printf("short: %d\n", (int)sizeof(TO_UNSIGNED((short)-1)));
  printf("int: %d\n", (int)sizeof(TO_UNSIGNED((int)-1)));
  printf("unsigned: %d\n", (int)sizeof(TO_UNSIGNED((unsigned)-1)));
  printf("long: %d\n", (int)sizeof(TO_UNSIGNED((long)-1)));
  printf("int64_t: %d\n", (int)sizeof(TO_UNSIGNED(__extension__ (int64_t)-1)));
#ifdef __SIZEOF_INT128__
  printf("__int128: %d\n", (int)sizeof(TO_UNSIGNED(__extension__ (__int128)-1)));
#endif

  return 0;
}
