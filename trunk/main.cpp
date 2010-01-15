#include "core.h"

int main(void)
{
    Task task;
    task.run();
    printf("task size: %d\n", sizeof(task));
    return 0;
}
