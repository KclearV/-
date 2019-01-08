#include"define.h"

int valuechart[15] = { 0, 0, 0, 0, 0, 10, 10, 50, 50, 60, 500, 600, 700, 3000, 6666666 };
//{ 0, 0, 0, 5, 10, 12, 15, 50, 60, 80, 500, 600, 700, 30000, 6666666 };
//0 0 0 d1 1 d2 d2p 2 d3 d3p 3 d4 d4p 4 5

int White_valuechart[257] = {
	0,50,100,150,500,550,600,650,1000,1050,1100,   0,1500,1550,   0,   0,
//  0 01  10  11 100 101 110 111 1000 1001 1010 1011 1100 1101 1110 1111 

	600,  650,  700,  750, 1100, 1150, 1200,    0, 1600, 1650,    0,    0, 2100,    0,    0,    0,
//10000 10001 10010 10011 10100 10101 10110 10111 11000 11001 11010 11011 11100 11101 11110 11111
	1200,  1250,  1300,     0,  1700,  1750,     0,     0,  2200,0,0,0,0,0,0,0,
//100000 100001 100010 100011 100100 100101 100110 100111 101000 101001 101010 101011 101100 101101 101110 101111
	1800,  1850,     0,     0,  2300,     0,     0,     0,     0,0,0,0,0,0,0,0, //64
//110000 110001 110010 110011 110100 110101 110110 110111 111000 111001 111010 111011 111100 111101 111110 111111
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,//64
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,6000,
	66666 //65
};

int Black_valuechart[257] = {
	0,50,100,150,500,550,600,650,0,0,0,   0,0,0,   0,   0,
//  0 01  10  11 100 101 110 111      1000    1001     1010  1011    1100     1101 1110 1111 
	600,  650,  700,  750, 1100, 1150, 1200,    0, 0, 0,    0,    0, 2100,    0,    0,    0,
// 10000 10001 10010 10011 10100 10101 10110 10111 11000 11001 11010 11011 11100 11101 11110 11111
	   0,     0,0, 0,0,0,  0,    0,0,0,0,0,0,0,0,0,
//100000 100001 100010 100011 100100 100101 100110 100111 101000 101001 101010 101011 101100 101101 101110 101111
0,0,     0,   0,0,     0,     0,     0,     0,0,0,0,0,0,0,0, //64
//110000 110001 110010 110011 110100 110101 110110 110111 111000 111001 111010 111011 111100 111101 111110 111111
	6000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//64
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	66666 //256
};

// 00010 00020 00030 00040 00110 00120 00130 00200 00210 00220 00300 00310 00400
// 01010       10000 
int Direction[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };

/*#define FSP_5 14

#define FSP_4 13
#define FSP_d4p 12
#define FSP_d4 11

#define FSP_3 10
#define FSP_d3p 9
#define FSP_d3 8

#define FSP_2 7
#define FSP_d2p 6
#define FSP_d2 5

#define FSP_1 4
#define FSP_d1 3*/

int gameover(int player)
{
	int p = (player == 1 ? 1 : 0);			
	if (s[num-1].Shape == 256)
		return 1;
	if (p == 1)
	{
	if (s[num - 1].Shape >= 8 && s[num - 1].Shape <= 15)
		return -1;
	if (s[num - 1].Shape >= 24 && s[num - 1].Shape <= 63)
		return -1;
	if (s[num - 1].Shape >= 72 && s[num - 1].Shape <= 255)
		return -1;
	}
	return 0;
}

int SearchShape(int x,int y,int z,int player)
{
	//z=0,从左到右；z=1，从上到下；z=2，从左上到右下；z=3，从右上到左下
	int  x_1, y_1, shape = 0, i;//, x_2, y_2
	for (i = -4; i <= 4; i++)
	{
		shape <<= 2;
		x_1 = x + i*Direction[z][0];
		y_1 = y + i*Direction[z][1];
		/*x_2 = x - i*Direction[z][0];
		y_2 = y - i*Directin[z][1];
		if (x + i*Direction[z][0]<0||y + i*Direction[z][1] < 0 ||x + i*Direction[z][0]>14||y + i*Direction[z][1]>14
			|| map[x + i*Direction[z][0]][y + i*Direction[z][1]] == 3 - player)
			shape += 2 *power(3,(4 - i));
		else if (map[x + i*Direction[z][0]][y + i*Direction[z][1]] == player)
			shape += 1 *power(3,(4 - i));*/
		shape |= map[player][x_1][y_1];	
	}
	return shape;
}

int Coherentshape(int x)
{
	int shape = 0;
	switch (x){
		case 7:shape += 1; break;
		case 8:shape += 1; break;
		case 9:shape += 1<<2; break;
		case 10:shape += 1<<2; break;
		case 11:shape += 1<<4; break;
		case 12:shape += 1<<4; break;
		case 13:shape = 64; break;
		case 14:shape = 256; break;
	}
	return shape;
}

