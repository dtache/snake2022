#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //utilizat pentru Consola - Text (Windows)

const WORD colors[12] =
{
0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
};

bool gameover;

const int width = 19;
const int height = 17;

int m1, x, y, fructX, fructY, scor;

int coadaX[100], coadaY[100]; //snake coordinates

int nCoada;

enum eDirecton {STOP = 0, LEFT, RIGHT, UP, DOWN}; // Controls

eDirecton dir;

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(console, coord);
}

void textcolor(int i)
{
	SetConsoleTextAttribute(console, colors[i]);
}

void Setup() 
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;				//se pleaca din mijloc
	
	srand(time(0));
	//setare locatie fruct
	fructX = 3 + rand() % (width - 3);
	fructY = 3 + rand() % (height - 3);
	
	scor = 0;
	
	ifstream fin("config.txt");
    if (!fin.is_open()) //nu exista fisierul
    {
    	m1 = 40;
    }
    else 
    {
		fin >> m1;
		fin.close();
	}
}

void Draw() {
	
	textcolor(0);	//culoarea default - verde pe albastru
	gotoxy(0, 0);
	for(int i = 0; i < width+2; i++) {
		gotoxy(i, 0); cout << "#";
	}
		
	//cout << endl ;
	for (int i = 0; i < height ; i++) 		//selecteaza linia = y
	{
		for (int j = 0; j < width; j++)   	//scrie pe o linie = x
		{
			if (j == 0) { gotoxy(j, i + 1); cout << "#";} //pereti
			
			if (i == y && j == x) 
			{	
				textcolor(9);
				gotoxy(j + 1, i + 1); cout << "*"; // cap sarpe
				textcolor(0);
			}
			else 
				if (i == fructY && j == fructX ) 
				{
					textcolor(7);
					gotoxy(j + 1 , i + 1); cout << "%"; // fructul
					textcolor(0);
				}
				else 
				{
					bool print = false;
					for (int k = 0; k< nCoada ; k++) 
					{
						if (coadaX [k] == j && coadaY [k] == i) 
						{
							textcolor(9);
							gotoxy(j + 1, i + 1); cout << "*"; print = true;
							textcolor(0);
						}
					}
					if (!print) {  gotoxy(j + 1, i + 1); cout << " "; }
				}

			if (j == width -1) 
			{
				gotoxy(j + 2, i + 1); cout << "#";
			}
			
		}		
		/*cout << endl;*/
	}
	
	for (int i = 0; i< width+2; i++) {
		gotoxy(i, height); cout << "#";
	}
	//cout << endl; schimbat cu gotoxy...
	textcolor(0);
	gotoxy(0, height + 1);
	if (scor == 0)
	cout << "Scor: " << scor << "              "; //scad cate un blank pe fiecare cifra
	else 
	if (scor >= 10 && scor < 100)
	cout << "Scor: " << scor << "             ";
	else 
	cout << "Scor: " << scor << "            ";
		
}

void Input ()
{
	Sleep(m1);		//pune o pauza de m1 milisecunde
	
	if (_kbhit ()) {
		switch (_getch ()) {
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN ;
				break;
			case 'x':
				gameover = true;
				break;
		}
	}
}

void algorithm()
{

	int prevX = coadaX [0];
	int prevY = coadaY [0];
	int prev2X, prev2Y;
	coadaX[0] = x;
	coadaY[0] = y;
	
	for(int i = 1; i < nCoada ; i++) 
	{
		prev2X = coadaX[i];
		prev2Y = coadaY[i];
		coadaX[i] = prevX;
		coadaY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y ;
	}

	switch (dir) 
	{
		case LEFT:
		x--;
		break;
	
		case RIGHT:
		x++;
		break;
	
		case UP:
		y--;
		break;
	
		case DOWN:
		y++;
		break;
	
		default:
		break;
	}

	//game over daca ma lovesc de pereti
	if ((x >= width) || (x < 0)) gameover = true;
	if ((y >= height) || (y < 0)) gameover = true;

	//game over daca ating coada
	for (int i =0; i< nCoada ;i++)
		if (coadaX[i] == x && coadaY[i] == y) gameover = true;

	if (x == fructX && y == fructY) {
		scor +=10;
		fructX = 3 + rand() % (width - 3);
		fructY = 3 + rand() % (height - 3);
		nCoada ++;
	}
}

int main()
{
	int i;
	Setup();
	while (!gameover) 
	{
		Draw ();
		Input ();
		algorithm ();
	}
	
	i = -1;
	while (true)
	{
		i++; 
		gotoxy((width - 10) / 2 + 1, height / 2);
		Sleep(60);
		textcolor(i%12);
		if (gameover) cout << "GAME OVER!";
		if (_kbhit ()) break;
	}
	textcolor(0);
	gotoxy(0, height + 4);
	
	
	return 0;
}
