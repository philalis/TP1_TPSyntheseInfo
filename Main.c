#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void main(){
	//int fd= open(fileName,O_RDWR);
	
	const static char* welcomeMessage = "$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n";
	const static char*  promptMessage = 		"enseash %\n";
	#define maxCommandLength 1024
	static char commandbuff[maxCommandLength];

	write(STDOUT_FILENO,welcomeMessage,strlen(welcomeMessage));
	while(1){

		write(STDOUT_FILENO,promptMessage,strlen(promptMessage));


		

		 int commandBytes =  read(STDIN_FILENO,commandbuff,maxCommandLength);
		 
		 commandbuff[commandBytes-1]='\0';

		 int status;
		 if (commandBytes>0){
			
			int pid = fork();
			if(pid ==0){				
				execlp(commandbuff,commandbuff,(char*)NULL);
				exit(EXIT_FAILURE);
			}
			else {
				wait(&status);
			}

		 }
		
	}
	


	
}