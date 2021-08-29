//Snake Game in C & C++.

//Here include the header files.
#include<stdio.h>
#include<dos.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define TOP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// Print the score.
void score(int s=1)
{
	static unsigned long sc=0;
	window(70,22,78,23);
	if(s)
	{
		sc=sc+100;
		cprintf("      ");
		window(70,22,78,23);
		cprintf("%ld",sc);
	}
	else
		sc=0;
}

// Generate length and effect.
void status(char *s,int c=WHITE)
{
	window(70,23,78,25);
	textcolor(c);
	cprintf("%s",s);
	for(int x=strlen(s);x<7;x++)
	cprintf(" ");
	textcolor(WHITE);
}
void main()
{
	clrscr();
	_setcursortype(_NOCURSOR);
	textcolor(WHITE);
	cprintf("\n   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
	for(int i=0;i<17;i++)
	cprintf("   ³                                                                         ³  ");
	cprintf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
	cprintf("   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿   Press 'X' to Exit            ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
	cprintf("   ³  S N A K E  G A M E  ³   Press 'P' to Pause and Play  ³ SCORE : 0       ³  ");
	cprintf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                                ³ STATUS: Playing ³  ");
	cprintf("                                                           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
	int snkx[20],snky[20],d=LEFT,p=0,sz=6,restart=1;
	while(1)
	{
		if(restart)
		{
			for(i=0;i<6;i++)
			snkx[i]=30+i*2;
			for(i=6;i<20;i++)
			snkx[i]=0;
			for(i=0;i<20;i++)
			snky[i]=9;
			sz=6;
			p=0;
			d=LEFT;
			restart=0;
			score();
			window(6,3,76,19);	//It defines a text window on screen , and it takes 4 parameteres.
			for(i=0;i<610;i++)
			cprintf("  ");
		}
		int x,y;
		if(p!=1)
		{
			randomize();	//Randomize function provide randomness over the method or value you want to be, it is used to,giving it (snake) a new seed value.
			do{
						x=random(70)+6;
					}while(x%2==1);
					y=random(16)+3;
			p=1;
			window(x,y,x+1,y+1);
			textcolor(LIGHTGREEN);
			cprintf("%c",1);
			textcolor(WHITE);
		}
		while(!kbhit())
		{
			status("Playing",LIGHTGREEN);
			window(snkx[sz-1],snky[sz-1],snkx[sz-1]+2,snky[sz-1]+2);
			cprintf(" ");
			for(i=0;i<sz-1;i++)
			{
				window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
				cprintf("");
			}
			for(i=sz-1;i>=1;i--)
			{
				snkx[i]=snkx[i-1];
				snky[i]=snky[i-1];
			}
			switch(d)
			{
				case RIGHT : snkx[0]+=2; break;
				case LEFT  : snkx[0]-=2; break;
				case TOP   : snky[0]-=1; break;
				case DOWN  : snky[0]+=1;
			}
			delay(200);
			if(x==snkx[0] && y==snky[0])
			{
				int f=0;
				do{
					do{
						x=random(70)+6;
					}while(x%2==1);
					y=random(16)+3;
					for(i=0;i<sz;i++)
						if(snkx[i]==x && snky[i]==y)
							f=1;
				}while(f);
				p=1;
				window(x,y,x+1,y+1);
				textcolor(LIGHTGREEN);
				cprintf("%c",1);
				textcolor(WHITE);

				score();
				sz++;

				// The following block of code is Used to provide Control Input for Snake.

				switch(d)							// Switch Statement it will run for any value of 'd' other than 0
				{
					case RIGHT : snkx[sz-1]+=2;				//when Player press "RIGHTArrow Key" then snake Turn toward right
								 snky[sz-1]=snky[sz-2];		// and starts to Move along Positive X axis toward Positive infinity
								 break;
					case LEFT  : snkx[sz-1]-=2;				//when Player press "LEFTArrow Key" then snake Turn toward left
								 snky[sz-1]=snky[sz-2];		// and starts to Move along Negative X axis toward Negative infinity
								 break;
					case TOP   : snky[sz-1]-=1;				//when Player press "UPArrow Key" then snake Turn toward Up
								 snkx[sz-1]=snkx[sz-2];		// and starts to Move along Positive Y axis toward Positive infinity
								 break;
					case DOWN  : snky[sz-1]+=1;				//when Player press "DOWNArrow Key" then snake Turn toward Down
								 snkx[sz-1]=snkx[sz-2];		// and starts to Move along Negative Y axis toward Negative infinity
				}
			}

			int sflag=0;
			//If Game is Over turn The Light to "LightRED" color and Update Status to "Stopped" From "Playing".
			for(i=0;i<sz-1;i++)
				if(snkx[sz-1]==snkx[i] && snky[sz-1]==snky[i])
				{
					sflag=1;
					break;
				}
			if(snkx[0]<5 || snkx[0]>76 || snky[0]<3 || snky[0]>19)
				sflag=1;
			if(sflag)
			{
				textcolor(LIGHTRED);
				for(i=1;i<sz;i++)
				{
					window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
					cprintf("");
				}
				status("Stoped",LIGHTRED);
				score(0);
				restart=1;
				break;
			}
		}
		char ch=getch();
		switch(tolower(ch))
		{
			case 'x' : return;
			case 'p' :
						status("Paused");
						getch();
						break;
			case 0 : {
						char chh=getch();
						switch(chh)
						{
							case 72 :{
									if(d==LEFT || d== RIGHT)
									d=TOP;
									} break;
							case 80 :{
									if(d==LEFT || d== RIGHT)
									d=DOWN;
									} break;
							case 75 :{
									if(d==TOP || d==DOWN)
									d=LEFT;
									} break;
							case 77 :{
									if(d==TOP || d==DOWN)
									d=RIGHT;
									}
						}
					} break;
		}
	}
}