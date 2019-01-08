#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"define.h"
#include"evaluate.h"
#include<fstream>
#include<iostream>
using namespace std;


int  Ult_x, Ult_y;
char p[20] = { 0 };
FILE *fpcyj;
//fpcyj = NULL;
//ofstream out("C5-先手参赛队Bvs后手参赛队W-先后手胜-比赛时间地点-赛事名称.txt");
void Init()
{
	InitHash();
}

/**/int Input(int choose)
{
	
	
	//scanf("%d", &choose);
	if (choose == 1)
	{
		//printf("8 8\n");
		fpcyj=fopen(p, "w+");
		fprintf(fpcyj, "8,8\n");
		fclose(fpcyj);
		cout << "8,8文件已经创建" << endl;
		fflush(stdout);
		Place(11, 11, 1);
		map[1][11][11] = 1;
		map[0][11][11] = 2;
		return 2;
	}
	else
		return 1;
	/*{
		printf("8 8\n");
		fflush(stdout);
		Place(11, 11, 1);
		map[1][11][11] = 1;
		map[0][11][11] = 2;
	}*/
}

void SelectMove(int x,int y,int player)
{
	int max, i, val, go, checkVCF, p;
	double duration;
	val = -99999999;
	makemove(player, x +3, y +3,val);
	player = 3 - player;
	clearmove(0);
	searchmove(player, 0);
	endtime = starttime = clock();
	for (int d = 3; d <= dep; d += 1)
	{
		memset(history, 0, sizeof(history));
		duration = (double)(endtime - starttime) / CLOCKS_PER_SEC;
		if (duration>2)
		{
			//printf("depth is %d \n", d);
			//printf("Time is %f \n", duration);
			break;
		}/**/
		for (i = 0, max = -66666666, p = (player == 1) ? 1 : 0; Moves[0][i].x != -1; i++)
		{
			//index_am++;
			//printf("                %d  %d    %d\n", Moves[0][i].x-3, Moves[0][i].y-3, Moves[0][i].value);

			/**/if (map_3[p][Moves[0][i].x - 4][Moves[0][i].y - 4] >= 16 && map_3[p][Moves[0][i].x - 4][Moves[0][i].y - 4]<64)
			{
				checkVCF = Check_VCF(player, Moves[0][i].x, Moves[0][i].y, Moves[0][i].value, 0);
				if (checkVCF == 1)
				{
					max = 66666666;
					Ult_x = Moves[0][i].x;
					Ult_y = Moves[0][i].y;
					//unmakemove(player, Moves[0][i].x, Moves[0][i].y);
					break;
				}
			}
			makemove(player, Moves[0][i].x, Moves[0][i].y, Moves[0][i].value);
			go = gameover(player);
			if (go == 1)
			{
				max = 66666666;
				Ult_x = Moves[0][i].x;
				Ult_y = Moves[0][i].y;
				unmakemove(player, Moves[0][i].x, Moves[0][i].y);
				break;
			}
			if (go == -1)
			{
				unmakemove(player, Moves[0][i].x, Moves[0][i].y);
				continue;
			}
			player = 3 - player;
			val = -alphabeta(d, -6666666, 6666666, player);
			player = 3 - player;
			unmakemove(player, Moves[0][i].x, Moves[0][i].y);
			Moves[0][i].value = val;
			if (val > max)//&&d == dep
			{
				max = val;
				Ult_x = Moves[0][i].x;
				Ult_y = Moves[0][i].y;
			}
		}
		//qsort(Moves[0], i, sizeof(Moves[0][0]), cmp);
		endtime = clock();
	}
	makemove(player, Ult_x, Ult_y, val);
	player = 3 - player;
}

