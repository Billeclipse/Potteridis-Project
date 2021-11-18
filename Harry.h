#include "Living.h"

class Harry : public Living{
public:	
	int GetMove(char **MapPart, int move);
	void ShowTempMap(int W, int H);
};