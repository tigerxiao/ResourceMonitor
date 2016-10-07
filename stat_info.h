#ifndef __STAT_INFO_H__
#define __STAT_INFO_H__

#include <limits.h>


///proc/pid/stat
typedef struct{                                     //http://man7.org/linux/man-pages/man5/proc.5.html
    int       processID;                            //The process ID.
    char      exeName[_POSIX_PATH_MAX];             //The filename of the executable
    char      state;                                //One INT8acter from the string "RSDZTW" where R is running, 
                                                    //S is sleeping in an INT32erruptible wait, D is waiting in unINT32erruptible disk sleep, 
                                                    //Z is zombie, T is traced or stopped (on a signal), and W is paging
    int       PPID;                                 //The PID of the parent.
    int       groupID;                              //The process group ID of the process.
    int       sessionID;                            //The session ID of the process.
    int       ttyID;                                //The controlling terminal of the process. (The minor device number is contained in the 
                                                    //combination of bits 31 to 20 and 7 to 0; the major device number is in bits 15 to 8.)
    int       tpgid;                                //The ID of the foreground process group of the controlling terminal of the process.
    unsigned int         flags;                     //The kernel flags word of the process. For bit meanings, see the PF_* defines in the Linux 
                                                    //kernel source file include/linux/sched.h. Details depend on the kernel version.
    long unsigned int    minflt;                    //The number of minor faults the process has made which have not required loading a memory 
                                                    //page from disk.
    long unsigned int    cminflt;                   //The number of minor faults that the process's waited-for children have made.
    long unsigned int    majflt;                    //The number of major faults the process has made which have required loading a memory page
                                                    //from disk.
    long unsigned int    cmajflt;                   //The number of major faults that the process's waited-for children have made.
    long unsigned int    utime;                     // Amount of time that this process has been scheduled in user mode, measured in clock ticks 
                                                    //(divide by sysconf(_SC_CLK_TCK)). This includes guest time, guest_time (time spent running a 
                                                    //virtual CPU, see below), so that applications that are not aware of the guest time field do 
                                                    //not lose that time from their calculations.
    long unsigned int    stime;                     //Amount of time that this process has been scheduled in kernel mode, measured in clock ticks 
                                                    //(divide by sysconf(_SC_CLK_TCK)).
    long unsigned int    cutime;                    //Amount of time that this process's waited-for children have been scheduled in user mode, 
                                                    //measured in clock ticks (divide by sysconf(_SC_CLK_TCK)). (See also times(2).) This includes 
                                                    //guest time, cguest_time (time spent running a virtual CPU, see below).
    long unsigned int    cstime;                    //Amount of time that this process's waited-for children have been scheduled in kernel mode, 
                                                    //measured in clock ticks (divide by sysconf(_SC_CLK_TCK)).
    long unsigned int    priority;                  //For processes running a real-time scheduling policy
    long unsigned int    nice;                      //The nice value (see setpriority(2)), a value in the range 19 (low priority) to -20 
                                                    //(high priority).
    long unsigned int    num_threads;               //Number of threads in this process (since Linux 2.6). Before kernel 2.6, this field was hard 
                                                    //coded to 0 as a placeholder for an earlier removed field.
    long unsigned int    itrealvalue;               //The time in jiffies before the next SIGALRM is sent to the process due to an INT32erval timer. 
                                                    //Since kernel 2.6.17, this field is no longer maINT32ained, and is hard coded as 0.
    long long unsigned int    starttime;            //The time the process started after system boot. In kernels before Linux 2.6, this value was 
                                                    //expressed in jiffies. Since Linux 2.6, the value is expressed in clock ticks (divide by sysconf(_SC_CLK_TCK)).
    long unsigned int    vsize;                     // Virtual memory size in bytes.
    long unsigned int    rss;                       //Resident Set Size: number of pages the process has in real memory. This is just the pages 
                                                    //which count toward text, data, or stack space. This does not include pages which have not 
                                                    //been demand-loaded in, or which are swapped out.
    long unsigned int    rsslim;                    //Current soft limit in bytes on the rss of the process
    long unsigned int    startcode;                 //The address above which program text can run.
    long unsigned int    endcode;                   //The address below which program text can run.
    long unsigned int    startstack;                //The address of the start (i.e., bottom) of the stack.
    long unsigned int    kstkesp;                   //The current value of ESP (stack poINT32er), as found in the kernel stack page for the process.
    long unsigned int    kstkeip;                   //The current EIP (instruction poINT32er).
    long unsigned int    signal;                    //The bitmap of pending signals, displayed as a decimal number. Obsolete, because it does not provide information on real-time signals; use /proc/[pid]/status instead.
    long unsigned int    blocked;                   //The bitmap of blocked signals, displayed as a decimal number. Obsolete, because it does not provide information on real-time signals
    long unsigned int    sigignore;                 //The bitmap of ignored signals, displayed as a decimal number. Obsolete, because it does not provide information on real-time signals
    long unsigned int    sigcatch;                  //The bitmap of caught signals, displayed as a decimal number. Obsolete, because it does not provide information on real-time signals
    long unsigned int    wchan;                     //This is the "channel" in which the process is waiting.
    long unsigned int    nswap;                     //Number of pages swapped (not maINT32ained).
    long unsigned int    cnswap;                    //Cumulative nswap for child processes (not maINT32ained).
    int                 exit_signal;                //Signal to be sent to parent when we die.
    int                 processor;                  //CPU number last executed on
    unsigned int        rt_priority;                //Real-time scheduling priority, a number in the range 1 to 99 for processes scheduled under a real-time policy, or 0, for non-real-time processes
    unsigned int        policy;                     //Scheduling policy
    long long unsigned int    delayacct_blkio_ticks;//Aggregated block I/O delays, measured in clock ticks 
    long unsigned int    guest_time;                //Guest time of the process (time spent running a virtual CPU for a guest operating system), measured in clock ticks (divide by sysconf(_SC_CLK_TCK)).
    long unsigned int    cguest_time;               //Guest time of the process's children, measured in clock ticks (divide by sysconf(_SC_CLK_TCK)).
    /*since linux 3.5*/
    long unsigned int    start_data;                //Address above which program initialized and uninitialized (BSS) data are placed.
    long unsigned int    end_data;                  //Address below which program initialized and uninitialized (BSS) data are placed.
    long unsigned int    start_brk;                 //Address above which program heap can be expanded  with brk(2).
    long unsigned int    arg_start;                 //Address above which program command-line arguments (argv) are placed.
    long unsigned int    arg_end;                   //Address below program command-line arguments (argv) are placed.
    long unsigned int    env_start;                 //Address above which program environment is placed.
    long unsigned int    env_end;                   //Address below which program environment is placed.
    int                  exit_code;                 //The thread's exit status in the form reported by waitpid(2).

}StatInfo,*PStatInfo;

///proc/pid/statm
typedef struct{
    int size;                                       //total program size
    int resident;                                   //resident set size
    int share;                                      //shared pages
    int text;                                       //text code size
    int lib;                                        //lib size(unused in Linux 2.6)
    int data;                                       //data + stack
    int dt;                                         //dirty pages (unused in Linux 2.6)
}StatmInfo,*PStatmInfo;

#define MAX_LEN_THREAD_NAME                         512
typedef struct{
    int         pid;                                //thread id
    int         memory;                             //KB
    int         cpu;                                //
    char        name[MAX_LEN_THREAD_NAME];          //the name of thread
    StatInfo    statInfo;                           //stat info
    StatmInfo   statmInfo;                          //statm info
}ThreadInfo,*PThreadInfo;


#define MAX_NUM_THREADS                             200
typedef struct{
    int threadNum;                                  //the num of threads, MAX num is MAX_NUM_THREADS
    ThreadInfo threadInfo[MAX_NUM_THREADS];         //
}TaskInfo,*PTaskInfo;


int get_thread_info(int processId,TaskInfo *task);

char *get_file_content(char *filePath);

pid_t get_thread_id();


#endif

