#include "Elevator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitElevator(Elevator *Elev)
{
    Elev->floorNum = 10;        // 初始化总楼层数量为10
    Elev->currentFloor = 0;     // 初始化当前所在楼层为0
    Elev->maxPassenger = 5;     // 最大载客数固定为5
    Elev->currentPassenger = 0; // 当前载客数为0
    Elev->state = STOP;         // 初始化当前运行状态为停止
    Elev->targetCount = 0;      // 目标楼层数量为0
    Elev->stopCount = 0;        // 停靠次数为0
}

// 外部请求结构体输入函数
void InputFloor(Elevator *Elev)
{
    printf("请输入外部楼层请求数量：");
    scanf("%d", &Elev->targetCount);
    printf("请输入外部楼层请求（格式：楼层 方向）：");
    for (int i = 0; i < Elev->targetCount; i++)
    {
        scanf("%d%c", &Elev->Request_out[i].floor,
              &Elev->Request_out[i].direction);
    }
}
// 输出电梯初始信息
void output_ElevatorInfo(Elevator *Elev)
{
    printf("电梯初始信息");
    printf("当前所在楼层：%d\n", Elev->currentFloor);
    printf("最大载客数：%d\n", Elev->maxPassenger);
    printf("当前载客数：%d\n", Elev->currentPassenger);
    printf("当前运行状态：%d\n", Elev->state);
    printf("目标楼层数量：%d\n", Elev->targetCount);
}
void ElevatorRun(Elevator *Elev)
{
    SortRequest(Elev);
    output_ElevatorInfo(Elev);
    printf("电梯运行结果\n");

    for (int i = 0; i < Elev->targetCount; i++)
    {
        if (i == Elev->targetCount - 1)
        {
            printf("%d", Elev->Request_out[i].floor);
            break;
        }
        printf("%d->", Elev->Request_out[i].floor);
    }
    printf("\n");
}

void SortRequest(Elevator *Elev)
{
    for (int i = 0; i < Elev->targetCount; i++)
    {
        int swapped = 0; // 没有交换
        for (int j = 0; j < Elev->targetCount - i - 1; j++)
        {
            if (Elev->Request_out[j].floor > Elev->Request_out[j + 1].floor)
            {
                Request temp = Elev->Request_out[j];
                Elev->Request_out[j] = Elev->Request_out[j + 1];
                Elev->Request_out[j + 1] = temp;
                swapped = 1;
            }
        }
        // 如果没有交换，说明已经有序，直接跳出循环
        if (!swapped)
        {
            break;
        }
    }
}