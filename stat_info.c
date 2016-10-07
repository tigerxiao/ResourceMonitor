#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>

#include "stat_info.h"

static void print_stat_info(const StatInfo *stat_info)
{
    if(NULL != stat_info){
        printf("%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d\n",
                        stat_info->processID,stat_info->exeName,
                        stat_info->state,stat_info->PPID,stat_info->groupID,stat_info->sessionID,stat_info->ttyID,
                        stat_info->tpgid,stat_info->flags,stat_info->minflt,stat_info->cminflt,stat_info->majflt,
                        stat_info->cmajflt,stat_info->utime,stat_info->stime,stat_info->cutime,stat_info->cstime,
                        stat_info->priority,stat_info->nice,stat_info->num_threads,stat_info->itrealvalue,stat_info->starttime,
                        stat_info->vsize,stat_info->rss,stat_info->rsslim,stat_info->startcode,stat_info->endcode,
                        stat_info->startstack,stat_info->kstkesp,stat_info->kstkeip,stat_info->signal,stat_info->blocked,
                        stat_info->sigignore,stat_info->sigcatch,stat_info->wchan,stat_info->nswap,stat_info->cnswap,
                        stat_info->exit_signal,stat_info->processor,stat_info->rt_priority,stat_info->policy,stat_info->delayacct_blkio_ticks,
                        stat_info->guest_time,stat_info->cguest_time,stat_info->start_data,stat_info->end_data,stat_info->start_brk,
                        stat_info->arg_start,stat_info->arg_end,stat_info->env_start,stat_info->env_end,stat_info->exit_code);
    }
}

//stat
static int fill_stat_info(const char *stat_string,StatInfo *stat_info)
{
    char *p = NULL;
    char *q = NULL;
    
    if(NULL == stat_info || NULL == stat_string){
        printf("para must not be null\n");
        return -1;
    }

    memset(stat_info,0,sizeof(StatInfo));
    if(0 >= sscanf(stat_string,"%u",&stat_info->processID)){
        return -1;
    }
    p = strchr(stat_string,'(');
    q = strchr(stat_string,')');

    if(NULL == p || NULL == q){
        printf("para must contain exe name\n");
        return -1;
    }
    strncpy(stat_info->exeName,p+1,q-p-1);

    if(50 != sscanf(q+2,"%c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d",
                        &stat_info->state,&stat_info->PPID,&stat_info->groupID,&stat_info->sessionID,&stat_info->ttyID,
                        &stat_info->tpgid,&stat_info->flags,&stat_info->minflt,&stat_info->cminflt,&stat_info->majflt,
                        &stat_info->cmajflt,&stat_info->utime,&stat_info->stime,&stat_info->cutime,&stat_info->cstime,
                        &stat_info->priority,&stat_info->nice,&stat_info->num_threads,&stat_info->itrealvalue,&stat_info->starttime,
                        &stat_info->vsize,&stat_info->rss,&stat_info->rsslim,&stat_info->startcode,&stat_info->endcode,
                        &stat_info->startstack,&stat_info->kstkesp,&stat_info->kstkeip,&stat_info->signal,&stat_info->blocked,
                        &stat_info->sigignore,&stat_info->sigcatch,&stat_info->wchan,&stat_info->nswap,&stat_info->cnswap,
                        &stat_info->exit_signal,&stat_info->processor,&stat_info->rt_priority,&stat_info->policy,&stat_info->delayacct_blkio_ticks,
                        &stat_info->guest_time,&stat_info->cguest_time,&stat_info->start_data,&stat_info->end_data,&stat_info->start_brk,
                        &stat_info->arg_start,&stat_info->arg_end,&stat_info->env_start,&stat_info->env_end,&stat_info->exit_code)){
        printf("para is not valid. \n");
        return -1;
    }
    
   // print_stat_info(stat_info);
    return 0;
}

static void print_statm_info(StatmInfo *statm_info)
{
    if(NULL != statm_info){
        printf("%d %d %d %d %d %d %d\n",statm_info->size,statm_info->resident,statm_info->share,
                                                statm_info->text,statm_info->lib,statm_info->data,statm_info->dt);
    }
}

//statm 可以计算内存占用多少,statm里面的单位是page，1page是4KB,占用内存大小为(text+data)*4KB
static int fill_statm_info(const char *statm,StatmInfo *statm_info)
{
    if(NULL == statm || NULL == statm_info){
        return -1;
    } 

    memset(statm_info,0,sizeof(StatmInfo));

    if(7 != sscanf(statm,"%d %d %d %d %d %d %d",&statm_info->size,&statm_info->resident,&statm_info->share,
                                                &statm_info->text,&statm_info->lib,&statm_info->data,&statm_info->dt)){
        return -1;
    }
    print_statm_info(statm_info);
    return 0;
}

