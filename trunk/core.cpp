#include "core.h"

void Task::run()
{
    printf("task %p running.\n", this);
}

void Scheduler::operator <<(Task* task)
{
    tasks[taskCount]=(void*)task;
    taskCount++;
    printf("Total tasks: %d\n", taskCount);
    //should test whether it overflows, however in most cases this is unnecessary.
}
