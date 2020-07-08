/*
Проект разработан студентом
Алтайского государственного технического университета им. И.И. Ползунова,
факультета ФИТ,
группы ПИ-51
Головвенсих Д.В.
*/

#include <iostream>
#include <queue>
#include <fstream>
#include <locale>
#include "ConsoleColor.h"
#include "Message.h"

int N = 0; //размер карты

/*Вывод начальных сообщений*/
void MsgOutput() {
	//вывод начальных сообщений
	cout << MsgHello << MsgDescript << Instruction1 << Instruction2;

	cout << " " << MsgMap1
			" " << MsgMap2
			" " << MsgMap3
			" " << MsgMap4
			" " << MsgMap5;

	//вывод обозначений
	cout << MsgSymbol1;

	cout << " "; Color(LightGray, MsgS1);
	Color(White, MsgSymbol2);

	cout << " "; Color(LightRed, MsgS2);
	Color(White, MsgSymbol3);

	cout << " "; Color(LightCyan, MsgS3);
	Color(White, MsgSymbol4);

	cout << " "; Color(LightMagenta, MsgS4);
	Color(White, MsgSymbol5);

	cout << " "; Color(LightGreen, MsgS5);
	Color(White, MsgSymbol6);

	cout << " "; Color(LightGreen, MsgS1);
	Color(White, MsgSymbol7);

	cout << " "; Color(Yellow, MsgS6);
	Color(White, MsgSymbol8);

	cout << " "; Color(LightRed, MsgS7);
	Color(White, MsgSymbol9);

	cout << MsgInputMap;

	Color(White);
}

/* нахождение пути*/
void FindPath(int row, int col, vector<vector<char>>& map_copy, vector<vector<int>>& visited, vector<vector<int>>& path, queue<int>& plan) {
	if (!visited[row][col]) {
		/* проверяем не вышли ли мы за границы лабиринта, есть ли клетка
		в массиве посещенных и можно ли через нее пройти*/
		//смотрим позицую справа
		if ((row + 1) < N && (row + 1) >= 0 && !visited[row + 1][col] &&
			(map_copy[row + 1][col] == '.' || map_copy[row + 1][col] == 'O')) {
			path[row + 1][col] = path[row][col] + 1;
			plan.push(row + 1);
			plan.push(col);
		}
		//смотрим позицию слева
		if ((row - 1) < N && (row - 1) >= 0 && !visited[row - 1][col] &&
			(map_copy[row - 1][col] == '.' || map_copy[row - 1][col] == 'O')) {
			path[row - 1][col] = path[row][col] + 1;
			plan.push(row - 1);
			plan.push(col);
		}
		//смотрим позицию сверху
		if ((col + 1) < N && (col + 1) >= 0 && !visited[row][col + 1] &&
			(map_copy[row][col + 1] == '.' || map_copy[row][col + 1] == 'O')) {
			path[row][col + 1] = path[row][col] + 1;
			plan.push(row);
			plan.push(col + 1);
		}	
		//смотрим позицию снизу
		if ((col - 1) < N && (col - 1) >= 0 && !visited[row][col - 1] &&
			(map_copy[row][col - 1] == '.' || map_copy[row][col - 1] == 'O')) {
			path[row][col - 1] = path[row][col] + 1;
			plan.push(row);
			plan.push(col - 1);
		}
		//диагонали
		//смотрим вверх-лево
		if ((col + 1) < N && (col + 1) >= 0 && (row - 1) < N && (row - 1) >= 0 && !visited[row - 1][col + 1] &&
			(map_copy[row - 1][col + 1] == '.' || map_copy[row - 1][col + 1] == 'O')) {
			path[row - 1][col + 1] = path[row][col] + 1;
			plan.push(row - 1);
			plan.push(col + 1);
		}
		//смотрим вверх-право
		if ((col + 1) < N && (col + 1) >= 0 && (row + 1) < N && (row + 1) >= 0 && !visited[row + 1][col + 1] &&
			(map_copy[row + 1][col + 1] == '.' || map_copy[row + 1][col + 1] == 'O')) {
			path[row + 1][col + 1] = path[row][col] + 1;
			plan.push(row + 1);
			plan.push(col + 1);
		}
		//смотрим снизу-лево
		if ((col - 1) < N && (col - 1) >= 0 && (row - 1) < N && (row - 1) >= 0 && !visited[row - 1][col - 1] &&
			(map_copy[row - 1][col - 1] == '.' || map_copy[row - 1][col - 1] == 'O')) {
			path[row - 1][col - 1] = path[row][col] + 1;
			plan.push(row - 1);
			plan.push(col - 1);
		}
		//смотрим снизу-права
		if ((col - 1) < N && (col - 1) >= 0 && (row + 1) < N && (row + 1) >= 0 && !visited[row + 1][col - 1] &&
			(map_copy[row + 1][col - 1] == '.' || map_copy[row + 1][col - 1] == 'O')) {
			path[row + 1][col - 1] = path[row][col] + 1;
			plan.push(row + 1);
			plan.push(col - 1);
		}
		visited[row][col] = 1; /* отмечаем клетку в которой побывали */
	}
}

