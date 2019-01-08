#include"define.h"
#include"evaluate.h"

move VCFmove[50][20];
move Defender[50];

int value_cmp(const void *a, const void *b)
{
	//return (Node *)a->x - (Node *)b->x;   //错误写法！
	return  ((struct move *)b)->value - ((struct move *)a)->value;   //正确写法1
																					 //return (*(struct move *)a).x - (*(struct move *)b).x;     //正确写法2
}
void Place(int a, int b,int value)
{
	s[num].x = a;
	s[num].y = b;
	s[num].value = value;
	num++;
	if (num > 1) {
		for (int i = a - 2; i <= a + 2; i++)
		{
			for (int j = b - 2; j <= b + 2; j++)
			{
				if (i >= 4 && j >= 4 && i < 19 && j < 19)
					vst[i - 4][j - 4]++;
			}
		}
	}
	else
	{
		for (int i = a - 1; i <= a + 1; i++)
		{
			for (int j = b - 1; j <= b + 1; j++)
			{
				if (i >= 0 && j >= 0 && i < 15 && j < 15)
					vst[i - 4][j - 4]++;
			}
		}
	}/**///
}

void UnPlace(int a, int b)
{
	num--;
	s[num].x = 0;
	s[num].y = 0;
	s[num].value = 0;
	s[num].value_p = 0;	
	for (int i = a - 2; i <= a + 2; i++)
	{
		for (int j = b - 2; j <= b + 2; j++)
		{
			if (i >= 4 && j >= 4 && i < 19 && j < 19)
				vst[i-4][j-4]--;
		}
	}
}

void makemove(int player,int x,int y,int value)
{	
	int i, p = (player == 1 ? 1 : 0);
	Place(x, y,value);
 	map[p][x][y] = 1;
	map[1 - p][x][y] = 2;
	for (i = 0; i < 4; i++)
	{ 
		map_2[p][i][x - 4][y - 4] = 0;
		map_2[1-p][i][x - 4][y - 4] = 0;
	}
	s[num-1].Shape = map_3[p][x-4][y-4];
	map_3[p][x - 4][y - 4] = 0;
	map_3[1 - p][x - 4][y - 4] = 0;
	EnhanceMap2(x, y, player);
	ChangeHashKey(x, y,player);
	/*if (player == 1)
	{
		B_BoardValue += value;
	}
	else
	{
		W_BoardValue += value;
	}*/
}

void unmakemove(int player,int x, int y)
{
	/*if (player == 1)
	{
		B_BoardValue -= s[num-1].value;
	}
	else
	{
		W_BoardValue -= s[num-1].value;
	}*/
	UnPlace(x, y);
	map[0][x][y] = 0;
	map[1][x][y] = 0;
	EnhanceMap2(x, y, player);
	ChangeHashKey(x, y, player);
}

int Calstage(int x,int p)
{
	//成三
	
	if (p == 1)
	{
		if (x >= 8 && x <= 15)
			return 0;
		if (x >= 24 && x <= 63)
			return 0;
		if (x >= 72 && x <= 255)
			return 0;
	}/**/
	//活三
	if (x >= 4 && x < 16)
	{
		return 1;
	}
	//冲四
	if (x >= 16 && x < 64)
	{
		return 2;
	}
	//活四
	if (x >= 64&& x<256)
	{
		return 3;
	}
	//成五
	if (x >= 256)
		return 4;
	return 0;
}

void clearVCFmove(int j)
{
	for (int i = 0; i < 225; i++)
	{
		VCFmove[j][i].value = 0;
		VCFmove[j][i].x = -1;
		VCFmove[j][i].y = -1;
		VCFmove[j][i].stage = 0;
	}
}

void SearchVCF(int depth,int p)
{
	int i, j,n=0;
	clearVCFmove(depth);
	for(i=0;i<15;i++)
		for (j = 0; j < 15; j++)
		{
			if (p == 1)
			{

				if (map_3[p][i][j] >= 16 && map_3[p][i][j] < 24) 
				{
					VCFmove[depth][n].x = i + 4;
					VCFmove[depth][n].y = j + 4;
					n++;
				}
				if (map_3[p][i][j] >= 64 && map_3[p][i][j] < 72) 
				{
					VCFmove[depth][n].x = i + 4;
					VCFmove[depth][n].y = j + 4;
					n++;
				}
			}
			else
			{
				if (map_3[p][i][j] >= 16 && map_3[p][i][j] < 256)
				{
					VCFmove[depth][n].x = i + 4;
					VCFmove[depth][n].y = j + 4;
					n++;
				}
			}
		}
}

