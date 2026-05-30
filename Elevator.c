#include "Elevator.h"

#include <stdio.h>

void Init_Elevator(Elevator *Elev)
{
    Elev->finalTargetCount = 0;
    for (int i = 0; i < MAX_FLOOR_COUNT; i++)
    {
        Elev->finalTargets[i] = -1;
    }

    Elev->currentFloor = 1;
    Elev->targetCount = 0;
    Elev->externalCount = 0;

    for (int i = 0; i < MAX_FLOOR_COUNT; i++)
    {
        Elev->externalRequests[i].floor = i + 1;
        Elev->externalRequests[i].type = EXTERNAL;
        Elev->externalRequests[i].targetFloor = -1;
        Elev->externalRequests[i].isProcessed = 0;
    }
}

void Input_Floor(Elevator *Elev)
{
    printf("请输入外部楼层请求数量：");
    scanf("%d", &Elev->externalCount);
    printf("请输入外部楼层请求(1 2 3): ");

    int target = 0;
    for (int i = 0; i < Elev->externalCount; i++)
    {
        scanf("%d", &target);
        Elev->externalRequests[target - 1].targetFloor = 0;

        // 先记录最终目标楼层,放入最终目标楼层队列
        Elev->finalTargetCount++;
        Elev->finalTargets[i] = target;
    }
}

void Output_ElevatorInfo(Elevator *Elev)
{
    printf("电梯初始信息\n");
    printf("当前所在楼层：%d\n", Elev->currentFloor);
    printf("目标楼层数量：%d\n", Elev->externalCount);
    printf("目标楼层队列：");
    for (int i = 0; i < MAX_FLOOR_COUNT; i++)
    {
        if (Elev->externalRequests[i].targetFloor != -1)
        {
            printf("%d -> ", i + 1);
        }
    }
    printf("\n");
}

void Input_Passenger(Elevator *Elev)
{
    printf("输入乘客请求 \n");
    for (int i = 0; i < MAX_FLOOR_COUNT; i++)
    {
        // 如果该楼层有乘客请求,则记录乘客目标楼层,放入最终目标楼层队列
        if (Elev->externalRequests[i].targetFloor != -1)
        {
            printf("请输入%d楼的乘客目标楼层:", i + 1);
            scanf("%d", &Elev->externalRequests[i].targetFloor);

            Elev->finalTargets[Elev->finalTargetCount++] =
                Elev->externalRequests[i].targetFloor;
        }
    }
}

void Output_finalTargets(Elevator *Elev)
{
    printf("最终目标楼层队列：");
    for (int i = 0; i < Elev->finalTargetCount; i++)
    {
        printf("%d -> ", Elev->finalTargets[i]);
    }
    printf("\n");
}