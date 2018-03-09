#include "Interface.h"

void showMenu(int number) {
	printf("______________MINSK AIRLINES______________\n              FLIGHT no. %d\n\n\n", number);
	printf("\n****************\nMenu:\na- amount of empty seats\nb - list of empty seats\nc - list of reserved seats(alphabetic order)");
	printf("\nd - book seat\nf - cancel reservation\ne - exit\n****************\n\n");
}

int confirmReservation() {
	int confirm = 0;
	printf("\n\nConfirm your reservation?\n1 - yes\n2 - no\n");
	scanf("%d", &confirm);
	return confirm;
}