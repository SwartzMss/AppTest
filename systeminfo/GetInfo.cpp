#include <sys/statfs.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "MyLogger.h"

#define KB 1024.0			// 2^10
#define MB 1048576.0		// 2^20 
#define GB 1073741824.0     // 2^30 

#define VMSIZE_LINE 13
MyLogger * pMyLogger = NULL;

//获取进程占用虚拟内存
unsigned int get_proc_virtualmem(unsigned int pid)
{
	
	char file_name[64]={0};
	FILE *fd;
	char line_buff[512]={0};
	sprintf(file_name,"/proc/%d/status",pid);
	
	fd =fopen(file_name,"r");
	if(NULL == fd){
		return 0;
	}
	
	char name[64];
	int vmsize;
	for (int i=0; i<VMSIZE_LINE-1;i++){
		fgets(line_buff,sizeof(line_buff),fd);
	}
	
	fgets(line_buff,sizeof(line_buff),fd);
	sscanf(line_buff,"%s %d",name,&vmsize);
	fclose(fd);

	return vmsize;
}



//获取指定目录下的硬盘使用情况
void GetDiskUsage(const char* pDir)
{
	struct statfs diskInfo;
	statfs(pDir, &diskInfo);
	uint64_t blocksize = diskInfo.f_bsize;				 	 // 每个block里包含的字节数
	uint64_t totalsize = blocksize * diskInfo.f_blocks; 	 // 总的字节数，f_blocks为block的数目
	printf("Total_size = %lld B = %f KB = %f MB = %f GB\n", 
		totalsize, 
		totalsize / KB, 
		totalsize / MB, 
		totalsize / GB);
	
	uint64_t freeDisk = diskInfo.f_bfree * blocksize;		// 剩余空间的大小
	uint64_t availableDisk = diskInfo.f_bavail * blocksize; // 可用空间大小
	printf("Disk_free = %f MB = %f GB\n"
			"Disk_available = %f MB = %f GB\n", 
		freeDisk / MB, 
		freeDisk / GB, 
		availableDisk / MB, 
		availableDisk / GB);
}

int main(void)
{
	pMyLogger = MyLogger::getInstance();
	DEBUG_LOG("main");
	char *pbuf = new char[1024*1024*10];
	memset(pbuf,0,1024*1024*10);
	GetDiskUsage("/home");
	int pid = getpid();
	printf("getpid = %d\n",pid);
	//返回的单位是K字节
	unsigned int men = get_proc_virtualmem(pid);
	printf("pid =%d,virtual men = %d K\n",pid,men);
	while(1)
	{
		sleep(100);
	}
	return 0;
}
