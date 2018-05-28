#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
static int count=9;
static pthread_mutex_t countlock=PTHREAD_MUTEX_INITIALIZER;

void* increment(void* data){
	int error;
	while(1){
	if(error=pthread_mutex_lock(&countlock))
		return (void *)error;
	count++;
	if(error=pthread_mutex_unlock(&countlock))
		return (void *)error;
	 usleep(10);
	}
}

void* decrement(void* data){
	int error;
	while(1){
	if(error=pthread_mutex_lock(&countlock))
		return (void *)error;
	count--;
	if(error=pthread_mutex_unlock(&countlock))
		return (void *)error;
	usleep(10);
	}
}
void* getcount(void* data){
	int error;
//	int countValue=0;
	//while(1){
	//if(error = pthread_mutex_lock(&countlock))
	//	return (void *)error;
	////countValue=*((int*)data);
	//if(error=pthread_mutex_unlock(&countlock))
	//	return (void *)error;
	//}
	//sleep(1);
	while(1){
	 printf("%d\n",count);
	// usleep(10);
	}
}
int main(void){
	pthread_t p_thread[3];
	int err;
	int cnt=0;
	int status;
		if((err=pthread_create(&p_thread[0],NULL,increment,(void*)NULL))<0){
		perror("thread create error:");
		exit(1);
		}
		if((err=pthread_create(&p_thread[1],NULL,decrement,(void*)NULL))<0){
		perror("thread create error:");
		exit(2);
		}
		if((err=pthread_create(&p_thread[2],NULL,getcount,(void*)NULL))<0){
		perror("thread create error:");
		exit(3);
		}
		err=pthread_detach(p_thread[0]);
		err=pthread_detach(p_thread[1]);
		err=pthread_detach(p_thread[2]);
		//pthread_join(p_thread[2],(void**)&status);
	//	printf("%d%d",status,count);
		while(1){

		}
	return 0;
}