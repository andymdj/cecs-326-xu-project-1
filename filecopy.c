/*
 * filecopy.c
 *
 * This program copies files using a pipe.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) {
   // Check for correct number of arguments.
   if(argc != 3) {
      printf("Error: Please provide one input filename and one output file name.\n");
      return 0;
   }

   char* sourceName = argv[1];
   char* destName = argv[2];
}
