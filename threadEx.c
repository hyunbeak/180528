#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

#define TH 100000

struct from{
	int argcount[2];
	int long sum;
};

void *Thread_function(void* data){
	int i =0;
	struct from Fm = *((struct from *)data);
	for(i=Fm.;i<Fm.;i++){
		Fm.sum+=i;
	}
	return (void *)(Fm.sum);
}



int main(int argc,char** argv){
	struct from Fm;
	struct timeval Ti1,Ti2;
	int i =0,err,status;

	//int sum=0;
	gettimeofday(&Ti2,NULL);
	if(argc ==1){
		for(i=0;i<TH;i++){
			Fm.sum+=i;
		}
	}
	else if(argc ==2){
			pthread_t *p_thread;
			int end=atoi(argv[1]);
			p_thread = (pthread_t*) malloc(sizeof(int)*end);
			
			for(i=0;i<end;i++){
			Fm.argcount[0]=i;
			Fm.argcount[1]=end;
			if((err=pthread_create(&p_thread[i],NULL,Thread_function,(void*)&Fm))<0){
				perror("thread create error:");
				exit(1);
			}

			for(i=0;i<end;i++){
				pthread_join(p_thread[i],(void**)&status);
				printf("thread join:%d\n",status);
			}
		}
			//Fm.sum=status;
	}
	else{
		fprintf(stderr, "arg error\n");
		exit(EXIT_FAILURE);
	}

	gettimeofday(&Ti2,NULL);
	printf("time=%ld\n",Ti2.tv_usec-Ti1.tv_usec);
	printf("%d\n",Fm.sum);
	return 0;
}