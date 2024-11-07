#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void ReadNPrint(int fd);
void ParseArgs(char **argv);

int main(int argc, char **argv) {
	(void)argv;
	if(argc == 1) {
		ReadNPrint(STDIN_FILENO);
	}
	else if (argc > 1) {
		ParseArgs(argv);
	} else {
		printf("%s", "error");
	}
	return 0;
}


void ReadNPrint(int fd) {
	char buffer[4056];
	int bytes_in_buffer = read(fd, buffer, 4056);
	while (bytes_in_buffer > 0) {
		printf("%.*s", bytes_in_buffer, buffer);
		bytes_in_buffer = read(fd, buffer, 4056);
	}
}

void ParseArgs(char **argv) {
	ReadNPrint(open(argv[1], O_RDONLY));
}