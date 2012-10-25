#ifndef Shark_H
#define Shark_H
#include "Cell.h"

int CheckIfEmtyShark(Cell * M)
{
	//return two if there is a fish to eat, 1 if there is a free space and 0 otherwise.
	if(M->shark == 0 && M->fish == 0)
	{
		//printf("%s\n", );("E");
		return 2;
	}
	if(M->shark == 0 && M->fish != 0)
	{
		//printf("F");
		return 1;
	}
	//printf("S");
	return 0;
}
int ChooseCellShark(Move Available)
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
	//check to see if the shark can move to eat a fish before trying other movements.
	if(Available.left == 1 ||
		Available.right == 1 ||
		Available.up == 1 ||
		Available.down == 1)
	{
		//printf("Should Eat\n");
		while(x == 0)
		{
			//srand(time(NULL));
			int r = rand() % 4;

			Dirrection = r;
			switch(r){
				case 0:
		   	 if(Available.up == 1)
					x = 1;
				break;
				case 1:
				if(Available.down == 1)
					x = 1;
				break;
				case 2:
				if(Available.left == 1)
					x = 1;
				break;
				case 3:
				if(Available.right == 1)
					x = 1;
				break;
			}
		}
	}
	while(x == 0)
	{
		int r = rand() % 4;

		Dirrection = r;
		switch(r){
			case 0:
		    if(Available.up == 2)
				x = 1;
			break;
			case 1:
			if(Available.down == 2)
				x = 1;
			break;
			case 2:
			if(Available.left == 2)
				x = 1;
			break;
			case 3:
			if(Available.right == 2)
				x = 1;
			break;
		}
	}
	return Dirrection;
}

void SharkMove(Cell * Moveto, Cell * currentCell){
	currentCell->shark->SpawnTime--;
	currentCell->shark->StarveTime--;
	if(currentCell->shark->StarveTime <= 0){
		//printf("Dead\n");
		currentCell->shark = 0;
	}
	else if(currentCell->shark->SpawnTime == 0)
	{
		//printf("Should Spawn \n");
		currentCell->shark->SpawnTime = 7;
		if(Moveto->fish != 0)
		{
			//printf("Eat\n");
			currentCell->shark->StarveTime = 10;
			Moveto->fish = 0;

		}
			
		Moveto->shark = malloc(sizeof(Shark));
		Moveto->shark->SpawnTime = 7;
		Moveto->shark->StarveTime = 4;
		Moveto->shark->moved = currentCell->shark->moved;
		
	}
	else if(Moveto->fish != 0){
		//printf("Eat\n");
		currentCell->shark->StarveTime = 4;
		Moveto->fish = 0;
		Moveto->shark = currentCell->shark;
		currentCell->shark = 0;
	}
	else
	{
		Moveto->shark = currentCell->shark;
		currentCell->shark = 0;
	}
	
}

void SharkUpdate(Cell * currentCell, Cell ** tempworld, int x, int y, int range)
{   
	if(currentCell->shark != 0)
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
		Available.up = CheckIfEmtyShark(array[0]);
		Available.down = CheckIfEmtyShark(array[1]);
		Available.left = CheckIfEmtyShark(array[2]);
		Available.right = CheckIfEmtyShark(array[3]);
		int ChoosenCell = ChooseCellShark(Available);
		//printf("\n");
		if (ChoosenCell != -1)
		{
			SharkMove(array[ChoosenCell], currentCell);
		}
	}
}
#endif