#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <winsock2.h>
#include"inttypes.h"
#define dep 10
#define HashfExact 0
#define HashfAlpha 1
#define HashfBeta 2

//define

struct move
{
	int x, y, value, stage,ostage;
	int history_value;
	//int LeftUp, LeftRight, RightUp, UpDown;
};

extern move Moves[15][255];

extern int sum;
extern int num;
extern int starttime;
extern int endtime;
extern int index;
extern int index_am;
extern int map[2][23][23];
extern int map_2[2][4][15][15];
extern int map_3[2][15][15];
extern int history[3][15][15];
extern int vst[15][15];
extern int v[15][15];
extern int dir[4][2];

struct counter
{
	int x, y, step, value,value_p;
	int Shape;
};



extern counter s[255];
extern move MaxMoves[255];

//RenjuShapeChart
//extern uint8_t Nshape[19683][9];
extern uint8_t Mshape[262144];

//makemove
int cmp(const void *a, const void *b);
void Place(int a, int b,int value);
void UnPlace(int a, int b);
void makemove(int player,int x,int y,int value);
void unmakemove(int player, int x, int y);
int searchmove(int player,int d); 
void clearmove(int j);

//alphabeta
int alphabeta(int depth, int alpha, int beta, int player);

//Hash
extern __int64 Z[3][15][15];
extern __int32 HashKey32[3][15][15];
extern __int32 TableNum;
extern __int64 MapSitu;
__int64 rand64();
void InitHash();
void ChangeHashKey(int, int, int);
int LookUpHashTable(int, int, int);
int LookUpVCFHashTable();
void AddValueToHashTable(int, int);//,int
void AddValueToVCFHashTable(int, int);//,int hashf

//Evaluate
extern int W_BoardValue;
extern int B_BoardValue;
//int eva(int player, int x, int y);
int Evaluate(int player);
int SearchShape(int , int , int , int);
void EnhanceMap2(int , int , int);
int Evaluatepoints(int , int , int);
void Changemap3(int , int , int);
int Check_VCF(int , int , int , int ,int);