#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	//int fd= open(fileName,O_RDWR);
	
	char * content = "$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\nenseash %\n";

	write(STDOUT_FILENO,content,strlen(content));

}