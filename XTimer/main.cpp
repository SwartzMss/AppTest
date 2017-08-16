#include "XTimer.h"

 void xTimerCallBack(void* ulUser)
 {
	 int num = *(int*)ulUser;
	printf("%d\n",num);
 }

int main()
{
	  XTimer pXTimer[3] ;
	  int Test[3]={1,2,3};
	  for(int i = 0;i<3;i++)
	  {
		  pXTimer[i].XTimerStart();
		  pXTimer[i].XTimerSetEvent(1000,xTimerCallBack, &Test[i],1);
		  sleep(3);
	  }

	  int n = 10;
      while(n--)
	  {
		  sleep(10);
	  }
	  for(int i =0;i<10;i++ )
	  {
		  pXTimer[i].XTimerStop();
	  }
	
	return 0;
}
