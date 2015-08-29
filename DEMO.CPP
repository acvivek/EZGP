#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#define dmx 0
#define dmy 0
#define dmw 640
#define dmh 480
char name[20][20]={"Kite","Fish","Car","Plane","Ball","WindMill","Clock"};
int length=8;
class demo
{
	int x1,y1,x2,y2;
	int xpos,ypos;
	int time_delay;
	int demo_no;
	int action;
	int dir;      //bouncing ball stops
	int ct;
	public:
	demo()
	{
	action=-1;
	xpos=175,ypos=100;
	time_delay=10;
	dir=1;
	ct=0;
	}
	void draw();
	int check();
	void play();
	void stop();
	void pause();
	void speed();
	void choice();
	void clock();
	void wind();
	void ball_draw(int,int);
	void ball_move();
	void fish_draw(int,int);
	void fish_move();
	void kite_draw(int,int);
	void kite_move();
	void aero_draw(int,int);
	void aero_move();
	void car_draw(int,int);
	void car_move();
};
void demo::wind()
{
	static int a=0,b=0,r=50;
	int x=255,y=150;
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(dmx+4,dmy+21,dmx+dmw-105,dmy+dmh-45);
	setcolor(LIGHTBLUE);
	line(x,y,x+r*cos((b+90)*3.14/180.),y+r*sin((b+90)*3.14/180.));
	line(x,y,x+r*cos((b+210)*3.14/180.),y+r*sin((b+210)*3.14/180.));
	line(x,y,x+r*cos((b+330)*3.14/180.),y+r*sin((b+330)*3.14/180.));
	setcolor(BLACK);
	line(x,y,x,y+200);
	line(x,y,x+r*cos((a+90)*3.14/180.),y+r*sin((a+90)*3.14/180.));
	line(x,y,x+r*cos((a+210)*3.14/180.),y+r*sin((a+210)*3.14/180.));
	line(x,y,x+r*cos((a+330)*3.14/180.),y+r*sin((a+330)*3.14/180.));
	b=a;
	a++;
	if(a==360) a=0;
}
void demo::clock()
{
	int x=255,y=230,k,i,j;
	static int theta1=90,theta2=90;
	int r1=50,r2=30;
	setcolor(YELLOW);
	circle(x,y,120);
	setfillstyle(SOLID_FILL,CYAN);
	floodfill(x,y,YELLOW);
	circle(x,y,60);
	setcolor(BLACK);
	for(k=1;k<=12;k++)
	{
		char *a=conv_totext(k);
		char b[5];
		for(i=0;i<strlen(a);i++)
		b[i]=*(a+i);
		b[i]='\0';

		if(k>=1 && k<=3)
		{
		i=k%4*30;
		j=sqrt(90*90-i*i);
		outtextxy(x+i+k%3*10,y-j+k%3*10,b);
		}
		else if(k>=4 && k<=6)
		{
		i=(6-k)*30;
		j=sqrt(90*90-i*i);
		outtextxy(x+i+(6-k)*10,y+j-(6-k)*10,b);
		}
		else if(k>=7 && k<=9)
		{
		i=k%6*30;
		j=sqrt(90*90-i*i);
		outtextxy(x-i-k%3*10,y+j-k%3*10,b);
		}
		else if(k>=10 && k<=12)
		{
		i=(12-k)*30;
		j=sqrt(90*90-i*i);
		outtextxy(x-i-(12-k)*10,y-j+(12-k)*10,b);
		}
	}
	theta1+=2;
	if(theta1==450) theta1=90;
	if((theta1-90)%12==0) theta2++;
	if(theta2==450) theta2=90;
	line(x,y,x-r1*cos(theta1*3.14/180.),y-r1*sin(theta1*3.14/180.));
	line(x,y,x-r2*cos(theta2*3.14/180.),y-r2*sin(theta2*3.14/180.));
}
void demo::ball_draw(int a,int b)
{
	setcolor(BROWN);
	circle(a,b,20);
	setfillstyle(SOLID_FILL,BROWN);
	floodfill(a,b,BROWN);

}
void demo::ball_move()
{
	if(ct==0)
	{
	xpos=255,ypos=380;
	ball_draw(xpos,ypos);
	setcolor(BLACK);
	line(427,220,427,240);
	line(83,220,83,240);
	line(245,58,265,58);
	line(245,402,265,402);
	}
	ct++;
	save_video(xpos-21,ypos-21,xpos+21,ypos+21);
	if(dir==1) {xpos++;ypos--;}
	else if(dir==2) {xpos--;ypos--;}
	else if(dir==3) {xpos--;ypos++;}
	else if(dir==0) {xpos++;ypos++;}
	if((xpos==405 && ypos==230) || (xpos==255 && ypos==80) || (xpos==105 && ypos==230) || (xpos==255 && ypos==380)) {delay(10);dir=(dir+1)%4;}
	restore_video(xpos-21,ypos-21,1);
}
void demo::fish_draw(int a,int b)
{
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(dmx+4,dmy+21,dmx+dmw-105,dmy+dmh-44);
	setcolor(BLACK);
	ellipse(a,b,0,360,60,30);
	line(a-60,b-40,a-60,b+40);
	line(a-60,b-40,a-40,b);
	line(a-60,b+40,a-40,b);
	circle(a+40,b,8);
	circle(a+40,b,4);
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(a+40,b,BLACK);
	line(a,b-30,a,b-45);
	line(a,b+30,a,b+45);
	arc(a,b-30,0,90,15);
	arc(a,b+30,270,360,15);
	setfillstyle(SOLID_FILL,MAGENTA);
	floodfill(a,b,BLACK);
	floodfill(a-59,b-35,BLACK);
	floodfill(a-59,b+35,BLACK);
	floodfill(a-59,b,BLACK);
	floodfill(a+1,b-31,BLACK);
	floodfill(a+1,b+31,BLACK);
}
void demo::fish_move()
{
	static int c=0;
	if(c==0)
	{
	hide_mouse();
	fish_draw(xpos,ypos+100);
	show_mouse();
	c++;
	}
	save_video(xpos-80,ypos+40,xpos+80,ypos+160);
	xpos++;
	restore_video(xpos-80,ypos+40,1);
	if(xpos==400)
	{
		setfillstyle(SOLID_FILL,LIGHTBLUE);
		bar(xpos-80,ypos+40,xpos+80,ypos+160);
		xpos=175;
		c=0;
	}
}
void demo::kite_draw(int a,int b)
{
	float i=1,j=1;
	setcolor(BLACK);
	line(a,b-40,a-30,b);
	line(a-30,b,a,b+40);
	line(a,b+40,a+30,b);
	line(a+30,b,a,b-40);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(a,b,BLACK);
	while(i<=10)
	{
		i+=.1;
		j=i*i;
		putpixel(a+i,b+40+j,BLACK);
	}
}
void demo::kite_move()
{
	hide_mouse();
	kite_draw(xpos+100,ypos+150);
	show_mouse();
	save_video(xpos+50,ypos+50,xpos+200,ypos+300);
	ypos--;
	xpos--;
	restore_video(xpos+50,ypos+50,1);
	if(ypos==-25)
	{
		setfillstyle(SOLID_FILL,WHITE);
		bar(xpos+50,ypos+50,xpos+200,ypos+300);
		ypos=100;
		xpos=175;
	}
}
void demo::aero_draw(int a,int b)
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	line(a-40,b+20,a+20,b-40);
	line(a+20,b-40,a+40,b-20);
	line(a+40,b-20,a-20,b+40);
	line(a-20,b+40,a-40,b+20);
	line(a+20,b-40,a+80,b-80);
	line(a+40,b-20,a+80,b-80);
	line(a-20,b+60,a-20,b+40);
	line(a-60,b+20,a-40,b+20);
	line(a-20,b+60,a-60,b+20);
	line(a+20,b-40,a-60,b-60);
	line(a+40,b-20,a+60,b+60);
	line(a-60,b-60,a+60,b+60);
	floodfill(a-30,b+35,BLACK);
	floodfill(a+45,b-45,BLACK);
	floodfill(a,b+1,BLACK);
	floodfill(a,b-1,BLACK);
	floodfill(a-20,b-30,BLACK);
	floodfill(a+40,b+30,BLACK);

}
void demo::aero_move()
{
	aero_draw(xpos,ypos+200);
	save_video(xpos-100,ypos+100,xpos+100,ypos+300);
	xpos++;ypos--;
	restore_video(xpos-100,ypos+100,1);
	if(xpos==350)
	{
		setfillstyle(SOLID_FILL,WHITE);
		bar(xpos-100,ypos+100,xpos+100,ypos+300);
		xpos=175;
		ypos=100;
	}
}
void demo::car_draw(int a,int b)
{
	setcolor(BLACK);
	line(a,b-40,a,b+40);
	line(a-150,b+40,a+150,b+40);
	line(a-75,b-20,a-150,b-10);
	line(a-50,b-40,a+50,b-40);
	line(a+50,b-40,a+75,b-10);
	line(a+150,b+40,a+150,b+10);
	line(a+75,b-10,a+150,b+10);
	line(a-150,b+40,a-150,b-10);
	line(a-50,b-40,a-75,b-20);
	line(a-75,b-10,a+75,b-10);
	line(a-75,b-10,a-75,b-20);
	line(a-50,b,a-50,b+40);
	line(a-50,b,a-75,b-10);
	line(a-50,b-10,a+75,b-10);
	line(a+50,b,a+50,b+40);
	line(a+50,b,a+75,b-10);
	line(a-50,b-40,a-50,b-10);
	line(a+50,b-40,a+50,b-10);
	circle(a-75,b+40,15);
	circle(a+75,b+40,15);
	arc(a+150,b+20,270,450,8);
	arc(a-150,b+10,90,270,10);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(a+151,b+20,BLACK);
	setfillstyle(SOLID_FILL,RED);
	floodfill(a-155,b+11,BLACK);
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	floodfill(a-70,b,BLACK);
	floodfill(a+70,b,BLACK);
	floodfill(a-30,b,BLACK);
	floodfill(a+30,b,BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(a-75,b+35,BLACK);
	floodfill(a-75,b+45,BLACK);
	floodfill(a+75,b+35,BLACK);
	floodfill(a+75,b+45,BLACK);
	setfillstyle(SOLID_FILL,DARKGRAY);
	floodfill(a-55,b-15,BLACK);
	floodfill(a+55,b-15,BLACK);
	floodfill(a-35,b-15,BLACK);
	floodfill(a+35,b-15,BLACK);
}
void demo::car_move()
{
	hide_mouse();
	car_draw(xpos,ypos+100);
	save_video(xpos-170,ypos+60,xpos+160,ypos+160);
	restore_video(xpos-169,ypos+60,1);
	show_mouse();
	xpos++;
	if(xpos==300)
	{
	setfillstyle(SOLID_FILL,WHITE);
	bar(xpos-170,ypos+60,xpos+160,ypos+160);
	xpos=175;
	}
}
void demo::choice()
{
	int i;
	static int c;
	static int count=0;
	for(i=0;i<length;i++)
		if(mx>=dmx+dmw-100 && my>=dmy+25+i*25 && my<=dmy+25+(i+1)*25) break;
	if(count!=0)
	{
		setcolor(LIGHTGRAY);
		outtextxy(dmx+dmw-30,dmy+25+c*25,"*");
	}
	setcolor(WHITE);
	outtextxy(dmx+dmw-30,dmy+25+i*25,"*");
	c=i;
	demo_no=i;
	(count+=1)%30+1;
}
void demo::play()
{
	static int c=-1;
	if(demo_no!=c) stop();
	switch(demo_no)
	{
		case 0:
			kite_move();
		break;
		case 1:
			fish_move();
		break;
		case 2:
			car_move();
		break;
		case 3:
			aero_move();
		break;
		case 4:
			ball_move();
		break;
		case 5:
			wind();
		break;
		case 6:
			clock();
		break;
	}
	delay(1000/time_delay);
	c=demo_no;
}
void demo::stop()
{
	setfillstyle(SOLID_FILL,WHITE);
	bar(dmx+4,dmy+21,dmx+dmw-105,dmy+dmh-44);
	if(demo_no==4) {xpos=255,ypos=380;dir=1;ct=0;}
	xpos=175,ypos=100;
}

void demo::pause()
{
}
void demo::speed()
{
	static int px;
	if(mx>=(x1+x2)/4+20 && my>=y1+15 && mx<=x2-20 && my<=y2-15 && px!=mx)
	{
		hide_mouse();
		setcolor(BLACK);
		line(px,y1+15,px,y2-15);
		setcolor(WHITE);
		line(mx,y1+15,mx,y2-15);
		px=mx;
		show_mouse();
		time_delay=mx-((x1+x2)/4+20);
	}
}
void demo::draw()
{
	setfillstyle(SOLID_FILL,BLUE);
	bar(dmx,dmy,dmx+dmw,dmy+20);
	bar(dmx,dmy,dmx+3,dmy+dmh);
	bar(dmx+dmw-3,dmy,dmx+dmw,dmy+dmh);
	bar(dmx,dmy+dmh-3,dmx+dmw,dmy+dmh);
	setfillstyle(SOLID_FILL,CYAN);
	x1=dmx+4,y1=dmy+dmh-43,x2=dmx+dmw-4,y2=dmy+dmh-4;
	bar(x1,y1,x2,y2);
	setfillstyle(SOLID_FILL,BLACK);
	setcolor(BLACK);
	line((x1+x2)/8,y1,(x1+x2)/8,y2);
	line((x1+x2)/4,y1,(x1+x2)/4,y2);
	line(3*(x1+x2)/8,y1,3*(x1+x2)/8,y2);
	line((x1+x2)/2,y1,(x1+x2)/2,y2);
	line(x1+25,y1+5,x1+25,y2-5);
	line(x1+25,y1+5,(x1+x2)/8-25,(y1+y2)/2);
	line(x1+25,y2-5,(x1+x2)/8-25,(y1+y2)/2);
	floodfill(x1+26,(y1+y2)/2,BLACK);
	bar((x1+x2)/8+25,y1+10,(x1+x2)/4-25,y2-10);
	bar((x1+x2)/2+20,y1+15,x2-20,y2-15);
	bar(3*(x1+x2)/8-35,y1+10,3*(x1+x2)/8-40,y2-10);
	bar(3*(x1+x2)/8-45,y1+10,3*(x1+x2)/8-50,y2-10);
	outtextxy((x1+x2)/2+20,y2-10,"L");
	outtextxy(x2-20,y2-10,"H");
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	circle(7*(x1+x2)/16,(y1+y2)/2,10);
	floodfill(7*(x1+x2)/16,(y1+y2)/2,RED);
	bar(dmx+dmw-20,dmy,dmx+dmw,dmy+20);
	setcolor(WHITE);
	line(dmx+dmw-15,dmy+5,dmx+dmw-5,dmy+15);
	line(dmx+dmw-15,dmy+15,dmx+dmw-5,dmy+5);
	outtextxy(dmx+20,dmy+5,"EZGP - Demo Mode");
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(dmx+dmw-104,dmy+21,dmx+dmw-4,dmy+dmh-44);
	for(int i=0;i<length;i++)
	outtextxy(dmx+dmw-100,dmy+25+i*25,name[i]);
}
int demo::check()
{
	show_mouse();
	get_button_press(0);
	if(mclick==1)
	{
		while(get_button_release(0)==1) mouse_status();
		if(mx>=dmx+4 && mx<=dmx+dmw-105 && my>=dmy+21 && my<=dmy+dmh-44);
		if(mx>=x1 && my>=y1 && mx<=(x1+x2)/8 && my<=y2) action=1;
		else if(mx>=(x1+x2)/8 && my>=y1 && mx<=(x1+x2)/4 && my<=y2) action=2;
		else if(mx>=(x1+x2)/4 && my>=y1 && mx<=3*(x1+x2)/8 && my<=y2) action=3;
		else if(mx>=3*(x1+x2)/8 && my>=y1 && mx<=(x1+x2)/2 && my<=y2) return 1;
		else if(mx>=(x1+x2)/2 && my>=y1 && mx<=x2 && my<=y2) speed();
		else if(mx>=dmx+dmw-100 && mx<=dmx+dmw-4 && my>=dmy+21 && my<=dmy+dmh-44) choice();
		else if(mx>=dmx+dmw-20 && my>=dmy && mx<=dmx+dmw && my<=dmy+20) return 1;
		else return -1;
	}
	switch(action)
	{
		case 1: play();
		break;
		case 2: stop();
		break;
		case 3: pause();
	}
	return 0;
}
void demo_init()
{
	hide_mouse();
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,0,640,480);
	demo de;
	de.draw();
	show_mouse();
	while(1)
		if(de.check()==1) break;
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,0,640,480);
	return;
}
