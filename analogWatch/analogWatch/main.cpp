#pragma once

#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<Windows.h>
using namespace std;

#define SIZE 30
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
	int r = 13;
	int x, y;


	for (int i = 1; i < 360; i++)
	{
		if (i != 90)
		{
			x = cos(i * DEG2RAD) * r + 15;
			y = sin(i * DEG2RAD) * r + 15;
			Circle[y][x] = 1;
		}
		// cout << x << ", " << y << endl;
	}

	Circle[SIZE / 2][SIZE / 2] = 1;
	Circle[SIZE / 2 - 1][SIZE / 2] = 1;
	Circle[SIZE / 2][SIZE / 2 - 1] = 1;
	Circle[SIZE / 2 - 1][SIZE / 2 - 1] = 1;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Circle[i][j] == 1)
			{
				cout << "¡à";
			}
			else if (Circle[i][j] == 0)
			{
				cout << "¡á";
			}
		}
		cout << endl;
	}

}

int main()
{
	system("mode con cols=80 lines=40");
	memset(Circle, 0, sizeof(int) * SIZE * SIZE);
	drawCircle();
	return 0;
}