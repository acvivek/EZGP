#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <alloc.h>
#include <ctype.h>
/*screen limits*/
#define scx 8
#define scy 41
#define scw 520
#define sch 384
#define mscx (scx+scw)/2
#define mscy (scy+sch)/2
#define tfile "x.txt"
/*global flag color,shape,save*/
int gd=DETECT,gm=DETECT;
void * buf1;
void far *dbuf1=NULL,far *dbuf2=NULL,far *dbuf3=NULL,far *dbuf4=NULL;
int saved=0;
int select_color=0;
int select_style=1;
int select_shape=-1;
char mainmenu[5][10]={"File","Edit","Image","Demos"," Help"};
char sub[6][5][12]=
{"New","Open","Save","Save As","Exit",
"Select","Cut","Copy","Paste","Clear",
"Choose","Rotate","Scale","InvertColor","Translation",
"Spiral","Cardioid","Astroid","Lemniscate","",
"Tips","About","Help","",""};
int len[]={5,5,5,4,3};
int m=0,s=0;
char tip[60];
/*File menu actions*/
int fnamed=0;
int fsaved=1;
char file_name[30];
int fname_len=0;
void file_save();
void file_saveas();
char imnum[10];
int imlen=0;
int * p_buf;
/*Mouse & Image functions*/
#include "mouse.h"
#include "function.cpp"
#include "video.h"
#include "dialog.cpp"
#include "demo.cpp"
#include "menuaction.cpp"
#include "comm.cpp"
//custom shapes line,rect,ellipse
void myline(int x1,int y1,int x2,int y2,int f)
{
	if(f==1 && p_buf==NULL) return;
	int d,de,dne,dx,dy,flag=0,incr,i=0;
	dx=abs(x1-x2);
	dy=abs(y1-y2);
	if(dy>dx)
	{
		swap(x1,y1);
		swap(x2,y2);
		swap(dx,dy);
		flag=1;
	}
	if(x1>x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	de=dy;
	dne=dy-dx;
	d=dy-dx/2;
	if(y1<y2) incr=1; else incr=-1;
	if(f==0) p_buf=(int*) malloc(sizeof(abs(x1-x2)+abs(y1-y2)));
	if(p_buf==NULL) return;
	while(x1<x2)
	{
		if(flag==1)
		{
			if(f==0)
			{
			*(p_buf+i)=getpixel(y1,x1);
			i++;
			putpixel(y1,x1,select_color);
			}
			else
			{
			putpixel(y1,x1,*(p_buf+i));
			i++;
			}
		}
		else
		{
			if(f==0)
			{
			*(p_buf+i)=getpixel(x1,y1);
			i++;
			putpixel(x1,y1,select_color);
			}
			else
			{
			putpixel(x1,y1,*(p_buf+i));
			i++;
			}
		}
		if(d<=0)
		{
			d+=de;
			x1++;
		}
		else
		{
			d+=dne;
			x1++;
			y1+=incr;
		}
	}
	if(f==1) free(p_buf);
}
void myrect(int x1,int y1,int x2,int y2,int f)
{
	if(f==1 && p_buf==NULL) return;
	int i,l=0;
	if(x1>x2) swap(x1,x2);
	if(f==0) p_buf=(int*)malloc(sizeof(2*abs(x1-x2)+2*abs(y1-y2)));
	if(p_buf==NULL) return;
	for(i=x1+1;i<x2;i++)
	{
		if(f==0)
		{
			*(p_buf+l)=getpixel(i,y1);
			l++;
			*(p_buf+l)=getpixel(i,y2);
			l++;
			putpixel(i,y1,select_color);
			putpixel(i,y2,select_color);
		}
		else
		{
			putpixel(i,y1,*(p_buf+l));
			l++;
			putpixel(i,y2,*(p_buf+l));
			l++;
		}
	}
	if(y1>y2) swap(y1,y2);
	for(i=y1+1;i<y2;i++)
	{
		if(f==0)
		{
			*(p_buf+l)=getpixel(x1,i);
			l++;
			*(p_buf+l)=getpixel(x2,i);
			l++;
			putpixel(x1,i,select_color);
			putpixel(x2,i,select_color);
		}
		else
		{
			putpixel(x1,i,*(p_buf+l));
			l++;
			putpixel(x2,i,*(p_buf+l));
			l++;
		}
	}
	if(f==1) free(p_buf);
}
void myellipse(int x1,int y1,double a,double b,int f)
{
	int l=0;static int col1,col2;
	if(f==1 && p_buf==NULL) return;
	double x=0,y=b;
	double d1=b*b-a*a*b+.25*a*a;
	double d2;
	if(f==0) col1=getpixel(x1+a,y1),col2=getpixel(x1-a,y1);
	if(f==0) p_buf=(int*)malloc(sizeof(4*(a+b)));
	if(f==0)
	{
		*(p_buf+l)=getpixel(x1+a,y1);
		l++;
		putpixel(x1+a,y1,select_color);
		*(p_buf+l)=getpixel(x1+a,y1);
		putpixel(x1+a,y1,select_color);
		l++;
		*(p_buf+l)=getpixel(x1,y1+b);
		l++;
		putpixel(x1,y1+b,select_color);
		*(p_buf+l)=getpixel(x1,y1-b);
		l++;
		putpixel(x1,y1-b,select_color);
	}
	else
	{
		putpixel(x1+a,y1,*(p_buf+l));
		l++;
		putpixel(x1+a,y1,*(p_buf+l));
		l++;
		putpixel(x1,y1+b,*(p_buf+l));
		l++;
		putpixel(x1,y1-b,*(p_buf+l));
		l++;
	}
	while(a*a*(y-.5)>b*b*(x+1))
	{
		if(d1<0)
			d1+=b*b*(2*x+3);
		else
		{
			d1+=b*b*(2*x+3)+a*a*(-2*y+2);
			y--;
		}
		x++;
		if(f==0)
		{
			*(p_buf+l)=getpixel(x1+x,y1+y);
			l++;
			putpixel(x1+x,y1+y,select_color);
			*(p_buf+l)=getpixel(x1+x,y1-y);
			l++;
			putpixel(x1+x,y1-y,select_color);
			*(p_buf+l)=getpixel(x1-x,y1+y);
			l++;
			putpixel(x1-x,y1+y,select_color);
			*(p_buf+l)=getpixel(x1-x,y1-y);
			l++;
			putpixel(x1-x,y1-y,select_color);
		}
		else
		{
			putpixel(x1+x,y1+y,*(p_buf+l));
			l++;
			putpixel(x1+x,y1-y,*(p_buf+l));
			l++;
			putpixel(x1-x,y1+y,*(p_buf+l));
			l++;
			putpixel(x1-x,y1-y,*(p_buf+l));
			l++;
		}
	}
	d2=b*b*(x+.5)*(x+.5)+a*a*(y-1)*(y-1)-(a*a*b*b);
	while(y>0)
	{
		if(d2<0)
		{
			d2+=b*b*(2*x+2)+a*a*(-2*y+3);
			x++;
		}
		else
			d2+=a*a*(-2*y+3);
		y--;
		if(f==0)
		{
			*(p_buf+l)=getpixel(x1+x,y1+y);
			l++;
			putpixel(x1+x,y1+y,select_color);
			*(p_buf+l)=getpixel(x1+x,y1-y);
			l++;
			putpixel(x1+x,y1-y,select_color);
			*(p_buf+l)=getpixel(x1-x,y1+y);
			l++;
			putpixel(x1-x,y1+y,select_color);
			*(p_buf+l)=getpixel(x1-x,y1-y);
			l++;
			putpixel(x1-x,y1-y,select_color);
		}
		else
		{
			putpixel(x1+x,y1+y,*(p_buf+l));
			l++;
			putpixel(x1+x,y1-y,*(p_buf+l));
			l++;
			putpixel(x1-x,y1+y,*(p_buf+l));
			l++;
			putpixel(x1-x,y1-y,*(p_buf+l));
			l++;
		}
	}
	if(f==1)
	{
		putpixel(x1+a,y1,col1);
		putpixel(x1-a,y1,col2);
		free(p_buf);
		setcolor(col2);
		line(x1-a,y1-b,x1-a,y1+b);
	}
}
void mytriangle(int x1,int y1,int x2,int y2,int f)
{
	if(f==1 && p_buf==NULL) return;
	int x3,y3,i,m1,m2,l=0,col=WHITE;
	x3=(x1+x2)/2;
	y3=y2;
	y2=y1;
	col=getpixel(x3,y3);
	if(x1>x2) swap(x1,x2);
	if(f==0) p_buf=(int*)malloc(sizeof(3*(x1-x2)+3*(y1-y2)));
	if(p_buf==NULL) return;
	for(i=x1;i<x2;i++)
	{
		if(f==0)
		{
			*(p_buf+l)=getpixel(i,y1);
			l++;
			putpixel(i,y1,select_color);
		}
		else
		{
			putpixel(i,y1,*(p_buf+l));
			l++;
		}
	}
	int j=y1;
	for(i=x1;i<=x3;i++)
	{
		if(y3<y1) j--; else j++;
		if(j<scy || j>scy+sch) break;
		if(f==0)
		{
			*(p_buf+l)=getpixel(i,j);
			l++;
			putpixel(i,j,select_color);
		}
		else
		{
			putpixel(i,j,*(p_buf+l));
			l++;
		}
	}
	j=y2;
	for(i=x2;i>x3;i--)
	{
		if(y1>y3) j--; else j++;
		if(j<scy || j>scy+sch) break;
		if(f==0)
		{
			*(p_buf+l)=getpixel(i,j);
			l++;
			putpixel(i,j,select_color);
		}
		else
		{
			putpixel(i,j,*(p_buf+l));
			l++;
		}
	}
	if(f==1) {free(p_buf);putpixel(x3,y3,col);}
}

//TITLE BAR & GRAY BACKGND
class title
{
	int x,y;
	char h[30];
	public:
	title()
	{
		x=0;
		y=0;
	}
	void show();
	void set(char []);
};
void title::show()
{
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(scx,scy+sch,scx+scw,scy+sch+50);
	bar(0,scy,scx,scy+450);
	bar(scx+scw,scy-25,scx+scw+120,scy+sch+50);
	setfillstyle(SOLID_FILL,BLUE);
	bar(x,y,x+639,y+19);
	bar(x,y+476,x+639,y+480);
	bar(x+636,y+1,x+639,y+480);
	bar(x,y+1,x+3,y+480);
	setcolor(WHITE);
	outtextxy(x+10,y+5,h);
}
void title::set(char a[30])
{
	strcpy(h,a);
}
//CLOSE BUTTON
class close
{
	int x,y,w;
	public:
	close()
	{
		x=620,y=0,w=20;
	}
	void show();
	void check();
};
void close::show()
{
	setfillstyle(SOLID_FILL,RED);
	bar(x+4,y+4,x+w-4,y+w-4);
	setcolor(WHITE);
	line(x+5,y+5,x+w-5,y+w-5);
	line(x+5,y+w-5,x+w-5,y+5);
}
void close::check()
{
	 get_button_press(0);
	 while(get_button_release(0)==1);
	 if(mx>=x+4 && mx<=x+w-4 && my>=y+4 && my<=y+w-4 && mclick==1) file_exit();
}
//MESSAGE BOX
class message
{
	int x1,x2,y1,y2;
	public:
	message()
	{
		x1=150,y1=100,x2=450,y2=300;
	}
	int get();
	void clear();
	void draw_messagebox(char[],char []);
};
void message::clear()
{
	restore_video(x1,y1,1);
}
void message::draw_messagebox(char t[],char m[])
{
	save_video(x1,y1,x2,y2);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	hide_mouse();
	bar(x1,y1,x2,y2);
	setfillstyle(SOLID_FILL,BLUE);
	bar(x1,y1,x2,y1+25);
	setcolor(BLACK);
	rectangle(x1,y1,x2,y2);
	line(x1,y1+25,x2,y1+25);
	outtextxy(x1+10,y1+50,m);
	int x=(x1+x2)/2;
	int y=(y1+y2)/2+50;
	setcolor(WHITE);
	outtextxy(x1+10,y1+10,t);
	line(x-20,y-10,x+20,y-10);
	line(x-20,y-10,x-20,y+10);
	setcolor(BLACK);
	line(x-20,y+10,x+20,y+10);
	line(x+20,y-10,x+20,y+10);
	outtextxy(x-8,y,"OK");
}
int message::get()
{
	int x=(x1+x2)/2;
	int y=(y1+y2)/2+50;
	show_mouse();
	get_button_press(0);
	if(mx>=x-20 && mx<=x+20 && my>=y-10 && my<=y+10 && mclick==1)
	{
		setcolor(BLACK);
		line(x-20,y-10,x+20,y-10);
		line(x-20,y-10,x-20,y+10);
		setcolor(WHITE);
		line(x-20,y+10,x+20,y+10);
		line(x+20,y-10,x+20,y+10);
		delay(100);
		return 1;
	}
	return 0;
}
//MENU DISP,CHECK,ACTION
class menu
{
	int x,y,w,h;
	int main_menu;
	int choice_mm;
	int choice_sb;
	public:
	int choice_flag;
	menu()
	{
		w=40;
		h=20;
		choice_flag=0;
	}
	void draw(int,int,char [5][10]);
	int mainclick();
	void subclick(int);
	void option();
	void refreshmenu(int);
	void subcheck(int);
	void highlight(int,int);
	void action();
};
void menu::action()
{
	int a,b;
	message me;
	switch(choice_mm)
	{
		case 1:
			switch(choice_sb)
			{
				case 1: file_new();
				break;
				case 2: file_open();
				break;
				case 3: file_save();
				break;
				case 4: file_saveas();
				break;
				case 5: file_exit();
			}
		break;
		case 2:
			switch(choice_sb)
			{
				case 1:   while(ed.select()==0);
				break;
				case 2:   ed.cut();
				break;
				case 3:   ed.copy();
				break;
				case 4:   ed.paste();
				break;
				case 5: ed.clear();
			}
		break;
		case 3:
			switch(choice_sb)
			{
				case 1: while(im.select()==0);
				break;
				case 2: im.rotate();
				break;
				case 3: im.scale();
				break;
				case 4: im.invert();
				break;
				case 5: im.translate();
			}
		break;
		case 4:
			switch(choice_sb)
			{
				case 1:   select_shape=20;
				break;
				case 2:   select_shape=21;
				break;
				case 3:   select_shape=22;
				break;
				case 4:   select_shape=23;
				break;
			}
			setcolor(LIGHTGRAY);
			for(a=0;a<=1;a++)
			for(b=0;b<=5;b++)
			rectangle(540+a*40+1,42+b*40+1,540+a*40+39,42+b*40+39);
		break;
		case 5:
			switch(choice_sb)
			{
				case 1:
					get_tip();
					me.draw_messagebox("TIP OF THE DAY!",tip);
					while(1)
						if(me.get()==1) break;
					me.clear();
				break;
				case 2:
					me.draw_messagebox("ABOUT EZ PAINT","This is done by A.C.Vivek");
					while(1)
						if(me.get()==1) break;
					me.clear();
				break;
				case 3:
					closegraph();
					system("notepad.exe help.txt");
					exit(0);
				break;
			}
		break;
	}
	choice_flag=0;
}
void menu::subcheck(int m)
{
	int j;
	hide_mouse();
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar((m-1)*50+10,40,(m-1)*50+110,len[m-1]*20+40);
	for(j=0;j<len[m-1];j++)
	{
		setcolor(BLACK);
		outtextxy((m-1)*50+12,j*20+45,sub[m-1][j]);
	}
	show_mouse();
}
void menu::highlight(int m,int s)
{
	static int a=0,b=0,c=0;
	if(s>len[m-1]) return;
	hide_mouse();
	if(a==m && b!=s)
	{
		c=0;
		setcolor(LIGHTGRAY);
		rectangle((a-1)*50+10,b*20+20,(a-1)*50+110,b*20+40);
	}
	else
	{
		setcolor(WHITE);
		line((m-1)*50+10,s*20+20,(m-1)*50+110,s*20+20);
		line((m-1)*50+10,s*20+20,(m-1)*50+10,s*20+40);
		setcolor(BLACK);
		line((m-1)*50+110,s*20+20,(m-1)*50+110,s*20+40);
		line((m-1)*50+10,s*20+40,(m-1)*50+110,s*20+40);
		c++;
		if(c==1)
		music();
	}
	a=m,b=s;
	show_mouse();
}
void menu::refreshmenu(int m)
{
	int i,j;
	hide_mouse();
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	for(i=1;i<=6;i++)
	{
		if(i!=m)
		{
			setcolor(LIGHTGRAY);
			rectangle((i-1)*50+10,20,(i-1)*50+59,39);
		}
		else
		{
			setcolor(BLACK);
			line((i-1)*50+10,20,(i-1)*50+59,20);
			line((i-1)*50+10,20,(i-1)*50+10,39);
			setcolor(WHITE);
			line((i-1)*50+10,39,(i-1)*50+59,39);
			line((i-1)*50+59,20,(i-1)*50+59,39);
		}
	}
	show_mouse();
}
int menu::mainclick()
{
	get_button_press(0);
	if(mclick==1)
	{
	if(mx>=10 && mx<=60 && my>=20 && my<=40) return 1;
	else
	if(mx>=60 && mx<=110 && my>=20 && my<=40) return 2;
	else
	if(mx>=110 && mx<=160 && my>=20 && my<=40) return 3;
	else
	if(mx>=160 && mx<=210 && my>=20 && my<=40) return 4;
	else
	if(mx>=210 && mx<=260 && my>=20 && my<=40) return 5;
	return -1;
	}
	return 0;
}
void menu::subclick(int m)
{
	int sub=0;
	mx=my=0;
	mouse_status();
	if(my>=40 && my<=60) highlight(m,1);
	if(my>=60 && my<=80) highlight(m,2);
	if(my>=80 && my<=100) highlight(m,3);
	if(my>=100 && my<=120) highlight(m,4);
	if(my>=120 && my<=140) highlight(m,5);
	if(get_button_release(0)==0)
	{
		if(mx>=(m-1)*50+10 && mx<=(m-1)*50+110)
		{
			if(my>=40 && my<=60) sub=1;
			if(my>=60 && my<=80) sub=2;
			if(my>=80 && my<=100) sub=3;
			if(my>=100 && my<=120) sub=4;
			if(my>=120 && my<=140) sub=5;
			if(choice_flag==0)
			{
				choice_flag=1;
				choice_mm=m;
				choice_sb=sub;
			}
		}
	}
	show_mouse();
}
void menu::option()
{
	m=mainclick();
	if(m==-1) return ;
	while(m>=1 && m<=6)
	{
		while(m==s)
		{
			show_mouse();
			m=mainclick();
			if(m==-1) return ;
			subclick(m);
		}
		refreshmenu(m);
		subcheck(m);
		s=m;
	}
}
void menu::draw(int x,int y,char a[5][10])
{
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(x-6,y,x+530,y+20);
	setcolor(BLACK);
	for(int i=0;i<5;i++)
		outtextxy(x+i*50,y+5,a[i]);
}
class fillstyle
{
	public:
	int x,y,w,h;
	fillstyle()
	{
		x=400,y=450,w=200,h=20;
	}
	void show();
	void check();
}fs;
void fillstyle::show()
{
	int i;
	setcolor(BLACK);
	outtextxy(x-150,y-5,"Fill Style");
	for(i=1;i<=10;i++)
	{
		setcolor(select_color);
		setfillstyle(i,select_color);
		bar(x+i*20-10+1,y-10,x+i*20+10-1,y+10);
	}
	setfillstyle(select_style,select_color);
	bar(x-20,y-10,x,y+10);
}
void fillstyle::check()
{
	int i;
	get_button_press(0);
	if(mclick==1 && mx>=x && my>=y-10 && mx<=x+w && my<=y+h)
	{
		for(i=1;i<=10;i++)
		{
			if(mx>=x+i*20-10 && mx<=x+i*20+10 && my>=y-10 && my<=y+10)
			{
				select_style=i;
				setfillstyle(select_style,select_color);
				bar(x-20,y-10,x,y+10);
				break;
			}
		}
	}
}

//COLOR SELECTION
class color
{
	public:
	int x,y,w,h;
	color()
	{
		s=BLACK;
		x=45,y=430,w=160,h=40;
	}
	void show();
	void check();
};
void color::show()
{
	int i,j;
	static int c=0;
	if(c==0)
	{
		for(i=0;i<8;i++)
		{
			setfillstyle(SOLID_FILL,i);
			bar(x+20*i+2,y+2,x+20+20*i-2,y+18);
			setcolor(BLACK);
			line(x+20*i+1,y+1,x+20*i+19,y+1);
			line(x+20*i+1,y+1,x+20*i+1,y+19);
			setcolor(WHITE);
			line(x+20*i+1,y+19,x+20*i+19,y+19);
			line(x+20*i+19,y+1,x+20*i+19,y+19);
		}
		for(i=0;i<8;i++)
		{
			setfillstyle(SOLID_FILL,i+8);
			bar(x+20*i+2,y+22,x+20+20*i-2,y+38);
			setcolor(BLACK);
			line(x+20*i+1,y+21,x+20*i+19,y+21);
			line(x+20*i+1,y+21,x+20*i+1,y+39);
			setcolor(WHITE);
			line(x+20*i+1,y+39,x+20*i+19,y+39);
			line(x+20*i+19,y+21,x+20*i+19,y+39);
		}
		setfillstyle(SOLID_FILL,select_color);
		bar(x-28,y+2,x-2,y+38);
		setcolor(BLACK);
		line(x-29,y+1,x-1,y+1);
		line(x-29,y+1,x-29,y+39);
		setcolor(WHITE);
		line(x-29,y+39,x-1,y+39);
		line(x-1,y+1,x-1,y+39);
	}
}
void color::check()
{
	int a,b;
	show_mouse();
	get_button_press(0);
	if(mx>=x && my>=y && mx<=x+w && my<=y+h)
	{
		if(mclick==1)
		{
			a=(mx-x)/20;
			b=(my-y)/20;
			if(a>=0 && a<=7 && b>=0 && b<=1)
				select_color=a+b*8;
			setfillstyle(SOLID_FILL,select_color);
			bar(x-28,y+2,x-2,y+38);
			fs.show();
			fs.check();
		}
	}
}
//ICONS SELECT
class icon
{
	public:
	int x,y,w,h;
	icon()
	{
		x=540,y=42,w=80,h=280;
	}
	void splash(int,int);
	void mirror(int,int);
	void text(int,int);
	void triangle(int,int);
	void poly(int,int);
	void spray(int,int);
	void brush(int,int);
	void pencil(int,int);
	void paint(int,int);
	void erase(int,int);
	void show();
	void check();
};
void icon::mirror(int x,int y)
{
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(x-1,y-6,x+1,y+6);
}
void icon::splash(int x,int y)
{
	line(x-5,y-5,x,y-2);
	line(x,y-2,x+5,y-5);
	line(x+5,y-5,x+2,y);
	line(x+2,y,x+5,y+5);
	line(x+5,y+5,x,y+2);
	line(x,y+2,x-5,y+5);
	line(x-5,y+5,x-2,y);
	line(x-2,y,x-5,y-5);
	setfillstyle(SOLID_FILL,MAGENTA);
	floodfill(x,y,BLACK);
}
void icon::text(int x,int y)
{
	setfillstyle(SOLID_FILL,BLACK);
	bar(x-2,y-4,x+2,y+8);
	bar(x-5,y-4,x+5,y-1);
}
void icon::triangle(int x,int y)
{
	line(x-5,y+5,x+5,y+5);
	line(x-5,y+5,x,y-5);
	line(x+5,y+5,x,y-4);
}
void icon::poly(int x,int y)
{
	setcolor(BLACK);
	line(x-3,y-5,x+1,y-5);
	line(x+1,y-5,x,y+2);
	line(x,y+2,x+5,y+2);
	line(x+5,y+2,x+5,y+5);
	line(x+5,y+5,x-5,y+5);
	line(x-5,y+5,x-3,y-5);
}
void icon::spray(int x,int y)
{
	setcolor(1);
	rectangle(x-2,y-5,x+2,y+5);
	arc(x,y-5,0,180,2);
	fill_color_bound(x,y,BLUE,SOLID_FILL);
	line(x-2,y-5,x-6,y-3);
	line(x-2,y-5,x-6,y-5);
	line(x-2,y-5,x-6,y-7);
}
void icon::pencil(int x,int y)
{
	setfillstyle(SOLID_FILL,RED);
	setcolor(RED);
	line(x-8,y+5,x+5,y-8);
	line(x-5,y+8,x+8,y-5);
	line(x+5,y-8,x+8,y-5);
	line(x-8,y+5,x-5,y+8);
	line(x-8,y+5,x-10,y+10);
	line(x-5,y+8,x-10,y+10);
	floodfill(x,y,RED);
}
void icon::erase(int x,int y)
{
	setfillstyle(SOLID_FILL,WHITE);
	bar(x-10,y-5,x+5,y+5);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(x-5,y-5,x+5,y+5);
}
void icon::paint(int x,int y)
{
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,GREEN);
	bar(x-5,y-6,x+5,y+6);
	setcolor(BLACK);
	line(x-7,y-6,x+5,y-6);
	line(x-5,y+2,x+5,y+2);
}
void icon::brush(int x,int y)
{
	setfillstyle(SOLID_FILL,BROWN);
	for(int i=0;i<=10;i+=2)
	line(x-5+i,y-12,x-5+i,y-8);
	bar(x-5,y-8,x+5,y-4);
	bar(x-1,y-5,x+1,y+5);
}
void icon::show()
{
	setcolor(BLACK);
	line(x+10,y+20,x+30,y+20);           //column 1
	circle(x+20,y+60,5);
	brush(x+20,y+100);
	arc(x+20,y+140,50,220,5);
	spray(x+20,y+180);
	setcolor(BLACK);
	mirror(x+20,y+260);
	rectangle(x+50,y+10,x+70,y+30);     //column 2
	paint(x+60,y+60);
	erase(x+60,y+100);
	pencil(x+60,y+140);
	poly(x+60,y+180);
	triangle(x+20,y+220);
	text(x+60,y+220);
	splash(x+60,y+260);
}
void icon::check()
{
	static int a,b;
	show_mouse();
	get_button_press(0);
	if(mx>x && my>y && mx<x+w && my<y+h)
	{
		if(mclick==1)
		{
		       hide_mouse();
		       setcolor(LIGHTGRAY);
		       rectangle(x+a*40+1,y+b*40+1,x+a*40+39,y+b*40+39);
		       a=(mx-x)/40;
		       b=(my-y)/40;
		       select_shape=a+b*2;
		       show_mouse();
		}
		else
		{
		       hide_mouse();
		       setcolor(BLACK);
		       line(x+a*40+1,y+b*40+1,x+a*40+39,y+b*40+1);
		       line(x+a*40+1,y+b*40+1,x+a*40+1,y+b*40+39);
		       setcolor(WHITE);
		       line(x+a*40+39,y+b*40+1,x+a*40+39,y+b*40+39);
		       line(x+a*40+1,y+b*40+39,x+a*40+39,y+b*40+39);
		       show_mouse();
		}
	}
	else return;
}
class shape
{
	public:
		void limit(int &,int &);
		void check();
		void sline();
		void srect();
		void spaint();
		void sellipse();
		void serase();
		void sbrush();
		void sarc();
		void spencil();
		void sspray();
		void spoly();
		void striangle();
		void stext();
		void shelix();
		void scardiod();
		void sastroid();
		void slemni();
		void splash();
		void mirror();
};
void shape::shelix()
{
	int alpha=30;
	float r=0,x,y,t=0,a=3;
	get_button_press(0);
	if(mclick==1 && mx-50>=scx && my-50>=scy && mx+50<=scx+scw && my+50<=scy+sch)
	{
		hide_mouse();
		for(r=1;r<=50;r+=.05)
		{
		       for(a=1;a<=4;a++)
		       {
		       t=log(r/a)*tan(alpha);
		       x=r*cos(t);
		       y=r*sin(t);
		       putpixel(mx+x,my+y,select_color);
		       }
		}
		fsaved=0;
		show_mouse();
	}
}
void shape::scardiod()
{
	float x,y,r;
	int t,a=25;
	mclick=1;
	get_button_press(0);
	if(mclick==1 && mx-60>=scx && my-40>=scy && mx+20<=scx+scw && my+40<=scy+sch)
	{
		hide_mouse();
		for(t=0;t<360;t++)
		{
			r=a*(1-cos(t));
			x=r*cos(t);
			y=r*sin(t);
			putpixel(mx+x,my+y,select_color);
			setcolor(select_color);
		}
		fsaved=0;
		show_mouse();
	}
}
void shape::sastroid()
{
	float a=30,x,y;
	get_button_press(0);
	if(mclick==1 && mx-30>=scx && mx+30<=scx+scw && my-30>=scy && my+30<=scy+sch)
	{
		hide_mouse();
		setcolor(select_color);
		for(int t=0;t<360;t++)
		{
			x=a*pow(cos(t),3);
			y=a*pow(sin(t),3);
			putpixel(mx+x,my+y,select_color);
		}
		fsaved=0;
	}
}
void shape::slemni()
{
	float a=30,x,y,m=-a,n;
	n=pow((a*a-m*m),.5)*(m/a);
	get_button_press(0);
	x=mx,y=my;
	if(mclick==1 && mx-35>=scx && mx+35<=scx+scw && my-20>=scy && my+20<=scy+sch)
	{
		hide_mouse();
		setcolor(select_color);
		for(x=-a;x<=a;x++)
		{
			y=pow((a*a-x*x),.5)*(x/a);
			putpixel(mx+x,my-y,select_color);
			line(mx+x,my-y,mx+m,my-n);
			putpixel(mx+x,my+y,select_color);
			line(mx+x,my+y,mx+m,my+n);
			m=x,n=y;
		}
		fsaved=0;
		show_mouse();
	}
}
void shape::limit(int &mx,int &my)
{
	if(mx<=scx) mx=scx+1;
	if(my<=scy) my=scy+1;
	if(mx>=scx+scw) mx=scx+scw-1;
	if(my>=scy+sch) my=scy+sch-1;
}
void shape::splash()
{
	int z1,z2;
	get_button_press(0);
	if(mx>scx+20 && mx<scx+scw-20 && my>scy+20 && my<scy+sch-20)
	{
		hide_mouse();
		setcolor(select_color);
		for(int i=1;i<=360;i+=30)
		{
			z1=rand()%20*cos(i)*pow(-1,i);
			z2=rand()%20*sin(i)*pow(-1,i);
			line(mx,my,mx+z1,my+z2);
		}
		fsaved=0;
		show_mouse();
	}
}
void shape::mirror()
{
	int mrx1,mry1,mry2,i,j;
	get_button_press(0);
	mrx1=mx,mry1=my;
	if(mx>scx && mx<scx+scw && my>scy && my<scy+sch)
	{
		while(get_button_release(0)==1)
			mouse_status();
	}
	if(mrx1>(scx+scx+scw)/2) return;
	mry2=my;
	for(i=scx+1;i<mrx1;i++)
		for(j=mry1;j<=mry2;j++)
		{
			if(getpixel(i,j)!=WHITE)
			putpixel(2*mrx1-i,j,getpixel(i,j));
			if(j>scy+sch-2) break;
		}
}
void shape::stext()
{
	char c,s[30]="\0\0\0\0";
	int i=0;
	mclick=0;
	get_button_press(0);
	if(mclick==1 && mx>scx && my>scy && mx+100<scx+scw && my+10<scy+sch)
	{
	       setfillstyle(SOLID_FILL,WHITE);
	       hide_mouse();
	       bar(mx-10,my-5,mx+100,my+10);
	       fflush(stdin);
	       c=getch();
	       while(c!='\x1B')         //escape character or more length
	       {
			if(c=='\r') ;    	//enter
			else if(c=='\t');   	//tab
			else if(c=='\b')        //backspace
			{
				setcolor(WHITE);
				outtextxy(mx,my,s);
				setcolor(select_color);
				s[--i]='\0';
				outtextxy(mx,my,s);
			}
			else
			{
			s[i++]=c;
			s[i]='\0';
			if(i==14) break;
			setcolor(select_color);
			outtextxy(mx,my,s);
			}
			fflush(stdin);
			c=getch();
			fsaved=0;
	       }
	       show_mouse();
	       mclick=0;
	}
	else
	{
	       for(int k=0;k<i;k++)
	       s[k]='\0';
	       fflush(stdin);
	}
}
void shape::striangle()
{
	int omx,omy,a,b;
	show_mouse();
	get_button_press(0);
	if(mx>scx && my>scy && mx<scx+scw && my<scy+sch && mclick==1)
	{
		omx=a=mx,omy=b=my;
		while(get_button_release(0)==1)
		{
			hide_mouse();
			mouse_status();
			if(my<scy) my=scy;
			if(my>scy+sch) my=scy+sch;
			limit(mx,my);
			if(a==mx && b==my)
				continue;
			mytriangle(omx,omy,a,b,1);
			mytriangle(omx,omy,mx,my,0);
			a=mx,b=my;
			show_mouse();
			delay(100);
		}
		mytriangle(omx,omy,a,b,1);
		mytriangle(omx,omy,mx,my,0);
		fsaved=0;
	}
}

