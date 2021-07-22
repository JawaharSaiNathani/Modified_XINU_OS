#include <xinu.h>
#include <stdio.h>
#include <string.h>

void	get_path(struct folder* f,char path[])		/* search for the directory that matches the current directoy id and return its parent directory */
{
	char	temp_path[100];
	strcpy(temp_path,path);
	strncat(temp_path,f->name,strlen(f->name));
	strncat(temp_path,"/",1);
	if(currdir->id == f->id)
	{
		strcpy(fold_path,temp_path);
		return;
	}
	int i = 0;
	for(i=0;i<f->folder_count;i++)
	{
		get_path(f->fo[i],temp_path);
	}
	return;
}

shellcmd xsh_pathfinder(int nargs, char *args[])
{
	kprintf("\n");
	get_path(home,"/");
	kprintf("pwd: %s\n",fold_path);
	kprintf("\n");
}
