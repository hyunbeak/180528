#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>

void clean_up(void*);

void *thread_func(void*);

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lmu = PTHREAD_MUTEX_INITIALIZER;

int main(int argc,char **argv){
	pthread_t pt;
	pthread_create(&pt,NULL,thread_func,NULL);

	pthread_cancel(pt);

	sleep(5);
	pthread_cond_signal(&cond);

	pthread_join(pt,NULL);
	printf("exit\n");
	exit(1);
}

void clean_up(void *arg){
	printf("Thread cancel Cleadn_up function\n");
}

void* thread_func(void *arg){
	//쓰레드에 대한 취소요청을 무시한다.
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	//쓰레드 종료시 홏룰된 함수 등록
	pthread_cleanup_push(clean_up,(void*)NULL);

	pthread_mutex_lock(&lmu);

	printf("THREAD cond wait\n");
	pthread_cond_wait(&cond,&lmu);
	printf("GET COND SIGNAL\n");

	pthread_mutex_unlock(&lmu);

	printf("EXIT\n");
	pthread_cleanup_pop(0);
}