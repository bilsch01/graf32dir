//  program graf.c 4/5/2015 compile gcc grf1.c -o grf1 -lm -lSDL2 -lncurses
//                          compile g++ graf.c -o graf -std=c++11 -Wall -lSDL2 -lncurses

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>							// dc version
#include <ncurses.h>			/* ncurses.h includes stdio.h */  							

int colr[9]={255,0,144,0,255,255,173,255,47};			//  solid color rgb triplets
int rgb[12]={0,0,255,204,0,204,255,0,153,204,0,204};    //  shaded color rgb triplets
int maxx=0, maxy=0, delay=20, lcount=1, flag0, flag1, flag2, restart=0, n1=0, n2=0, m1=0, xf=6, yf=5;      
int glength=2400, x2, y2, c1=0, c2=0, c3=255, xm=200, xof=600, ym=200, yof=300;
float t, k1=.01, w1=0.5, w2=2.0, w3=0.14159, f1, f2, f3;
char fmsg[]="\n\nf1=sin(w1*t), f2=sin(w2*t), f3=sin(w3*t), f4=f1+f2, f5=f1*f2, f6=(f1+f2)*f3, f7=f1*f2*f3, f8=exp(-f1),\n\nf9=exp(-(f1+f2)), f10=exp(-(f1+f3)), f11=exp(-(f1*f2)), f12=exp(-(f2*f3))\n\n";
char yesno, proceed;
	
int front_end(void);

int main(int argc, char **argv){		// 4 lines total for 'double click'  dc version
//int main(int argc, char *argv[]){
    
if (!isatty(STDIN_FILENO))	// crashes w/o this line		//  dc version
	execlp("xterm", *argv, "-e", *argv, (void *)0);			//  dc version

printf("\n\n\n****************************************************************************\n");
printf("****                   NOTES FOR RUNNING THIS PROGRAM:                  ****\n");
printf("****  To change graph parameters hit '\\' key while graph is plotting.   ****\n");
printf("****      To quit program hit 'ENTER' key While graph is plotting.      ****\n");
printf("****        Right now, hit 'c' then hit 'Enter' to run program.         ****\n");
printf("****************************************************************************\n\n\n");
scanf("%s", &proceed); // it says enter 'C', but any char works

goto x300;
 
x200:;
front_end();	//  ncurses UI

x300:;
SDL_Init(SDL_INIT_VIDEO);
SDL_DisplayMode vmode;				// display mode structure
SDL_GetDisplayMode(0, 0, &vmode);
SDL_Window *win1 = NULL;
win1=SDL_CreateWindow("graf",0,0,vmode.w,vmode.h,SDL_WINDOW_SHOWN); //disp#=mode#=0=current
SDL_Renderer* ren = NULL;
ren =  SDL_CreateRenderer( win1, 0, SDL_RENDERER_ACCELERATED);
SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );    //set render to black for background
SDL_RenderClear( ren );				// Clear window
SDL_Event event;         		        // The event structure

	
while(1)
{	if(SDL_PollEvent(&event) != 0 )  //SDL_PE = 1 if key hit
	{	const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_RETURN]) 
			goto x100;   //  quit if enter key
		if (state[SDL_SCANCODE_BACKSLASH])
		{	restart = 1;  //restart if backslash key
			goto x100;
		}
	}
	flag1 = 0;
	flag2 = 0;
	while (flag1 == 0)      // flag1=1 black pxl is glength pxls behind color pxl
	{	if (flag2 == 0)    // flag2=1 means color pxl plotted
                {	t  = k1*(lcount+glength);
			flag2 = 1;
		}
		else
		{	t  = k1*lcount;
			c1 = 0;
			c2 = 0;
			c3 = 0;		//  r=g=b=0 = black pixel
			flag1 = 1;
		}

		f1 = sin(w1*t);
		f2 = sin(w2*t);
		f3 = sin(w3*t);

		switch(xf)
		{
			case 1:  x2 = xof + (int)(xm*f1);
				break;
			case 2:  x2 = xof + (int)(xm*f2);
				break;
			case 3:  x2 = xof + (int)(xm*f3);
				break;
			case 4:  x2 = xof + (int)(xm*(f1+f2));
				break;
			case 5:  x2 = xof + (int)(xm*(f1*f2));
				break;
			case 6:  x2 = xof + (int)(xm*(f1+f2)*f3);
				break;
			case 7:  x2 = xof + (int)(xm*(f1*f2)*f3);
				break;
			case 8:  x2 = xof + (int)(xm*exp(- f1));
				break;
			case 9:  x2 = xof + (int)(xm*exp(-(f1+f2)));
				break;
			case 10: x2 = xof + (int)(xm*exp(-(f1+f3)));
				break;
			case 11: x2 = xof + (int)(xm*exp(-(f1*f2)));
				break;
			case 12: x2 = xof + (int)(xm*exp(-(f2*f3)));
				break;
			default: 
				puts("keyboard input out of range");
		}

		switch(yf)
		{
			case 1:  y2 = yof + (int)(ym*f1);
				break;
			case 2:  y2 = yof + (int)(ym*f2);
				break;
			case 3:  y2 = yof + (int)(ym*f3);
				break;
			case 4:  y2 = yof + (int)(ym*(f1+f2));
				break;
			case 5:  y2 = yof + (int)(ym*(f1*f2));
				break;
			case 6:  y2 = yof + (int)(ym*(f1+f2)*f3);
				break;
			case 7:  y2 = yof + (int)(ym*(f1*f2)*f3);
				break;
			case 8:  y2 = yof + (int)(ym*exp(- f1));
				break;
			case 9:  y2 = yof + (int)(ym*exp(-(f1+f2)));
				break;
			case 10: y2 = yof + (int)(ym*exp(-(f1+f3)));
				break;
			case 11: y2 = yof + (int)(ym*exp(-(f1*f2)));
				break;
			case 12: y2 = yof + (int)(ym*exp(-(f2*f3)));
				break;
			default: 
				puts("keyboard input out of range");
		}


		SDL_SetRenderDrawColor(ren,c1,c2,c3,255);  
		SDL_RenderDrawPoint(ren,x2,y2);
		SDL_RenderPresent(ren);			//  plot pixel

	}			// end while(flag1) loop
	
	SDL_Delay(delay);		//  delay between pixels

	lcount++;
	if (lcount == 10000)		//  clears screen & changes color after 10,000 pixels
	{	lcount=1;
		SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );
		SDL_RenderClear(ren);
		m1++;			//  m1 is solid color index
		if (m1==4)
		m1 = 0;
	}
	if (m1<3)
	{	c1=colr[(3*m1)+0];
		c2=colr[(3*m1)+1];	
		c3=colr[(3*m1)+2];
	}
	else	//   m1=3
	{   	c1=rgb[(3*n1)+0];		//  gets shades from array
		c2=rgb[(3*n1)+1];
		c3=rgb[(3*n1)+2];
		n2++;
		if(n2==15)			//  15 pixels per shade
		{n2=0;
		n1++;}
		if(n1==4)			//  4 shades in array  
		n1=0;           
	}

}					//  end while(1) loop

