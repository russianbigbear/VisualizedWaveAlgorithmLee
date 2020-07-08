/*
������ ���������� ���������
���������� ���������������� ������������ ������������ ��. �.�. ���������,
���������� ���,
������ ��-51
����������� �.�.
*/

#include <stdio.h>
#include <string>
#include <Windows.h>// ������������ ����������� �����
using namespace std;

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���������� �������

/*����� ����� ����������� �����*/
void Color(ConsoleColor _color) {
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | _color));
}

/*������ ������ ������������� �����*/
void Color(ConsoleColor _color, string Msg) {
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | _color));
	cout << Msg;
	Color(White);
}

/*������ ������� ������������� �����*/
void Color(ConsoleColor _color, char Msg) {
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | _color));
	cout << Msg;
	Color(White);
}
