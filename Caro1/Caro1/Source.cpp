#include<iostream>
#include<Windows.h>
#include<string>
#include<conio.h>
#include <cwchar>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

struct position
{
	int x, y;
};

string name1, name2;
char tran;
int score1, score2;
int heighh = 0, heighl = 20, widthl = 0, widthr = 20;
int banco[1001][1001], bancocom[1001][1001];
int n = 0;
position turn[1000000];
position cursor;

void pvp();
int main();
void ez();
void normal();
void hard();

void gtxy(int x, int y)
{
	COORD vitri;
	vitri.X = x;
	vitri.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), vitri);
}

void font()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 5;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void namepvp()
{
	cout << "Please enter first player's name: " << endl;
	cin >> name1; score1 = 0;
	cout << "Please enter second player's name: " << endl;
	cin >> name2; score2 = 0;
}

void drawtable()
{
	system("cls");
	for (int i = heighh; i <= heighl; i++)
	{
		cout << "_";
		for (int j = widthl; j <= widthr; j++)
		{
			cout << "|_";
		}
		cout << "|" << endl;
	}
	cursor.x = 0; cursor.y = 0;
	gtxy(0, 0);
}

void resetbanco()
{
	for (int i = 0; i <= 1000; i++)
		for (int j = 0; j <= 1000; j++)
		{
			banco[i][j] = 0;
		}
}

void init()
{
	drawtable();
	gtxy((widthr - widthl) * 2 + 10, 0);
	cout << name1 << " VS " << name2;
	gtxy((widthr - widthl) * 2 + 10, 1);
	cout << name1 << ": " << score1 << "    " << name2 << ": " << score2;
	gtxy((widthr - widthl) * 2 + 10, 2);
	cout << "Press p to pause game" << endl;
	gtxy(0, 0);
}

void loadthisgame()
{
	init();
	for (int i = 1; i <= n; i++)
	{
		gtxy(turn[i].x * 2, turn[i].y);
		banco[turn[i].x][turn[i].y] = (i - 1) % 2 + 1;
		if (i % 2 == 1) cout << 'X';
		else cout << 'O';
	}
	gtxy(turn[n].x * 2, turn[n].y);
	cursor.x = turn[n].x * 2; cursor.y = turn[n].y;
}

void savegame()
{
	string tenthumuc = "Save.txt";
	ofstream file(tenthumuc, ios::app);
	file << '@' << endl;
	file << name1 << endl;
	file << name2 << endl;
	file << score1 << ' ' << score2 << endl;
	file << widthl << ' ' << widthr << ' ' << heighh << ' ' << heighl << endl;
	file << n << endl;
	for (int i = 1; i <= n; i++)
	{
		file << turn[i].x << ' ' << turn[i].y << endl;
	}
	file << tran << endl;
	file.close();
	cout << "Game Saved!" << endl;
	system("pause");
	loadthisgame();
}

void save()
{
	system("cls");
	cout << "Do you want to save game ? y/n" << endl;
	char t;
	do
	{
		t = _getch();
	} while ((t != 'y') && (t != 'n'));
	if (t == 'n')
		loadthisgame();
	else savegame();
}

void check()
{
	int k = 0;
	if (cursor.x < 0)
	{
		widthl = widthl - 5; k = 1;
	}
	if (cursor.y < 0)
	{
		heighh = heighh - 5; k = 2;
	}
	if (cursor.x > widthr * 2)
	{
		widthr = widthr + 5; k = 3;
	}
	if (cursor.y > heighl - heighh)
	{
		heighl = heighl + 5; k = 4;
	}
	if (k != 0)
	{
		resetbanco();
		for (int i = 1; i <= n; i++)
		{
			if (k == 1) turn[i].x += 5;
			if (k == 2) turn[i].y += 5;
		}
		loadthisgame();
	}
}

