#include<iostream>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include<time.h>
#include <conio.h>
using namespace std;

void userinfo(void);
void clearscreen(); //used to prevent flicker
char name[10];
int main()
{
	
	userinfo();
//start:
	//clearscreen();
	char map[25][25];	//rows into col

		//loads the map with spaces and borders
		for(int i=0; i < 20; ++i) 
		{
			for(int j=0; j < 20; j++)
			{
				map[i][0] = '!';
				map[i][18] = '!';
				map[i][j] = ' ';
			}
		}

		int y = 17, x = 9; //the cars coordinates   y=row x=col

		srand(time(0));

		int a = 0, b = rand() % 15 + 2; //the obstacles coordiantes  a=rows    b=col

		int points = 0; //points that the player has earned
		int speed = 90; //determines the speed of the obstacles (and the car)
		int q = 0, p = rand() % 15 + 2; //the cash coordinates
		int cashcheck = 0; //balances when the cash spawns
		int cashpickedup = 0;
		bool startup = true; //bool startup = 1;

		char cash = '$';
		char obstacle = 221;  //219

		char car = 'X';
		map[y][x] = car;
		//the game loop
		for(;;) 
		{
			clearscreen();
		
			//CAR SHAPE
									//places the car at its default location
				map[y][x] = 233;				//car center
				
				map[y][x+1] = 1;		//edges					//y=row    x=col
				map[y][x-1] = 1;
				map[y+1][x-1] = 178;
				map[y+1][x+1] = 178;
				map[y-1][x-1] = 177;
				map[y-1][x+1] = 177;

			//generates the obstacles   a=rows    b=col
				map[a][b] = ' ';
				map[a][b] = ' ';
				map[a][b+1] = ' ';
				map[a][b-1] = ' ';
				map[a+1][b-1] = ' ';
				map[a+1][b+1] = ' ';
				map[a-1][b-1] = ' ';
				map[a-1][b+1] = ' ';
				++a;
				map[a][b] = obstacle;
				map[a][b+1] = obstacle;
				map[a][b-1] = obstacle;
				map[a+1][b-1] = obstacle;
				map[a+1][b+1] = obstacle;
				map[a-1][b-1] = obstacle;
				map[a-1][b+1] = obstacle;
				if(a > 20) 
				{
					a = 0;
					b = rand() % 15 + 2;
				}
		//displays the map
		for(int i=0; i < 20; ++i)
		{
			for(int j=0; j < 20; ++j) //used for printing spaces
			{
				cout<<map[i][j];

					if(j >= 19) 
					{
						cout<<"\n";
					}
				}
			}
											
		cout<<"     Points : "<<points + (cashpickedup*30);
		// game starts after a key is pressed
		if(startup) 
		{
			
			getch();
						//PlaySound(L"car.wav", NULL, SND_FILENAME | SND_ASYNC | SND_PURGE);

			startup = false;
		}
		//moves the car to the left
		if(GetAsyncKeyState(VK_LEFT)) 
		{
			if(map[y][x-3] == obstacle) 
			{
				goto lost;
			}
			else if(map[y][x-3] != '!') // y=rows    x=col
			{
				map[y][x] = ' ';			//to clear the previous object
				map[y][x+1] = ' ';
				map[y][x-1] = ' ';
				map[y+1][x-1] = ' ';
				map[y+1][x+1] = ' ';
				map[y-1][x-1] = ' ';
				map[y-1][x+1] = ' ';
				x -= 1;
			
			}
		}
		//moves the car to the right
		if(GetAsyncKeyState(VK_RIGHT)) 
		{
			if(map[y][x+3] == obstacle)
			{
				goto lost;
			}
			else if(map[y][x+3] != '!') 
			{

				map[y][x] = ' ';
				map[y][x+1] = ' ';
				map[y][x-1] = ' ';
				map[y+1][x-1] = ' ';
				map[y+1][x+1] = ' ';
				map[y-1][x-1] = ' ';
				map[y-1][x+1] = ' ';
				x += 1;
				
			}
		}
		//checks if the car crashed
		if(map[y-2][x] == obstacle || map[y-2][x-1] == obstacle || map[y-2][x+1] == obstacle) {
lost:
			
				
			cout<<"\n\n You crashed ";
			cout<<name<<" earned $ "<<cashpickedup<<endl;
			//PlaySound(L"crash.wav", NULL, SND_FILENAME);
		system("pause");
			//Sleep(5000);
			//getch();
			system("color 2f");
			
			 
			system("cls");
				
			cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\(CREDITS)////////////////////";
			cout<<"\n\n";
			cout<<"\t        Abubakr Shafique";
			Sleep(5000);
//PlaySound(L"tada.wav", NULL, SND_FILENAME);
			
			return 0;
		}
		//checks if the player picked up cash
		if(map[y-2][x] == cash || map[y-2][x-1] == cash || map[y-2][x+1] == cash)   //y=row    x=col
		{
			map[y-2][x] = ' ';			//vanishing the cash
			map[y-2][x-1] = ' ';
			map[y-2][x+1] = ' ';
			++cashpickedup;
		
			cout<<"\a";
			q = 0;
			p = rand() % 15 + 2;
		}
		//generates the cash
		else if(q > 20) {
			q = 0;
			p = rand() % 15 + 2;
		}
		//does so the cash doesnt appear next to the obstacle
		if(a > 15) //?
		{
			++cashcheck;
		}
		//places the cash
		if(cashcheck) 
		{
		map[q][p] = ' ';
		++q;
		map[q][p] = cash;
		}
			++points;
		//speeds up the obstacles each time the player gets another 100 points
		if(points == 100 || points == 200 || points == 300 || points == 400) 
		{
				speed -= 20;
			}
		Sleep(speed);
		}
		//PlaySound(L"car.wav", NULL, SND_FILENAME);
	return 0;
}
void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
void userinfo()
{
	//char name[10];
	system("color 5f");//f9 ,2f

//PlaySound(L"car.wav", NULL, SND_FILENAME | SND_SYNC);



	cout<<("\n\t\t\t\tEnter Your name ? ");
	gets(name);

	
	//PlaySound(L"Intro.wav", NULL, SND_FILENAME);

	cout<<"Welcome to Mini Need for Speed: "<<name<<"\n\n\n";
	cout<<"To read the instructions press i \n\n\n";
	//PlaySound(L"SystemStart", 0, SND_ALIAS | SND_SYNC);
	cout<<"To skip, Press s\n";
	
	
	if(getch()=='i')
	{
		system("cls");
		cout<<"\n Use arrow keys to move left & right\n\n";
		cout<<" Avoid the coming hurdle\n\n";
		cout<<" Pick up cash to get 30 extra points\n\n";
		cout<<" GOOD LUCK ! \n";
		Sleep(5000);
		//getch();
		//system("cls");

	}
	system("cls");

	cout<<"\n\n\n\n\n\t\t\t"<<name<<" is playing";
}
