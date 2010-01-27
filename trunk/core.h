#ifndef CORE_H
#define CORE_H
//#include <stdio.h>
#define MAX_TASKS 64
typedef unsigned char uchar;
typedef unsigned int uint;
class Task;
class Scheduler
/*
   All tasks register themselves to this class.
   This class schedules the tasks according to their priorities
   A system can have one and only one scheduler instance
*/
{
    public:
        Scheduler();//constructor
        void operator <<(Task* task);//add a task to the scheduler
        void runOs();//start the loop
    protected:
        void schedule();//re-schedule the tasks
        void* tasks[MAX_TASKS];//64 tasks max
        uchar taskCount;//count the task heads
};

class Task
{
    public:
        Task(uchar priority=8, uint ticks=0)
		//ticks indicates how after how many ticks the task gets invoked and run once
        {
            tPriority=priority;
            tTicks=ticks;
        }
        virtual void run();//the loop
        void tick();//called every loop of scheduling
        bool inUse;//indicate whether the task resource is in use
        //we use the address of the task as task id, so no id member is required
        uchar tState:4;//states: 0-15: running, ready, blocked, waiting...
        uchar tPriority:4;//priorities: 0-15, lower better
    protected:
        uint tTicks,tickCount;
};
#endif
