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
	char * command=malloc(maxCommandLength);
	char ** argumentTable= malloc(maxCommandLength);

	write(STDOUT_FILENO,welcomeMessage,strlen(welcomeMessage));
	while(1){
		write(STDOUT_FILENO,promptMessage,strlen(promptMessage));
		 int commandBytes =  read(STDIN_FILENO,commandbuff,maxCommandLength);
		  command = SetCommandTable(commandbuff,argumentTable);
		 char test[4];
		strcpy(test,commandbuff);
		if(strcmp(test,"exit\n")==0 || strcmp(test,"^D")){
			write(STDOUT_FILENO,"Bye Bye ...\n",16);
			exit(EXIT_SUCCESS);
		}
		commandbuff[commandBytes-1]='\0';
		int status;
		if (commandBytes>0){
			int pid = fork();
			if(pid2 == 0 ){
				//execlp(commandbuff,commandbuff,(char*)NULL);
				execvp(argumentTable[0],argumentTable);
				exit(EXIT_FAILURE);
			}
			else {
				wait(&status);
				char * ExitText;
				if(WIFEXITED(status)){
					sprintf(ExitText,"%d", WEXITSTATUS(status));
				}
				if(WIFSIGNALED(status)){
					sprintf(ExitText,"%d", WTERMSIG(status));
				}
				write(STDOUT_FILENO,ExitText,8);
				exit(EXIT_SUCCESS);
			}
		else {
			wait(&status);
		}

		}
	
	}	
}

char * SetCommandTable(char * commandbuff,char ** argumentTable){
	char * currentcommand=malloc(maxCommandLength);
	int nthCommand = 0;
	int current=0;
	char * command;
	for (int i=0;i<strlen(commandbuff);i++){
		if (commandbuff[i]== ' '|| commandbuff[i]=='\n'){
			if (nthCommand ==0){
				command=currentcommand;
			}
			argumentTable[nthCommand]=currentcommand;
			nthCommand+=1;
			current=0;
			currentcommand= "";
		}
		else{
			currentcommand[current]=commandbuff[i];
			current+=1;
		}
	}
	//free(currentcommand);
	return command;
}



