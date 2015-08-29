class error_box
{
	int x1,y1,x2,y2;
	public:
	error_box()
	{
		x1=200,y1=150,x2=400,y2=250;
	}
	void show(char []);
	int check();
};
void error_box::show(char e[])
{
	int x=x1+25,y=y1+60;
	save_video(x1,y1,x2,y2);
	hide_mouse();
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(x1,y1,x2,y2);
	setcolor(BLACK);
	rectangle(x1,y1,x2,y2);
	setfillstyle(SOLID_FILL,BLUE);
	bar(x1,y1,x2,y1+20);
	rectangle(x1,y1,x2,y1+20);
	setcolor(WHITE);
	outtextxy(x1+20,y1+5,"Error !");
	setcolor(RED);
	circle(x,y,20);
	setfillstyle(SOLID_FILL,RED);
	floodfill(x,y,RED);
	setcolor(WHITE);
	line(x-5,y-5,x+5,y+5);
	line(x-5,y+5,x+5,y-5);
	setcolor(BLACK);
	outtextxy(x1+70,y1+40,e);
	setcolor(WHITE);
	line(x1+100,y2-40,x1+140,y2-40);
	line(x1+100,y2-40,x1+100,y2-20);
	setcolor(BLACK);
	line(x1+100,y2-20,x1+140,y2-20);
	line(x1+140,y2-40,x1+140,y2-20);
	outtextxy(x1+110,y2-30,"OK");
	show_mouse();
}
int error_box::check()
{
       get_button_press(0);
       if(mclick==1 && mx>=x1+100 && mx<=x1+140 && my>=y2-40 && my<=y2-20)
       {
		setcolor(BLACK);
		line(x1+100,y2-40,x1+140,y2-40);
		line(x1+100,y2-40,x1+100,y2-20);
		setcolor(WHITE);
		line(x1+100,y2-20,x1+140,y2-20);
		line(x1+140,y2-40,x1+140,y2-20);
		delay(100);
		hide_mouse();
		setfillstyle(SOLID_FILL,WHITE);
		bar(x1,y1,x2,y2);
		show_mouse();
		restore_video(x1,y1,1);
		delay(200);
		return 0;
       }
       return 1;
}
class yes_no_box
{
	int x1,y1,x2,y2;
	public:
	yes_no_box()
	{
		x1=150,y1=100,x2=450,y2=300;
	}
	void show(char []);
	int check();   		//returns 1 for yes 0 for no
};
void yes_no_box::show(char a[])
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
	setcolor(WHITE);
	outtextxy(x1+5,y1+10,a);
	int x=(x1+x2)/2;
	int y=(y1+y2)/2+50;
	setcolor(WHITE);
	line(x-100,y-10,x-60,y-10);
	line(x-100,y-10,x-100,y+10);
	setcolor(BLACK);
	line(x-100,y+10,x-60,y+10);
	line(x-60,y-10,x-60,y+10);
	outtextxy(x-90,y,"Yes");
	setcolor(WHITE);
	line(x+60,y-10,x+100,y-10);
	line(x+60,y-10,x+60,y+10);
	setcolor(BLACK);
	line(x+60,y+10,x+100,y+10);
	line(x+100,y-10,x+100,y+10);
	outtextxy(x+70,y,"No");
	show_mouse();
}
int yes_no_box::check()
{
	int x=(x1+x2)/2;
	int y=(y1+y2)/2+50;
	get_button_press(0);
	if(mclick==1)
	{
		hide_mouse();
		if(mx>=x-100 && mx<=x-60 && my>=y-10 && my<=y+10)
		{
			setcolor(BLACK);
			line(x-100,y-10,x-60,y-10);
			line(x-100,y-10,x-100,y+10);
			setcolor(WHITE);
			line(x-100,y+10,x-60,y+10);
			line(x-60,y-10,x-60,y+10);
			delay(100);
			setfillstyle(SOLID_FILL,WHITE);
			bar(x1,y1,x2,y2);
			restore_video(x1,y1,1);
			show_mouse();
			return 1;
		}
		else if(mx>=x+60 && mx<=x+100 && my>=y-10 && my<=y+10)
		{
			setcolor(BLACK);
			line(x+60,y-10,x+100,y-10);
			line(x+60,y-10,x+60,y+10);
			setcolor(WHITE);
			line(x+60,y+10,x+100,y+10);
			line(x+100,y-10,x+100,y+10);
			delay(100);
			setfillstyle(SOLID_FILL,WHITE);
			bar(x1,y1,x2,y2);
			restore_video(x1,y1,1);
			show_mouse();
			return 0;
		}
	}
	show_mouse();
	return -1;
}