//计算某个线程或进程的内存消耗
static int calc_memory(StatmInfo *statm_info)
{
    if(NULL != statm_info){
        return (statm_info->text+statm_info->data)*4;
    }
    
    return 0;
}

static int calc_cpu(StatInfo *stat_info)
{
    if(NULL != stat_info){
        //return (stat_info->cstime+stat_info->utime+stat_info->stime+stat_info->cutime);
        return (stat_info->utime+stat_info->stime);
    }
    return 0;
}

//根据文件名，获得文件内容，谁调用谁释放
char *get_file_content(char *filePath)
{
    char *fileContent = NULL;
    FILE *fp = NULL;
    int size = 0;

    if(NULL == filePath)
    {
        return NULL;
    }
    
    fp = fopen(filePath,"rb");
    if(NULL == fp){
        printf("error to open %s\n",filePath);
        return NULL;
    }

    fseek(fp,0L,SEEK_END);
    size = (ftell(fp) == 0) ? 4096 : ftell(fp);

    fileContent = malloc(size);
    if(NULL == fileContent){
        printf("malloc failed \n");
        fclose(fp);
        return NULL;
    }
    fseek(fp,0,SEEK_SET);
    if(fread(fileContent,1,size,fp) <= 0){
        printf("fread failed %s \n",strerror(errno));
        fclose(fp);
        free(fileContent);
        return NULL;
    }
    //printf("fileName: %s, content: %s\n",filePath,filePath);
    fclose(fp);
    return fileContent;
}

static void print_thread_info(TaskInfo *task)
{
    int i = 0;
    if(NULL == task){
        return;
    }
    for(i = 0;i < task->threadNum; i++){
        printf("%s:%d: cpu: %d, mem: %d\n",task->threadInfo[i].name,task->threadInfo[i].pid,task->threadInfo[i].cpu,task->threadInfo[i].memory);
    }
}

int get_thread_info(int processId,TaskInfo *task)
{
    int targetProcessId = (processId <= 0) ? getpid() : processId;
    char *fileContent = NULL;
    char filePath[1024] = {0};
    DIR  *dir = NULL;
    struct dirent *dirp = NULL;
    int num_thread = 0;
    
    if(NULL == task){
        return -1;
    }
    memset(task,0,sizeof(TaskInfo));
    snprintf(filePath,sizeof(filePath),"/proc/%d/task/",targetProcessId);
    dir = opendir(filePath);
    if(NULL == dir){
        printf("open dir: %s failed %s\n",filePath,strerror(errno));
        return -1;
    }

    while((dirp = readdir(dir)) != NULL){
        //printf("child thread : %s\n",dirp->d_name);
        if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0){
            continue;
        }
        
        memset(filePath,0,sizeof(filePath));
        snprintf(filePath,sizeof(filePath),"/proc/%d/task/%s/stat",targetProcessId,dirp->d_name);
        fileContent = get_file_content(filePath);
        fill_stat_info(fileContent, &task->threadInfo[num_thread].statInfo);
        task->threadInfo[num_thread].cpu = calc_cpu(&task->threadInfo[num_thread].statInfo);
        task->threadInfo[num_thread].pid = task->threadInfo[num_thread].statInfo.processID;
        if(NULL != fileContent){
            free(fileContent);
            fileContent = NULL;
        }

        memset(filePath,0,sizeof(filePath));
        snprintf(filePath,sizeof(filePath),"/proc/%d/task/%s/statm",targetProcessId,dirp->d_name);
        fileContent = get_file_content(filePath);
        fill_statm_info(fileContent, &task->threadInfo[num_thread].statmInfo);
        task->threadInfo[num_thread].memory = calc_memory(&task->threadInfo[num_thread].statmInfo);
        if(NULL != fileContent){
            free(fileContent);
            fileContent = NULL;
        }
        
        if(++num_thread >= MAX_NUM_THREADS){
            break;
        }
        
    }
    
    task->threadNum = num_thread;
    if(NULL != fileContent)
        free(fileContent);

    print_thread_info(task);
    closedir(dir);
    return 0;
}

pid_t get_thread_id()
{
    return syscall(SYS_gettid);
}

void create_new_thread(TaskInfo *task,void *thread_func,void *thread_arg)
{
    pthread_t thread_t = 0;

    if(NULL == task || NULL == thread_func){
        return;
    }
    pthread_create(&thread_t,NULL,thread_func,thread_arg);
}


