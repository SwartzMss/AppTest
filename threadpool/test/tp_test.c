
#define __DEBUG__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread_pool.h"

#define THD_NUM 100 

static pthread_mutex_t lock;
static unsigned exit_cnt;
TpThreadPool *pTp;

void proc_fun(void *arg){
	int i;
	int idx=(int) arg;
	i = 1000000.0 + (int)(9000000.0 * rand() / RAND_MAX);
	fprintf(stderr, "Begin: job %d, sleep %d us\n", idx, i);
	usleep(i);
	fprintf(stderr, "End:   job %d\n", idx);
	pthread_mutex_lock(&lock);
	exit_cnt++;
	pthread_mutex_unlock(&lock);
	if(exit_cnt == THD_NUM)
		tp_exit(pTp);
}

int main(int argc, char **argv){
	pTp= tp_create(10, THD_NUM);
	int i;

	exit_cnt = 0;
	pthread_mutex_init(&lock, NULL);
	tp_init(pTp);
	srand((int)time(0));
	for(i=0; i < THD_NUM; i++){
		tp_process_job(pTp, proc_fun, i);
	}
	tp_run(pTp);
	free(pTp);
	fprintf(stderr, "All jobs done!\n");
	return 0;
}

