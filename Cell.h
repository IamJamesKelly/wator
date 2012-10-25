#ifndef CELL_H
#define CELL_H
/**
*Intailize the structs used In the Program
*/
/**
*@param Struct Fish 
*Holds the Fish  data three int SpawnTime and moved.
*/
typedef struct{
int moved; 
int SpawnTime;
}Fish;
/**
*@param Struct Shark 
*Holds the shark data three int SpawnTime,StarveTime and moved.
*/
typedef struct{
int SpawnTime;
int StarveTime;
int moved;
}Shark;
/**
*@param Struct Cell 
*Holds the Cell Data a pointers to Shark Struct and Fish Struct.
*/
typedef struct{
Shark * shark;
Fish * fish;
}Cell;

/**
*@param Struct Move 
*
*/
typedef struct{
int left;
int right;
int up;
int down;
}Move;
#endif