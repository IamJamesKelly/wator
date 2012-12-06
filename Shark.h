/**	@Name:		Shark.h
	@Authors:	Mark Gethings, Gearóid Neville.
	@Brief:		This is the Shark Class. This class holds all the
				Functionality of every Shark in the simulation. Controls 
				the checks, movements, updates and death and creation of
				other Sharks.
	@Arguments:	N/A
	@Returns:	N/A
*/
#ifndef Shark_H
#define Shark_H
#include "Cell.h"


/**	@Name:		CheckIfEmtyShark
	@Brief:		This is the check every Shark makes before any movement
				has been made. Checks if whether a Cell is empty, full
				or has a Fish to eat in it.		
	@Arguments:	Cell * M ( Takes in a pointer to a Cell )
	@Returns:	This function has three return possibilities
				1. It can return 0, which means the Cell is occupied.
				2. It can return 1, which means the Cell has a Fish in it.
				3. It can return 2, which means the Cell is unoccupied.
*/
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
/**	@Name:		ChooseCellShark
	@Brief:		This function dictates what direction the Shark should take.
				This function takes into account the number of spaces available,
				taking a priorty with the spaces with Fish in them, and then 
				gives a direction for the Shark to move in if there is any cell
				available.
	@Arguments:	Move Available ( Takes in a struct Move ( A Direction ) )
	@Returns:	Returns Dirrection ( An integer dictating the direction of the
				movement of the Shark. )
*/
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
		//printf("Should Eat\n")
		//#pragma ibm parallel_loop
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
	
	return Dirrection;
}
/**	@Name:		SharkMove
	@Brief:		This function dictates what direction the Shark should take.
				This function takes into account the number of spaces available,
				taking a priorty with the spaces with Fish in them, and then 
				gives a driection for the shark to move in if there is any cell
				available.
	@Arguments:	Cell * Moveto ( A pointer to a Cell that the Shark will move to), 
				Cell * currentCell ( A pointer to a Cell that the Shark is currently in )
	@Returns:	Returns Dirrection ( An integer dictating the direction of the
				movement of the Shark. )
*/
void SharkMove(Cell * Moveto, Cell * currentCell){
	

	currentCell->shark->SpawnTime--;
	currentCell->shark->StarveTime--;
	if(currentCell->shark->SpawnTime == 0)
	{
		//printf("Should Spawn \n");
		currentCell->shark->SpawnTime = 7;	
		Moveto->shark = malloc(sizeof(Shark));
		Moveto->shark->SpawnTime = 7;
		Moveto->shark->StarveTime = 4;
		Moveto->shark->moved = currentCell->shark->moved;
		
	}
	else
	{
		Moveto->shark = currentCell->shark;
		currentCell->shark = 0;
	}
	
}
/**	@Name:		SharkUpdate
	@Brief:		This function updates tall the Sharks in the simulation. It controls the
				wrap around for the Sharks, sets the new positions of new Sharks and checks
				for possible Cells to occupy when Sharks are moving to new Cells.
	@Arguments:	Cell * currentCell ( A ponter to a Cell that the shark is currently in ), 
				Cell ** tempworld ( A ponter to a pointer of the simulation world where the Sharks and Fishes dwell ),
				int x ( An integer that represents the left and right cells of the grid ),
				int y ( An integer that represents the top and bottom cells of the grid ),
				int range ( An integer that represents the length and width of the world grid. )
	@Returns:	N/A.
*/
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
