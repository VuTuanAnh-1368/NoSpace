#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include"console.h"
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define consoleWidth 49 //x->0-49*4
#define consoleHeight 40 //y->0-40
#define Lim 6

enum DICHUYEN { UP, DOWN, LEFT, RIGHT };
enum TRANGTHAI { Empty, Fill, Obs};

struct GAME 
{
	char s[50], c[50]; ////////////////////////////////C thua
	int x, y;     //Coordinate Axis Oxy
	DICHUYEN tt;
};

void Frame()
{
	TextColor(6);
	/////////////////Top and Bottom/////////////////////
	for(int i=0;i<consoleWidth*4+3;i++)
	{      ////////////Top///////////
		gotoXY(Lim+i,Lim-2);
    	printf("_");
		/////////TextColor(6);
		gotoXY(Lim+i,Lim-1);
    	printf("_");  
    	/////////////Bottom////////////
    	gotoXY(Lim+i,Lim+consoleHeight);
    	printf("_");
	    ///////////TextColor(6);
		gotoXY(Lim+i,Lim+consoleHeight+1);
    	printf("_");
    }
     
     ///////////////////Left and Right//////////////////////
     for(int i=-1;i<consoleHeight+1;i++)
	{
		gotoXY(Lim-1,Lim+i);
    	printf("| |");             //////////Left
    	gotoXY(Lim+1+consoleWidth*4,Lim+i);   
    	printf("| |");            ////////////Right
    }
}

int main()
{
	GAME P,O;          //////////////PLAY AND Obs//////////
	TRANGTHAI table[consoleWidth][consoleHeight];
	int fill,obs,tym;
	int slp,tg,appe;
	char level;
	srand(time(NULL));
while(1)
{	
	gotoXY(consoleWidth*2,5);
	//TextColor(2);
	//printf("NOSPACE");
	TextColor(8 + rand() % 8);
	printf("N ");
	TextColor(8 + rand() % 8);
	printf("O ");
	TextColor(8 + rand() % 8);
	printf("S ");
	TextColor(8 + rand() % 8);
	printf("P ");
	TextColor(8 + rand() % 8);
	printf("A ");
	TextColor(8 + rand() % 8);
	printf("C ");
	TextColor(8 + rand() % 8);
	printf("E ");
	
	TextColor(8 + rand() % 8);
	printf("\n \n \n \n \n \n                                                                                        Please choose the game level");                    //// MENU 
	printf("\n \n \n                                                                                              1 : Noob");
	printf("\n \n \n                                                                                              2 : Easy");
	printf("\n \n \n                                                                                              3 : Hard");
	printf("\n \n \n                                                                                              4 : Supper ultra pro max");
	printf("\n \n \n \n \n \n                                                                                       Choose 0 to exit the game...");
	
	do
	{
		level=_getch();
	} 
	while(level<'0'||level>'9');
		switch(level)
		{
		case '0':
			clrscr();   ////Clear screen
			return 0;
		case '1':
			slp=100; 
			appe=50000; 
			break;  
		case '2':
			slp=50; 
			appe=15000; 
			break;
		case '3':
			slp=25; 
			appe=5000; 
			break;
		default:
			slp=1; 
			appe=30; 
		}
	
	for (int i = 3; i >= 0; i--) {
		clrscr();
		gotoXY(consoleWidth*2, consoleHeight/2);
		printf("Game will start in %ds", i);
		Sleep(1000);
	}
	clrscr();
	              //// SETUP
	strcpy(O.s, ":))");
	strcpy(P.s, "<^>");
	P.y = 0;
	P.x = consoleWidth / 2;
	P.tt = DOWN;
	for(int i=0;i<consoleWidth;i++)
			{
				for(int j=0;j<consoleHeight;j++)
						table[i][j]=Empty;
			}
	fill=0;obs=0;tg=0;tym=5;
	Frame();
	
	while(1)               //// GAMEPLAY
	{   ///////Specifications
		TextColor(9);//2 9
		gotoXY(1, 1);
		printf("       %.1f %% \n",(float)fill/(consoleWidth*consoleHeight)*100);
		gotoXY(1, 2);
		printf("     Time: %d s \n",tg/1000);
		TextColor(4);
		for(int i=0;i<tym;i++)
		{
			printf("  <3",tg/1000);
		}
		//////////////////////Draw
		gotoXY((P.x)*4+Lim+2, P.y+Lim);   
		TextColor(8 + rand() % 8);
		printf("%s", P.s);                
		///////////////////////obstacles appear                                                              
		if(tg%appe==0)
		{
			O.x = rand()% consoleWidth;
			O.y = rand()% consoleHeight;
			if(table[O.x][O.y]== Fill) fill-=1;
			table[O.x][O.y]= Obs;
			obs+=1;
			gotoXY((O.x)*4+Lim+2, O.y+Lim);
			TextColor(8 + rand() % 8);
			printf("%s", O.s);
		}
		/////////////////////Game mechanism
		if(table[P.x][P.y]==Empty)
		{
			table[P.x][P.y]=Fill;
			fill+=1;
		}
		else if (table[P.x][P.y]==Obs)
		{
			clrscr();
			Frame();
			for(int i=0;i<consoleWidth;i++)
			{
				for(int j=0;j<consoleHeight;j++)
				{
					if(table[i][j]==Obs)
					{
						gotoXY(i*4+Lim+2,j+Lim);
						TextColor(8 + rand() % 8);
						printf("%s", O.s);
					}
					else
					table[i][j]=Empty;
				}
			}
			fill=0;tym-=1; 
		}
		if(fill+obs>=consoleWidth*consoleHeight||tym<=0)
		break;
		
		/////////////////////////////////////////////////  Control / Move
		
		if (_kbhit())  // letter recognition
		{
			char key = _getch(); //use library Conio.h

			if (key == 'A' || key == 'a' || key == 75)  
				P.tt = LEFT;   /////////move left
			else if (key == 'D' || key == 'd' || key == 77)
				P.tt = RIGHT;  ////////move right
			else if (key == 'W' || key == 'w' || key == 72)
				P.tt = UP;     ///////move up
			else if (key == 'S' || key == 's' || key == 80)
				P.tt = DOWN;   ///////move down
			else if (key == 27) break;
		}
		if (P.y >= consoleHeight - 1 && P.tt == DOWN)                                            /**/
			P.tt = UP;
		else if (P.y <= 0 && P.tt == UP)
			P.tt = DOWN;
		else if (P.x <= 0 && P.tt == LEFT)
			P.tt = RIGHT;
		else if (P.x >= consoleWidth - 1 && P.tt == RIGHT)
			P.tt = LEFT;
		
		
		if (P.tt == DOWN)
			P.y += 1;
		else if (P.tt == UP)
			P.y -= 1;
		else if (P.tt == LEFT)
			P.x -= 1;
		else if (P.tt == RIGHT)
			P.x += 1;
		
		Sleep(slp);
		tg+=slp;
		
   }
	clrscr();                                                                    //// ENDGAME
	if(fill+obs>=consoleWidth*consoleHeight)
	{   gotoXY(consoleWidth*2, consoleHeight/2);
		printf("YOU WON");
		gotoXY(consoleWidth*2, consoleHeight/2+1);
		printf("Time: %d s", tg/1000);
	}
	else
	{
		gotoXY(consoleWidth*2, consoleHeight/2);
		printf("GAMEOVER");
	}
	Sleep(3000);
	clrscr();
}
	return 0;
}
