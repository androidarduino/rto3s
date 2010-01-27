#include "core.h"

void Task::run()
{
//    printf("task %p running.\n", this);
}

void Scheduler::operator <<(Task* task)
{
    tasks[taskCount]=(void*)task;
    taskCount++;
//    printf("Total tasks: %d\n", taskCount);
    //should test whether it overflows, however in most cases this is unnecessary.
}

Scheduler::Scheduler()
{
	taskCount=0;//reset taskCount
	for(int i=0;i<MAX_TASKS;i++)//init task list
		tasks[i]=(void*)0;
}

void Task::tick()
{
	if(tTicks==0)
		return;
    if(++tickCount>tTicks)
    {
        tickCount=0;
        tState=1;
    }
}

void Scheduler::runOs()
/* 	the current scheduling algorithm is not efficient. 
	should do this way: sort the tasks regarding its priorities,
	then search the first ready task, and finishes at the end of its priority.
	when a task changes its priority, re-sort the whole list.
*/
{
	//if(use_internal_tick)//external interrupt tick might be used instead, which is much more precises
		for(int i=0;i<MAX_TASKS;i++)
			((Task*)tasks[i])->tick();
	uchar highestPriority=15;
	for(int i=0;i<MAX_TASKS;i++)//find the ready tasks' highgest priority
	{
		Task* task=(Task*)tasks[i];
		if(task!=0)//if task exists
		{
			if(task->tState!=1)
				return;
			if(task->tPriority>highestPriority)
				highestPriority=task->tPriority;
		}
	}
	for(int i=0;i<MAX_TASKS;i++)
	{
		Task* task=(Task*)tasks[i];
		if(task->tState==1&&task->tPriority==highestPriority)
			task->run();
	}
}
