#include "core.h"
#include "binports.h"

int main(void)
{
    Scheduler sch;
    Task task1(8, 5000);
    Task task2(8, 10000);
    sch<<&task1;
    sch<<&task2;
 //   printf("task size: %d\n", sizeof(task1));
 	Port p(PORTA);
    //sch.runOs();
    return 0;
}

