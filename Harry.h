#include "Living.h"

class Harry : public Living {
	//char **mapHarry;
public:
	int GetMove(char** MapPart, int move);
	//void InitMap(char **map, int W, int H);
	//void ShowMap(int W, int H);
	void ShowTempMap(int W, int H);
	//void SaveMap();
};