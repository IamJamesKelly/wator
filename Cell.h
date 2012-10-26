#ifndef CELL_H
#define CELL_H
/**
*Intailize the structs used In the Program
*/
/**
*@Name: Struct Fish 
*@Brief: Holds the Fish  data three int SpawnTime and moved.
*/
typedef struct{
int moved; 
int SpawnTime;
}Fish;
/**
*@Name: Struct Shark 
*@Brief:Holds the shark data three int SpawnTime,StarveTime and moved.
*/
typedef struct{
int SpawnTime;
int StarveTime;
int moved;
}Shark;
/**
*@Name: Struct Cell 
*@Brief:Holds the Cell Data a pointers to Shark Struct and Fish Struct.
*/
typedef struct{
Shark * shark;
Fish * fish;
}Cell;

/**
*@Name: Struct Move 
*@Brief: hold Four Int left,right,Up and Down of value 1 or 0
*/
typedef struct{
int left;
int right;
int up;
int down;
}Move;
#endif