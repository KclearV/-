#include"define.h"
#include"evaluate.h"

int cmp(const void *a, const void *b)
{
	//return (Node *)a->x - (Node *)b->x;   //����д����
	return  ((struct move *)b)->history_value - ((struct move *)a)->history_value;   //��ȷд��1
																	 //return (*(struct move *)a).x - (*(struct move *)b).x;     //��ȷд��2
}

int alphabeta(int depth, int alpha, int beta, int player)
{
	int l = dep - depth + 1, i, p, val, go, checkVCF;//, best
	int  best_num = -1;	
	bool fFoundPV = false;	

	p = (player == 1) ? 1 : 0;
	go = gameover(3 - player);
	if (go == 1)
		return -6666666 - depth;
	if (go == -1)
		return 6666666 + depth;
	if (depth <= 0)
	{
		val = Evaluate(player);
		return val;
	}

	clearmove(l);
	int cnt = searchmove(player, l);
	for (i = 0; Moves[l][i].x != -1; i++) {
		Moves[l][i].history_value = history[player][Moves[l][i].x-4][Moves[l][i].y-4];
	}
	qsort(Moves[l], cnt, sizeof(Moves[l][0]), cmp);

	for (i = 0; Moves[l][i].x != -1; i++)//i<45&&
	{
		/**/if (map_3[p][Moves[l][i].x - 4][Moves[l][i].y - 4] >= 16 && map_3[p][Moves[l][i].x - 4][Moves[l][i].y - 4] < 256)
		{
			checkVCF = Check_VCF(player, Moves[l][i].x, Moves[l][i].y, Moves[l][i].value, 0);
			if (checkVCF == 1)
			{
				//unmakemove(player, Moves[l][i].x, Moves[l][i].y);
				return 6666666;
			}
		}
		makemove(player, Moves[l][i].x, Moves[l][i].y, Moves[l][i].value);
		player = 3 - player;
		if (fFoundPV) // �ҵ���Ҫ���� 
		{			
			val = -alphabeta(depth - 1, -alpha - 1, -alpha, player);	// �մ�̽�� 
			if ((val > alpha) && (val < beta)) {						// ̽��ʧ��, ȫ�������� 
				val = -alphabeta(depth - 1, -beta, -alpha, player);
			}
		}
		else // û����Ҫ����, ȫ�������� 
		{					
			val = -alphabeta(depth - 1, -beta, -alpha, player);
		}	
		player = 3 - player;
		unmakemove(player, Moves[l][i].x, Moves[l][i].y);
		if (val >= beta) {		// beta��֦ 
			best_num = i;				// ��¼�õ��з� - ������֦���з� 
			history[player][Moves[l][best_num].x-4][Moves[l][best_num].y-4] += (2 << depth);
			return beta;
		}

		if (val > alpha) {		// �������ֵ 
			fFoundPV = true;			// �ҵ���Ҫ���� 
			alpha = val;				// �޸�alpha�߽� 
			best_num = i;				// ��¼�õ��з� - �����ֵܽ�������з� 
		}			
	}
	clearmove(l);
	if (best_num != -1)
	{
		history[player][Moves[l][best_num].x-4][Moves[l][best_num].y-4] += (2 << depth);
	}
	return alpha;
}


/*
int alphabeta(int depth, int alpha, int beta, int player)
{
	int l = dep - depth + 1, i, p, va, go, checkVCF;//, best
	bool fFoundPV = false;
	p = (player == 1) ? 1 : 0;
	//int hashf = HashfAlpha;
	go = gameover(3 - player);
	if (go == 1)
		return -6666666 - depth;
	if (go == -1)
		return 6666666 + depth;
	/*
	//if ((va = LookUpHashTable(depth, alpha, beta)) != 99999999) {
	//��valUNKNOWN����С��-INFINITY�����INFINITY������������ֵ��������
	//		return va;
	//}
	if (depth == 0)
	{
		sum++;
		index++;
		/*if (player == 1)
		va = B_BoardValue- W_BoardValue;
		else
		va = W_BoardValue- B_BoardValue;
		va = Evaluate(player);
		//if(va>=666666)
		//printf("%d %d %d\n", va, s[num-1].x, s[num-1].y);
		//AddValueToHashTable(va, depth);//, HashfExact
		return va;
		//return eva(player, x, y) -eva(3-player, x, y) - depth;
	}
	clearmove(l);
	searchmove(player, l);
	//�������
	/*
	makemove(player, Moves[l][0].x, Moves[l][0].y);
	player = 3 - player;
	best = -alphabeta(depth - 1, -beta, -alpha, player);
	player = 3 - player;
	unmakemove(player, Moves[l][0].x, Moves[l][0].y);
	//����ֵ 
	for (i = 0; Moves[l][i].x != -1; i++)//i<45&&
	{
		//if (best < beta)
		//{
		index_am++;
		//if (best > alpha)
		//alpha = best;

		if (map_3[p][Moves[l][i].x - 4][Moves[l][i].y - 4] >= 16 && map_3[p][Moves[l][i].x - 4][Moves[l][i].y - 4]<256)
		{
			checkVCF = Check_VCF(player, Moves[l][i].x, Moves[l][i].y, Moves[l][i].value, 0);
			if (checkVCF == 1)
			{
				//unmakemove(player, Moves[l][i].x, Moves[l][i].y);
				return 6666666;
			}
		}/*
		makemove(player, Moves[l][i].x, Moves[l][i].y, Moves[l][i].value);
		player = 3 - player;
		va = -alphabeta(depth - 1, -beta, -alpha, player);
		/*if (va >= beta) {
			//AddValueToHashTable(beta, depth);//,HashfBeta
			player = 3 - player;
			unmakemove(player, Moves[l][i].x, Moves[l][i].y);
			return beta;
		}
		if (va > alpha) {
			alpha = va;
			//hashf = HashfAlpha;
		}
		player = 3 - player;
		unmakemove(player, Moves[l][i].x, Moves[l][i].y);
		/*}
		if (va > alpha&&va < beta)
		{
		best = -alphabeta(depth - 1, -beta, -va, player);
		AddValueToHashTable(best, depth);
		}
		else if (va > best)
		{
		best = va;
		}
		//}
	}
	//AddValueToHashTable(alpha, depth);//, hashf
	clearmove(l);
	return alpha;
}
*/