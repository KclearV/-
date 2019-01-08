#include"define.h"

__int64 Z[3][15][15];
__int32 HashKey32[3][15][15];

__int32 TableNum;
//旋转90' 180' 270'
__int32 TableNum_1;
__int32 TableNum_2;
__int32 TableNum_3;
//对称棋型及旋转90' 180' 270'
__int32 TableNum_4;
__int32 TableNum_5;
__int32 TableNum_6;
__int32 TableNum_7;

__int64 MapSitu;
__int64 MapSitu_1;
__int64 MapSitu_2;
__int64 MapSitu_3;
__int64 MapSitu_4;
__int64 MapSitu_5;
__int64 MapSitu_6;
__int64 MapSitu_7;

typedef struct HASHITEM {
	__int64 checksum;
	int depth;
	int value;
	int flag;
}HashItem;

HashItem TransTable[1024 * 1024];
HashItem VCFTable[1024 * 1024];

__int64 rand64()
{
	return rand() ^ ((__int64)rand() << 15) ^ ((__int64)rand() << 30) ^ ((__int64)rand() << 45) ^ ((__int64)rand() << 60);
}  
__int32 rand32()
{
	return rand() ^ ((__int64)rand() << 15) ^ ((__int64)rand() << 30) ;
}

void InitHash()
{
	int i, j, k;
	//初始值
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 15; j++)
		{
			for (k = 0; k < 15; k++)
			{
				Z[i][j][k] = rand64();
				HashKey32[i][j][k] = rand32();
				TableNum ^= HashKey32[i][j][k];
				MapSitu ^= Z[i][j][k];
			}
		}
	}
	//上下对称
	/*for (i = 0; i < 3; i++)
	{
		for (j = 1; j <8;j++ )
		{
			for (k = 0; k < 15; k++)
			{
				Z[i][7+j][k] = Z[i][7 - j][k];
				HashKey32[i][7+j][k] = HashKey32[i][7-j][k];
			}
		}
	}
	//左右对称
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j <15; j++)
		{
			for (k = 1; k < 8; k++)
			{
				Z[i][j][7+k] = Z[i][j][7-k];
				HashKey32[i][j][7 + k] = HashKey32[i][j][7 - k];
			}
		}
	}
	
	//左斜对称
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j <14; j++)
		{
			for (k = j+1; k < 15; k++)
			{
				Z[i][j][k] = Z[i][k][j];
				HashKey32[i][j][k] = HashKey32[i][k][j];
			}
		}
	}
	//右斜对称
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j <14; j++)
		{
			for (k = 0; k <= 14-j; k++)
			{
				Z[i][j][14-j-k] = Z[i][j+k][14-j];
				HashKey32[i][j][14 - j - k] = HashKey32[i][j + k][14 - j];
			}
		}
	}*/
	
	//初始键值	

	TableNum_1 = TableNum;
	TableNum_2 = TableNum;
	TableNum_3 = TableNum;
	TableNum_4 = TableNum;
	TableNum_5 = TableNum;
	TableNum_6 = TableNum;
	TableNum_7 = TableNum;

	MapSitu_1 = MapSitu;
	MapSitu_2 = MapSitu;
	MapSitu_3 = MapSitu;
	MapSitu_4 = MapSitu;
	MapSitu_5 = MapSitu;
	MapSitu_6 = MapSitu;
	MapSitu_7 = MapSitu;
}

void ChangeHashKey(int x,int y,int player)
{
	TableNum ^= HashKey32[player][x][y];
	/*
	TableNum_1 ^= HashKey32[player][y][14 - x];
	TableNum_2 ^= HashKey32[player][14-x][14-y];
	TableNum_3 ^= HashKey32[player][14-y][x];
	
	TableNum_4 ^= HashKey32[player][y][x];
	TableNum_5 ^= HashKey32[player][x][14-y];
	TableNum_6 ^= HashKey32[player][14-y][14-x];
	TableNum_7 ^= HashKey32[player][14-x][y];*/

	MapSitu ^= Z[player][x][y]; 
	/*
	MapSitu_1 ^= Z[player][y][14 - x];
	MapSitu_2 ^= Z[player][14 - x][14 - y];
	MapSitu_3 ^= Z[player][14 - y][x];

	MapSitu_4 ^= Z[player][y][x];
	MapSitu_5 ^= Z[player][x][14 - y];
	MapSitu_6 ^= Z[player][14 - y][14 - x];
	MapSitu_7 ^= Z[player][14 - x][y];*/
}