void EnhanceMap2(int x,int y,int player)
{
	int i, j, xx, yy, p, index,index_2;//k,,index_31, index_32
	p = (player == 1 ? 1 : 0);	
	for (j = -4; j < 5; j++)
	{
		for (i = 0; i < 4; i++)
		{
			xx = x + j*Direction[i][0] - 4;
			yy = y + j*Direction[i][1] - 4;
			if (map[0][xx + 4][yy + 4] != 0 || xx < 0 || yy < 0 || xx>14 || yy>14)
				continue;
			index = SearchShape(xx + 4, yy + 4, i, p);
			map_2[p][i][xx][yy] = Mshape[index];
			index_2 = SearchShape(xx + 4, yy + 4, i, 1 - p);
			map_2[1 - p][i][xx][yy] = Mshape[index_2];
			Changemap3(xx, yy, p);
		}
	}
}

void Changemap3(int x, int y,int player)
{
	int i, index=0, index_2=0;
	for (i = 0; i < 4; i++)
	{
		if (Coherentshape(map_2[player][i][x][y]) >= 256)
		{
			index = Coherentshape(map_2[player][i][x][y]);
			break;
		}
		index += Coherentshape(map_2[player][i][x][y]);
	}
	for (i = 0; i < 4; i++)
	{
		if (Coherentshape(map_2[1 - player][i][x][y]) >= 256)
		{
			index_2 = Coherentshape(map_2[1 - player][i][x][y]);
			break;
		}
		index_2 += Coherentshape(map_2[1 - player][i][x][y]);
	}
	map_3[player][x][y] = index;
	map_3[1-player][x][y] = index_2;
}

/*
int EvaLine(int shape1, int shape2)
{
	s[num].value_p = valuechart[Nshape[shape1][4]];
	return s[num].value_p +valuechart[Nshape[shape2][4]]/2;
}
*/
int Evaluate(int player)
{
	int j, k, value = 0, p;//i, 
	p = (player == 1 ? 1 : 0);
	
	for (j = 0; j < 15; j++)
	{
		for (k = 0; k < 15; k++)
		{
			//if (map_2[p][i][j][k] > 6)
			if (p == 1)
			{
				value += White_valuechart[map_3[p][j][k]] + v[j][k];//Black_valuechart[map_3[p][j][k]] + v[j][k];
			//if (map_2[1 - p][i][j][k] > 6)
				value -= White_valuechart[map_3[1 - p][j][k]] + v[j][k];
			}
			else {
				value += White_valuechart[map_3[p][j][k]] + v[j][k];
				//if (map_2[1 - p][i][j][k] > 6)
				value -= White_valuechart[map_3[1 - p][j][k]] + v[j][k];//Black_valuechart[map_3[1 - p][j][k]] + v[j][k];
			}
		}
	}
	//左右,gene_1,gene_2
	/*for (int i = 0; i < 9; i++)
	{
		gene_1 = Mshape[lr];
		gene_2 = map_2[player][0][x][y];
		if (gene_1 > gene_2)
		{
			value += valuechart[gene_1] - valuechart[gene_2];
			//map_2[player][0][x][y] = Nshape[lr][i];
		}
	}
	//上下
	for (int i = 0; i < 9; i++)
	{
		gene_1 = Mshape[ud];
		gene_2 = map_2[player][1][x][y];
		if (gene_1 > gene_2)
		{
			value += valuechart[gene_1] - valuechart[gene_2];
			//map_2[player][1][x][y] = Nshape[ud][i];
		}
	}
	//左上
	for (int i = 0; i < 9; i++)
	{
		gene_1 = Mshape[lu];
		gene_2 = map_2[player][2][x][y];
		if (gene_1 > gene_2)
		{
			value += valuechart[gene_1] - valuechart[gene_2];
			//map_2[player][2][x][y] = Nshape[lu][i];
		}
	}
	//右上
	for (int i = 0; i < 9; i++)
	{
		gene_1 = Mshape[ru];
		gene_2 = map_2[player][3][x][y];
		if (gene_1 > gene_2)
		{
			value += valuechart[gene_1] - valuechart[gene_2];
			//map_2[player][3][x][y] = Nshape[ru][i];
		}
	}

	for (i = 0; i < 4; i++)
	{

		Shp1 = SearchShape(x, y, i, player);
		Shp2 = SearchShape(x, y, i, 3 - player);
		value+=EvaLine(Shp1, Shp2);
	}*/

	return value;
}

int Evaluatepoints(int player,int x,int y)
{
	int value=0,p;//i,
	p = (player == 1 ? 1 : 0);
	//if (p == 1)
		value += /* +Black_valuechart[map_3[p][x-4][y-4]]*/White_valuechart[map_3[p][x - 4][y - 4]] +White_valuechart[map_3[1 - p][x-4][y-4]];
	//else
		//value += /* +*/Black_valuechart[map_3[1-p][x - 4][y - 4]] + White_valuechart[map_3[p][x - 4][y - 4]];

	return value+v[x-4][y-4];
}