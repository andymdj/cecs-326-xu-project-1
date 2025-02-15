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

   // Store the filenames in string variables from args.
   char* sourceName = argv[1];
   char* destName = argv[2];

   // Open the source file in read mode.
   FILE* sourcePtr = fopen(sourceName, "r");
   if(sourcePtr == NULL) {
      fprintf(stderr, "Error: No such file %s.\n", sourceName);
      return 0;
   }

   // Open the destination file in write mode.
   FILE* destPtr = fopen(destName, "w");
   if(destPtr == NULL) {
      fprintf(stderr, "Error: No such file %s.\n", destName);
      return 0;
   }

   // Create array for pipe file descriptors.
   int fd[2];

   // Create pipe and store file descriptors in fd.
   if(pipe(fd) == -1) {
      fprintf(stderr, "Error: Pipe not created.\n");
   };
}
