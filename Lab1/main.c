#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "ru");
	char f[1000000];
	int bytes = 0, words=0, lines=0, i=1;
	FILE* file = fopen(argv[2],"r");
	if (!file) {
		fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], argv[2]);
	}
	if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--bytes") == 0)
	{
		while (fscanf(file, "%c", f) != EOF)
			bytes++; 
		printf("%d", bytes);
	}
	else if (strncmp(argv[1], "-w") == 0 || strncmp(argv[1], "--words") == 0)
		{
			while (fscanf(file, "%s", f) != EOF)
				words++;
			printf("%d", words);
		}
	return 0;
}