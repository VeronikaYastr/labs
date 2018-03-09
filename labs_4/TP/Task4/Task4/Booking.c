#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include "Interface.h"
#include "WorkWithFiles.h"
#include "WorkWithSeats.h"


struct Seat seats[NUMSEATS];



int main() {
	char* filenames[] = { "101.txt", "102.txt", "201.txt", "202.txt" };
	int flight = 0;
	bool allFree = true;

	printf("Enter number of flight : ");
	scanf("%d", &flight);
	int num = chooseNumFlight(flight);

	char filename[100];
	strcpy(filename, filenames[num]);

	FILE* file = fopen(filename, "r");
	int emptySeats = NUMSEATS;

	if (file == NULL)
	{
		file = fopen(filename, "w");
		for (int i = 0; i < NUMSEATS; i++)
		{
			seats[i].id = i + 1;
			seats[i].isFree = true;
			strcpy(seats[i].name, "nothing");
		}
		writeData(filename, seats);
	}
	else
		readData(filename, seats);

	fclose(file);

	char option;
	do
	{
		if (amountEmpty(seats) == NUMSEATS)
			allFree = true;
		else
			allFree = false;

		showMenu(flight);
		printf("Enter option : ");
		scanf("%c", &option);
		switch (option)
		{
		case 'a': {
			printf("Amount of empty seats : %d\n\n", amountEmpty(seats));
			break;
		}
		case 'b': {
			listOfEmpty(allFree, seats);
			printf("\n\n");
			break;
		}
		case 'c':
		{
			listOfReserved(allFree, seats);

			printf("\n\n");
			break;
		}
		case 'd': {
			char j = 0;
			printf("Enter the number of seat(or 'o' to break) : ");
			scanf("%c", &j);
			if (j != 'o')
				bookSeat(j, seats);
			else
				break;
			break;

		}
		case 'f': {
			int k;
			printf("Enter the number of seat : ");
			scanf("%d", &k);
			cancelReservation(k, seats);
			break;
		}
		case 'e': {
			break;
		}
		}
		
	} while (option != 'e');


	file = fopen(filename, "wt");
	writeData(filename, seats);
	fclose(file);
	system("pause");
	return 0;
}