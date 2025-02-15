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
      fprintf(stderr, "Error: Please provide one input file name and one output file name.\n");
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
      fprintf(stderr, "Error: Could not open file %s.\n", destName);
      return 0;
   }

   // Create array for pipe file descriptors.
   int fd[2];

   // Create pipe and store file descriptors in fd.
   // fd[0] - read
   // fd[1] - write
   if(pipe(fd) == -1) {
      fprintf(stderr, "Error: Pipe not created.\n");
   };

   // Fork the main process.
   int id = fork();

   // Code use for reading and writing taken and modified from
   // https://www.gnu.org/software/libc/manual/html_node/Creating-a-Pipe.html
   if(id != 0) {
      // If id is not 0, we're in the parent process.
      // Close the read end of the pipe immediately.
      close(fd[0]);

      // Read from source file and write to pipe.
      int c;
      FILE* pipeIn = fdopen(fd[1], "w");
      while((c = fgetc(sourcePtr)) != EOF) {
         fputc(c, pipeIn);
      }

      // Close the pipe stream and file descriptor.
      fclose(pipeIn);
      close(fd[1]);
   }
   else {
      // Otherwise we're in the child process.
      // Close the write end of the pipe immediately.
      close(fd[1]);

      // Read from pipe and write to destination file.
      int c;
      FILE* pipeOut = fdopen(fd[0], "r");
      while((c = fgetc(pipeOut)) != EOF) {
         fputc(c, destPtr);
      }

      // Close the pipe stream and file descriptor.
      fclose(pipeOut);
      close(fd[1]);
      printf("File successfully copied from %s to %s.\n", sourceName, destName);
   }

   // Close source and destination files.
   fclose(sourcePtr);
   fclose(destPtr);
   return 0;
}
