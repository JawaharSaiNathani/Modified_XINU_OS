#include <xinu.h>
#include <stdio.h>
#include <string.h>


shellcmd xsh_mkdir(int nargs, char *args[])
{
	kprintf("\n");

	/* check all the files if there is any file with same name */

	int i = 0;
	int j = 0;
	for(i=0;i<currdir->folder_count;i++)
	{
		if(strcmp(args[1],currdir->fo[i]->name)==0)
		{
			j = 1;
			break;
		}
	}
	if(j==0)
	{
	for(i=0;i<currdir->file_count;i++)
	{
		if(strcmp(args[1],currdir->files[i])==0)
		{
			j = 1;
			break;
		}
	}
	}
	if(j==0){
	struct folder* temp;
	temp = (struct folder*)getbuf(sfo);		/* get buffer space for new folder */

	/* create new empty folder */

	strcpy(temp->name,args[1]);
	temp->id = total_folders;
	total_folders = total_folders + 1;
	temp->folder_count = 0;
	temp->file_count = 0;
	currdir->fo[currdir->folder_count] = temp;
	currdir->folder_count = currdir->folder_count + 1;
	}else{
		kprintf("mkdir: error: %s File exists\n",args[1]);
	}
	kprintf("\n");
}
