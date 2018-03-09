#include <iostream>
#include <windows.h>

using namespace std;

struct MatrixRow
{
	int* elements;
	int num;
	int* vector;
	DWORD id;
	int* result;
	int n;

};


DWORD WINAPI mul(LPVOID lp)
{
	MatrixRow* matrRow = (MatrixRow*)lp;
	
	for (int i = 0; i < matrRow->n; i++)
	{
		matrRow->result[matrRow->num] += matrRow->elements[i] * matrRow->vector[i];
		Sleep(matrRow->num * 100);
	}

	printf("\nMultiplication %d string on vector = %d\n", matrRow->num + 1, matrRow->result[matrRow->num]);
	return 0;
}

int main()
{
	int n;
	cout << "Enter the size of matrix : " << endl;
	cin >> n;
	HANDLE* hThread = new HANDLE[n];
	MatrixRow *matrRow = new MatrixRow[n];
	int **matrix = new int*[n];
	int *vector = new int[n];
	int *result = new int[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		result[i] = 0;
	}

	cout << "\nEnter elements of matrix:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "a[" << i << "][" << j << "] = ";
			cin >> matrix[i][j];
		}
	}

	cout << "\nYour matrix" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}

	cout << "\nEnter elements of vector:" << endl;
	for (int i = 0; i < n; i++) {
		int element;
		cout << "vector[" << i << "] = ";
		cin >> vector[i];
	}

	for (int i = 0; i < n; i++)
	{
		matrRow[i].vector = vector;
		matrRow[i].elements = matrix[i];
		matrRow[i].num = i;
		matrRow[i].n = n;
		matrRow[i].result = result;
		hThread[i] = CreateThread(
			NULL,                           // дескриптор защиты
			0,                              // начальный размер стека
			(LPTHREAD_START_ROUTINE)mul,  // функция потока
			(LPVOID)&matrRow[i],                 // параметр потока
			0,                              // опции создания
			&matrRow[i].id                       // идентификатор потока
		);
	}

	WaitForMultipleObjects(n, //The number of object handles in the array pointed to by lpHandles. The maximum number of object handles is MAXIMUM_WAIT_OBJECTS. This parameter cannot be zero.
		hThread, //An array of object handles.The handles must have the SYNCHRONIZE access right. 
		1, //If this parameter is TRUE, the function returns when the state of all objects in the lpHandles array is signaled. 
		//If FALSE, the function returns when the state of any one of the objects is set to signaled.
		//In the latter case, the return value indicates the object whose state caused the function to return.
		INFINITE);//The time-out interval, in milliseconds. If a nonzero value is specified, the function waits until
	//the specified objects are signaled or the interval elapses. If dwMilliseconds is zero, 
	//the function does not enter a wait state if the specified objects are not signaled; 
	//it always returns immediately. If dwMilliseconds is INFINITE, the function will return only when the specified objects are signaled.
	cout << "\nResult : " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << matrRow[i].result[i] << " ";
		CloseHandle(hThread[i]);
	}
	cout << endl;
	delete[] matrRow;
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] vector;
	system("pause");
	return 0;
}