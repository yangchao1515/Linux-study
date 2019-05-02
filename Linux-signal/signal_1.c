  1 /*信号处理的修改
  2  *     *
  3  *       * sighadnler_t signal (int signum,sighandler_ t handler);
  4  *         *
  5  *           * sighadnler_t signal (int signum,sighandler_ t handler);
  6  *             *         signum: 信号的编号
  7  *               *       handler: 信号的处理方式
  8  *                 *     typedef void(*sighandler_t)(int);))
  9  *                   *
 10  *                     */
 11 
 12 #include<stdio.h>
 13 #include<error.h>
 14 #include<unistd.h>
 15 #include<stdlib.h>
 16 #include<signal.h>
 17 
 18 int main(int argc,char *argv[])
 19 {
 20     //ctrl+ c 没反应，，ctrl+ \  有反应
 21     signal(SIGINT,SIG_IGN); //SIG_IGN是忽略信号
 22     while(1)
 23     {
 24         printf("hello ! \n");
 25         sleep(1);
 26     }
 27 
 28     return 0;
 29 }