void dichuyen(char t)
{
	switch (t)
	{
	case 97: cursor.x -= 2; check(); gtxy(cursor.x, cursor.y); break;
	case 119: cursor.y -= 1; check(); gtxy(cursor.x, cursor.y); break;
	case 100: cursor.x += 2; check(); gtxy(cursor.x, cursor.y); break;
	case 115: cursor.y += 1; check(); gtxy(cursor.x, cursor.y); break;
	case 112: save(); break;
	}
}

position danh()
{
	position co;
	char t;
	do
	{
		do
		{
			t = 0;
			t = _getch();
			dichuyen(t);
		} while (t != 13);
		co.x = cursor.x / 2; co.y = cursor.y;
	} while (banco[co.x][co.y] != 0);
	n++;
	turn[n].x = co.x; turn[n].y = co.y;
	return co;
}

void gameend()
{
	char a;
	cout << "Play Again ? y/n or Main Menu: m" << endl;
	do
		a = _getch();
	while ((a != 'n') && (a != 'y') && (a != 'm'));
	switch (a)
	{
	case 'y':
		resetbanco(); init(); n = 0;
		switch (tran)
		{
		case 'p': pvp(); break;
		case 'e': ez(); break;
		case 'n': normal(); break;
		case 'h': hard(); break;
		}
		break;
	case 'm': main(); break;
	case 'n':
		system("cls");
		cout << "Thank you for playing !!!" << endl;
		system("pause");
	}
}

void pvpend(int t)
{
	system("cls");
	if (t == 1)
		cout << "Player " << name1 << " Won This Game" << endl;
	else
		cout << "Player " << name2 << " Won This Game" << endl;
	cout << name1 << ": " << score1 << "    " << name2 << ": " << score2 << endl;
	gameend();
}

int pwin(position k, int p, int dem)
{
	int cheonguoc, doc, conchay, ngang, cheoxuoi;
	conchay = 1; doc = 1; ngang = 1; cheoxuoi = 1; cheonguoc = 1;
	while (banco[k.x + conchay][k.y + conchay] == p)
	{
		conchay++; cheoxuoi++;
	} conchay = 1;
	while (banco[k.x - conchay][k.y - conchay] == p)
	{
		conchay++; cheoxuoi++;
	} conchay = 1;
	while (banco[k.x + conchay][k.y - conchay] == p)
	{
		conchay++; cheonguoc++;
	} conchay = 1;
	while (banco[k.x - conchay][k.y + conchay] == p)
	{
		conchay++; cheonguoc++;
	} conchay = 1;
	while (banco[k.x + conchay][k.y] == p)
	{
		conchay++; ngang++;
	} conchay = 1;
	while (banco[k.x - conchay][k.y] == p)
	{
		conchay++; ngang++;
	} conchay = 1;
	while (banco[k.x][k.y + conchay] == p)
	{
		conchay++; doc++;
	} conchay = 1;
	while (banco[k.x][k.y - conchay] == p)
	{
		conchay++; doc++;
	} conchay = 1;
	if ((cheonguoc >= dem) || (cheoxuoi >= dem) || (ngang >= dem) || (doc >= dem)) return 1;
	return 0;
}

void danhco()
{
	position co;
	while (true)
	{
		co = danh();
		if (n % 2 == 1)
		{
			banco[co.x][co.y] = 1;
			cout << "X";
			gtxy(cursor.x, cursor.y);
			if (pwin(co, 1, 5) == 1)
			{
				score1++; pvpend(1);
				break;
			}
		}
		else
		{
			banco[co.x][co.y] = 2;
			cout << "O";
			gtxy(cursor.x, cursor.y);
			if (pwin(co, 2, 5) == 1)
			{
				score2++; pvpend(2);
				break;
			}
		}
	}
}

void pvp()
{
	resetbanco();
	init();
	n = 0;
	danhco();
}

position coez(position co)
{
	position random[1000];
	int dem, k, c;
	dem = 1; c = 1;
	do
	{
		for (int i = -c; i <= c; i++)
			for (int j = -c; j <= c; j++)
				if (banco[co.x + i][co.y + j] == 0)
				{
					random[dem].x = i; random[dem].y = j;
					dem++;
				}
		c++;
	} while (dem == 1);
	k = rand() % (dem - 1) + 1;
	co.x = co.x + random[k].x; co.y = co.y + random[k].y;
	cursor.x = co.x * 2; cursor.y = co.y;
	n++;
	turn[n].x = co.x; turn[n].y = co.y;
	check();
	return turn[n];
}

