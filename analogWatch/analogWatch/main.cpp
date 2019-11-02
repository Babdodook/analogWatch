#pragma once

#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<Windows.h>
using namespace std;

#define SIZE 30
#define DEG2RAD M_PI/180

void Draw(int);
void plotLine(int sx, int sy, int fx, int fy);
void plotLineLow(int sx, int sy, int fx, int fy);
void plotLineHigh(int sx, int sy, int fx, int fy);

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
	pos(x, y); cout << "■";
}


int main()
{
	system("mode con cols=80 lines=40");

	int timerad = 0;
	memset(Circle, 0, sizeof(int) * SIZE * SIZE);
	Draw(timerad);
	/*while (1)
	{
		memset(Circle, 0, sizeof(int) * SIZE * SIZE);
		Draw(timerad);
		Sleep(1000);
		system("cls");
		timerad += 10;
	}*/
	return 0;
}


void Draw(int timerad)
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
	}

	Circle[SIZE / 2][SIZE / 2] = 1;
	Circle[SIZE / 2 - 1][SIZE / 2] = 1;
	Circle[SIZE / 2][SIZE / 2 - 1] = 1;
	Circle[SIZE / 2 - 1][SIZE / 2 - 1] = 1;

	int Fx = cos(350 * DEG2RAD) * r + 15;
	int Fy = sin(350 * DEG2RAD) * r + 15;

	int centerX = SIZE / 2;
	int centerY = SIZE / 2;

	cout << "(" << centerX << "," << centerY << ") " << " - (" << Fx << "," << Fy << ") " << endl;

	plotLine(centerX, centerY, Fx, Fy);

	//plotLineHigh(Fx, Fy, centerX, centerY);
	//*
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Circle[i][j] == 1)
			{
				cout << "□";
			}
			else if (Circle[i][j] == 0)
			{
				cout << "■";
			}
		}
		cout << endl;
	}
	//*/


	pos(30, 1); cout << "12";
	pos(1, 30); cout << "a";
}

void plotLine(int sx, int sy, int fx, int fy)
{
	if (sx < fx)
	{
		if (fx > fy)
		{
			plotLineLow(sx, sy, fx, fy);
		}
		else if (fx < fy)
		{
			plotLineHigh(sx, sy, fx, fy);
		}
	}
	else if (sx > fx)
	{
		if (fx < fy)
		{
			plotLineLow(fx, fy, sx, sy);
		}
		else if (fx > fy)
		{
			plotLineHigh(fx, fy, sx, sy);
		}
	}

	if (sx < fx && sy > fy)
	{
		plotLineLow(sx, sy, fx, fy);
	}
	/*
	if (abs(fy - sy) < abs(fx - sx))	//절댓값 fy - sy < 절댓값 fx - sx 
	{
		if (sx > fx)
			plotLineLow(fx, fy, sx, sy);
		else
			plotLineLow(sx, sy, fx, fy);
	}
	else
	{
		if (sy > fy)
			plotLineHigh(fx, fy, sx, sy);
		else
			plotLineHigh(sx, sy, fx, fy);
	}
	*/
}

void plotLineLow(int sx, int sy, int fx, int fy)	//x가 y보다 클때
{
	int x = sx;
	int y = sy;

	int W = abs(fx - sx);
	int H = abs(fy - sy);

	int F = 2 * H - W;		//초기 판별식

	int dF1 = 2 * H;		// F < 0
	int dF2 = 2 * (H - W);	// F > 0

	for (x = sx; x < fx; x++)
	{
		Circle[y][x] = 1;

		if (F < 0)
			F += dF1;
		else
		{
			y++;
			F += dF2;
		}
	}	
}

void plotLineHigh(int sx, int sy, int fx, int fy)	//y가 x보다 클때
{
	int x = sx;
	int y = sy;

	int W = abs(fy - sy);
	int H = abs(fx - sx);

	int F = 2 * H - W;		//초기 판별식

	int dF1 = 2 * H;		// F < 0
	int dF2 = 2 * (H - W);	// F > 0

	for (y = sy; y < fy; y++)
	{
		Circle[y][x] = 1;

		if (F < 0)
			F += dF1;
		else
		{
			x++;
			F += dF2;
		}
	}
}