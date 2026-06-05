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

    // 初始化电梯
    Init_Elevator(&Elev);
    // 输入外部请求
    Input_External_Requests(&Elev);
    // 确定初始方向
    Determine_Initial_Direction(&Elev);
    // 输出电梯信息
    Output_ElevatorInfo(&Elev);
    // 输入内部目标
    Input_Internal_Requests(&Elev);
    // 查看并排序目标
    Look_Sort(&Elev);
    // 输出最终目标
    Output_finalTargets(&Elev);

    return 0;
}