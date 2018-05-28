#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

#define FALSE 0
#define TRUE 1
#define FAIL -1
#define DEBUG 999
#define SHMSIZE (1024*10)
#define BUFSIZE 128
void Fork_(pid_t result_fork);


void handler(int s) {
	if (s == SIGUSR1) {
		printf("Success, Write txt file\n");
	}
	else if (s == SIGUSR2) {
		printf("Success, PID trade\n");
	}
}

int main(void){
	pid_t hyunfork;
	hyunfork=fork();
		if (hyunfork == FAIL) {
		fprintf(stderr, "check fork\n");
		exit(EXIT_FAILURE);
	}
		Fork_(hyunfork);
	return 0;
}
void Fork_(pid_t hyunfork){
	int id,status;
	char *address;
	void* mem = (void*)0;
	FILE *frp;
	char buffer[BUFSIZE];
	int count;

	frp = fopen("lena.bmp", "rb");
	if(hyunfork==FALSE){
		//exclp("./ascii_art_server","ascii_art_server",(char*)0);
	}
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);

#ifdef DEBUG
		printf("memset %p\n",memset);
#endif

		address = (char *)mem;
		//WriteMemory(address);
		kill(hyunfork,SIGUSR1);
		pause();

	while (TRUE) {
			memset(buffer, '\0', BUFSIZE);
			if (*address == 0) {
				count = fread(buffer, 1, BUFSIZE, frp);
				if (feof(frp) == 0) {
					strcpy(address + 1, buffer);
					*address = 1;
				}
				else {
					strcpy(address + 1, buffer);
					*(address + BUFSIZE + 1) = count;
					*address = 2;
					break;
				}
			}
			while (*address == 1);
		}

		if (shmdt(mem) == FAIL){
			fprintf(stderr, "Check shmdt\n");
			exit(EXIT_FAILURE);
		}

		wait(&status);

		if (shmctl(id, IPC_RMID, 0) == FAIL) {
			fprintf(stderr, "Check shmctl\n");
			exit(EXIT_FAILURE);
		}


}