#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameover;

const int width = 20;
const int height = 17;

int x, y, fructX, fructY, score;

int coadaX[100], coadaY[100]; //snake coordinates

int nCoada;

enum eDirecton {STOP = 0, LEFT,RIGHT, UP, DOWN}; // Controls

eDirecton dir;

void Setup() 
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fructX = rand() % width; 	//setare locatie fruct
	fructY = rand() % height; 	//setare locatie fruct 
	score = 0;
}

void Draw() {
	
	system("cls");
	for(int i = 0; i < width+2; i++) cout << "#";
	cout << endl ;

	for (int i = 0; i < height ; i++) 
	{
		for (int j = 0; j < width; j++) 
		{
			if (j == 0) cout << "#"; //pereti
			if (i == y && j == x) cout << "*"; // coada sarpe
			else 
				if (i == fructY && j == fructX ) cout << "%"; // fructul
				else 
				{
					bool print = false;
					for (int k = 0; k< nCoada ; k++) 
					{
						if (coadaX [k] == j && coadaY [k] == i) 
						{
							cout << "*"; print = true;
						}
					}
					if (!print) cout << " ";
				}

			if (j == width -1) cout << "#";
		}		
		cout << endl;
	}

	for (int i = 0; i< width+2; i++) cout << "#";
	cout << endl;
	cout << "Scor:" << score << endl ;

}

void Input ()
{
	Sleep(40);
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

	if ((x >= width) || (x < 0)) gameover = true;
	if ((y >= height) || (y < 0)) gameover = true;

	for (int i =0; i< nCoada ;i++)
		if (coadaX[i] == x && coadaY[i] == y) gameover = true;

	if (x == fructX && y == fructY) {
		score +=10;
		fructX = rand() % width;
		fructY = rand() % height;
		nCoada ++;
	}
}

int main()
{
	Setup();
	while (!gameover) 
	{
		Draw ();
		Input ();
		algorithm ();
	}
	if (gameover) cout << ">>>   GAME OVER!    <<<<";

	return 0;
}
