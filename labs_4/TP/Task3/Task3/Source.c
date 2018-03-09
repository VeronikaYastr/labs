#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	FILE *in = fopen("input.txt", "r");
	FILE *out = fopen("output.txt", "w");
	char str[100];
	int len = 0;

	while (fgets(str, 100, in) != NULL)
	{
		len = strlen(str);
		for (int i = 0; i < len; i++)
		{
			char c = str[i];
			if (c >= -32 && c <= -1)
				fputc(c - 32, out);
			else
				fputc(c, out);
		}
	}

	fclose(in);
	fclose(out);
	system("pause");
	return 0;
}