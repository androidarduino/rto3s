#ifndef CORE_H
#define CORE_H
#include <stdio.h>
typedef unsigned char uchar;
typedef unsigned int uint;
void test();
class Task;
class Scheduler
/*
   All tasks register themselves to this class.
   This class schedules the tasks according to their priorities
   A system can have one and only one scheduler instance
*/
{
    public:
        Scheduler(){}//constructor
        void operator <<(Task* task);//add a task to the scheduler
    protected:
        void schedule();//re-schedule the tasks
        void* tasks[32];
};
class Task
{
    public:
        //Task States:{Ready, Running, Blocked, Waiting};
        Task(uchar priority=8, uint stackSize=128)
        {tPriority=priority;}
        virtual void run();
    protected:
        //we use the address of the task as task id, so no id member is required
        uchar tState:4;
        uchar tPriority:4;
};
#endif
