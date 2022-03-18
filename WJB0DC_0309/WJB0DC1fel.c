#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int status, status1;
	status=system("dir");
	status1=system("ASDASFRGKMW");
	if(status < 0) perror("system() error");
	if(WIFEXITED(status)) printf("Normalis befejezodes, visszaadott ertek: %d\n", WEXITSTATUS(status));
	else printf("Nem normalis befejezodes\n");
	if(status < 0) perror("system() error");
	if(WIFEXITED(status)) printf("Normalis befejezodes, visszaadott ertek: %d\n ", WEXITSTATUS(status));
	else printf("Nem normalis befejezodes\n");
	exit(0);
}
