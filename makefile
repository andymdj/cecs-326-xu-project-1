CC=gcc

all: filecopy

filecopy: filecopy.c
	$(CC) filecopy.c -o filecopy

clean:
	rm filecopy