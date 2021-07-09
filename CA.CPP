#include<iostream.h>
#include<graphics.h>
#include<stdio.h>
#include<dos.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define  gt  gotoxy
#define  tc  textcolor
#define  tb  textbackground

struct dosdate_t date;

void cur_time()
{
	char *mer=(char *)malloc(2*sizeof(char));
	while(!kbhit())
	{
		struct dostime_t t;
		_dos_gettime(&t);
		gt(65,10); tb(0); tc(15);
		if(t.hour<12) mer="AM";
		else strcpy(mer,"PM");
		if(t.hour>12) t.hour=t.hour-12;
		cprintf("Current Time :-");
		gt(65,12); cprintf("%d:%02d:%02d  %s",t.hour,t.minute,t.second,mer);
	}
}

void agecal();
void public_day();

void main()
{
	int gdriver=0, gmode=0;
	initgraph(&gdriver,&gmode,"C:\\TURBOC3\\bgi");
	setbkcolor(9);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR,5);
	setcolor(14);
	outtextxy(100,210,"Calendar Applications");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(3);
	setcolor(1);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);

	int l=getmaxy()-40;
	int m=getmaxy()-450;
	int q=10,r=618;

	for(int b=0;b<39;b++)
	{
		outtextxy(q,l,"=");
		outtextxy(r,l,"=");
		outtextxy(q,m,"=");
		outtextxy(r,m,"=");
		q+=8;
		r-=8;
		delay(50);
	}

	closegraph();

	char *day[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	char *month[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	char ca[]="Calendar of year";
	long tdm[]={31,28,31,30,31,30,31,31,30,31,30,31};
	long year,i,j,n,T,Startday,color,k=0,ch,endday,to,lastday;

	start:
	_setcursortype(_NORMALCURSOR); tc(14);
	gt(21,10); cprintf("====================================");
	gt(21,12); cprintf("====================================");
	gt(21,14); cprintf("====================================");

	iy:
	gt(42,11); clreol();
	gt(23,11); tc(15); cprintf("Enter the year : ");
	gt(45,11); scanf("%ld",&year);

	if(year<=0 || year>=999999999) goto iy;

	im:
	gt(40,13); clreol();
	gt(23,13); tc(15); cprintf("Enter the month : ");
	gt(45,13); scanf("%ld",&k);

	if(k<1 || k>12) goto im;
	else k--;

	_setcursortype(_NOCURSOR);
	clrscr();

	for(i=0;i<strlen(ca);i++)
	{
		gt(30+strlen(ca)-1-i,2);
		cprintf("%c",ca[strlen(ca)-1-i]);
		delay(30);
	}

	for(i=0;i<strlen(ca);i++)
	{
		gt(30+strlen(ca)-1-i,2);
		cprintf(" ");
		delay(30);
	}

	for(i=0;i<strlen(ca);i++)
	{
		gt(30+i,2);
		cprintf("%c",ca[i]);
		delay(30);
	}

	gt(47,2); cprintf("%ld",year);

	tha:
	tb(14);
	tc(WHITE);
	gt(5,21); cprintf("  nput year ");
	gt(43,21); cprintf(" P blic holiays ");
	gt(23,21); cprintf(" Current  ate ");
	gt(65,21); cprintf(" E it = Esc ");
	gt(5,23); cprintf("  ge calculator ");
	tc(10);
	gt(6,21); cprintf("I");
	gt(45,21); cprintf("u");
	gt(32,21); cprintf("d");
	gt(67,21); cprintf("x");
	gt(6,23); cprintf("A");
	tb(0);
	tc(3);
	gt(2,8); cprintf("%c increase year",24);
	gt(2,14); cprintf("%c increase month",26);
	gt(2,10); cprintf("%c decrease year",25);
	gt(2,16); cprintf("%c decrease month",27);
	tc(7);

	tt:
	tb(0); to=0; lastday=0;
	/*Formula of the firstday(1 Jan)*/
	T=((year-1)*365)+((year-1)/4)-((year-1)/100)+((year-1)/400)+1;
	Startday=T%7;
	/*Formula of Leap year*/
	tdm[1]=(!((year%4) || !(year%100) && (year%400)))? 29 : 28;

	if(k>0)
	{
		for(i=0;i<k;i++) to=to+tdm[i];
		lastday=to%7;
	}
	Startday=Startday+lastday;
	_dos_getdate(&date);
	j=0;

	tb(0);
	tc(15);
	gt(47,2); clreol();
	gt(30,2); cprintf("Calendar of year %ld",year);
	gt(30,3); cprintf("---------------------");
	gt(39,4); cprintf("%s",month[k]);
	/*the last day in the month*/
	endday=tdm[k];

	tc(14);
	gt(21,5); cprintf("=======================================");
	gt(21,7); cprintf("=======================================");
	gt(22,8); cprintf("                                     "  );

	for(i=0;i<10;i++)
	{
		gt(21,10+i);
		cprintf("                                       ");
	}

	for(i=0;i<7;i++)
	{
		if(i==0) color=12;
		else color=7;
		gt(24+5*i,6); tc(color); cprintf("%s",day[i]);
	}

	for(i=1;i<=endday;i++)
	{
		if(Startday>6)
		{
			Startday=Startday-7;
			j++;
		}
		if(Startday==0) color=12;
		else color=7;
		/*public day*/
		if(year>1993)
		{
			if(k==0) if(i==1 || i==7) color=12;
			if(k==2) if(i==8) color=12;
			if(k==3) if(i==13 || i==14 || i==15 || i==16 || i==30) color=12;
			if(k==4) if(i==1) color=12;
			if(k==5) if(i==1 || i==18) color=12;
			if(k==8) if(i==24) color=12;
			if(k==9) if(i==23 || i==30 || i==31) color=12;
			if(k==10) if(i==1 || i==9) color=12;
			if(k==11) if(i==10) color=12;
		}
		if(Startday==0) color=12;
		if(i==1) j=0;
		/*show the current date*/
		((i==date.day) && ((k+1)==date.month) && (year==date.year)) ? tb(9) : tb(0);
		/*Output calendar of each month*/
		gt(25+5*Startday,8+2*j); tc(color); cprintf("%ld",i);
		Startday++;
	}

	tc(14); tb(0);
	for(i=8;i<=8+2*j;i++)
	{
		gt(21,i); cprintf(" ");
		gt(59,i); cprintf(" ");
	}
	gt(21,8+2*j+1) ; cprintf("=======================================");

	again:
	cur_time(); /*call function for time*/

	ch=getch();
	if(ch==77)
	{
		if(k<11) k++;
		else
		{
			k=0;
			year++;
		}
		goto tt;
	}
	else if(ch==72)
	{
		year++;
		goto tt;
	}
	else if(ch==80)
	{
		if(year>1) year--;
		goto tt;
	}
	else if(ch==75)
	{
		if(k>0) k=k-1;
		else
		{
			if(year>1)
			{
				year--;
				k=11;
			}
			else k=0;
		}
		goto tt;
	}
	else if(ch==27 || ch=='x' || ch=='X') exit(1);
	else if(ch=='d' || ch=='D')
	{
		k=date.month-1;
		year=date.year;
		goto tt;
	}
	else if(ch=='I' || ch=='i')
	{
		clrscr();
		goto start;
	}
	else if(ch=='u' || ch=='U')
	{
		public_day();
		clrscr();
		goto tha;
	}
	else if(ch=='a' || ch=='A')
	{
		agecal();
		clrscr();
		goto tha;
	}
	else goto again;
}

void agecal()
{
	clrscr();

	int bd,cd,aged,bm,cm,agem,by,cy,agey;
	int month[]={31,28,31,30,31,30,31,31,30,31,30,31};

	gt(22,4); tc(15) ; cprintf("Enter Birth Date : ");
	gt(45,4); scanf("%d",&bd);
	gt(22,6); tc(15) ; cprintf("Enter Birth Month : ");
	gt(45,6); scanf("%d",&bm);
	gt(22,8); tc(15) ; cprintf("Enter Birth Year : ");
	gt(45,8); scanf("%d",&by);
	gt(22,10); tc(15) ; cprintf("Enter Current Date : ");
	gt(45,10); scanf("%d",&cd);
	gt(22,12); tc(15) ; cprintf("Enter Current Month : ");
	gt(45,12); scanf("%d",&cm);
	gt(22,14); tc(15) ; cprintf("Enter Current Year : ");
	gt(45,14); scanf("%d",&cy);
	gt(20,16); tc(14); cprintf("=======================================");

	if(bd > cd)
	{
		cd=cd+month[bm-1];
		cm=cm-1;
	}

	if(bm > cm)
	{
		cy=cy-1;
		cm=cm+12;
	}

	aged=cd-bd;
	agem=cm-bm;
	agey=cy-by;

	gt(22,18); tc(14); cprintf("Age is %d years %d months %d Days",agey,agem,aged);
	getch();
}

void public_day ()
{
	int i,j=0;
	clrscr();

	for(i=0;i<74;i++)
	{
		gt(4+i,5); cprintf("อ");
		gt(4+i,21); cprintf("อ");
	}

	for(i=0;i<15;i++)
	{
		gt(41,i+6); cprintf("ณ");
	}

	tc(1); gt(7,7); cprintf("1-Jan : ");
	tc(7); cprintf("New Year");
	tc(1); gt(7,9); cprintf("14-Jan : ");
	tc(7); cprintf("Maker Sankranti");
	tc(1); gt(7,11); cprintf("26-Jan : ");
	tc(7); cprintf("Republic Day");
	tc(1); gt(7,13); cprintf("14-Feb : ");
	tc(7); cprintf("Valentines Day");
	tc(1); gt(7,15); cprintf("4-Mar : ");
	tc(7); cprintf("MahaShiv ratri");
	tc(1); gt(7,17); cprintf("20-Mar : ");
	tc(7); cprintf("Holika Daihen");
	tc(1); gt(7,19); cprintf("15-Aug : ");
	tc(7); cprintf("Indipendance Day");
	tc(1); gt(44,7); cprintf("10-sept : ");
	tc(7); cprintf("Muharram");
	tc(1); gt(44,9); cprintf("11-Sept : ");
	tc(7); cprintf("onam");
	tc(1); gt(44,11); cprintf("8-Oct : ");
	tc(7); cprintf("Dussehra");
	tc(1); gt(44,13); cprintf("27-Oct : ");
	tc(7); cprintf("Diwali");
	tc(1); gt(44,15); cprintf("12-Nov : ");
	tc(7); cprintf("Guru Nanakdev Jayanti");
	tc(1); gt(44,17); cprintf("14-Nov : ");
	tc(7); cprintf("children Day");
	tc(1); gt(44,19); cprintf("25-Dec : ");
	tc(7); cprintf("Christmas");

	tc(14+BLINK); gt(28,24); cprintf("Press Any Key to go back...");

	while(!kbhit())
	{
		if(i>15) i=1;
		if(j>10) j=0;
		tc(15); gt(34,4); cprintf("    ออออออ     ");
		tc(i); gt(34,3); cprintf("PUBLIC HOLIDAYS");
		tc(j); gt(35+j,4); cprintf("อ");
		i++;
		j++;
	}
}