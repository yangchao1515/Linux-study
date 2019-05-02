#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("recv signo :%d\n",signo);
}


int main()
{

    signal(SIGINT,sigcb);   //  不可靠信号
    signal(SIGRTMIN+5,sigcb);   //可靠信号

    //先阻塞所有信号，当按下回车，恢复原有信号
    sigset_t set,oldset;

    sigemptyset(&set);
    //int sigfillset(sigset_t *set)
    //将所有的信号添加到set集合中
    //int sigaddset(sigaet_t *set ,int signum);
    //将指定信号signum添加到set中

    //注意这里9号和19号信号无法阻塞
    sigfillset(&set);
    sigprocmask(SIG_BLOCK,&set,&oldset);

    printf("按下回车解除阻塞\n");
    getchar();


    //下面两个作用相同，都是还原到原先的block状态）
    sigprocmask(SIG_UNBLOCK,&set,NULL);
    // sigprocmask(SIG_SETMASK,&oldset,NULL);
    return 0;
}


