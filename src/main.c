#include <stdlib.h>

#include "pam.h"

/*
 * Entry point to the application. Called on program start.
 */ 
int main(int argc, char *argv[]) {
  const int x = 255, y = 255;
  write_pam("images/hello_world.pam", x, y);

  return EXIT_SUCCESS;
}