#define _CRT_SECURE_NO_WARNINGS
#include "WorkWithSeats.h"

int amountEmpty(struct Seat* seats) {
	int emptySeats = NUMSEATS;
	for (int i = 0; i < NUMSEATS; i++)
	{
		if (seats[i].isFree == 0)
			emptySeats--;
	}
	return emptySeats;
}

void alphabeticalSort(struct Seat* seats) {
	struct Seat tmp;
	for (int i = 0; i < NUMSEATS; i++)
	{
		if (!seats[i].isFree) {
			for (int j = i + 1; j < NUMSEATS; j++)
				if ((strcmp(seats[i].name, seats[j].name) > 0) && (!seats[j].isFree))
				{
					tmp = seats[i];
					seats[i] = seats[j];
					seats[j] = tmp;
				}
		}
	}
}

int chooseNumFlight(int flight) {
	switch (flight) {
	case 101: return 0;
	case 102: return 1;
	case 201: return 2;
	case 202: return 3;
	default: {
		printf("Invalid number!");
		return -1;
	}
	}
}

void listOfEmpty(bool allFree, struct Seat* seats) {
	if (!allFree)
		for (int i = 0; i < NUMSEATS; i++)
		{
			if (seats[i].isFree == 1)
			{
				printf("ID : %d \n", seats[i].id);
				allFree = false;
			}
		}
	else
		printf("\nAll seats are free");
}

void listOfReserved(bool allFree, struct Seat* seats) {
	printf("List of reserved seats(alphabetical order) : \n");

	if (!allFree)
	{
		alphabeticalSort(seats);
		for (int i = 0; i < NUMSEATS; i++)
			if (!seats[i].isFree)
				printf("ID : %d   Name : %s   Status : %d\n", seats[i].id, seats[i].name, seats[i].isFree);
	}
	else
		printf("\nAll seats are free");
}

void bookSeat(int j, struct Seat* seats) {
	for (int i = 0; i < NUMSEATS; i++)
		if (seats[i - 1].id == j)
		{
			if (seats[i - 1].isFree)
			{
				char name[101];
				printf("Enter your name : ");
				scanf("%s", &seats[i - 1].name);
				if (confirmReservation() == 1)
				{
					seats[i - 1].isFree = false;
					printf("Your seat is booked.\n\n");
				}
				else
					printf("Reservation cancelled.\n");
			}
			else
				printf("Forbidden : this seat is already booked or invalid number of seat!\n\n");
			break;

		}
}

void cancelReservation(int j, struct Seat* seats) {
	for (int i = 0; i < NUMSEATS; i++)
	{
		if (seats[i - 1].id == j)
		{
			if (seats[i - 1].isFree)
				printf("Forbidden : this seat is alredy free.\n\n");
			else
			{
				seats[i - 1].isFree = true;
				strcpy(seats[i - 1].name, "nothing");
				printf("Reservation is cancelled.\n\n");
			}
		}
	}
}