void SearchVCFdefender(int depth,int x, int y,int p)
{
	int i,j,xx,yy;
	for (j = -4; j < 5; j++)
	{
		for (i = 0; i < 4; i++)
		{
			xx = x + j*dir[i][0] - 4;
			yy = y + j*dir[i][1] - 4;			
			if (map_3[1-p][xx][yy] == 256)
			{
				Defender[depth].x = xx+4;
				Defender[depth].y = yy+4;
				Defender[depth].value = 66666;
				return;
			}
		}
	}
}

int Cal_VCFvalue(int p)
{
	int i, j, num = 0, op_num = 0;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (map_3[p][i][j]==256)
			{
				num++;
			}
			if (map_3[1-p][i][j]==256)
			{
				op_num++;
			}
		}
	}
	if (op_num >= 1)
		return -1;
	if (num >= 2)
		return 1;
	return 0;
}

int Check_VCF(int player,int x,int y,int v,int d)
{
	int i,p,val=0;
	p = (player == 1)?1:0;
	makemove(player, x, y, v);
	if ((val = LookUpVCFHashTable()) != 0)
	{
		unmakemove(player, x, y);
		return val;
	}
	if ((val = Cal_VCFvalue(p)) != 0)
	{
		unmakemove(player, x, y);
		AddValueToVCFHashTable(val, d);
		return val;
	}
	SearchVCFdefender(d,x,y,1-p);
	makemove(3-player, Defender[d].x, Defender[d].y, Defender[d].value);
	SearchVCF(d, p);
	for (i = 0; VCFmove[d][i].x != -1; i++)
	{
		/*
		if (map_3[p][VCFmove[d][i].x - 4][VCFmove[d][i].y - 4] >= 20 && map_3[p][VCFmove[d][i].x - 4][VCFmove[d][i].y - 4] < 24)
		{
			unmakemove(3 - player, Defender[d].x, Defender[d].y);
			unmakemove(player, x, y);
			AddValueToVCFHashTable(val, d);
			return 1;
		}
		if (p == 0)
		{
			if (map_3[p][VCFmove[d][i].x - 4][VCFmove[d][i].y - 4] >= 20 && map_3[p][VCFmove[d][i].x - 4][VCFmove[d][i].y - 4] < 64)
			{
				unmakemove(3 - player, Defender[d].x, Defender[d].y);
				unmakemove(player, x, y);
				AddValueToVCFHashTable(val, d);
				return 1;
			}
		}*/
		if (p == 1&& map_3[p][VCFmove[d][i].x - 4][VCFmove[d][i].y - 4] >= 24 && map_3[p][VCFmove[d][i].x - 4][VCFmove[d][i].y - 4] < 64)
		{
			continue;
		}
		//makemove(player, VCFmove[d][i].x, VCFmove[d][i].y, VCFmove[d][i].value);
		val = Check_VCF(player, VCFmove[d][i].x, VCFmove[d][i].y, VCFmove[d][i].value,d+1);
		if (val == 1)
			break;
		//unmakemove(player, VCFmove[d][i].x, VCFmove[d][i].y);
	}
	unmakemove(3 - player, Defender[d].x, Defender[d].y);
	AddValueToVCFHashTable(val, d);
	unmakemove(player, x, y);
	return val;
}

