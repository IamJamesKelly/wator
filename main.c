#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cell.h"
#include "Fish.h"
#include "Shark.h"
#include <sys/timeb.h>
#include <omp.h>
#include <string.h>

/**
*Make2dArray
* -Create 2-d Array in memory
*@param  int rows 
*	-Rows of in array.
*@param  int cols 
*	-CoLs of in array.
*@return Cell ** array
* 	-return 2-D pointer cell Array
*/
Cell ** Make2dArray(int row,int col)
{
	Cell ** array;
	array = (Cell**) malloc(row*sizeof(Cell*));  
	int i = 0;
	for (i = 0; i < row; i++)  
		array[i] = (Cell*) malloc(col*sizeof(Cell));  
   return array;  
}
/**
*randomEmptyCell
* -Picks Random Empty Cell
*@param  Cell ** world
*	-2-D world array.
*@param  int rows 
*	-Rows of in array.
*@param  int cols 
*	-Cols of in array.
*@return Cell * &world[randomRow][randomCol]
* 	-return pointer to empty cell from Array
*/
Cell * randomEmptyCell(Cell ** world,int row,int col)
{
	int randomCol = rand() % row;
	int randomRow = rand() % col;

	while(world[randomRow][randomCol].fish != 0 && world[randomRow][randomCol].shark != 0)
	{
		randomCol = rand() % row;
		randomRow = rand() % col;
	}
	return &world[randomRow][randomCol] ;
}
/**
*PopulateWorld
* -Populates the World array
*@param  int nFish 
*	-Number of fish to create.
*@param  int rows 
*	-Rows of in array.
*@param  int cols 
*	-CoLs of in array.
*@param  Cell ** world
*	-2-D world array.
*/
void PopulateWorld(int nFish,int nSharks,int rows, int cols,Cell ** world)
{
	int i;

	Cell * p;
	for (i = 0; i < nFish; ++i)
	{
		p = randomEmptyCell(world,rows,cols);
		p->fish =  malloc(sizeof(Fish));
		p->fish->moved = -1;
		p->fish->SpawnTime=3;
	}
	int j;
	
  
	for (j = 0; j < nSharks; ++j)
	{
		p = randomEmptyCell(world,rows,cols);
		p->shark =  malloc(sizeof(Shark));
		p->shark->moved = -1;
		p->shark->SpawnTime = 4;
		p->shark->StarveTime = 3;
	}
}
void loopMain(int run,int scale)
{

	FILE * file; 
	file = fopen("WatorData.txt","a+");
	fprintf(file,"%s","{ Name:");
	fprintf(file, "%d",run);
	fprintf(file,"%s",",");
	fprintf(file,"%s","\nType:Serial,");
	
	srand(time(NULL));

	int Gridsize = 10 * scale;


	int FishPop = 30 * scale;

	int SharkPop = 30 * scale;

	Cell ** world = Make2dArray(Gridsize,Gridsize);

	PopulateWorld(FishPop,SharkPop,Gridsize,Gridsize,world);
	
	int i;
	int j;
	int k;
	int Year = 0;
	int YearReached= 0;
	int endYear = 100;
	struct timeval tim;  
  	gettimeofday(&tim, NULL);  
   	double dTime1 = tim.tv_sec+(tim.tv_usec/1000000.0); 

	SharkPop = 0;				
	FishPop = 0;
		
		
	while(Year < endYear)
	{
		
		//To switch between two parallel versions of code do the following:
		// Uncomment 	//#pragma omp parallel firstprivate(world,i,j)
		// Comment out the #pragma omp for imediatly after it.	

		//#pragma omp parallel firstprivate(world,i,j)
		{
			#pragma omp for
			for(i=0; i < Gridsize;i++)
			{
				#pragma omp for
				for(j=0; j < Gridsize;j++)
				{
					if(world[i][j].shark != 0 && world[i][j].shark->moved != Year)
					{
					
						world[i][j].shark->moved = Year;
						SharkUpdate(&world[i][j], world, i, j, (Gridsize - 1));
						
					}
					if(world[i][j].shark != 0)
					{
						if(world[i][j].fish != 0)
						{
							world[i][j].shark->StarveTime = 4;
							world[i][j].fish =0;
							FishPop--;
						}
						if(world[i][j].shark->StarveTime <= 0)
						{
							world[i][j].shark = 0;
							SharkPop--;
						}
						
						SharkPop++;
					}
					else if(world[i][j].fish != 0)
					{
						
						FishPop++;
					}
					if(world[i][j].fish != 0 && world[i][j].fish->moved != Year){
						world[i][j].fish->moved = Year;
						FishUpdate(&world[i][j], world, i, j, (Gridsize - 1));
					}
				}
			}
		}
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		#pragma omp for
		for(k=0; k < Gridsize * Gridsize;k++)
            	{
                i = k / Gridsize;
                j = k % Gridsize;

				if(world[i][j].shark != 0)
					fputs("S",stdout);
				else if(world[i][j].fish != 0)
					fputs("F",stdout);
				else 
					fputs("-",stdout);
		if(j == Gridsize-1)
			printf("\n");
	     	}
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		Year++;
		YearReached++;
		if(SharkPop == 0 || FishPop == 0)
		{
			Year = endYear;
		}	
	}
	printf("\n");

	printf("%i ", SharkPop);
	printf("%i\n", FishPop);
		
	printf("%s\n\n\n\n","endrun" );
	gettimeofday(&tim, NULL);  

    double dTime2 = tim.tv_sec+(tim.tv_usec/1000000.0); 

	double Sec = (dTime2 - dTime1); 


	double fps = (double)YearReached/Sec;

	fprintf(file,"%s","\nTimeTaken: ");
	fprintf(file, "%f",Sec );
	fprintf(file,"%s",",\nFramesPerSecond: ");
	fprintf(file, "%f",fps );
	fprintf(file,"%s",",\nGridsize: ");	
	fprintf(file, "%d",Gridsize );
	fprintf(file,"%s",",\nYear: ");	
	fprintf(file, "%d",YearReached );
	fprintf(file,"%s",",\nTargetYear: ");	
	fprintf(file, "%d",endYear );
	fprintf(file,"%s"," } \n\n\n");	
//	for (i = 0; i < Gridsize; i++){  
//	free( world [i]);  
//	}	  
//	free(world); 
	fclose(file);

}
int main()
{
	int tread = 12;
	int scale = 50;
	loopMain(tread,scale);
}
