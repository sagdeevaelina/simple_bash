#include <unistd.h>//тут сам опен и прочие
#include <stdio.h>//тут товарищ принтф
#include <fcntl.h>//тут флаги для опена
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct {	
	bool number_all;
	bool show_endl;
	bool number_empty;
	bool squeeze;
	bool show_tabs;
} CatInfo;


void CatNoArgs(int fd, char* name) {
	char buf[4096];
	int bytes_read;
	if(fd == -1) {
		perror(name);
		return;
	}
	bytes_read = read(fd, buf, 4096);
	while(bytes_read > 0) {
		printf("%.*s", bytes_read, buf); 
		bytes_read = read(fd, buf, 4096);
	}
}

bool CatParseArg(CatInfo *info, char *argv, char* name) {
	++argv;
	if (*argv == '-') {
		++argv;
		if (strcmp(argv,"number-nonblank") == 0) {
			info->number_empty = true;
		} else if (strcmp(argv,"number") == 0) {
			info->number_all = true;
		} else if (strcmp(argv,"squeeze-blank") == 0) {
			info->squeeze = true;
		} else {
			dprintf(STDERR_FILENO, "%s: %s%s\n", name, "invalid option2 -", argv);
		}
		return 1;
	}
	for (char *it = argv; *it; ++*it) {
		switch(*it) {
			case 'b':
				info->number_empty = true;
				break;
			case 'e':
				info->show_endl = true;
				break;
			case 'n':
				info->number_all = true;
				break;
			case 's':
				info->squeeze = true;
				break;
			case 't':
				info->show_tabs = true;
				break;
			default:
				dprintf(STDERR_FILENO, "%s: %s%s\n", name, "invalid option1 -", argv);
				return false;
		}
	}
	return true;
}

bool CatArgs(int argc, char *argv[]) {
	CatInfo info = {0,0,0,0,0};
	for (int i = 1; i < argc; i++) {
		if(*argv[i] == '-') {
			return CatParseArg(&info, argv[i], argv[0]);
		}
	}
	if (!(info.number_empty + info.number_all + info.squeeze + info.show_endl + info.show_tabs)) {
			for (int i = 1; i < argc; i++) {
				if(*argv[i] != '-') {
					CatNoArgs(open(argv[i], O_RDONLY), argv[0]);
					return false; 
				}
			}
	}
	return true;
}

int main(int argc, char **argv) {
	(void)argv;
	if (argc == 1) 
		CatNoArgs(STDIN_FILENO, argv[0]);
	else
		if	(!CatArgs(argc, argv))
			return EXIT_FAILURE;
	return 0;
}
