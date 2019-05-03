
/*实现互斥锁基本使用以及线程安全的基本认识
 *
 *黄牛抢票
 *
 */

//为何要和互斥锁，下面一个简单的例子说明线程的不安全性

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int ticket  =100;

void *thr_start(void *arg)
{
    while(1)
    {
        if(ticket>0)
        {
            printf("yellow bull --%d---get a ticket : %d\n",(int)arg,ticket);
            ticket--;
            usleep(1000);
        }

        else
        {
            pthread_exit(NULL); //线程终止
        }

        
    }
    return NULL;
}

int main(int argc,char *argv[])
{


    pthread_t tid[4];

    int i=0,ret;
    for(i=0;i<4;i++)
    {
        ret=pthread_create(&tid[i],NULL,thr_start,(void*)i);
        if(ret!=0)  //成功返回0
        {
            printf("yellow bull no exit !!!\n");
            return -1;
        }
    }

for(i=0;i<4;i++)
    {

        pthread_join(tid[i],NULL);  //线程等待
    }

    return 0;
}





