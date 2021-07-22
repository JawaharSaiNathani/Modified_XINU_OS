/*  main.c  - main */

#include <xinu.h>
#include<stdio.h>
#include<string.h>


process	main(void)
{
	/* Run the Xinu shell */


	recvclr();
	resume(create(shell, 8192, 1, "shell", 1, CONSOLE));

	sfo = mkbufpool(136,30);        /* create space in memory for file system*/

	home = (struct folder*)getbuf(sfo);     /*  create home directory */
        strcpy(home->name,"Home");              /* assign name */
	home->id = 0;                           /* assign id */
        home->file_count = 3;                   /* assign no of files */
        home->folder_count = 3;                 /* assign folders count */
        strcpy(home->files[0],"main");
        strcpy(home->files[1],"resched");
        strcpy(home->files[2],"create");

        struct folder* temp1;
        struct folder* temp2;
        
        temp1 = (struct folder*)getbuf(sfo);    /* create sub folders for Home directory */
        strcpy(temp1->name,"Documents");
	temp1->id = 1;
        temp1->file_count = 2;
        temp1->folder_count = 2;
        strcpy(temp1->files[0],"results");
        strcpy(temp1->files[1],"certificates");
        
        temp2 = (struct folder*)getbuf(sfo);    /* create sub folder for Documents directory  */
        strcpy(temp2->name,"xinu");
	temp2->id = 2;
        temp2->file_count = 2;
        temp2->folder_count = 0;
        strcpy(temp2->files[0],"resched");
        strcpy(temp2->files[1],"process");
        temp1->fo[0] = temp2;                   /* attach sub folder xinu to main folder Documents */
        
        temp2 = (struct folder*)getbuf(sfo);
        strcpy(temp2->name,"OS");
	temp2->id = 3;
        temp2->file_count = 1;
        temp2->folder_count = 0;
        strcpy(temp2->files[0],"report");
        temp1->fo[1] = temp2;
        
        home->fo[0] = temp1;                    /* attach sub folder Documents to main Folder Home */
        
        temp1 = (struct folder*)getbuf(sfo);
        strcpy(temp1->name,"Desktop");
	temp1->id = 4;
        temp1->file_count = 2;
        temp1->folder_count = 2;
        strcpy(temp1->files[0],"valorant");
        strcpy(temp1->files[1],"gta5");
        
        temp2 = (struct folder*)getbuf(sfo);
        strcpy(temp2->name,"movies");
	temp2->id = 5;
        temp2->file_count = 2;
        temp2->folder_count = 0;
        strcpy(temp2->files[0],"tenet");
        strcpy(temp2->files[1],"ff9");
        temp1->fo[0] = temp2;
        
        temp2 = (struct folder*)getbuf(sfo);
        strcpy(temp2->name,"songs");
	temp2->id = 6;
        temp2->file_count = 2;
        temp2->folder_count = 0;
        strcpy(temp2->files[0],"aurora");
        strcpy(temp2->files[1],"drivers license");
        temp1->fo[1] = temp2;
        
        home->fo[1] = temp1;
        
        temp1 = (struct folder*)getbuf(sfo);
        strcpy(temp1->name,"Downloads");
	temp1->id = 7;
        temp1->file_count = 2;
        temp1->folder_count = 1;
        strcpy(temp1->files[0],"game");
        strcpy(temp1->files[1],"ad");
        
        temp2 = (struct folder*)getbuf(sfo);
        strcpy(temp2->name,"series");
	temp2->id = 8;
        temp2->file_count = 2;
        temp2->folder_count = 0;
        strcpy(temp2->files[0],"silicon valley");
        strcpy(temp2->files[1],"game of thrones");
        temp1->fo[0] = temp2;
        
        home->fo[2] = temp1;
	currdir = home;
	total_folders = 9;

	currindex = 0;
	currentpos = 0;


	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
