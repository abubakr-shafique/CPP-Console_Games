#include<iostream>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include<time.h>
#include <conio.h>

using namespace std;

void userinfo(void);

void clearscreen (); //used to prevent flicker

char name[10];

int main()
{

userinfo();

char map[25][45];	//rows into col
//loads the map with spaces and borders

   for(int i=0; i < 20; ++i) 
   {
       for(int j=0; j < 40; j++)
       {
		  map[0][j] = '!';
          map[i][0] = '!';
          map[i][38] = '!';
          map[i][j] = ' ';
       }
   }

int y = 17, x = 9; //the plate's coordinates y=row x=col

srand(time(0));

int a=1, b=rand() % 35 + 2; //the obstacles coordiantes a=rows b=col

int q=1, p=rand() % 35 + 2; //the cash coordinates

int points=0; //points that the player has earned

int cashcheck=0; //balances when the cash spawns

int cashpickedup=0;

int speed=90; //determines the speed of the obstacles (and the plate)

bool startup = true; //bool startup = 1;

char cash = '$';

char obstacle = 234; //219

char car = 'X';

map[y][x] = car;

//the game loop
   
for(;;) 
{
     clearscreen();

     //PLATE SHAPE
     //places the plate at its default location

	 map[y][x] = 209;	 //plate center

     map[y][x+1] = 209;	 //edges	 //y=row x=col

	 map[y][x-1] = 209;

	 //generates the obstacles a=rows b=col
    
	 //remove the imprint as the obstacle moves down
	 map[a][b] = ' ';
	 
	 //move the obstacle down
	 ++a;

	 map[a][b] = obstacle;

	 //initialize to initial value when the obstacle has travelled all the distance down
     if(a > 20) 
     {
        a = 1;
        b = rand() % 15 + 2;
     }

	 //displays the map

	 for (int i=0; i < 20; ++i)
     {
        for (int j=0; j < 40; ++j) //used for printing spaces
        {
           cout<<map[i][j];

		   if (j >= 39) 
           {
              cout<<"\n";
           }
        }
     }

     
   	 cout<<" Points : "<<points + (cashpickedup*30);

     // game starts after a key is pressed

     if (startup) 
     {

         getch();

		 startup = false;
     }

	 //moves the car to the left

	 if(GetAsyncKeyState(VK_LEFT)) 
     {
        if(map[y][x-1] == obstacle) 
        {
           goto lost;
        }

	    else if(map[y][x-3] != '!') // y=rows x=col
        {

		map[y][x] = ' ';	 //to clear the previous object

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
        if(map[y][x+1] == obstacle)
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

	 if(map[y][x] == obstacle || map[y][x-1] == obstacle || map[y][x+1] == obstacle) 
     {

        lost:

        cout<<"\n\n You crashed \n";

        cout<<name<<" earned $ "<<cashpickedup<<endl;

        system("color 2f");

        Sleep(5000);

        return 0;

     }

     //checks if the player picked up cash

     if(map[y-1][x] == cash || map[y-1][x-1] == cash || map[y-1][x+1] == cash || map[y][x] == cash || map[y][x-1] == cash || map[y][x+1] == cash) //y=row x=col
     {
		map[y-1][x] = ' ';	 //vanishing the cash

		map[y-1][x-1] = ' ';

		map[y-1][x+1] = ' ';

		++cashpickedup;

        cout<<"\a";
        
		q = 1;

		p = rand() % 35 + 2;
     }

	 //generates the cash

	 else if(q > 37) 
     {
	    q = 1;
  
		p = rand() % 35 + 2;
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

    system("color 5f");//f9 ,2f

    cout<<("\n\t\t\t\tEnter Your name : ");
    
	gets(name);

    cout<<"Welcome to Mini Need for Speed: "<<name<<"\n\n\n";
    cout<<"To read the instructions press i \n\n\n";
    cout<<"To skip, Press s\n";

    if(getch()=='i')
    {

		system("cls");

		cout<<"\n Use arrow keys to move left & right\n\n";
        cout<<" Avoid the coming hurdle\n\n";
        cout<<" Pick up cash to get 30 extra points\n\n";
        cout<<" GOOD LUCK ! \n";

		Sleep(5000);

    }

	system("cls");

	cout<<"\n\n\n\n\n\t\t\t/"<<name<<" is Playing";
}