void ez()
{
	position co;
	co.x = 0; co.y = 0;
	while (true)
	{
		co = danh();
		banco[co.x][co.y] = 1;
		cout << 'X';
		gtxy(cursor.x, cursor.y);
		if (pwin(co, 1, 5) == 1)
		{
			system("cls");
			cout << "You won this game" << endl;
			break;
		}
		co = coez(co);
		gtxy(cursor.x, cursor.y); cout << 'O'; gtxy(cursor.x, cursor.y);
		banco[co.x][co.y] = 2;
		if (pwin(co, 2, 5) == 1)
		{
			system("cls");
			cout << "You lost to ez mode ??" << endl;
			break;
		}
	}
	gameend();
}

position conor(position co)
{
	position cotmp,uutien;
	int dem,max = 0;
	dem = 1;
	for (int c = 1; c <= 5; c++)
		for (int i = -c; i <= c; i++)
			for (int j = -c; j <= c; j++)
				if (banco[co.x + i][co.y + j] == 0)
				{
					cotmp.x = co.x + i; cotmp.y = co.y + j;
					for (int k = 5; k > 0; k--)
						if ((pwin(cotmp,1,k) == 1)&&(k > max))
						{
							uutien.x = cotmp.x; uutien.y = cotmp.y;
							max = k;
							dem++;
						}
				}
	cursor.x = uutien.x * 2; cursor.y = uutien.y;
	n++;
	turn[n].x = uutien.x; turn[n].y = uutien.y;
	check();
	return uutien;
}

void normal()
{
	position co;
	co.x = 0; co.y = 0;
	while (true)
	{
		co = danh();
		banco[co.x][co.y] = 1;
		cout << 'X';
		gtxy(cursor.x, cursor.y);
		if (pwin(co, 1, 5) == 1)
		{
			system("cls");
			cout << "You won this game" << endl;
			break;
		}
		co = conor(co);
		gtxy(cursor.x, cursor.y); cout << 'O'; gtxy(cursor.x, cursor.y);
		banco[co.x][co.y] = 2;
		if (pwin(co, 2, 5) == 1)
		{
			system("cls");
			cout << "You lost to normal mode." << endl;
			break;
		}
	}
	gameend();
}

position cohar()
{
	position cotmp, uutien;
	int dem, max = 0;
	dem = 1;
	for (int k = 1; k <= n; k++)
	{
		for (int c = 1; c <= 5; c++)
			for (int i = -c; i <= c; i++)
				for (int j = -c; j <= c; j++)
					if (banco[turn[k].x + i][turn[k].y + j] == 0)
					{
						cotmp.x = turn[k].x + i; cotmp.y = turn[k].y + j;
						for (int k = 5; k > 0; k--)
							if (k > max)
							{
								if ((pwin(cotmp, 1, k) == 1) || (pwin(cotmp, 2, k) == 1))
								{
									uutien.x = cotmp.x; uutien.y = cotmp.y;
									max = k;
									dem++;
								}
							}
					}
	}
	cursor.x = uutien.x * 2; cursor.y = uutien.y;
	n++;
	turn[n].x = uutien.x; turn[n].y = uutien.y;
	check();
	return uutien;
}

void hard() 
{
	position co;
	co.x = 0; co.y = 0;
	while (true)
	{
		co = danh();
		banco[co.x][co.y] = 1;
		cout << 'X';
		gtxy(cursor.x, cursor.y);
		if (pwin(co, 1, 5) == 1)
		{
			system("cls");
			cout << "You won this game" << endl;
			break;
		}
		co = cohar();
		gtxy(cursor.x, cursor.y); cout << 'O'; gtxy(cursor.x, cursor.y);
		banco[co.x][co.y] = 2;
		if (pwin(co, 2, 5) == 1)
		{
			system("cls");
			cout << "You lost to hard mode!!!" << endl;
			break;
		}
	}
	gameend();
}

