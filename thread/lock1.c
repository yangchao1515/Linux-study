
/*实现互斥锁基本使用以及线程安全的基本认识
 *
 *黄牛抢票
 *
 *互斥锁操作步骤：
 1.定义互斥锁变量          pthread_mutex_t
 2.初始化互斥锁变量        prhread_mutex_intit
 3.加锁                    pthread_mutex_lock
 4.解锁                    pthread_mutex_unlock 
 4.销毁互斥锁              pthread_mutex_destroy
 *
 *
 */


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int ticket  =100;
pthread_mutex_t mutex;

void *thr_start(void *arg)
{
    while(1)
    {
        //加锁要在临界资源访问之前
        //int pthread_mutex_lock(thread_mutex_t *mutex);
        //  阻塞加锁
        //int pthread_mutes_trylock(pthread_mutex_t *mutex);
        //  非阻塞加锁；加不上锁就直接报错返回
        //pthread_mutex_timelock    限时的阻塞加锁

        pthread_mutex_lock(&mutex); //加锁

        if(ticket>0)
        {
            printf("yellow bull --%d---get a ticket : %d\n",(int)arg,ticket);
            ticket--;
            usleep(1000);
        }

        else        //加锁之后要在线程任意有可能退出的地方进行解锁
        {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL); //线程终止
        }
        //解锁
        pthread_mutex_unlock(&mutex);

    }
    return NULL;
}

int main(int argc,char *argv[])
{


    pthread_t tid[4];


    int i=0,ret;

    //初始化互斥锁
    //int pthread_mutex_init(pthread_mutex_t *mutex,pthread_mutexattr_t *attr)
    //  mut:    互斥锁变量
    //  attr:   属性，通常为NULL

    pthread_mutex_init(&mutex,NULL);

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
    pthread_mutex_destroy(&mutex);
    return 0;
}





