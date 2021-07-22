#include <xinu.h>
#include <stdio.h>
#include <string.h>

void find(struct folder* f,int id)		/* function to find the prevoius directory */
{
	int i = 0;
	for(i=0;i<f->folder_count;i++)
	{
		if(f->fo[i]->id == id)		/* if id of current directory matches then return directory */
		{cd_dir=f;
		break;}
		find(f->fo[i],id);
	}
}

shellcmd xsh_changedir(int nargs, char *args[])
{
	kprintf("\n");
	if(strcmp(args[1],"..")==0 && currdir->id!=0)		/* changing to previous directory  */
	{
		find(home,currdir->id);
		currdir = cd_dir;
	}else{												/* changing to specific directory */
	int i = 0;
	int j = 0;
	for(i=0;i<currdir->folder_count;i++)
	{
		if(strcmp(args[1],currdir->fo[i]->name)==0)
		{
			currdir = currdir->fo[i];
			j = 1;
			break;
		}
	}
	if(j==0)
	{kprintf("cd: error: no such directory found\n");}
	}
	kprintf("\n");
}
