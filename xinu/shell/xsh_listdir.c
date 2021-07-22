#include <xinu.h>
#include <stdio.h>
#include <string.h>


shellcmd xsh_listdir(int nargs, char *args[])
{

	/* print all the files and folders present in current directory */

	int i = 0;
	for(i=0;i<currdir->folder_count;i++)
	{
		kprintf("%s\n",currdir->fo[i]->name);
	}
	for(i=0;i<currdir->file_count;i++)
	{
		kprintf("%s\n",currdir->files[i]);
	}
}
