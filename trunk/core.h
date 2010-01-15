#ifndef CORE_H
#define CORE_H
#include <stdio.h>
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
        Scheduler(){taskCount=0;}//constructor
        void operator <<(Task* task);//add a task to the scheduler
    protected:
        void schedule();//re-schedule the tasks
        void* tasks[64];//64 tasks max
        uchar taskCount;//count the task heads
};

class Task
{
    public:
        Task(uchar priority=8, uint stackSize=128)
        {
            tPriority=priority;
            timerTask=false;
        }
        virtual void run();//the loop
        bool inUse;//indicate whether the task resource is in use
        bool timerTask;//true if this is a timer task
    protected:
        //we use the address of the task as task id, so no id member is required
        uchar tState:4;//states: 0-15: running, ready, blocked, waiting...
        uchar tPriority:4;//priorities: 0-15, lower better
};

class TimerTask: public Task
{
    public:
        TimerTask(uint interval, uchar priority=8, uint stackSize=128):Task(priority, stackSize)
        {
            tInterval=interval;
            timerTask=true;
            tickCount=0;
        }
        void tick()
        {
            if(++tickCount>tInterval)
            {
                tickCount=0;
                run();
            }
        }
    protected:
        uint tInterval,tickCount;
};
#endif
