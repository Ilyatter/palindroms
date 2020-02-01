#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 

using namespace std;

int main()
{
	try
	{
		char* str = new char[300];
		cout << "Enter the data string:" << endl;
		cin.getline(str, 300);
		
		if (strlen(str) <= 0)
		{
			delete[] str;
			throw "The entered string is empty!";
		}

		char* i_begin = str; // �������� �� ������� ���� � ������
		while (*i_begin)
		{
			if (*i_begin > 47 && *i_begin < 58)
			{
				delete[] str;
				throw "Error! There are digits in the eneterd string.";
			}
			++i_begin;
		}

		char deline[] = " ,.";
		char* tok = strtok(str, deline);
		
		char** palindromes = new char*[150];  // ������, � ������� �������� ��� ���������� ������ (������������ �� ����������� ���� �����������)
		int count = 0;

		while (tok)
		{
			if (strlen(tok) < 3) // �����, ���������� ������ 3 ��������, �� ����� ���� �����������
			{
				tok = strtok(NULL, deline);
				continue;
			}

			char* begin = tok;
			char* end = begin + strlen(tok) - 1;
			while (begin < end) // �������� �� ���������
			{
				if (*begin == *end || (*begin < *end ? (*begin) + 32 == *end : (*begin) - 32 == *end))
				{
					++begin;
					--end;
				}
				else
					break;
			}

			if (begin >= end)   // ���� ���������, �� ������ ��������� �� ����� ��������� � ������ ������� ������� ���������� �� ����������
			{
				int tokLength = strlen(tok);
				int index = 0;
				for (; index < count; index++)
					if (strlen(palindromes[index]) > tokLength)
						break;
				for (int i = count - 1; i >= index; i--)
					palindromes[i + 1] = palindromes[i];
				palindromes[index] = new char[300];
				strcpy(palindromes[index], tok);
				++count;
			}
			tok = strtok(NULL, deline);
		}

		if (count > 0)  // ���� ���������� ���� � �������� ������, �� ������ �� �� ������� � ������ ����������, �������� ���������
		{
			char resultStr[300];

			int i = 0;
			strcpy(resultStr, palindromes[i]);
			delete[] palindromes[i++];

			while(i < count)
			{
				strcat(resultStr, " ");
				strcat(resultStr, palindromes[i]);
				delete[] palindromes[i++];
			}

			cout << "Result string:" << endl;
			puts(resultStr);
		}
		else
		{
			delete[] str;
			delete[] palindromes;
			throw "There is no palindromes in str.";
		}

		delete[] str;
		delete[] palindromes;
	}
	catch (const char* msg)
	{
		cerr << msg;
	}
	return 0;
}