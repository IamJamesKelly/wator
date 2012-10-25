#ifndef CELL_H
#define CELL_H

typedef struct{
int moved; 
int SpawnTime;
}Fish;

typedef struct{
int SpawnTime;
int StarveTime;
int moved;
}Shark;

typedef struct{
Shark * shark;
Fish * fish;
}Cell;

typedef struct{
int left;
int right;
int up;
int down;
}Move;
#endif