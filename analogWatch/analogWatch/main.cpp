#pragma once

#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<Windows.h>
using namespace std;

#define SIZE 21
#define DEG2RAD M_PI/180

int Circle[SIZE][SIZE];

void pos(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setPixel(int x, int y)
{
	pos(x, y); cout << "¡¤";
}

/*	12½Ã
*	r = 2
*	rad = 360
*	x = cos 360 / 180 * r
*	y = sin 360 / 180 * r
*/

void drawCircle()
{
	int r = 10;
	int x, y;


	for (int i = 1; i <= 12; i++)
	{
		x = cos(360 / i * DEG2RAD) * r + 10;
		y = sin(360 / i * DEG2RAD) * r + 10;

		cout << x << ", " << y << endl;
		Circle[y][x] = 2;

	}

	Circle[SIZE / 2][SIZE / 2] = 2;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Circle[i][j] == 0)
			{
				cout << "¡á";
			}
			else if (Circle[i][j] == 2)
			{
				cout << "¡à";
			}
			else
				cout << "¡¡";
		}
		cout << endl;
	}

	cout << x << ", " << y << endl;

}

int main()
{
	system("mode con cols=80 lines=40");
	memset(Circle, 0, sizeof(int) * SIZE * SIZE);
	drawCircle();
	return 0;
}