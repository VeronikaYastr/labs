// ������ ������������� ������� � ������ ��������� 
// � �������������� ������������ �������

#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hInEvent;
wchar_t lpEventName[] = L"InEventName";

int main()
{
	char c;

	hInEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, lpEventName);
	if (hInEvent == NULL)
	{
		cout << "Open event failed." << endl;
		cout << "Press any key to exit." << endl;
		cin.get();

		return GetLastError();
	}

	cout << "Input any char: ";
	cin >> c;
	// ������������� ������� � ����� �������	
	SetEvent(hInEvent);
	// ��������� ���������� ������� � ������� ��������
	CloseHandle(hInEvent);

	cout << "Press any key to exit from the process.";
	cin.get();

	return 0;
}