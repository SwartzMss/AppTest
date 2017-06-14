#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void mem_leak1(void)
{
	char* p = malloc (10);
}

void mem_leak2(void)
{
	FILE* p = fopen("11.txt","w");
}

void mem_overrun(void)
{
	char *szbuf = malloc(1);
	szbuf[10]='f';
	free(szbuf);
}

void mem_doublefree(void)
{
	char* p1 = malloc (20);
	free(p1);
	free(p1);
}

void mem_free_void_point(void)
{
	char* p2 ;
	free(p2) ;
}
int main()
{
	mem_leak1();
	mem_leak2();
	mem_overrun();
	mem_doublefree();
	mem_free_void_point();
	return 0;
}
