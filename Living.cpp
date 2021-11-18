#include "living.h"

Living::Living() {
	x = 0;
	y = 0;
	TempMap = new char* [7];
	for (int i = 0; i < 7; ++i)
	{
		TempMap[i] = new char[7];
	}
}

void Living::Init(char** map, int C, int L) {
	time_t t;
	srand((unsigned)time(&t));
	do {
		x = rand() % C;
		y = rand() % L;
	} while (map[y][x] != ' ');
}

int Living::getX() {
	return x;
}

int Living::getY() {
	return y;
}

void Living::setX(int _x) {
	x = _x;
}
void Living::setY(int _y) {
	y = _y;
}

void Living::CreateTempMap(char** map) {
	int i, j;
	for (i = 0; i < 7; i++)
		for (j = 0; j < 7; j++)
		{
			if (y - 3 + i > 0 && y - 3 + i < 20 && x - 3 + j>0 && x - 3 + j < 60)
				TempMap[i][j] = map[y - 3 + i][x - 3 + j];
			else
				TempMap[i][j] = '*';
		}
	/*for (i = 0; i < 7; i++){
		for (j = 0; j < 7; j++)
			mvprintw(i + 2, j + 63, "%c", TempMap[i][j]);
	}*/
}

char** Living::getTempMap() {
	return TempMap;
}