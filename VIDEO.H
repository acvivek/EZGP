void *buf=NULL;
int flag=0;
unsigned int area;
void save_video(int x1,int y1,int x2,int y2)
{
	hide_mouse();
	area=imagesize(x1,y1,x2,y2);
	buf=(void*)malloc(area);
	if (buf!=NULL)
		getimage(x1,y1,x2,y2,(void far*)buf);
	show_mouse();
}
void restore_video(int x1,int y1,int f)
{
	hide_mouse();
	putimage(x1,y1,(void far*)buf,COPY_PUT);
	if(f==1)
	{
		flag=0;
		free(buf);
	}
	show_mouse();
}
