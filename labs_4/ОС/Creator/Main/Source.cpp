#include <fstream>      
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

struct student
{
	char  name[10];  // имя студента
	int  num;    // номер группы
	double grade;   // средний балл
};

int main() {
	char binaryFile[256];
	char number[20];
	cout << "Input name of binary file : " << endl;
	cin >> binaryFile;
	cout << "Input number of records : " << endl;
	cin >> number;

	char argsCreator[200] = "Creator.exe ";
	strcat_s(argsCreator, binaryFile);
	strcat_s(argsCreator, " ");
	strcat_s(argsCreator, number);

	STARTUPINFO siCreator; //Во - первых, перед  запуском  консольного  процесса
		//ConsoleProcess.exe все поля структуры si типа STARTUPINFO должны заполняться нулями.Это делается при
		//помощи вызова функции ZeroMemory, которая предназначена для этой цели
	PROCESS_INFORMATION piCreator;

	ZeroMemory(&siCreator, sizeof(STARTUPINFO));
	siCreator.cb = sizeof(STARTUPINFO);
	if (!CreateProcess(NULL, argsCreator, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &siCreator, &piCreator))
	{
		cout << "Creator is not working" << endl;
		return 1;
	}
	WaitForSingleObject(piCreator.hProcess, INFINITE);// ждем завершения созданного прцесса
	CloseHandle(piCreator.hThread);
	CloseHandle(piCreator.hProcess);

	cout << "Binary file : " << endl;
	ifstream in(binaryFile, ios::binary);
	student st;
	while (in.read((char*)&st, sizeof(student)))
	{
		cout << st.name << " - group num " << st.num << " - grade : " << st.grade << endl;
	}
	in.close();

	char reportFile[256];
	char mark[20];
	cout << "\nInput name of report file : " << endl;
	cin >> reportFile;
	cout << "Input average mark : " << endl;
	cin >> mark;


	char reporterName[200] = "Reporter.exe ";
	strcat_s(reporterName, binaryFile);
	strcat_s(reporterName, " ");
	strcat_s(reporterName, reportFile);
	strcat_s(reporterName, " ");
	strcat_s(reporterName, mark);
	STARTUPINFO siReporter;//инф для настройки свойств процесса
	PROCESS_INFORMATION piReporter;

	ZeroMemory(&siReporter, sizeof(STARTUPINFO));
	siReporter.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(NULL, //имя исполняемого модуля
		reporterName,//командная строка
		NULL,//указатель на  SECURITY_ATTRIBUTES, указывает может ли наследоваться возвращенный описатель 
		//дочерними процессами. если NULL - не наследуется
		NULL, 
		FALSE,// If the parameter is FALSE, the handles are not inherited.
	CREATE_NEW_CONSOLE,
		NULL,//A pointer to the environment block for the new process. If this parameter is NULL, the new process uses the environment of the calling process.
		NULL,//If this parameter is NULL, the new process will have the same current drive and directory as the calling process.
		&siReporter,//A pointer to a STARTUPINFO or STARTUPINFOEX structure.
		&piReporter))//хранит информацию о процессе
	{
		cout << "Creation of 'Reporter' failed!";
		return 0;
	}

	WaitForSingleObject(piReporter.hProcess, INFINITE);
	CloseHandle(piReporter.hThread);
	CloseHandle(piReporter.hProcess);
	
	system("pause");
	return 0;
}