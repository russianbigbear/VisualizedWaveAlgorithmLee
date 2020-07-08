/*
Проект разработан студентом
Алтайского государственного технического университета им. И.И. Ползунова,
факультета ФИТ,
группы ПИ-51
Головвенсих Д.В.
*/

#include <stdio.h>
#include <string>
#include <Windows.h>// Обязательное подключение файла
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

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор консоли

/*смена цвета консольного цвета*/
void Color(ConsoleColor _color) {
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | _color));
}

/*выввод текста определенного цвета*/
void Color(ConsoleColor _color, string Msg) {
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | _color));
	cout << Msg;
	Color(White);
}

/*выввод символа определенного цвета*/
void Color(ConsoleColor _color, char Msg) {
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | _color));
	cout << Msg;
	Color(White);
}
