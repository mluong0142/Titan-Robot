#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define FAIL -1
#define SUCCESS 0

char ImageDetec(char path[]);
void main()
{
	ImageDetec("/home/avinash/ImagePackage/ImageDectec.py");

}

char ImageDetec(char path[])
{
	int fdShape;
	char edges;
	pid_t pid1;


	fdShape = mkfifo("/home/avinash/ImagePackage/shape",0666);
	if(fdShape == FAIL)
	{
		printf("Error file may already exists\n");
	}
	pid1 = fork();
	if(pid1 == FAIL)
	{
		printf("fork failed\n");
	}

	else if(pid1 == SUCCESS)
	{//Child
		execv(path,(char*)NULL);
	}
	else
	{//Parent
		fdShape = open("/home/avinash/ImagePackage/shape",O_RDONLY);
		if(fdShape == FAIL)
		{
			printf("Cannot open fifo\n");
		}
		else if (fdShape != FAIL)
		{
			read(fdShape,&edges,sizeof(char));
			printf("%c",edges);
			close(fdShape);
			remove("/home/avinash/ImagePackage/shape");

		}

	}

}




