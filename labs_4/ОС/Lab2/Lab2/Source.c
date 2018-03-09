#include <iostream>
#include <windows.h>

using namespace std;


struct MatrixRow
{
	int* row;
	int num;
	int* vector;
	DWORD id;
	int res;
	int n;


	void init(int size) {
		n = size;
		row = new int[size];
		vector = new int[size];
		res = 0;

	}
};


DWORD WINAPI mult(LPVOID lp)
{
	struct MatrixRow* mr = (struct MatrixRow*)lp;
	for (int i = 0; i < mr->n; i++)
	{
		mr->res += mr->row[i] * mr->vector[i];
		Sleep(500);
	}
	printf("Multiplication %d  string on vector is %d\n", mr->num, mr->res);
	return 0;
}

int main()
{
	int n;
	cout << "Enter the size of matrix : " << endl;
	cin >> n;
	HANDLE* hThread = new HANDLE[n];
	MatrixRow *mr = new MatrixRow[n];


	cout << "matrix:" << endl;
	for (int i = 0; i < n; i++) {
		mr[i].init(n);
		for (int j = 0; j < n; j++) {
			cout << "a[" << i << "][" << j << "] = ";
			cin >> mr[i].row[j];
		}
	}

	cout << "vector:" << endl;
	for (int i = 0; i < n; i++) {
		int element;
		cout << "vector[" << i << "] = ";
		cin >> element;
		for (int j = 0; j < n; j++) {
			mr[j].vector[i] = element;
		}
	}

	for (int i = 0; i < n; i++)
	{
		mr[i].num = i;
		hThread[i] = CreateThread(
			NULL,                           // дескриптор защиты
			0,                              // начальный размер стека
			(LPTHREAD_START_ROUTINE)mult,  // функция потока
			(LPVOID)&mr[i],                 // параметр потока
			0,                              // опции создания
			&mr[i].id                       // идентификатор потока
		);
	}

	WaitForMultipleObjects(n, hThread, 1, INFINITE);
	for (int i = 0; i < n; i++)
	{
		cout << mr[i].res << " ";
		CloseHandle(hThread[i]);
	}
	cout << endl;
	delete[] mr;
	return 0;
}