x100:;
SDL_DestroyRenderer(ren);		//  clean u
SDL_DestroyWindow(win1);
SDL_Quit();
if(restart == 1)			//  restart=0  goes to end
	{restart=0;
	 goto x200;
	}
}  			// end main


/*************************************** front_end(void)   ***************************************/
int front_end(void){
#include <ncurses.h>			/* ncurses.h includes stdio.h */  

 int width=79, height=24, starty=0, startx=0; 
 int ch, xc, yc, loop1=1;
 mmask_t *oldstate;
 WINDOW *winx;

 initscr();				/* start the curses mode */
 keypad(stdscr, TRUE);

 //  getmaxyx(stdscr,height,width);		/* get the number of rows and columns */
 //  printw("\n ht=%d   wd=%d  /n",height, width  );

 refresh();  //  must have this line or it doesn't work
 
 //  wclear(winx);
  winx = newwin(height, width, starty=0, startx=0);
 //  wborder(winx, '|', '|', '-', '-', '+', '+', '+', '+');
 box(winx, 0 , 0); 			 // 0, 0 gives default characters 
 mvprintw(2,1," To change, click value, type new value, then hit Enter.  To exit hit End.");
 mvprintw(4,1,"  Parameter    Value   Max    Min ");
 mvprintw(5,1," ------------  -----  -----  -----");
 //  move(8,8);
 mvprintw(6,1,"   frequency w1: %1.3f  9.999  0.001",w1);
 mvprintw(7,1,"   frequency w2: %1.3f  9.999  0.001",w2);
 mvprintw(8,1,"   frequency w3: %1.3f  9.999  0.001",w3);
 mvprintw(10,1,"    x-axis fcn#: %i",xf);
 mvprintw(10,23,"    12      1 ");
 mvprintw(11,1,"    y-axis fcn#: %i",yf);
 mvprintw(11,23,"    12      1 ");
 mvprintw(13,1," x offset (xof): %i",xof);
 mvprintw(13,23,"  99999     0 ");
 mvprintw(14,1," y offset (yof): %i",yof);
 mvprintw(14,23,"  99999     0 ");
 mvprintw(16,1,"    x mult (xm): %i",xm);
 mvprintw(16,23,"  99999     0 ");
 mvprintw(17,1,"    y mult (ym): %i",ym);
 mvprintw(17,23,"  99999     0 ");
 mvprintw(19,1,"    pixel delay: %i",delay);
 mvprintw(19,23,"  99999     0 ");
 mvprintw(20,1,"   graph length: %i",glength);
 mvprintw(20,23,"   9999     0 ");
 mvprintw(21,1,"     time scale: %1.3f  9.999  0.001",k1); 
 wrefresh(winx);
 
mvprintw(4,38,"| fcn#  x-axis fcn (y-axis: yof & ym)");
mvprintw(5,38,"| ---- ------------------------------");		//  these
mvprintw(6,38,"|   1  xof+(int)(xm*sin(w1*t))");		//  lines
mvprintw(7,38,"|   2  xof+(int)(xm*sin(w2*t))");		//  print
mvprintw(8,38,"|   3  xof+(int)(xm*sin(w3*t))");		//  text
mvprintw(9,38,"|   4  xof+(int)(xm*(f1+f2))");			//  only
mvprintw(10,38,"|   5  xof+(int)(xm*(f1*f2))");			//
mvprintw(11,38,"|   6  xof+(int)(xm*(f1+f2)*f3)");		//
mvprintw(12,38,"|   7  xof+(int)(xm*(f1*f2)*f3)");		//
mvprintw(13,38,"|   8  xof+(int)(xm*exp(-f1))");		//
mvprintw(14,38,"|   9  xof+(int)(xm*exp(-(f1+f2)))");		//
mvprintw(15,38,"|  10  xof+(int)(xm*exp(-(f1+f3)))");		//
mvprintw(16,38,"|  11  xof+(int)(xm*exp(-(f1*f2)))");		//
mvprintw(17,38,"|  12  xof+(int)(xm*exp(-(f2*f3)))");		//
mvprintw(18,38,"|");						//
mvprintw(19,38,"|            f1 = fcn#1");			//
mvprintw(20,38,"|");						//
mvprintw(21,38,"|          program: graf.cpp");			//

 mousemask(ALL_MOUSE_EVENTS, oldstate);
 MEVENT event;
 while(loop1==1)
 {   
    ch = getch();
    if(ch == KEY_MOUSE)
     {    if(getmouse(&event) == OK)  //  if(getmouse(&event) == BUTTON1_CLICKED)
         {   xc = event.x;
	     yc = event.y;
//	     printw("\n x-coord is:  %d\n",xc);
//	     printw("\n y-coord is:  %d\n",yc);
	     if(xc>=18 && xc<=22)
	     {  switch(yc)
		{
			case 6: mvprintw(6,18,"     ");
				wrefresh(winx);
				mvscanw(6,18,"%f",&w1);
				mvprintw(6,18,"%1.3f",w1);
				wrefresh(winx);
				break;
			case 7: mvprintw(7,18,"     ");
				wrefresh(winx);
				mvscanw(7,18,"%f",&w2);
				mvprintw(7,18,"%1.3f",w2);
				wrefresh(winx);
				break;
			case 8: mvprintw(8,18,"     ");
				wrefresh(winx);
				mvscanw(8,18,"%f",&w3);
				mvprintw(8,18,"%1.3f",w3);
				wrefresh(winx);
				break;
			case 10: mvprintw(10,18,"     ");
				wrefresh(winx);
				mvscanw(10,18,"%i",&xf);
				mvprintw(10,18,"%i",xf);
				wrefresh(winx);
				break;
			case 11: mvprintw(11,18,"     ");
				wrefresh(winx);
				mvscanw(11,18,"%i",&yf);
				mvprintw(11,18,"%i",yf);
				wrefresh(winx);
				break;
			case 13: mvprintw(13,18,"     ");
				wrefresh(winx);
				mvscanw(13,18,"%i",&xof);
				mvprintw(13,18,"%i",xof);
				wrefresh(winx);
				break;
			case 14: mvprintw(14,18,"     ");
				wrefresh(winx);
				mvscanw(14,18,"%i",&yof);
				mvprintw(14,18,"%i",yof);
				wrefresh(winx);
				break;
			case 16: mvprintw(16,18,"     ");
				wrefresh(winx);
				mvscanw(16,18,"%i",&xm);
				mvprintw(16,18,"%i",xm);
				wrefresh(winx);
				break;
			case 17: mvprintw(17,18,"     ");
				wrefresh(winx);
				mvscanw(17,18,"%i",&ym);
				mvprintw(17,18,"%i", ym);
				wrefresh(winx);
				break;
			case 19: mvprintw(19,18,"     ");
				wrefresh(winx);
				mvscanw(19,18,"%i",&delay);
				mvprintw(19,18,"%i",delay);
				wrefresh(winx);
				break;
			case 20: mvprintw(20,18,"     ");
				wrefresh(winx);
				mvscanw(20,18,"%i",&glength);
				mvprintw(20,18,"%i",glength);
				wrefresh(winx);
				break;
			case 21: mvprintw(21,18,"     ");
				wrefresh(winx);
				mvscanw(21,18,"%f",&k1);
				mvprintw(21,18,"%1.3f",k1);
				wrefresh(winx);
				break;


		 }
              } //  end of if (xc	
	  }  	//  end of if (getmouse	 
      }      	//  end of if (ch==KEY_MOUSE
    if(ch == KEY_END)
    loop1=0;      	
 }		//  end of while(loop1)
 delwin(winx);
 endwin();
 return 0;
}



