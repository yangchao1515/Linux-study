#include<stdio.h>
#include<error.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

struct sigaction act, oldact;

void sigcb(int signo)
{
    printf("recv signo : %d \n",signo);
    //还原原来的动作
    sigaction(signo,&oldact,NULL);
}

//使用act动作替换signum原有的处理动作，并且将原有的处理动作拷贝到oldact中

int main()
{
    act.sa_handler = sigcb;
    act.sa_flags = 0;

    //清空信号集合
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT,&act,&oldact);

    while(1)
    {
        printf("----------\n");
        sleep(1);
    }



return 0;
}
