int buff_leng;
int * buffer;
void swap(int &a,int &b)
{
	int t=a;
	a=b;
	b=t;
}
int convnum(char a[])
{
	int l,i,num=0;
	l=strlen(a);
	for(i=l-1;i>=0;i--)
		num=num+pow(10,l-i-1)*(a[i]-48);
	return num;
}
void put_fname()        //put file name on title bar
{
	static char a[]="Untitled";
	if(fnamed==1)
	{
		if(strcmp(file_name,a)==0);
		else
		{
			setcolor(BLUE);
			outtextxy(300,5,a);
			setcolor(WHITE);
			outtextxy(300,5,file_name);
		}
		strcpy(a,file_name);
	}
	else
	{
		setcolor(WHITE);
		outtextxy(300,5,a);
	}
}
void get_fname()                   //get file name from user
{
	if(fname_len==10 || !kbhit()) return;
	char ch=getch();
	if(ch=='\t' || ch=='\r');
	else if(ch=='\b')
	{
	setcolor(LIGHTGRAY);
	outtextxy(225,175,file_name);
	file_name[--fname_len]='\0';
	setcolor(BLACK);
	}
	else
	{
	file_name[fname_len++]=ch;
	file_name[fname_len]='\0';
	}
}
char *conv_totext(int n)
{
	char c[20];
	int i=0;
	if(n==0) return "0";
	while(n>0)
	{
	     c[i++]=n%10+48;
	     n=n/10;
	}
	c[i]='\0';
	strrev(c);
	return c;
}
void disp_pos()
{
	char *x,*y;
	char a[10],b[10],c;
	static char m[10],n[10];
	int i=0;
	mouse_status();
	x=conv_totext(mx-scx);
	c=*(x+i);
	while(c!='\0')
	{
		a[i++]=c;
		c=*(x+i);
	}
	a[i]='\0';
	i=0;
	y=conv_totext(my-scy);
	c=*(y+i);
	while(c!='\0')
	{
		b[i++]=c;
		c=*(x+i);
	}
	b[i]='\0';
	if(strcmp(m,a)==0 && strcmp(n,b)==0);
	else
	{
	setcolor(LIGHTGRAY);
	outtextxy(550,350,m);
	outtextxy(575,350,",");
	outtextxy(585,350,n);
	setcolor(BLACK);
	outtextxy(550,350,a);
	outtextxy(575,350,",");
	outtextxy(585,350,b);
	strcpy(m,a);
	strcpy(n,b);
	}
}
int angle(int x1,int y1,int x2,int y2)
{
	int s;
	if(x2-x1>0)
	s=(y2-y1)/(x2-x1);
	return atan(abs(s));
}
void get_tip()
{
	FILE * fp;
	static int count=1;
	int l=0,i=0;
	char tmp[60],c;
	if(count==14) count=1;
	fp=fopen(tfile,"r");
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			c=fgetc(fp);
			if(c=='\n')
			{
				tmp[i]='\0';
				i=0;
				l++;
				if(l==count) break;
			}
			else
			{
				tmp[i++]=c;
			}
		}
		strcpy(tip,tmp);
		count++;
	}
}
void music()            //Menu selection sound
{
	sound(200);
	delay(100);
	nosound();
}
void fill_color_bound(int x,int y,int c,int p)
{
	hide_mouse();
	setfillstyle(p,c);
	floodfill(x,y,c);
	show_mouse();
}
void getnum()
{
	char c;
	if(!kbhit()) return ;
	c=getch();
	if(isdigit(c))
	{
		setcolor(LIGHTGRAY);
		outtextxy(225,185,imnum);
		imnum[imlen++]=c;
		imnum[imlen]='\0';
		setcolor(BLACK);
		outtextxy(225,185,imnum);
	}
}
