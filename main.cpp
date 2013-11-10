#include "structures.h"
#include "utils.h"
#include <stdio.h>

int main () {
  char *input = (char *)malloc(sizeof(char));

	// intro text
  printf("Welcome to the quadtree implementation.\nEnter a command after the prompt.\n");
  printf("The \"help\" command will display the help dialogue.\n\n");

	// main run loop
  while(1) {
    printf("?> ");
    input = fgets(input, 32, stdin);
    printf("%s\n", input);

		if(input == "help") {
			display_help();
		}
  }

  return 0;
}