int searchmove(int player,int d)
{
	int n = 0, i, j, p, o_stage = 0,p_stage=0;
	p = (player == 1 ? 1 : 0);
	//double win;
	for (i = 4; i < 19; i++) 
	{
		for (j = 4; j < 19; j++)
		{
			if (map[0][i][j] == 0 && vst[i - 4][j - 4] > 0)
			{
				//e1 = eval(player) - eval(3 - player);
				//makemove(player, i, j);
				//e2= eval(player) - eval(3 - player);
				//player = 3 - player;
				//if (abs(e2 - e1) > 10||num<3)
				//{
				Moves[d][n].x = i;
				Moves[d][n].y = j;
				//Moves[d][n].value = e2;
				//map[p][i][j] = 1;
				//map[1-p][i][j] = 2;
				//EnhanceMap2(i,j,player);
				/*Moves[d][n].LeftRight = SearchShape(i, j, 0, player);
				Moves[d][n].UpDown = SearchShape(i, j, 1, player);
				Moves[d][n].LeftUp = SearchShape(i, j, 2, player);
				Moves[d][n].RightUp = SearchShape(i, j, 3, player);	*/
				Moves[d][n].value = Evaluatepoints(player, i, j);
				Moves[d][n].stage = Calstage(map_3[p][i - 4][j - 4],p);
				if (Moves[d][n].stage == 4)
				{
					p_stage = 4;
					Moves[d][0] = Moves[d][n];
					return 1;
				}
				Moves[d][n].ostage = Calstage(map_3[1 - p][i - 4][j - 4], 1 - p);			
				if (o_stage < Moves[d][n].ostage)
					o_stage = Moves[d][n].ostage;
				if (p_stage < Moves[d][n].stage)
					p_stage = Moves[d][n].stage;
				//map[0][i][j] = 0;
				//map[1][i][j] = 0;
				//EnhanceMap2(i, j, player);
				
				//}
				//unmakemove(player, i, j);
				//player = 3 - player;
				n++;
			}
		}
	}
	
	if (p_stage == 4)
	{
		for (int i = 1; i >= 1; i++)
		{
			if (Moves[d][i].x == -1)
				break;
			Moves[d][i].value = -99999999;
			Moves[d][i].x = -1;
			Moves[d][i].y = -1;
		}
	}
	else if (o_stage == 4)
	{
		for (int i = 0; i < n; i++)
		{
			if (Moves[d][i].stage < 4 & Moves[d][i].ostage < 4)
			{
				Moves[d][i].value = -99999999;
				Moves[d][i].x = -1;
				Moves[d][i].y = -1;
			}
		}
	}
	else if (p_stage == 3)
	{
		for (int i = 0; i < n; i++)
		{
			if (Moves[d][i].stage < 3 & Moves[d][i].ostage < 4)
			{
				Moves[d][i].value = -99999999;
				Moves[d][i].x = -1;
				Moves[d][i].y = -1;
			}
		}
	}
	else if (o_stage == 3)
	{
		for (int i = 0; i < n; i++)
		{
			if (Moves[d][i].stage < 2 & Moves[d][i].ostage < 3)
			{
				Moves[d][i].value = -99999999;
				Moves[d][i].x = -1;
				Moves[d][i].y = -1;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if ((o_stage > Moves[d][i].stage + 1&& o_stage > Moves[d][i].ostage + 1)||(p_stage> Moves[d][i].stage+1 && p_stage > Moves[d][i].ostage + 1))
		{
			Moves[d][i].value = -99999999;
			Moves[d][i].x = -1;
			Moves[d][i].y = -1;
		}
	}/*
	if (o_stage > Moves[d][i].stage + 1 || (o_stage == 4 && Moves[d][i].stage != 4))//
	{
		Moves[d][i].value = -99999999;
		Moves[d][i].x = -1;
		Moves[d][i].y = -1;
	}*/	
	qsort(Moves[d], n, sizeof(Moves[d][0]), value_cmp);
	for (int i = 0; i>=0; i++)
	{
		if (Moves[d][i].x == -1)
			return i;
	}
	//win = (Moves[d][0].value - Moves[d][n - 1].value) *0.01;
		//num<85?(Moves[d][0].value-Moves[d][n - 1].value) / (10-num*0.1):((Moves[d][0].value-Moves[d][n - 1].value) / 1.5);
	
	/*for (i = 0; i < n; i++)
	{
		if(Moves[d][i].value<win+Moves[d][n-1].value)
		{
			Moves[d][i].value = 0;
			Moves[d][i].x = -1;
			Moves[d][i].y = -1;
		}
	}*/
	return n;
}

void clearmove(int j)
{
	for (int i = 0; i < 225; i++)
	{
		Moves[j][i].value = 0;
		Moves[j][i].x = -1;
		Moves[j][i].y = -1;
		Moves[j][i].stage = 0;
	}
}

void ClearMove()
{
	for (int i = 0; i < 225; i++)
	{
		MaxMoves[i].value = 0;
		MaxMoves[i].x = -1;
		MaxMoves[i].y = -1;
	}
}