/*востановление пути*/
void RestoringWay(vector<vector<char>>& map, vector<vector<int>>& path, int x_end, int y_end) {
	int x = x_end;
	int y = y_end;

	// восстановление пути
	while (path[x][y] != 2) {
		//путь лево
		if ((x - 1) >= 0 && (x - 1) < N && (path[x - 1][y] == path[x][y] - 1)) {
			x = x - 1;
			map[x][y] = '*';
		}
		//путь право
		else if ((x + 1) >= 0 && (x + 1) < N && (path[x + 1][y] == path[x][y] - 1)) {
			x = x + 1;
			map[x][y] = '*';
		}
		//путь вниз
		else if ((y - 1) >= 0 && (y - 1) < N && (path[x][y - 1] == path[x][y] - 1)) {
			y = y - 1;
			map[x][y] = '*';
		}
		//путь вверх
		else if ((y + 1) >= 0 && (y + 1) < N && (path[x][y + 1] == path[x][y] - 1)) {
			y = y + 1;
			map[x][y] = '*';
		}
		//путь вверх-лево
		else if ((y + 1) >= 0 && (y + 1) < N && (x - 1) >= 0 && (x - 1) < N && (path[x - 1][y + 1] == path[x][y] - 1)) {
			y = y + 1;
			x = x - 1;
			map[x][y] = '*';
		}
		//путь вверх-право
		else if ((y + 1) >= 0 && (y + 1) < N && (x + 1) >= 0 && (x + 1) < N && (path[x + 1][y + 1] == path[x][y] - 1)) {
			y = y + 1;
			x = x + 1;
			map[x][y] = '*';
		}
		//путь низ-лево
		else if ((y - 1) >= 0 && (y - 1) < N && (x - 1) >= 0 && (x - 1) < N && (path[x - 1][y - 1] == path[x][y] - 1)) {
			y = y - 1;
			x = x - 1;
			map[x][y] = '*';
		}
		//путь низ-право
		else if ((y - 1) >= 0 && (y - 1) < N && (x + 1) >= 0 && (x + 1) < N && (path[x + 1][y - 1] == path[x][y] - 1)) {
			y = y - 1;
			x = x + 1;
			map[x][y] = '*';
		}
	}

}

/*печать карты на экран*/
void PrintMap(vector<vector<char>> map, vector<vector<int>> visited, bool flag, int x, int y) {
	system("cls");

	/*вывод сообщения о результате*/
	if (flag) cout << MsgWell;
	if (!flag) cout << MsgBad;

	for (int i = 0; i < N + 2; i++)
		Color(LightRed, '+');
	cout << endl;

	//вывод карты(с волной)
	if (!flag) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {

				if(j == 0) Color(LightRed, '+');

				if (i == x && j == y) 
					Color(LightGreen, '~');
				else {
					if (visited[i][j] == 1 && map[i][j] == '.') 
						Color(LightGreen, map[i][j]);
					else {
						if (map[i][j] == '.') 
							Color(LightGray, map[i][j]);
						if (map[i][j] == 'P') 
							Color(LightCyan, map[i][j]);
						if (map[i][j] == 'O') 
							Color(LightMagenta, map[i][j]);
						if (map[i][j] == '=') 
							Color(LightRed, map[i][j]);
					}
				}

				if (j == N - 1) Color(LightRed, '+');
			}
			cout << endl;
		}
	}

	//вывод карты(с путём)
	if (flag) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {

				if (j == 0) Color(LightRed, '+');

				if (map[i][j] == '*') 
					Color(Yellow, map[i][j]);
				if (map[i][j] == '.') 
					Color(LightGray, map[i][j]);
				if (map[i][j] == 'P') 
					Color(LightCyan, map[i][j]);
				if (map[i][j] == 'O') 
					Color(LightMagenta, map[i][j]);
				if (map[i][j] == '=') 
					Color(LightRed, map[i][j]);					

				if (j == N - 1) Color(LightRed, '+');
			}
			cout << endl;
		};
	}

	for (int i = 0; i < N + 2; i++)
		Color(LightRed, '+');
	cout << endl << endl;

	Color(White);
}

/*Основная функция*/
int main() {
	setlocale(LC_ALL, "rus"); //русский язык
	Color(White); //белый цвет текста консоли

	char ch = ' ';
	do {
		system("cls");		//очистка экрана
		int	x_start, y_start, //координаты X, У начала
			x_end, y_end,	  //координаты X, У конца
			x, y;			  //координаты X, Y в данный момент

		ifstream input; //входной поток

		//вывод сообщений
		MsgOutput();

		//ввод названия карты
		Color(LightGray);
		string name_map; cin >> name_map;
		Color(White);

		//открытие карты с именем
		input.open(name_map + ".txt");

		input >> N;
		queue <int> plan; //очередь посещения клеток
		vector<vector<char>> map(N, vector<char>(N));			// хранения лабиринта 
		vector<vector<char>> map_copy(N, vector<char>(N));		// копия карты
		vector<vector<int>> visited(N, vector<int>(N, 0));		// хранения информации о посещении клеток
		vector<vector<int>> path(N, vector<int>(N, -1));		// хранения найденных путей 

		//чтение данных с файла
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				input >> map[i][j]; //вводим лабиринт

				//находим начало пути
				if (map[i][j] == 'P') {
					x_start = i;
					y_start = j;
					plan.push(i);  /* заносим начальную клетку */
					plan.push(j);  /* в план посещения */
					path[i][j] = 1; //заносим коррдинаты начала пути
				}
				//находим конечную точку
				else if (map[i][j] == 'O') {
					x_end = i;
					y_end = j;
				}
			}
		}
		input.close();

		map_copy = map; //копируем карту

		//пока очередь посещения клеток непустая
		while (!plan.empty()) {
			x = plan.front();
			plan.pop();
			y = plan.front();
			plan.pop();
			FindPath(x, y, map_copy, visited, path, plan); // ищем путь

			if (!visited[x_end][y_end])
				PrintMap(map_copy, visited, false, x, y);
			else {
				RestoringWay(map, path, x_end, y_end);
				PrintMap(map, visited, true, -1, -1);
			}
			Sleep(400);
		}

		cout << MsgExit;
		getchar();
		ch = getchar();

	} while (ch != 'Q');
	return 0;

}