void pvc()
{
	cout << "Please enter your name: " << endl;
	cin >> name1; name2 = "Computer";
	cout << "Choose difficulty" << endl;
	cout << "h : Hard n : Normal e : easy" << endl;
	char t;
	do
		t = _getch();
	while ((t != 'h') && (t != 'n') && (t != 'e'));
	init(); n = 0;
	switch (t)
	{
	case 'h': tran = 'h'; hard();  break;
	case 'n': tran = 'n'; normal();  break;
	case 'e':  tran = 'e'; ez(); break;
	}
}

void remove(int k)
{
	ifstream file("Save.txt");
	ofstream filetemp("SaveTemp.txt");
	char t; int h = 0;
	while (!file.eof())
	{
		file >> t;
		if (t == '@') h++;
		if ((h != k)&&(t == '@'))
		{
			file >> name1;
			file >> name2;
			file >> score1 >> score2;
			file >> widthl >> widthr >> heighh >> heighl;
			file >> n;
			filetemp << '@' << endl;
			filetemp << name1 << endl;
			filetemp << name2 << endl;
			filetemp << score1 << ' ' << score2;
			filetemp << widthl << ' ' << widthr << ' ' << heighh << ' ' << heighl << endl;
			filetemp << n << endl;
			for (int i = 1; i <= n; i++)
			{
				file >> turn[i].x >> turn[i].y;
				filetemp << turn[i].x << ' ' << turn[i].y << endl;
			}
			file >> tran;
			filetemp << tran << endl;
		}
		t = '0';
	}
	file.close();
	filetemp.close();
	remove("Save.txt");
	rename("SaveTemp.txt", "Save.txt");
	cout << "Removed!!!" << endl;
	system("pause");
	main();
}

void loadgame(int k)
{
	ifstream file("Save.txt");
	char t; int i = 0;
	while (i < k)
	{
		file >> t;
		if (t == '@') i++;
	}
	file >> name1; 
	file >> name2;
	file >> score1 >> score2;
	file >> widthl >> widthr >> heighh >> heighl;
	file >> n;
	init(); resetbanco();
	for (int i = 1; i <= n; i++)
	{
		file >> turn[i].x >> turn[i].y;
	}
	loadthisgame();
	file >> t;
	file.close();
	switch (t)
	{
	case 'p': danhco(); break;
	case 'e': ez(); break;
	case 'n': normal(); break;
	case 'h': hard(); break;
	}
}

void load()
{
	ifstream file("Save.txt");
	char t; int i = 0, k;
	while (!file.eof())
	{
		file >> t;
		if (t == '@')
		{
			file >> name1 >> name2;
			i++;
			cout << " " << i << ": " << name1 << " VS " << name2 << endl;
		}
	}
	file.close();
	if (i > 0)
	{
		do
			cin >> k;
		while ((k <= 0) || (k > i));
		cout << "Load : l or Remove : r" << endl;
		do
			t = _getch();
		while ((t != 'l') && (t != 'r'));
		if (t == 'l')
			loadgame(k);
		else remove(k);
	}
	else
	{
		cout << "No saved game" << endl;
		system("pause");
		main();
	}
}

int main()
{
	font();
	heighh = 0; heighl = 20; widthl = 0; widthr = 20;
	system("cls");
	cout << "This is a caro games program" << endl;
	cout << "Producer: Tran Thien Phuc" << endl;
	system("pause"); system("cls");
	cout << "Choose your game type" << endl;
	cout << "p : pvp or c : pvc or view saved games : v" << endl;
	char t;
	do
		t = _getch();
	while ((t != 'p') && (t != 'c') && (t != 'v'));
	switch (t)
	{
	case 'p': namepvp(); tran = 'p'; pvp(); break;
	case 'c': pvc(); break;
	case 'v': load(); break;
	}
}
