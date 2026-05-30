#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Elevator.h"

int main()
{
    printf("\n");
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║                                              ║\n");
    printf("║          电梯调度算法演示系统                ║\n");
    printf("║                                              ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    printf("\n");

    Elevator Elev;
    Init_Elevator(&Elev);
    Input_External_Requests(&Elev);
    Determine_Initial_Direction(&Elev);
    Output_ElevatorInfo(&Elev);
    Input_Internal_Requests(&Elev);
    Look_Sort(&Elev);
    Output_finalTargets(&Elev);

    return 0;
}