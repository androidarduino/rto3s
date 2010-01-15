#include "core.h"

int main(void)
{
    Scheduler sch;
    Task task;
    sch<<&task;
    task.run();
    printf("task size: %d\n", sizeof(task));
    return 0;
}
