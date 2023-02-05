#include <iostream>
#include <conio.h>
#include <random>
#include <Windows.h>
#include <string.h>
#include <ctime>
using namespace std;
bool GameEnd, Restart=true,Interface;
int width = 30, hight = 40, x, y, ItemX, ItemY, score, bodyX[50], bodyY[50], bodyLength = 5,Highscore=0,FPS=0,Fps2[1], Timer;
char Dificulty,HeadShape='O', BodyShape='o', FoodSahpe='X', GridShape='*';
int Dificultys;
enum edirecion { Stop = 0, L, R, U, D };
edirecion edr=R;
default_random_engine generator;
void setup();
void start();
void map();
void input();
void ClearScreen();
int main()
{
	system("Color F0");
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	cout << "Welcom To the Snake game !\n";
	Sleep(1500);
	cout << "best console size is full screen , if you want to exit full screen mode , press F11 :)\n";
	Sleep(1500);
	cout << "Select The Game Mode (Easy : E , Medium : M ,  Hard : H) :";
	cin >> Dificulty;
	cout << "Do you want to Change the snake interface charachters ? \n(defualt characters are : head = O , bosy = o , Food = X , grid = * ) ";
	cin >> Interface;
	if (Interface)
	{
		cout << "New Head char :";
		cin >> HeadShape;
		cout << "New Body char :";
		cin >> BodyShape;
		cout << "New Food char :";
		cin >> FoodSahpe;
		cout << "New Grid char :";
		cin >> GridShape;
	}
	cout << "Are you ready ? press enter to proseed !";
	_getch();
	system("cls");
	switch (Dificulty)
	{
	case'E':
		Dificultys = 40;
		break;
	case'M':
		Dificultys = 20;
		break;
	case'H':
		Dificultys = 0;
		break;
	default:
		break;
	}
	while (Restart==true)
	{
		setup();
		while (!GameEnd)
		{
			Timer = clock();
			map();
			input();
			start();
			Sleep(Dificultys);
			cout << "\n\n\t\t" << "score : " << score << "\t\tHighScore : " << Highscore << "\n";
			if (Timer % 100==0)
			{
				Fps2[0] = FPS;
				FPS = 0;
			}
		}
		if (score > Highscore)
		{
			Highscore = score;
		}
		cout << "\n\t\tGAME OVER !!" << "\n\n\t\tWant to restart ? (true = 1 /false = 0) :";
		cin >> Restart;
		system("cls");
	}
	system("cls");
	cout << "\n\n-------------------------------------------------------------------\n\n";
	cout << "\tThanks For Playing The Game :)" << "\n\n\tHighscore : " << Highscore<<"\n\n"<<"\tContact Us : Email : rezafathisamani1383@gmail.com";
	cout << "\n\n-------------------------------------------------------------------\n\n";
}
void setup()
{
	GameEnd = false;
	bodyLength = 0;
	edr = Stop;
	x = width / 2;
	y = hight / 2;
	uniform_int_distribution<int> distributionHight(1,hight);
	uniform_int_distribution<int> distributionWidth(1, width-3);
	ItemX = distributionWidth(generator);
	ItemY = distributionHight(generator);
	score = 0;
}
void map()
{
	ClearScreen();
	cout << "\n\n\n\n\n\n\n\t\t";
	for (int i = 0; i < width; i++)
	{
		cout << "*";
	}
	cout << "\t" << "FPS : " << Fps2[0];
	cout << "\n";
	for (int i = 0; i < hight; i++)
	{
		cout << "\t\t";
		for (int j = 0; j <= width; j++)
		{
			if (j == 0)
			{
				cout << GridShape;
			}
			else if (j == width - 2)
			{
				cout << GridShape;
			}
			if (i == y && j == x)
			{
				cout << HeadShape;
			}
			else if (i == ItemY && j == ItemX)
			{
				cout << FoodSahpe;
			}
			else
			{
				bool BodyIsPrinted = false;
				for (int k = 0; k < bodyLength; k++)
				{
					if (bodyX[k] == j && bodyY[k] == i)
					{
						cout << BodyShape;
						BodyIsPrinted = true;
					}
				}
				if (!BodyIsPrinted)
				{
					cout << " ";
				}
			}
		}
		cout << "\n";
	}
	cout << "\t\t";
	for (int i = 0; i < width; i++)
	{
		cout << "*";
	}
}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 65:
		case 'w':
			edr = U;
			break;
		case 66:
		case 's':
			edr = D;
			break;
		case 67:
		case 'd':
			edr = R;
			break;
		case 68:
		case 'a':
			edr = L;
			break;
		case 'x':
			GameEnd = true;
			break;
		}
	}
}
void start()
{
	int lastX = bodyX[0], lastY = bodyY[0], lastX2, lastY2;
	bodyX[0] = x;
	bodyY[0] = y;
	for (int i = 1; i < bodyLength; i++)    
	{
		lastX2 = bodyX[i];
		lastY2 = bodyY[i];
		bodyX[i] = lastX;
		bodyY[i] = lastY;
		lastX = lastX2;
		lastY = lastY2;
	}
	switch (edr)
	{
	case L:
		x--;
		break;
	case R:
		x++;
		break;
	case U:
		y--;
		break;
	case D:
		y++;
		break;
	default:
		break;
	}
	if (x>width-3)
	{
		x = 0;
	}
	if (x<0)
	{
		x = width - 3;
	}
	if (y>hight)
	{
		y = 0;
	}
	if (y<0)
	{
		y = hight;
	}
	for (int i = 0; i < bodyLength; i++)
	{
		if (bodyX[i] == x && bodyY[i] == y)
		{
			GameEnd = true;
			break;
		}
	}
	if (x == ItemX && y == ItemY)
	{
		bodyLength++;
		score += 10;
		uniform_int_distribution<int> distributionHight(1, hight);
		uniform_int_distribution<int> distributionWidth(1, width-3);
		ItemX = distributionWidth(generator);
		ItemY = distributionHight(generator);
	}
}
void ClearScreen()
{
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	FPS++;
}
