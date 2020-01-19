#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int fileChecker(char *source, char copy[]);

double plagiarism(char *sourcefile, char *copyfile) {

	FILE *fp1; //creates file pointer for 1st file
	FILE *fp2;//creates file pointer for 2nd file

	fp1 = fopen(sourcefile, "r"); //gets the first agrument and opens the file it represents in read mode
	fp2 = fopen(copyfile, "r"); //gets the second agrument and opens the file it represents in read mode
	
	if (NULL == fp1)
    	{
         	perror("opening source file");
         	return (-1);
    	}
	if (NULL == fp2)
    	{
         	perror("opening target file");
         	return (-1);
    	}	
	
	double degree, lines = 1, same = 0;
	char *buffer;
	long size1, size2;
	int position, read;
	
	fseek(fp1, 0L, SEEK_END);
	size1 = ftell( fp1 );
	rewind( fp1 );
	
	fseek(fp2, 0, SEEK_END);
	size2 = ftell(fp2);
	rewind(fp2);

	buffer = calloc( 1, size1+1 );	
	if( !buffer ) {
		fclose(fp1);
		fputs("memory alloc fails", stderr);
		exit(1);
	}
	if( 1 != fread( buffer, size1, 1, fp1) ) {
		fclose(fp1);
		free(buffer);
		fputs("entire read fails", stderr);
		exit(1);
	}
	

	char copy[size2+1];
	
	while(EOF != fscanf(fp2, "%100[^\n]\n", copy))
	{
		position = fileChecker(buffer, copy);

		if(position != -1) {
			//printf("Found at location: %d\n", position + 1);
			same++;
		}
		lines++;
	}

	degree = same/lines;
	//printf("Sameness is %.0f, number of lines is %.0f and similarity score is: %.1f\n", same, lines, degree);

	fclose(fp1); //closes the 1st file
	fclose(fp2); //closes the 2nd file
	free(buffer);
	return degree;
}

int fileChecker(char *source, char copy[]) {
	int c, d, e, file_length, copy_length, position = -1;
	
	file_length = strlen(source);
	copy_length = strlen(copy);

	if (copy_length > file_length) {
		return -1;
	}

	for (c = 0; c <= file_length - copy_length; c++) {
		position = e = c;

		for (d = 0; d < copy_length; d++) {
			if (copy[d] == source[e]) {
				e++;
			} else {
				break;	
			}
		}
		if (d == copy_length) {
			return position;	
		}
	}
	return -1;
}
