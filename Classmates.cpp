#include "Classmates.h"

int Classmates::GetMove(char** MapPart, int move) {
	switch (move) {
	case 1:
		if (MapPart[3 - 1][3] == ' ') {
			y = y - 1;
		}
		else if (MapPart[3 - 1][3] == 'T')
			return 2;
		else
			return 0;
		break;
	case 2:
		if (MapPart[3 + 1][3] == ' ') {
			y = y + 1;
		}
		else if (MapPart[3 + 1][3] == 'T')
			return 2;
		else
			return 0;
		break;
	case 3:
		if (MapPart[3][3 + 1] == ' ') {
			x = x + 1;
		}
		else if (MapPart[3][3 + 1] == 'T')
			return 2;
		else
			return 0;
		break;
	case 4:
		if (MapPart[3][3 - 1] == ' ') {
			x = x - 1;
		}
		else if (MapPart[3][3 - 1] == 'T')
			return 2;
		else
			return 0;
		break;
	}
	return 1;
}

bool Classmates::CanMove(char** MapPart) {
	if (MapPart[3 - 1][3] == ' ' || MapPart[3 + 1][3] == ' ' || MapPart[3][3 + 1] == ' ' || MapPart[3][3 - 1] == ' ')
		return true;
	return false;
}

int Classmates::FindSortestPath(char** map, int x, int y, int step) {
	int res[4] = { 1000, 1000, 1000, 1000 };
	int i, p;
	if (map[y + 1][x] == 'T' || map[y - 1][x] == 'T' || map[y][x + 1] == 'T' || map[y][x - 1] == 'T')
		return 0;
	map[y][x] = '.';
	if (map[y - 1][x] == ' ' || map[y - 1][x] == 'T')
		res[0] = Classmates::FindSortestPath(map, x, y - 1, step + 1) + 1;
	if (map[y + 1][x] == ' ' || map[y + 1][x] == 'T')
		res[1] = Classmates::FindSortestPath(map, x, y + 1, step + 1) + 1;
	if (map[y][x + 1] == ' ' || map[y][x + 1] == 'T')
		res[2] = Classmates::FindSortestPath(map, x + 1, y, step + 1) + 1;
	if (map[y][x - 1] == ' ' || map[y][x - 1] == 'T')
		res[3] = Classmates::FindSortestPath(map, x - 1, y, step + 1) + 1;
	map[y][x] = ' ';
	p = 0;
	for (i = 1; i < 4; i++)
		if (res[i] < res[p])
			p = i;
	if (step)
		return res[p];
	else
		return (p + 1);
}

int Classmates::GetMoveHard(char** map) {
	int newx = x;
	int newy = y;
	int move = FindSortestPath(map, newx, newy, 0);
	switch (move) {
	case 0:
		return 2;
		break;
	case 1:
		if (map[y - 1][x] == ' ')
			y--;
		return 1;
		break;
	case 2:
		if (map[y + 1][x] == ' ')
			y++;
		return 1;
		break;
	case 3:
		if (map[y][x + 1] == ' ')
			x++;
		return 1;
		break;
	case 4:
		if (map[y][x - 1] == ' ')
			x--;
		return 1;
		break;
	}
	return 0;
}