int main(int argc, char * argv[])
{
	cout << argc << endl;
	if (argc != 1) {
		
		cout << argv[1] << endl;
		for (int i = 2; i < 10; i++) {
			cout << argv[i];
			strcat(p, argv[i]);
		}
	/*	if ((fpcyj = fopen(p, "w+")) != NULL) {
			fclose(fpcyj);
			cout << "创建文件成功"<< endl;
		}*/
		cout << endl;
		cout << p << endl;
	//	cout << "ok" << endl;
		Sleep(3000);
		//cout <<"ok" << endl;
	
	
		
			int player,cch;
			Init();
			if (strcmp(argv[1],"2")==0)cch = 2;
				else cch = 1;
			player = Input(cch);
			cout << "cch:" << cch << ",player:" << player << endl;
			cout << "ok" << endl;
			cout << player<<"player"<<endl;
			int x=-1, y=-1,x1=-1,y1=-1;
			if (cch == 1) {
				x1 = 8; y1 = 8;
			}
			while (1)
			{
				
				sum = 0;
				while (1) {
					fpcyj = fopen(p, "r+");
					if (fpcyj == NULL) {
						Sleep(5000);
						cout << "sleep" << endl;
						continue;
					}
					fscanf(fpcyj, "%d,%d", &x, &y);
					
					if (x1 == x&&y1 == y) {
						fclose(fpcyj);
						Sleep(1000);
					}
					else {
						printf("cyj %d %d", x, y);
						fclose(fpcyj);
						break;
					}
				}
				
				SelectMove(x,y,player);
				fpcyj = fopen(p, "w+");
				fprintf(fpcyj,"%d,%d\n", Ult_x - 3, Ult_y - 3);
				x1 = Ult_x - 3; y1 = Ult_y - 3;
				fclose(fpcyj);
				fflush(stdout);
			}
		
	}
	
	
}/**/
/*
int main()
{
	int player;
	Init();
	//player = Input();
	char str[1000];
	player = 1;
	int x;
	int y;
	int cnum = 1;
	char ch;
	while (1)
	{
		fflush(stdout);
		sum = 0;
		SelectMove(player);
		printf("%d %d\n", Ult_x - 3, Ult_y - 3);
		fflush(stdout);
		/*if (strcmp(str, "name") == 0)
		{

			out << "{" << "[先手参赛队B]" << "[后手参赛队W]" << "[先手胜]" << "[2018.08.3 15:00 合肥][2018 全国计算机博弈大赛];" << endl;
			cout << "name Fire July" << endl;
			//type[0][0] = 225;
			//type[1][0] = 225;
			continue;
		}
		else if (strcmp(str, "new") == 0)
		{
			//fflush(stdout);
			scanf("%s", str);
			if (strcmp(str, "black") == 0)
			{
				//out.open("C:\\Users\\dell\\Desktop\\renju\\renju\\renju\\棋谱.txt", ios::app);
				printf("move 8 8\n");
				//type[0][0] = 225;
				//type[1][0] = 225;
				makemove(1, 11, 11, 1);
				out << "B(H,8);";
				//out.close();
				player = 2;
			}
			else
				player = 1;
		}
		else if (strcmp(str, "move") == 0)
		{
			//out.open("C:\\Users\\dell\\Desktop\\renju\\renju\\renju\\棋谱.txt",ios::app);
			//fflush(stdout);
			cin >> x >> y;
			if (map[0][x + 3][y + 3] == 0)
			{
				ch = y - 1 + 'A';
				if (player == 1)
					out << "B(" << ch << "," << 16 - x << ");";
				else
					out << "W(" << ch << "," << 16 - x << ");" << endl;
			}
			makemove(player, x + 3, y + 3, -99999999);

			SelectMove(player);
			printf("move %d %d\n", Ult_x - 3, Ult_y - 3);
			ch = Ult_y - 4 + 'A';
			if (player == 2)
				out << "B(" << ch << "," << 19 - Ult_x << ");";
			else
				out << "W(" << ch << "," << 19 - Ult_x << ");" << endl;
			//out.close();
		}
		else if (!*str || strcmp(str, "pass") == 0)
		{
			//out.open("C:\\Users\\dell\\Desktop\\renju\\renju\\renju\\棋谱.txt", ios::app);
			SelectMove(player);
			ch = Ult_y - 4 + 'A';
			printf("move %d %d\n", Ult_x - 3, Ult_y - 3);
			if (player == 2)
				out << "B(" << ch << "," << 19 - Ult_x << ");";
			else
				out << "W(" << ch << "," << 19 - Ult_x << ");" << endl;
			//out.close();
		}
		else if (strcmp(str, "change") == 0)
		{
			if(player==2)
				player = 3 - player;	
			else {
				SelectMove(player);
				printf("move %d %d\n", Ult_x - 3, Ult_y - 3);
				ch = Ult_y - 4 + 'A';
				if (player == 2)
					out << "B(" << ch << "," << 19 - Ult_x << ");";
				else
					out << "W(" << ch << "," << 19 - Ult_x << ");" << endl;
				player = 3 - player;
			}
		}
		else if (strcmp(str, "choice") == 0)
		{
			//out.open("C:\\Users\\dell\\Desktop\\renju\\renju\\renju\\棋谱.txt", ios::app);
			cin >> x >> y;
			makemove(player, x + 3, y + 3, -99999999);

			ch = y - 1 + 'A';
			if (player == 1)
				out << "B(" << ch << "," << 16 - x << ");";
			else
				out << "W(" << ch << "," << 16 - x << ");" << endl;
			printf("putstone: %d %d\n", x,y);
			player = 3 - player;
			//out.close();
		}
		else
		{
			printf("Invalid command.");
		}
		/*
		SelectMove(player);
		printf("%d %d\n", Ult_x -3, Ult_y -3);
		fflush(stdout);
	}
	system("pause");
	return 0;
}*/