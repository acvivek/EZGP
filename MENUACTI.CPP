void pixel(int x,int y,int c,int r)
{
	int i,j;
	for(i=-r;i<=r;i++)
	for(j=-r;j<=r;j++)
	putpixel(x+i,y+j,c);
}
void file_new()
{
	static int c=-1;
	if(fsaved==1)
	{
		setfillstyle(SOLID_FILL,WHITE);
		bar(scx+1,scy+1,scx+scw-1,scy+sch-1);
	}
	else
	{
		yes_no_box yn;
		yn.show("File Not Saved");
		outtextxy(225,175,"Do U want to Save it");
		c=yn.check();
		while(c==-1)
			c=yn.check();
		if(c==0){c=-1;fsaved=1;file_new();}
		else if(c==1)
		{
			c=-1;
			if(fnamed==0)
			file_saveas();
			else
			file_save();
		}
	}
}
void file_open()                   //screen into quadrants
{
	static int c=-1;
	char f[30];
	strcpy(f,file_name);
	fname_len=0;
	fnamed=0;
	fsaved=1;
	for(int i=0;i<10;i++)
	file_name[i]='\0';
	yes_no_box yn;
	yn.show("Open File -Type File Name");
	while(c==-1)
	{
		get_fname();
		outtextxy(225,175,file_name);
		c=yn.check();
	}
	if(c==0) {c=-1;return;}
	c=-1;
	fnamed=1;
	FILE *fp=fopen(file_name,"r");
	if(fp!=NULL)
	{
		put_fname();
		buf1=(void*) malloc(imagesize(scx,scy,mscx,mscy));
		if(buf1!=NULL)
		{
			hide_mouse();
			fread(buf1,1,imagesize(scx,scy,mscx,mscy),fp);
			putimage(scx,scy,buf1,COPY_PUT);
			free(buf1);
			show_mouse();
		}
		buf1=(void*) malloc(imagesize(mscx,scy,scx+scw,mscy));
		if(buf1!=NULL)
		{
			hide_mouse();
			fread(buf1,1,imagesize(mscx,scy,scx+scw,mscy),fp);
			putimage(mscx,scy,buf1,COPY_PUT);
			free(buf1);
			show_mouse();
		}

		buf1=(void*) malloc(imagesize(scx,mscy,mscx,scy+sch));
		if(buf1!=NULL)
		{
			hide_mouse();
			fread(buf1,1,imagesize(scx,mscy,mscx,scy+sch),fp);
			putimage(scx,mscy,buf1,COPY_PUT);
			free(buf1);
			show_mouse();
		}
		buf1=(void*) malloc(imagesize(mscx,mscy,scx+scw,scy+sch));
		if(buf1!=NULL)
		{
			hide_mouse();
			fread(buf1,1,imagesize(mscx,mscy,scx+scw,scy+sch),fp);
			putimage(mscx,mscy,buf1,COPY_PUT);
			free(buf1);
			show_mouse();
		}
		fclose(fp);
	}
	else
	{
		error_box er;
		er.show("File Not Found");
		while(er.check()==1);
		strcpy(file_name,f);
		put_fname();
		return;
	}
}
void file_save()
{
	if(fnamed==1)
	{
		FILE *fp=fopen(file_name,"w");
		buf1=(void*) malloc(imagesize(scx,scy,mscx,mscy));
		if(buf1!=NULL)
		{
			hide_mouse();
			getimage(scx,scy,mscx,mscy,buf1);
			fwrite(buf1,1,imagesize(scx,scy,mscx,mscy),fp);
			free(buf1);
			show_mouse();
		}
		buf1=(void*) malloc(imagesize(mscx,scy,scx+scw,mscy));
		if(buf1!=NULL)
		{
			hide_mouse();
			getimage(mscx,scy,scx+scw,mscy,buf1);
			fwrite(buf1,1,imagesize(mscx,scy,scx+scw,mscy),fp);
			free(buf1);
			show_mouse();
		}
		buf1=(void*) malloc(imagesize(scx,mscy,mscx,scy+sch));
		if(buf1!=NULL)
		{
			hide_mouse();
			getimage(scx,mscy,mscx,scy+sch,buf1);
			fwrite(buf1,1,imagesize(scx,mscy,mscx,scy+sch),fp);
			free(buf1);
			show_mouse();
		}

		buf1=(void*) malloc(imagesize(mscx,mscy,scx+scw,scy+sch));
		if(buf1!=NULL)
		{
			hide_mouse();
			getimage(mscx,mscy,scx+scw,scy+sch,buf1);
			fwrite(buf1,1,imagesize(mscx,mscy,scx+scw,scy+sch),fp);
			free(buf1);
			show_mouse();
		}
		fsaved=1;
		fclose(fp);
	}
	else file_saveas();
}
void file_saveas()
{
	static int c=-1;
	fname_len=0;
	file_name[fname_len]='\0';
	yes_no_box yn;
	yn.show("Save File - Type File Name");
	while(c==-1)
	{
		get_fname();
		outtextxy(225,175,file_name);
		c=yn.check();
	}
	if(c==0) {c=-1;return;}
	c=-1;
	show_mouse();
	fnamed=1;
	FILE * fp1=fopen(file_name,"r");
	if(fp1==NULL)
	{
		file_save();
		put_fname();
	}
	else
	{
		error_box er;
		er.show("File Exists");
		strcpy(file_name,"Untitled");
		put_fname();
		int q=er.check();
		while(q==1)
			q=er.check();
		fclose(fp1);
		return;
	}
}
void file_exit()
{
	int c=-1;
	if(fsaved==1)
	{
		c=-1;
		exit(0);
	}
	else
	{
		yes_no_box yn;
		yn.show("File Not Saved");
		outtextxy(225,175,"Do U want to Save it");
		c=yn.check();
		while(c==-1)
			c=yn.check();
		if(c==0) {c=-1;exit(0);}
		else if(c==1)
		{
			c=-1;
			if(fnamed==0)
			file_saveas();
			else
			file_save();
		}
	}
}
class edit
{
	void * ebuf;
	unsigned int earea;
	int x1,y1,x2,y2;
	int sel;
	public:
	edit(){x1=y1=x2=y2=sel=0;}
	int select();
	void cut();
	void copy();
	void paste();
	void clear();
}ed;
int edit::select()
{
	get_button_press(0);
	if(mclick==1 && mx>=scx && my>=scy && mx<=scx+scw && my<=scy+sch)
	{
	x1=mx,y1=my;
	setcolor(WHITE);
	outtextxy(500,5,"select");
	while(get_button_release(0)==1)
	{
		mouse_status();
		if(mx-x1>200 || my-y1>200) break;
	}
	x2=mx,y2=my;
	setcolor(BLUE);
	outtextxy(500,5,"select");
	sel=1;
	return 1;
	}
	return 0;
}
void edit::cut()
{
	if(x1==0) return;
	area=imagesize(x1,y1,x2,y2);
	ebuf=(void*) malloc(area);
	hide_mouse();
	if(ebuf!=NULL)
		getimage(x1,y1,x2,y2,ebuf);
	setfillstyle(SOLID_FILL,WHITE);
	bar(x1,y1,x2,y2);
	delay(100);
	show_mouse();
}
void edit::copy()
{
	if(x1==0) return;
	area=imagesize(x1,y1,x2,y2);
	ebuf=(void*) malloc(area);
	hide_mouse();
	if(ebuf!=NULL)
		getimage(x1,y1,x2,y2,ebuf);
	else free(ebuf);
	show_mouse();
}
void edit::paste()
{
	if(sel==1)
	{
	putimage(scx+100,scy+100,ebuf,COPY_PUT);
	free(ebuf);
	sel=0;
	}
}
void edit::clear()
{
	hide_mouse();
	setfillstyle(SOLID_FILL,WHITE);
	bar(scx+1,scy+1,scx+scw-1,scy+sch-1);
	free(ebuf);
	show_mouse();
}
class image
{
	int x1,y1,x2,y2;
	int *c;
	public:
	image()
	{
	}
	int select();
	void invert();
	void rotate();
	void scale();
	void translate();
}im;
int image::select()
{
	get_button_press(0);
	x1=mx,y1=my;
	if(mclick==1 && mx>=scx && my>=scy && mx<=scx+scw && my<=scy+sch)
	{
		setcolor(WHITE);
		outtextxy(400,10,"s");
		while(get_button_release(0)==1)
		{
			mouse_status();
			if(mx-x1>=200 || my-y1>200) break;
		}
		x2=mx;
		y2=my;
		setcolor(BLUE);
		outtextxy(400,10,"s");
		return 1;
	}
	return 0;
}
void image::rotate()
{
	static int c=-1;
	int i,j;//m1=(x1+x2)/2,m2=(y1+y2)/2;
	int a2=0;double angle;
	yes_no_box yn;
	yn.show("Rotate - Enter Angle");
	c=yn.check();
	while(c==-1)
	{
		getnum();
		c=yn.check();
	}
	a2=convnum(imnum);
	angle=((double)(a2)*3.14)/180.;
	if(c==0) {c=-1;return;}
	for(i=0;i<imlen;i++) imnum[i]='\0';
	imlen=0;
	c=-1;
	int *a=new int((x2-x1)*(y2-y1));
	hide_mouse();
	for(i=0;i<=x2-x1;i++)
		for(j=0;j<=y2-y1;j++)
			*(a+i*(x2-x1)+j)=getpixel(x1+i,y1+j);
	setfillstyle(SOLID_FILL,WHITE);
	bar(x1,y1,x2,y2);
	for(i=0;i<=x2-x1;i++)
	for(j=0;j<=y2-y1;j++)
	{
	if(x1+i*cos(angle)-j*sin(angle)>scx && x1+i*cos(angle)-j*sin(angle)<scx+scw)
	if(y1+i*sin(angle)+j*cos(angle)>scy && y1+i*sin(angle)+j*cos(angle)<scy+sch)
	putpixel(double(x1)+double(i)*cos(angle)-double(j)*sin(angle),double(y1)+double(i)*sin(angle)-double(j)*cos(angle),*(a+i*(x2-x1)+j));
	}
	show_mouse();
	delete(a);
}
void image::scale()
{
	static int c=-1;
	int scale=0,i,j,m1=(x1+x2)/2,m2=(y1+y2)/2;
	yes_no_box yn;
	yn.show("Scale - Enter Scale Factor");
	c=yn.check();
	while(c==-1)
	{
		getnum();
		c=yn.check();
	}
	scale=convnum(imnum);
	if(c==0) {c=-1;return;}
	else
	{
		for(int i=0;i<imlen;i++) imnum[i]='\0';
		imlen=0;
		c=-1;
		if(scale>4) return;
	}
	int *a=new int ((x2-x1)*(y2-y1));
	hide_mouse();
	for(i=0;i<=x2-x1;i++)
	for(j=0;j<=x2-x1;j++)
	*(a+i*(x2-x1)+j)=getpixel(x1+i,y1+j);
	setfillstyle(SOLID_FILL,WHITE);
	bar(x1,y1,x2,y2);
	for(i=0;i<=x2-x1;i++)
	for(j=0;j<=x2-x1;j++)
	{
	if(x1-(m1-x1)*scale+i*scale<scx+scale || x1-(m1-x1)*scale+i*scale>scx+scw || y1-(m2-y1)*scale+j*scale<scy || y1-(m2-y1)*scale+j*scale>scy+scw-scale) break;
	pixel(x1-(m1-x1)*scale+i*scale,y1-(m2-y1)*scale+j*scale,*(a+i*(x2-x1)+j),scale);
	}
	delete(a);
	show_mouse();
}
void image::translate()
{
	static int c=-1;
	int xpos=0,ypos=0;
	yes_no_box yn;
	yn.show("Translate - Enter x Value");
	c=yn.check();
	while(c==-1)
	{
		getnum();
		c=yn.check();
	}
	xpos=convnum(imnum);
	if(c==0) {c=-1;return;}
	else
	{
		for(int i=0;i<imlen;i++) imnum[i]='\0';
		imlen=0;
		c=-1;
	}
	yn.show("Translate - Enter y Value");
	c=yn.check();
	while(c==-1)
	{
		getnum();
		c=yn.check();
	}
	ypos=convnum(imnum);
	if(c==0) {c=-1;return;}
	else
	{
		for(int i=0;i<imlen;i++) imnum[i]='\0';
		imlen=0;
		c=-1;
	}
	if(x2+xpos<scx+scw && y2+ypos<scy+sch)
	{
		save_video(x1,y1,x2,y2);
		setfillstyle(SOLID_FILL,WHITE);
		bar(x1,y1,x2,y2);
		restore_video(x1+xpos,y1+ypos,1);
	}
}
void image::invert()
{
	int i,j,k,l;
	static int c=0;
	void * buf;
	k=scw/2,l=sch/2;
	for(i=scx+1;i<scx+scw;i+=k)
	for(j=scy+1;j<scy+sch;j+=l)
	{
		hide_mouse();
		buf=(void*)malloc(imagesize(i,j,i+k,j+l));
		if(buf!=NULL)
		{
		getimage(i,j,i+k,j+l,buf);
		putimage(i,j,buf,NOT_PUT);
		free(buf);
		}
	}
	if(c%2==0)
	setcolor(BLACK);
	else
	setcolor(WHITE);
	line(scx+1,scy+1+l,scx+scw,scy+l+1);
	line(scx+1+k,scy+1,scx+1+k,scy+sch);
	show_mouse();
	c++;
	if(c==100) c=0;
}