void shape::spoly()
{
	static int c=0;
	static int omx,omy;
	hide_mouse();
	get_button_press(0);
	if(mx>scx && mx<scx+scw && my>scy && my<scy+sch)
	{
		setcolor(select_color);
		if(c>0)
		line(omx,omy,mx,my);
		omx=mx,omy=my;
		c++;
		if(c==100) c=1;
		show_mouse();
		fsaved=0;
	}
}
void shape::sspray()
{
	int i,j;
	int x,y;
	static int c=0;
	show_mouse();
	get_button_press(0);
	if(mx-10>scx && mx+10<scx+scw && my-10>scy && my+10<scy+sch)
	{
		while(get_button_release(0)==1)
		{
			hide_mouse();
			mouse_status();
			if(mx+10<scx+scw && my+10<scy+sch && mx-10>scx && my-10>scy)
			{
				limit(mx,my);
				setcolor(select_color);
				if(c%600==0)
				{
					x=rand()%10;
					y=rand()%10;
					if(x*x+y*y<=100)
					{
					putpixel(mx+x,my+y,select_color);
					putpixel(mx-x,my-y,select_color);
					putpixel(mx+x,my-y,select_color);
					putpixel(mx-x,my+y,select_color);
					}
				}
				c++;
			}
			fsaved=0;
		}
	}
}
void shape::spencil()
{
	show_mouse();
	get_button_press(0);
	if(mx>scx && mx<scx+scw && my>scy && my<scy+sch)
	{
		int omx=mx,omy=my;
		while(get_button_release(0)==1)
		{
			hide_mouse();
			mouse_status();
			limit(mx,my);
			setcolor(select_color);
			if(mx>scx && my>scy && mx<scx+scw && my<scy+sch)
			{
			line(omx,omy,mx,my);
			omx=mx,omy=my;
			fsaved=0;
			}
		}
	}
}
void shape::sarc()
{
	static int a,b,c,d;
	static int e=0;
	int cur_color=0;
	if(e==1) e=0;
	show_mouse();
	setcolor(select_color);
	get_button_press(0);
	save_video(mscx-157,mscy-104,mscx+157,mscy+104);
	if(mx>scx && mx<scx+scw && my>scy && my<scy+sch)
	{
		int omx=mx,omy=my;
		while(get_button_release(0)==1)
		{
			if(e==0)
			{
			setcolor(cur_color);
			ellipse((a+c)/2,(b+d)/2,angle(a,b,c,d),angle(a,b,c,d)+90,abs((c-a)/2),abs((d-b)/2));
			}
			setcolor(select_color);
			mouse_status();
			limit(mx,my);
			hide_mouse();
			cur_color=getpixel(omx,omy);
			if(omx!=my && omy!=my)
			ellipse((omx+mx)/2,(omy+my)/2,angle(omx,omy,mx,my),angle(omx,omy,mx,my)+90,abs((mx-omx)/2),abs((my-omy)/2));
			a=omx;b=omy;c=mx;d=my;
			delay(200);
			fsaved=0;
		}
		restore_video(mscx-157,mscy-104,1);
		ellipse((omx+mx)/2,(omy+my)/2,angle(omx,omy,mx,my),angle(omx,omy,mx,my)+90,abs((mx-omx)/2),abs((my-omy)/2));
		a=0,b=0,c=0;
		e=1;
	}
}
void shape::serase()
{
	show_mouse();
	get_button_press(0);
	if(mx>scx && mx<scx+scw && my>scy && my<scy+sch)
	{
		while(get_button_release(0)==1)
		{
			mouse_status();
			if(mx>scx+3 && mx<scx+scw-3 && my>scy+3 && my<scy+sch-3)
			{
				hide_mouse();
				setfillstyle(SOLID_FILL,WHITE);
				rectangle(mx-2,my-2,mx+3,my+3);
				bar(mx-2,my-2,mx+3,my+3);
			}
			fsaved=0;
		}
	}
}
void shape::sbrush()
{
	show_mouse();
	get_button_press(0);
	if(mx>scx && mx<scx+scw && my>scy && my<scy+sch)
	{
		int omx=mx,omy=my;
		while(get_button_release(0)==1)
		{
			hide_mouse();
			mouse_status();
			limit(mx,my);
			setcolor(select_color);
			setfillstyle(SOLID_FILL,select_color);
			line(omx,omy,mx,my);
			line(omx-1,omy,mx-1,my);
			line(omx+1,omy,mx+1,my);
			line(omx,omy-1,mx,my+1);
			omx=mx,omy=my;
			fsaved=0;
		}
	}
}
void shape::spaint()
{
	int c=-1,f,i,j;
	get_button_press(0);
	if(mx<=scx || my<=scy || mx>=scx+scw || my>=scy+sch) return;
	while(get_button_release(0)==1);
	if(mclick==1 && mx>scx+1 && my>scy+1 && mx<scx+scw-1 && my<scy+scw-1)
	{
		hide_mouse();
		i=mx,j=my;
		c=getpixel(i,j);
		while(c==(f=getpixel(i++,j)));
		setcolor(f);
		rectangle(scx+1,scy+1,scx+scw-1,scy+sch-1);
		setfillstyle(select_style,select_color);
		floodfill(mx,my,f);
		setcolor(WHITE);
		rectangle(scx+1,scy+1,scx+scw-1,scy+sch-1);
		show_mouse();
		fsaved=0;
	}
}
void shape::sellipse()
{
	int omx,omy,a,b;
	show_mouse();
	get_button_press(0);
	if(mx>scx && my>scy && mx<scx+scw && my<scy+sch && mclick==1)
	{
		omx=a=mx,omy=b=my;
		while(get_button_release(0)==1)
		{
			delay(100);
			hide_mouse();
			mouse_status();
			limit(mx,my);
			if(abs(a-mx)<1 || abs(b-my)<1) continue;				myellipse((omx+a)/2,(omy+b)/2,abs(a-omx)/2,abs(b-omy)/2,1);
			a=mx,b=my;
			myellipse((omx+mx)/2,(omy+my)/2,abs(mx-omx)/2,abs(my-omy)/2,0);
			show_mouse();
		}
		myellipse((omx+a)/2,(omy+b)/2,abs(a-omx)/2,abs(b-omy)/2,1);
		myellipse((omx+mx)/2,(omy+my)/2,abs(mx-omx)/2,abs(my-omy)/2,0);
		fsaved=0;
	}
}
void shape::srect()
{
	int omx,omy,a,b;
	show_mouse();
	get_button_press(0);
	if(mx>scx && my>scy && mx<scx+scw && my<scy+sch && mclick==1)
	{
		omx=a=mx,omy=b=my;
		while(get_button_release(0)==1)
		{
			hide_mouse();
			mouse_status();
			limit(mx,my);
			if(a==mx && b==my) continue;
			else
			{
				myrect(omx,omy,a,b,1);
				myrect(omx,omy,mx,my,0);
				a=mx,b=my;
			}
			show_mouse();
			delay(50);
		}
		delay(100);
		myrect(omx,omy,a,b,1);
		myrect(omx,omy,mx,my,0);
		fsaved=0;
	}
}
void shape::sline()
{
	int omx,omy,a,b;
	show_mouse();
	get_button_press(0);
	if(mx>scx && my>scy && mx<scx+scw && my<scy+sch && mclick==1)
	{
		omx=a=mx,omy=b=my;
		while(get_button_release(0)==1)
		{
			hide_mouse();
			mouse_status();
			limit(mx,my);
			if(a==mx && b==my) continue;
			else
			{
				myline(omx,omy,a,b,1);
				myline(omx,omy,mx,my,0);
				a=mx,b=my;
			}
			show_mouse();
			delay(50);
		}
		myline(omx,omy,a,b,1);
		myline(omx,omy,mx,my,0);
		fsaved=0;
	}
}
void shape::check()
{
	get_button_press(0);
	if(mclick==1)
	{
		switch(select_shape)
		{
			case 0: sline();
			break;
			case 1: srect();
			break;
			case 2: sellipse();
			break;
			case 3: spaint();
			break;
			case 4: sbrush();
			break;
			case 5: serase();
			break;
			case 6: sarc();
			break;
			case 7: spencil();
			break;
			case 8: sspray();
			break;
			case 9: spoly();
			break;
			case 10:  striangle();
			break;
			case 11:  stext();
			break;
			case 12:  mirror();
			break;
			case 13:  splash();
			break;
			case 20:  shelix();
			break;
			case 21:  scardiod();
			break;
			case 22:  sastroid();
			break;
			case 23:  slemni();
		}
	}
}
void main()
{
	initgraph(&gd,&gm,"");
	fill_color_bound(0,0,WHITE,SOLID_FILL);
	icon ic;
	color co;
	menu me;
	close cl;
	title ti;
	shape sh;
	ti.set("EZGP - Draw Mode");
	ti.show();
	cl.show();
	ic.show();
	co.show();
	fs.show();
	setcolor(BLACK);
	rectangle(scx,scy,scx+scw,scy+sch);
	setcolor(WHITE);
	line(scx,scy+sch,scx+scw,scy+sch);
	line(scx+scw,scy,scx+scw,scy+sch);
	me.draw(10,20,mainmenu);
	put_fname();
	while(1)
	{
	       if(kbhit())
	       {
		      int c=getch();
		      setcolor(BLACK);
		      if(c==4)
		      {
			      hide_mouse();
			      dbuf1=(void far*)farmalloc(imagesize(scx,scy,mscx,mscy));
			      if(dbuf1!=NULL)
					getimage(scx,scy,mscx,mscy,dbuf1);
			      dbuf2=(void far*)farmalloc(imagesize(mscx,scy,scx+scw,mscy));
			      if(dbuf2!=NULL)
					getimage(mscx,scy,scx+scw,mscy,dbuf2);
			      dbuf3=(void far*) farmalloc(imagesize(scx,mscy,mscx,scy+sch));
			      if(dbuf3!=NULL)
					getimage(scx,mscy,mscx,scy+sch,dbuf3);
			      dbuf4=(void far*) farmalloc(imagesize(mscx,mscy,scx+scw,scy+sch));
			      if(dbuf4!=NULL)
					getimage(mscx,mscy,scx+scw,scy+sch,dbuf4);
			      show_mouse();
			      demo_init();
			      hide_mouse();
			      ti.show();
			      cl.show();
			      ic.show();
			      co.show();
			      fs.show();
			      setcolor(BLACK);
			      rectangle(scx,scy,scx+scw,scy+sch);
			      setcolor(WHITE);
			      line(scx,scy+sch,scx+scw,scy+sch);
			      line(scx+scw,scy,scx+scw,scy+sch);
			      me.draw(10,20,mainmenu);
			      put_fname();
			      putimage(scx,scy,dbuf1,COPY_PUT);
			      putimage(mscx,scy,dbuf2,COPY_PUT);
			      putimage(scx,mscy,dbuf3,COPY_PUT);
			      putimage(mscx,mscy,dbuf4,COPY_PUT);
			      farfree(dbuf1);
			      farfree(dbuf2);
			      farfree(dbuf3);
			      farfree(dbuf4);
			      show_mouse();
		      }
		      else if(c==20) command();
	       }
	       show_mouse();
	       mouse_status();
	       if(mx>=0 && my>=20 && mx<=260 && my<=40)
	       {
			save_video(1,20,400,200);
			me.option();
			restore_video(1,20,1);
			if(me.choice_flag==1)
				me.action();
	       }
	       else if(mx>=ic.x && my>=ic.y && mx<=ic.x+ic.w && my<=ic.y+ic.h) ic.check();
	       else if(mx>=co.x && my>=co.y && mx<=co.x+co.w && my<=co.y+co.h) co.check();
	       else if(mx>=fs.x && my>=fs.y && mx<=fs.x+fs.w && my<=fs.y+fs.h) fs.check();
	       else if(mx>=scx && mx<=scx+scw && my>=scy && my<=scy+sch)
	       {
			disp_pos();
			sh.check();
	       }
	       else
	       {

			cl.check();
	       }
	}
}
