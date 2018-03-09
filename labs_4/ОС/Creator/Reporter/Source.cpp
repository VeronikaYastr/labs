#include <fstream>     
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
	char filename[256];
	strcpy_s(filename, argv[1]);
	char reportname[256];
	strcpy_s(reportname, argv[2]);
	double grade = atof(argv[3]);

	ofstream out(reportname);
	out << "Report on file '" << filename << "'" << endl;
	out << "List of students with grade over '" << grade << "' : " << endl;

	ifstream in(filename, ios::binary);
	student st;
	while (in.read((char*)&st, sizeof(student)))
	{
		if (st.grade > grade)
			out << st.name << " - group №" << st.num << " - grade : " << st.grade << endl;
	}
	
	in.close();
	out.close();
	ExitProcess(1);
	return 0;
}