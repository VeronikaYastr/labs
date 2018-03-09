#include <fstream>      //Для работы с файлом
#include <iostream>
#include <string.h>
#include <windows.h>

struct student
{
	char  name[10];  // имя студента
	int  num;    // номер группы
	double grade;   // средний балл
};

using namespace std;

int main(int argc, char *argv[]) {
	char name[256];
	strcpy_s(name, argv[1]);
	int number = 0;
	number = atoi(argv[2]);

	ofstream out(name, ios::binary);
	for (int i = 0; i < number; i++)
	{
		struct student st;
		cout << "Input student's name : " << endl;
		cin >> st.name;
		cout << "Input number of group : " << endl;
		cin >> st.num;
		cout << "Input grade : " << endl;
		cin >> st.grade;
		out.write((char*)&st, sizeof(student));
	}
	out.close();

	ExitProcess(1);
	return 0;
}