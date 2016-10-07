#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "stat_info.h"

void *thread_1(void *arg)
{
    char buf[1024];
    while(1){
        sleep(1);
        printf("%s : %d\n",__func__,get_thread_id());
    }
    return NULL;
}
void *thread_2(void *arg)
{
    char buf[10240];
    while(1){
        sleep(2);
        printf("%s : %d\n",__func__,get_thread_id());
    }
    return NULL;
}
void *thread_3(void *arg)
{
    char buf[45];
    while(1){
        sleep(3);
        printf("%s : %d\n",__func__,get_thread_id());
    }
    return NULL;
}
void *thread_4(void *arg)
{
    char buf[1234];
    while(1){
        sleep(67);
    }
    return NULL;
}
void *thread_5(void *arg)
{
    char buf[987];
    while(1){
        usleep(23);
    }
    return NULL;
}
void *thread_6(void *arg)
{
    char buf[631];
    while(1){
        sleep(1);
    }
    return NULL;
}
void *thread_7(void *arg)
{
    char buf[555];
    while(1){
        sleep(55);
    }
    return NULL;
}
void *thread_8(void *arg)
{
    char buf[999];
    while(1){
        sleep(431);
    }
    return NULL;
}
void *thread_9(void *arg)
{
    char buf[12];
    while(1){
        sleep(31);
    }
    return NULL;
}
void *thread_10(void *arg)
{
    char buf[333];
    while(1){
        sleep(19);
    }
    return NULL;
}

int main(int argc,char **argv)
{
    pthread_t thread_t = 0;
    TaskInfo task;
    pthread_create(&thread_t,NULL,thread_1,NULL);
    pthread_create(&thread_t,NULL,thread_2,NULL);
#if 0
    pthread_create(&thread_t,NULL,thread_3,NULL);
    pthread_create(&thread_t,NULL,thread_4,NULL);
    pthread_create(&thread_t,NULL,thread_5,NULL);
    pthread_create(&thread_t,NULL,thread_6,NULL);
    
    sleep(1);
#endif    
    while(1){
        sleep(1);
        get_thread_info(0,&task);
    }
    return 0;
}



