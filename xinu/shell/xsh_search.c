#include <xinu.h>
#include <stdio.h>
#include <string.h>s

void procA(struct folder* temp, int currpos,char path[],int nargs);

void setFlag(int index)		/* give signal to next child process */
{
	if(currindex == currentpos)
	{return;}
	if(index == currindex-1)
	{
		setFlag(-1);		/* start first child process after last child process */
	}
	else
	{
		int i = 0;
		int j = 0;
		for(i=0;i<currentpos;i++)
		{
			if(stor_flag[i] == index+1)
			{
				setFlag(index+1);
				j = 1;
			}
		}
		if(j == 0)
		{
			signal(flag[index+1]);
		}
	}
}

int check(char file_name[],int nargs)		/* function to compare file names */
{
	int j = 1;
	int i = 0;
	for(i=0;i<nargs-1;i++)
	{
		if(strstr(file_name,arguments[i+1]) == NULL)
		{j=0;}
	}
	return j;
}

void searchFile(struct folder* temp,int index,char path[],int nargs)		/* function to search all the files in a specific folder */
{
    	struct folder* temp4;
    	temp4 = temp;
	if(check(temp4->name,nargs) == 1)		/* check folder name */
        {printf("%s\n",path);}
	int i = 0;
    	for(i=0;i<temp->file_count;i++)
    	{
		wait(flag[index]);					/* stall the process and wait for it's turn */
		char temp_path[100];
		strcpy(temp_path,path);
		strncat(temp_path,"/",1);
		strncat(temp_path,temp4->files[i],strlen(temp4->files[i]));
		if(check(temp4->files[i],nargs) == 1)
        	{
		umsg32	msg;
		strcpy(search_msg,temp_path);		/* send message 1 to main process if file name matches with search query */
		msg = 1;
		send(search_index,msg);
		}else{
		umsg32 msg;
		msg = 0;
		send(search_index,msg);				/* send message 0 to main process if file name does not matche with search query */
}
		running_prindex = index;
		
		signal(run_search);				/* give signal to the main process */
    	}
	return;
}

void searchFolder(struct folder* temp,char path[],int nargs)		/* Function to navigate through all directories and start child process for each directory */
{
	char temp_path[100];
	strcpy(temp_path,path);
	strncat(temp_path,"/",1);
	strncat(temp_path,temp->name,strlen(temp->name));
    	struct folder* temp3;
    	temp3 = temp;
	resume(create(procA,1024,20,"procA",4,temp3,currindex,temp_path,nargs));		/* start child process */
	currindex = currindex + 1;
	int i = 0;
    	for(i = 0;i<temp3->folder_count;i++)
    	{
        	searchFolder(temp3->fo[i],temp_path,nargs);
    	}
	
	return;
}

shellcmd xsh_search(int nargs, char *args[])
{
	kprintf("\n");
	run_search = semcreate(0);
	currindex = 0;
	currentpos = 0;
	running_prindex = 0;
	int i = 0;
	for(i=0;i<100;i++)
	{stor_flag[i]=-1;}
	for(i=0;i<nargs;i++)
	{arguments[i]=args[i];}
	char path[100];
	strcpy(path,"");
	searchFolder(currdir,path,nargs);
	signal(flag[0]);		/* signal to start the first child process */
	while(currentpos < currindex){
	wait(run_search);		/* stall the parent process and wait for the signal */
	umsg32	msg;
	msg = receive();		/* receive message sent from child process */
	if(msg == 1)
	{kprintf("%s\n",search_msg);}
	
	setFlag(running_prindex);
}
	
	kprintf("\n");
}

void procA(struct folder* temp,int currpos,char path[],int nargs)	/* child process to search all the files present in a specific folder */
{
	int index = currpos;
	flag[index] = semcreate(0);
	char temp_path[100];
	strcpy(temp_path,path);
	searchFile(temp,index,temp_path,nargs);
	stor_flag[currentpos] = index;
	currentpos = currentpos + 1;
}
