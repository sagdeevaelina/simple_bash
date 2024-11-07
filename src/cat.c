#include <unistd.h>//тут сам опен и прочие
#include <stdio.h>//тут товарищ принтф
#include <fcntl.h>//тут флаги для опена
#include <stdbool.h>
#include <string.h>

typedef struct {	
	bool number_all;
	bool show_endl;
	bool number_empty;
	bool squeeze;
	bool show_tabs;
} CatInfo;


void CatNoArgs(int fd) {
	char buf[4096];
	int bytes_read;
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
		if (srtcmp(argv,"number-nonblank") == 0) {
			info->number_empty = true;
		} else if (srtcmp(argv,"number") == 0) {
			info->number_all = true;
		} else if (srtcmp(argv,"squeeze-blank") == 0) {
			info->squeeze = true;
		} else {
			dprintf(STDERR_FILENO, "%s: %s '%s'\n", name, "invalid option --",argv);
		}
		return 1;
	}
	for (char *it = argv; *it; *it++) {
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
				dprintf(STDERR_FILENO, "%s: %s '%s'\n", name, "invalid option --",argv);
				return false;
		}
	}
}

bool CatArgs(int argc, char *argv[]) {
	//(void)argc; //зануляем ибо не используется
	CatInfo info = {0,0,0,0,0};
	for (int i = 1; i < argc; i++) {
		if(*argv[i] == '-') {
			return CarParseArg(&info, argv[i], argv[0]);
		}
	}
	//CatNoArgs(open(argv[1], O_RDONLY));
}

int main(int argc, char **argv) {
	(void)argv;
	if (argc == 1) 
		CatNoArgs(STDIN_FILENO);
	else
		// for(int i = 1; i < argc; i++)
		// 	{		printf("%s\n", *(argv+i)); //argv[i]
		// 	}
		if	(!CatArgs(argc, argv))
			return EXIT_FAILURE;
	return 0;
}
