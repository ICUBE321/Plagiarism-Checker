#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

double plagiarism(char *sourcefile, char *copyfile);

int main() {

	int fdt;//target file descriptor
	int flags;//flag values holder
	mode_t permissions;//permissions holder
	flags = O_CREAT | O_WRONLY| O_TRUNC;//initialize flags
	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	fdt = open("csv.txt", flags, permissions);

	
	if (close(fdt) == -1){//close target file and catch error on closing
		printf("tester: %s\n",strerror(errno)); 
    		perror("tester: ");
		exit(EXIT_FAILURE);
	}

	FILE *fd;
	double placer;
	char buf[12];	
	
	for(int i=1; i <= 100; i++) {
		snprintf(buf, 12, "%d.txt", i);

		fd = fopen("csv.txt", "a");
		
		placer = plagiarism("a.txt", buf);
		fprintf(fd,"%.1f,", placer);
		placer = plagiarism("b.txt", buf);
		fprintf(fd,"%.1f,", placer);
		placer = plagiarism("c.txt", buf);
		fprintf(fd,"%.1f,", placer);
		placer = plagiarism("d.txt", buf);
		fprintf(fd,"%.1f,", placer);
		placer = plagiarism("e.txt", buf);
		fprintf(fd,"%.1f\n", placer);
		fclose(fd);
	}

	return 0;
}
