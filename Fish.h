#ifndef FISH_H
#define FISH_H
#include "Cell.h"


int CheckIfEmty(Cell * M)
{
	if(M->shark == 0 && M->fish == 0)
	{
		return 1;
	}
	return 0;
}
int ChooseCell(Move Available)
{
	int x = 0;
	int Dirrection = 0;
	if (Available.left == 0 &&
		Available.right == 0 &&
		Available.up ==0 &&
		Available.down ==0)
	{
		x = 1;
		Dirrection = -1;
	}
	while(x == 0)
	{
		int r = rand() % 4;
		Dirrection = r;
		switch(r){
			case(0):
		    if(Available.up == 1)
				x = 1;
			break;
			case(1):
			if(Available.down == 1)
				x = 1;
			break;
			case(2):
			if(Available.left == 1)
				x = 1;
			break;
			case(3):
			if(Available.right == 1)
				x = 1;
			break;
		}
	}
	return Dirrection;
}

void FishMove(Cell * Moveto, Cell * currentCell){
	if(currentCell->fish->SpawnTime == 0)
	{
		currentCell->fish->SpawnTime = 3;
		Moveto->fish = malloc(sizeof(Fish));
		Moveto->fish->SpawnTime = 3;
		Moveto->fish->moved = currentCell->fish->moved;

	}
	else
	{
		Moveto->fish = currentCell->fish;
		Moveto->fish->SpawnTime--;
		currentCell->fish = 0;
	}
	
}

void FishUpdate(Cell * fish, Cell ** tempworld, int x, int y, int range)
{   
	Move Available;
	int top = y - 1;
	int bot = y + 1;
	int left = x - 1;
	int right = x + 1;
	if (top < 0)
		top = range;
	if (left < 0)
		left = range;
	if (right > range)
		right = 0;
	if (bot > range)
		bot = 0;
	Cell * array[4] = {&(tempworld)[x][top],&(tempworld)[x][bot],&(tempworld)[left][y],&(tempworld)[right][y]};
	Available.up = CheckIfEmty(array[0]);
	Available.down = CheckIfEmty(array[1]);
	Available.left = CheckIfEmty(array[2]);
	Available.right = CheckIfEmty(array[3]);
	int ChoosenCell = ChooseCell(Available);
	if (ChoosenCell != -1)
	{
		FishMove(array[ChoosenCell], fish);
	}
}
#endif