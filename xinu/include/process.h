/* process.h - isbadpid */

/* Maximum number of processes in the system */

#ifndef NPROC
#define	NPROC		8
#endif		

/* Process state constants */

#define	PR_FREE		0	/* Process table entry is unused	*/
#define	PR_CURR		1	/* Process is currently running		*/
#define	PR_READY	2	/* Process is on ready queue		*/
#define	PR_RECV		3	/* Process waiting for message		*/
#define	PR_SLEEP	4	/* Process is sleeping			*/
#define	PR_SUSP		5	/* Process is suspended			*/
#define	PR_WAIT		6	/* Process is on semaphore queue	*/
#define	PR_RECTIM	7	/* Process is receiving with timeout	*/

/* Miscellaneous process definitions */

#define	PNMLEN		16	/* Length of process "name"		*/
#define	NULLPROC	0	/* ID of the null process		*/

/* Process initialization constants */

#define	INITSTK		65536	/* Initial process stack size		*/
#define	INITPRIO	20	/* Initial process priority		*/
#define	INITRET		userret	/* Address to which process returns	*/

/* Inline code to check process ID (assumes interrupts are disabled)	*/

#define	isbadpid(x)	( ((pid32)(x) < 0) || \
			  ((pid32)(x) >= NPROC) || \
			  (proctab[(x)].prstate == PR_FREE))

/* Number of device descriptors a process can have open */

#define NDESC		5	/* must be odd to make procent 4N bytes	*/

/* Definition of the process table (multiple of 32 bits) */

struct procent {		/* Entry in the process table		*/
	uint16	prstate;	/* Process state: PR_CURR, etc.		*/
	pri16	prprio;		/* Process priority			*/
	char	*prstkptr;	/* Saved stack pointer			*/
	char	*prstkbase;	/* Base of run time stack		*/
	uint32	prstklen;	/* Stack length in bytes		*/
	char	prname[PNMLEN];	/* Process name				*/
	sid32	prsem;		/* Semaphore on which process waits	*/
	pid32	prparent;	/* ID of the creating process		*/
	umsg32	prmsg;		/* Message sent to this process		*/
	bool8	prhasmsg;	/* Nonzero iff msg is valid		*/
	char	*ipc_msgs[50];
	int	msg_count;
	int16	prdesc[NDESC];	/* Device descriptors for process	*/
	uint32  pridid;
};

/* Definition of the directory (multiple of 136 bits) */

struct folder {		
	int	id;						/* Id of the folder */
	char	name[20];			/* name of the directory */
	char	files[5][20];		/* store files present in this directory */
	int	file_count;				/* number of files present */
	int	folder_count;			/* number of sub directories present */
	struct	folder* fo[10];		/* store sub folders */
};

/* Marker for the top of a process stack (used to help detect overflow)	*/
#define	STACKMAGIC	0x0A0AAAA9

extern	struct	procent proctab[];
extern	struct	procent newproctab[];
extern	int32	prcount;	/* Currently active processes		*/
extern	pid32	currpid;	/* Currently executing process		*/	
extern  int	currindex;		/* search: current created child process */
extern	int	flag[100];		/* semaphore count for wait and signal for child processes */
extern	int	stor_flag[100];	/* store pid of all completed child processes */
extern	char	*arguments[100];
extern	int	currentpos;
extern	int	search_index;
extern	int	run_search;		/* semaphore count for wait and signal for parent processes */
extern	int	running_prindex;	/* current executing child process */
extern	int	total_folders;		/* total number of folders */
extern	char	fold_path[100];	/* current directory path */
extern	char	search_msg[100];	/* store file path of search algorithm */
extern	bpid32	sfo;			/* store buffer pool */
extern	bpid32	buffer;		
extern	struct	bpentry* First;
extern	struct	folder* home;	/* home directory */
extern	struct	folder*	currdir;	/* current directory */
extern	struct	folder*	cd_dir;		/* change directory to */
