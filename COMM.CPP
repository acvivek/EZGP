int count;
int f[10][10];
int n;
void show()
{
	int gd=DETECT,gm=DETECT;
	initgraph(&gd,&gm,"c:\\tc\\");
	for(int i=0;i<=count;i++)
	{
		switch(f[i][0])
		{
			case 1:
				circle(f[i][1],f[i][2],f[i][3]);
			break;
			case 2:
				rectangle(f[i][1],f[i][2],f[i][3],f[i][4]);
			break;
			case 3:
				line(f[i][1],f[i][2],f[i][3],f[i][4]);
			break;
			case 4:
				line(f[i][1],f[i][2],f[i][3],f[i][4]);
				line(f[i][1],f[i][2],f[i][5],f[i][6]);
				line(f[i][3],f[i][4],f[i][5],f[i][6]);
			break;
		}
	}
	getch();
	closegraph();
}
void command()
{
	closegraph();
	char c[20],tmp[10];
	int i,j=0,l;
	clrscr();
	printf("Enter the commands \n");
	while(1)
	{
		n=1;
		printf("\nEZ>");
		gets(c);
		if(strcmp(c,"exit")==0) exit(0);
		else if(strcmp(c,"view")==0)
			show();
		else if(strcmp(c,"clear")==0)
		{
			 for(int q=0;q<=10;q++)
			 for(int z=0;z<=10;z++)
			 f[q][z]=0;
		}
		else
		{
			l=strlen(c);
			switch(c[0])
			{
				case 'c': f[count][0]=1;
				break;
				case 'r': f[count][0]=2;
				break;
				case 'l': f[count][0]=3;
				break;
				case 't': f[count][0]=4;
				break;
				default: printf("\nInvalid commmand");continue;
			}
			for(i=2;i<l;i++)
			{
			       if(c[i]==' ')
			       {
					tmp[j]='\0';
					f[count][n++]=convnum(tmp);
					j=0;
				}
				else tmp[j++]=c[i];
			}
			tmp[j]='\0';
			f[count][n++]=convnum(tmp);
			j=0;
			count++;
		}
	}
}
