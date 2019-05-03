
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg)
{
//    int pthread_detach(pthread_t thread);
  //  分离一个指定的线程---自己也可以
    //    线程的分离，对于一个线程来说，任意线程在任意位置调用都可以
        pthread_detach(pthread_self());
    sleep(3);

    return "nihao~~";
}
int main(int argc, char *argv[])
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
        printf("thread  create error\n");
        return -1;
    }
    pthread_detach(tid);
    pthread_cancel(tid);        //如果一个线程被取消，那么他的返回值是-1，还没有到return;
    char *ptr = NULL;
    ret = pthread_join(tid, (void**)&ptr);  //注意这里指针的使用
    if (ret == EINVAL) //这里判断是否能等待
    {
        printf("this thread can not be wait!!\n");
    }
    printf("retval:%d--%d\n", ret, (int)ptr);
    return 0;
}

