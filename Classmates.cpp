#include "Classmates.h"

int Classmates::GetMove(char **MapPart, int move){
	switch (move){
	case 1:
		if (MapPart[3 - 1][3] == ' '){
			y = y - 1;
		}
		else if (MapPart[3 - 1][3] == 'T')
			return 2;
		else
			return 0;
		break;
	case 2:
		if (MapPart[3 + 1][3] == ' '){
			y = y + 1;
		}
		else if (MapPart[3 + 1][3] == 'T')
			return 2;
		else
			return 0;
		break;
	case 3:
		if (MapPart[3][3 + 1] == ' '){
			x = x + 1;
		}
		else if (MapPart[3][3 + 1] == 'T')
			return 2;
		else
			return 0;
		break;
	case 4:
		if (MapPart[3][3 - 1] == ' '){
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

bool Classmates::CanMove(char **MapPart){
	if (MapPart[3 - 1][3] == ' ' || MapPart[3 + 1][3] == ' ' || MapPart[3][3 + 1] == ' ' || MapPart[3][3 - 1] == ' ')
		return true;
	return false;
}