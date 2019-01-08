#include"define.h"
/*
int pts(int p, int r, int m)
{
	if (p == 2 && r == 1)
		return 10;
	if (p == 2 && r == 0)
	{
		if (m == 0)
			return 60;
		else
			return 50;
	}
	if (p == 3 && r == 1)
		return 50;
	if (p == 3 && r == 0)
	{
		if (m == 0)
			return 500;
		else
			return 400;
	}
	if (p == 4 && r == 1)
		return 600;
	if (p == 4 && r == 0)
	{
		if (m == 0)
			return 3000;
		else
			return 700;
	}
	if (p == 5 && m == 0)
		return 6666666;
	return 0;
}

int eva(int player,int x,int y)
{
	int i,l,sum=0,box[3],vbox[3],xi,yi,mark1,mark2,m1,m2,s1,s2;
	for (i = 0; i < 4; i++)//四个方向搜
	{
		memset(box, 0, sizeof(box));
		box[0] = 1;
		for (l = 1,mark1=0; l <= 5; l++)
		{
			xi = x + dir[i][0]*l;
			yi = y + dir[i][1]*l;
			if (xi < 0 || xi>14 || yi < 0 || yi>14)
			{
				box[1]++;
				break;
			}
			else if (map[xi][yi] == player)
				box[0]++;
			else
			{
				if (map[xi][yi] == 3 - player)
					box[1]++;
				else if (map[xi + dir[i][0]][yi + dir[i][1]] == player&&mark1==0)
						mark1 = l+1;
				break;
			}
		}
		for (l = 1,mark2=0; l <= 5; l++)
		{
			xi = x - dir[i][0]*l;
			yi = y - dir[i][1]*l;
			if (xi < 0 || xi>14 || yi < 0 || yi>14)
			{
				box[1]++;
				break;
			}
			else if (map[xi][yi] == player)
				box[0]++;
			else
			{
				if (map[xi][yi] == 3 - player)
					box[1]++;
				else if (map[xi - dir[i][0]][yi - dir[i][1]] == player&&mark1 == 0)
						mark2 = l+1;
				break;
			}
		}
		if (mark1 >0)
		{
			box[2] = 1;s1 = 0;
			for (m1 = mark1; m1-mark1<6; m1++)
			{
				xi = x + dir[i][0] * m1;
				yi = y + dir[i][1] * m1;
				if (xi < 0 || xi>14 || yi < 0 || yi>14)
				{
					box[1]++;
					break;
				}
				else if (map[xi][yi] == player&&box[0]+s1<4)
					s1++;
				else
				{
					if (map[xi][yi] == 3 - player)
						box[1]++;
					break;
				}
			}
			sum += pts(box[0]+s1, box[1], box[2]);
		}
		if (mark2 >0)
		{
			box[2] = 1; s2 = 0;
			for (m2 = mark2; m2 - mark2<6; m2++)
			{
				xi = x - dir[i][0] * m2;
				yi = y - dir[i][1] * m2;
				if (xi < 0 || xi>14 || yi < 0 || yi>14)
				{
					box[1]++;
					break;
				}
				else if (map[xi][yi] == player&&box[0] + s2<4)
					s2++;
				else
				{
					if (map[xi][yi] == 3 - player)
						box[1]++;
					break;
				}
			}
			sum += pts(box[0] + s2, box[1], box[2]);
		}
		if(!mark1&&!mark2)
			sum += pts(box[0], box[1], box[2]);

		memset(vbox, 0, sizeof(vbox));
		vbox[0] = 1;
		for (l = 1, mark1 = 0; l <= 5; l++)
		{
			xi = x + dir[i][0] * l;
			yi = y + dir[i][1] * l;
			if (xi < 0 || xi>14 || yi < 0 || yi>14)
			{
				vbox[1]++;
				break;
			}
			else if (map[xi][yi] ==3 - player)
				vbox[0]++;
			else
			{
				if (map[xi][yi] == player)
					vbox[1]++;
				else if (map[xi + dir[i][0]][yi + dir[i][1]] == 3-player&&mark1 == 0)
					mark1 = l + 1;
				break;
			}
		}
		for (l = 1, mark2 = 0; l <= 5; l++)
		{
			xi = x - dir[i][0] * l;
			yi = y - dir[i][1] * l;
			if (xi < 0 || xi>14 || yi < 0 || yi>14)
			{
				vbox[1]++;
				break;
			}
			else if (map[xi][yi] ==3-player)
				vbox[0]++;
			else
			{
				if (map[xi][yi] == player)
					vbox[1]++;
				else if (map[xi - dir[i][0]][yi - dir[i][1]] == 3-player&&mark1 == 0)
					mark2 = l + 1;
				break;
			}
		}
		if (mark1 >0)
		{
			vbox[2] = 1; s1 = 0;
			for (m1 = mark1; m1 - mark1<6; m1++)
			{
				xi = x + dir[i][0] * m1;
				yi = y + dir[i][1] * m1;
				if (xi < 0 || xi>14 || yi < 0 || yi>14)
				{
					vbox[1]++;
					break;
				}
				else if (map[xi][yi] == 3-player&&vbox[0] + s1<4)
					s1++;
				else
				{
					if (map[xi][yi] == player)
						vbox[1]++;
					break;
				}
			}
			sum += pts(vbox[0] + s1, vbox[1], vbox[2]);
		}
		if (mark2 >0)
		{
			vbox[2] = 1; s2 = 0;
			for (m2 = mark2; m2 - mark2<6; m2++)
			{
				xi = x - dir[i][0] * m2;
				yi = y - dir[i][1] * m2;
				if (xi < 0 || xi>14 || yi < 0 || yi>14)
				{
					vbox[1]++;
					break;
				}
				else if (map[xi][yi] == 3-player&&vbox[0] + s2<4)
					s2++;
				else
				{
					if (map[xi][yi] ==player)
						vbox[1]++;
					break;
				}
			}
			sum += pts(vbox[0] + s2, vbox[1], vbox[2]);
		}
		if (!mark1 && !mark2)
			sum += pts(vbox[0], vbox[1], vbox[2]);
	}
	sum += v[x][y];
	return sum;
}*/