#pragma once
#pragma warning(disable:4996)

#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<Windows.h>
#include<time.h>
using namespace std;

#define SIZE 30
#define DEG2RAD M_PI/180

#define SPACE 0
#define EDGE 101
#define SEC 102
#define MIN 103
#define HOUR 104

void DrawTime(float,float,float);
void plotLine(int x0, int y0, int x1, int y1, int type);
void pos(int x, int y);
void color(unsigned short color);

void OldplotLine(int sx, int sy, int fx, int fy);
void OldplotLineLow(int sx, int sy, int fx, int fy);
void OldplotLineHigh(int sx, int sy, int fx, int fy);

int Watch[SIZE][SIZE];

int main()
{
	system("mode con cols=60 lines=31");
	system("tiTle Analog Watch");

	float second;
	float minute;
	float hour;

	while (1)
	{
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

		second = tm.tm_sec * 6 - 90;
		minute = tm.tm_min * 6 - 90;
		hour = tm.tm_hour;

		if (hour > 12)
			hour = (hour - 12) * 30 - 90;

		pos(0, 0);
		memset(Watch, 0, sizeof(int) * SIZE * SIZE);
		DrawTime(second,minute,hour);

		Sleep(1000);		
	}
	return 0;
}


void DrawTime(float second, float minute, float hour)
{
	int r = 13;
	int x, y;

	for (int i = 1; i < 360; i++)
	{
		if (i != 90)
		{
			x = cos(i * DEG2RAD) * r + 15;
			y = sin(i * DEG2RAD) * r + 15;
			Watch[y][x] = EDGE;
		}
	}

	int count = 3;
	for (int i = 0; i < 360; i += 30)
	{
			x = cos(i * DEG2RAD) * 14 + 15;
			y = sin(i * DEG2RAD) * 14 + 15;
			Watch[y][x] = count;
			count++;
			if (count > 12)
				count = 1;
	}

	int centerX = SIZE / 2;
	int centerY = SIZE / 2;

	r = 10;
	int secX = cos(second * DEG2RAD) * r + 15;
	int secY = sin(second * DEG2RAD) * r + 15;

	r = 11;
	int minX = cos(minute * DEG2RAD) * r + 15;
	int minY = sin(minute * DEG2RAD) * r + 15;

	r = 7;
	int hourX = cos(hour * DEG2RAD) * r + 15;
	int hourY = sin(hour * DEG2RAD) * r + 15;

	plotLine(centerX, centerY, secX, secY, SEC);
	plotLine(centerX, centerY, minX, minY, MIN);
	plotLine(centerX, centerY, hourX, hourY, HOUR);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Watch[i][j] == SPACE)
			{
				color(15);
				cout << "　";
			}
			else if (Watch[i][j] == EDGE)
			{
				color(15);
				cout << "■";
			}
			else if(Watch[i][j] == SEC)
			{
				color(12);
				cout << "＊";
			}
			else if (Watch[i][j] == MIN)
			{
				color(15);
				cout << "◆";
			}
			else if (Watch[i][j] == HOUR)
			{
				color(15);
				cout << "●";
			}
			else 
			{
				color(15);
				if(Watch[i][j] >= 10)
					cout << Watch[i][j];
				else
				 cout << Watch[i][j] << " ";
			}
			
		}
		cout << endl;
	}
}

void plotLine(int x0, int y0, int x1, int y1, int type)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while (true)
	{
		Watch[y0][x0] = type;
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void pos(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void color(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void OldplotLine(int sx, int sy, int fx, int fy)
{
	if (sx < fx)
	{
		if (fx > fy)
		{
			OldplotLineLow(sx, sy, fx, fy);
		}
		else if (fx < fy)
		{
			OldplotLineHigh(sx, sy, fx, fy);
		}
	}
	else if (sx > fx)
	{
		if (fx < fy)
		{
			OldplotLineLow(fx, fy, sx, sy);
		}
		else if (fx > fy)
		{
			OldplotLineHigh(fx, fy, sx, sy);
		}
	}

	if (sx < fx && sy > fy)
	{
		OldplotLineLow(sx, sy, fx, fy);
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

void OldplotLineLow(int sx, int sy, int fx, int fy)	//x가 y보다 클때
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
		Watch[y][x] = 1;

		if (F < 0)
			F += dF1;
		else
		{
			y++;
			F += dF2;
		}
	}	
}

void OldplotLineHigh(int sx, int sy, int fx, int fy)	//y가 x보다 클때
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
		Watch[y][x] = 1;

		if (F < 0)
			F += dF1;
		else
		{
			x++;
			F += dF2;
		}
	}
}