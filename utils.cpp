#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include "structures.h"
#include "utils.h"

// Load a script file.
int load_script (char * name) {
  FILE * fpscript;
  char * input = (char *) malloc(sizeof(char));
  char * inputr = (char *) malloc(sizeof(char));
  if (!(fpscript = fopen(name, "r"))) {
    printf("\nError: Unable to open file. Does it exist?\n");
    return -1;
  }
  while (!(inputr = fgets(input, 64, fpscript))) {
    parse_input(input);
  }
  if (feof(fpscript)) {
    printf("Finished reading script file \"%s\"\n", name);
    return 0;
  }
  if (ferror(fpscript)) {
    printf("\nError: Read error on script file \"%s\"\n", name);
    return -2;
  }
  return 1; // Huh?
}

// Add point.
// Add boundary.
// Add tree.
// Query range.

// Display help.
void display_help () {
  printf("Enter a command. Available commands are as follows.\n");
  printf("  load - load a command script\n");
  printf("  point - add a point\n");
  printf("  boundary - add a boundary\n");
  printf("  tree - add a tree\n");
  printf("  query - query a range\n");
  printf("  quit - quit the application\n");
  printf("  help - display help\n");
  printf("Enter \"help\" followed by a specific command for detailed information.\n");
}

// Parse input.
int parse_input (char * input) {    
  char * cmd = (char *) malloc(sizeof(char));
  char * arg1 = (char *) malloc(sizeof(char));

  sscanf(input, "%s%s", cmd, arg1);
  printf("cmd: %s\n", cmd);
  printf("arg1: %s\n", arg1);

  if (!strcmp(cmd, "load")) {
    load_script(arg1);
  } else if (!strcmp(cmd, "point")) {
    //add_point();
  } else if (!strcmp(cmd, "boundary")) {
    //add_boundary();
  } else if (!strcmp(cmd, "tree")) {
    //add_tree();
  } else if (!strcmp(cmd, "query")) {
    //query_range();
  } else if (!strcmp(cmd, "quit")) {
    printf("Goodbye!\n");
    exit(EXIT_SUCCESS);
  } else if (!strcmp(cmd, "help")) {
    display_help();
  } else {
    printf("\nUnknown command, please try again. \"help\" displays more information.\n");
    //continue;
  }
}
