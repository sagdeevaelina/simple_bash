#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void CatNoArgs(int argc) {
	char buf[4096];
	int fd = argc; // =1
	int bytes_read;

	bytes_read = read(fd, buf, 4096);
	while(bytes_read <= 0) {
		printf("%.*s", bytes_read, buf); //?
		bytes_read = read(fd, buf, 4096);
	}
}

void CatArgs(int argc, char *argv[]) {
	(void)argc;
	CatNoArgs(open(argv[1], O_RDONLY));
}
//1 аргумент - сама команда, следующие - параметры
int main(int argc, char **argv) {
	(void)argv;
	if (argc == 1) 
		CatNoArgs(STDIN_FILENO);
	else
		CatArgs(argc, argv);
	return 0;
}
