#pragma once
#define MAXLEN 100
#define bool char
#define true 1
#define false 0
#define NUMSEATS 12

struct Seat {
	int id;
	char isFree;
	char name[MAXLEN];
};

int amountEmpty(struct Seat* seats);
int chooseNumFlight(int flight);
void alphabeticalSort(struct Seat* seats);
void listOfEmpty(bool allFree, struct Seat* seats);
void listOfReserved(bool allFree, struct Seat* seats);
void bookSeat(int j, struct Seat* seats);
void cancelReservation(int j, struct Seat* seats);
