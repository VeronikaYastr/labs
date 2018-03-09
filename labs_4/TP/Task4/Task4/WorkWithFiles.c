#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "WorkWithFiles.h"
#define MAXLEN 100
#define NUMSEATS 12

struct Seat {
	int id;
	char isFree;
	char name[MAXLEN];
};

int writeData(char* filename, struct Seat* array) {
	FILE *f = fopen(filename, "w");
	if (f == NULL)
		return 0;

	for (int i = 0; i < NUMSEATS; i++)
		fprintf(f, "%d %d %s\n", array[i].id, array[i].isFree, array[i].name);

	fclose(f);
	return 1;
}

int readData(char* filename, struct Seat* array) {
	FILE *f = fopen(filename, "rt");
	if (f == NULL)
		return 0;

	for (int i = 0; i < NUMSEATS; i++)
		fscanf(f, "%d %d %s\n", &array[i].id, &array[i].isFree, &array[i].name);

	fclose(f);
	return 1;
}