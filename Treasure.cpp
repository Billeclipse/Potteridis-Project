#include "Treasure.h"
#include <time.h>
#include <stdlib.h>

void Treasure::Init(char** map, int C, int L) {
	time_t t;
	srand((unsigned)time(&t));
	do {
		x = rand() % C;
		y = rand() % L;
	} while (map[y][x] != ' ');
}

int Treasure::getX() {
	return x;
}

int Treasure::getY() {
	return y;
}