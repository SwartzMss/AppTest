#include <unistd.h>
#include <pthread.h>

void* thread1(void*args)
{

	//可以使用ulimit -s 查看当前系统的堆栈限制
	char szbuf[1*1024*1024]={0};
	int a = 1/0; 

}

int main()
{
	pthread_t id;
	pthread_create(&id,NULL,thread1,NULL);
	pthread_join(id,NULL);
	return 0;
}
