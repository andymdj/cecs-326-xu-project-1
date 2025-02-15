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
      fprintf(stderr, "Error: Please provide one input filename and one output file name.\n");
      return 0;
   }

   char* sourceName = argv[1];
   char* destName = argv[2];

   FILE* sourcePtr = fopen(sourceName, "r");
   if(sourcePtr == NULL) {
      fprintf(stderr, "Error: No such file %s.\n", sourceName);
      return 0;
   }

   FILE* destPtr = fopen(destName, "w");
   if(destPtr == NULL) {
      fprintf(stderr, "Error: No such file %s.\n", destName);
      return 0;
   }
}