int LookUpHashTable(int depth,int alpha,int beta)
{
	__int64 CheckSum = MapSitu;
	/*__int64 CheckSum1 = MapSitu_1;
	__int64 CheckSum2 = MapSitu_2;
	__int64 CheckSum3 = MapSitu_3;
	__int64 CheckSum4 = MapSitu_4;
	__int64 CheckSum5 = MapSitu_5;
	__int64 CheckSum6 = MapSitu_6;
	__int64 CheckSum7 = MapSitu_7;*/

	int tablenum = TableNum & 0xFFFFF;
	/*int tablenum1 = TableNum_1 & 0xFFFFF;
	int tablenum2 = TableNum_2 & 0xFFFFF;
	int tablenum3 = TableNum_3 & 0xFFFFF;
	int tablenum4 = TableNum_4 & 0xFFFFF;
	int tablenum5 = TableNum_5 & 0xFFFFF;
	int tablenum6 = TableNum_6 & 0xFFFFF;
	int tablenum7 = TableNum_7 & 0xFFFFF;*/

	
	if (TransTable[tablenum].checksum == CheckSum)
	{
		if (depth > TransTable[tablenum].depth)
			return 99999999;
		return TransTable[tablenum].value;/*
		else
		{
			if (TransTable[tablenum].flag == HashfExact)
			{
			}
			if ((TransTable[tablenum].flag == HashfAlpha) && (TransTable[tablenum].value <= alpha))
			{
				return alpha;
			}
			if ((TransTable[tablenum].flag == HashfBeta) && (TransTable[tablenum].value >= beta))
			{
				return beta;
			}
		}*/
	}/*
	else if (TransTable[tablenum1].checksum == CheckSum1)
	{
		if (depth > TransTable[tablenum1].depth)
			return 99999999;
		else
			return TransTable[tablenum1].value;
	}
	else if (TransTable[tablenum2].checksum == CheckSum2)
	{
		if (depth > TransTable[tablenum2].depth)
			return 99999999;
		else
			return TransTable[tablenum2].value;
	}
	else if (TransTable[tablenum3].checksum == CheckSum3)
	{
		if (depth > TransTable[tablenum3].depth)
			return 99999999;
		else
			return TransTable[tablenum3].value;
	}
	else if (TransTable[tablenum4].checksum == CheckSum4)
	{
		if (depth > TransTable[tablenum4].depth)
			return 99999999;
		else
			return TransTable[tablenum4].value;
	}
	else if (TransTable[tablenum5].checksum == CheckSum5)
	{
		if (depth > TransTable[tablenum5].depth)
			return 99999999;
		else
			return TransTable[tablenum5].value;
	}
	else if (TransTable[tablenum6].checksum == CheckSum6)
	{
		if (depth > TransTable[tablenum6].depth)
			return 99999999;
		else
			return TransTable[tablenum6].value;
	}
	else if (TransTable[tablenum7].checksum == CheckSum7)
	{
		if (depth > TransTable[tablenum7].depth)
			return 99999999;
		else
			return TransTable[tablenum7].value;
	}*/
	else
		return 99999999;
}

void AddValueToHashTable(int value,int depth)//,int hashf
{
	int tablenum = TableNum & 0xFFFFF;
	TransTable[tablenum].checksum = MapSitu;
	TransTable[tablenum].value = value;
	TransTable[tablenum].depth = depth;
	//TransTable[tablenum].flag = hashf;
}


int LookUpVCFHashTable()
{
	__int64 CheckSum = MapSitu;
	int tablenum = TableNum & 0xFFFFF;

	if (VCFTable[tablenum].checksum == CheckSum)
	{
		if (VCFTable[tablenum].value == 1)
			return 1;
		else if (VCFTable[tablenum].value == -1)
			return -1;
		else
			return 0;
	}
	return 0;
}

void AddValueToVCFHashTable(int value, int depth)//,int hashf
{
	int tablenum = TableNum & 0xFFFFF;
	VCFTable[tablenum].checksum = MapSitu;
	VCFTable[tablenum].value = value;
	VCFTable[tablenum].depth = depth;
	//TransTable[tablenum].flag = hashf;
}