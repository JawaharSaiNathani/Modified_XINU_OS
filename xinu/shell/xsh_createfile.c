#include <xinu.h>
#include <stdio.h>
#include <string.h>


shellcmd xsh_createfile(int nargs, char *args[])
{
	kprintf("\n");
	int i = 0;
	int j = 0;
	char file_name[100];
	strcpy(file_name,args[1]);

	/* check all the files if there is any file with same name */

	for(i=0;i<nargs-2;i++)
	{
		strncat(file_name," ",1);
		strncat(file_name,args[i+2],strlen(args[i+2]));
	}
	for(i=0;i<currdir->file_count;i++)
	{
		if(strcmp(file_name,currdir->files[i])==0)
		{
			j = 1;
			break;
		}
	}
	if(j==0){
	for(i=0;i<currdir->folder_count;i++)
	{
		if(strcmp(file_name,currdir->fo[i]->name)==0)
		{
			j = 1;
			break;
		}
	}
	}

	/* if there is no file matching it, then create the file */

	if(j==0){
		strcpy(currdir->files[currdir->file_count],file_name);		/* copy file name into files array */
		currdir->file_count = currdir->file_count + 1;
	}else{
		kprintf("create: error: %s File exists\n",file_name);
	}
	kprintf("\n");
}
