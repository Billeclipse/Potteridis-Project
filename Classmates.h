#include "Living.h"

class Classmates : public Living {
public:
	int GetMove(char** MapPart, int move);
	bool CanMove(char** MapPart);
	int FindSortestPath(char** map, int x, int y, int step);
	int GetMoveHard(char** map);
	//void InitMap(char **map, int W, int H){}
	//void ShowMap(int W, int H){}
	//void SaveMap(){}
};