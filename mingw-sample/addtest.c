/* addtest_basic.c

   Demonstrates using the function imported from the DLL, the inelegant way.
*/

#include <stdlib.h>
#include <stdio.h>
#include "add.h"

int main(int argc, char** argv)
{
  printf("%d\n", Add(6, 23));

  return EXIT_SUCCESS;
}
