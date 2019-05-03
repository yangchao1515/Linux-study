/*> Describe: 实现条件变量的基本使用
吃面---前提有人做面
如果没有现成的面，等待老板做出来
老板做出来面，就要唤醒顾客

老板不会做太多的面---老板只会提前做一碗面
如果已经有面做出来，但是没人吃，不会再做（等待）
顾客吃碗面之后，老板再来一碗（唤醒老板 的等待）
*************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int have_noodle = 1;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond;
pthread_mutex_t mutex;
void *thr_boss(void * arg) 
{
    while(1) {
        pthread_mutex_lock(&mutex);
 //       若面没有卖出去，则等待
            if (have_noodle == 1)
            {

                pthread_cond_wait(&cond, &mutex);
            }
   //     面被人买了，要再做一碗
            printf("ding niu la mian~~~+1\n");
        have_noodle += 1;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *thr_customer(void *arg) 
{
    while(1) {
        pthread_mutex_lock(&mutex);
     //   若没有现成的面，等老板做好
            if (have_noodle == 0) {
       //         等待
                    pthread_cond_wait(&cond, &mutex);
            }
       // 有面了就可以开心的吃了
            printf("noodler~~delicious\n");
        have_noodle -= 1;
      //  吃完面因为太好吃，因此再来一碗--唤醒老板
            pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    int ret;


    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    ret = pthread_create(&tid1, NULL, thr_boss, NULL);
    if (ret != 0) {
        printf("boss error\n");
        return -1;
    }
    ret = pthread_create(&tid2, NULL, thr_customer, NULL);
    if (ret != 0) {
        printf("boss error\n");
        return -1;
    }
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
  // 销毁条件变量
  //      int pthread_cond_destroy(pthread_cond_t *cond);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}
