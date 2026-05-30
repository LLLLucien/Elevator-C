#include "Elevator.h"

#include <stdio.h>
int Red[MAX_FLOOR_COUNT] = {0};
int blue[MAX_FLOOR_COUNT] = {0};
int r_i = 0;
int b_i = 0;

void Init_Elevator(Elevator *Elev)
{
    Elev->finalTargetCount = 0;
    for (int i = 0; i < MAX_TARGET_COUNT; i++)
    {
        Elev->finalTargets[i] = -1;
    }

    Elev->currentFloor = 0; // 电梯初始所在楼层
    Elev->direction = 0; // 方向的标志位，0表示向上，1表示向下
    Elev->externalCount = 0; // 外部请求数量
    Elev->internalCount = 0; // 内部目标请求数量

    // for (int i = 0; i < MAX_FLOOR_COUNT; i++)
    // {
    //     Elev->externalRequests[i].floor = i + 1;
    //     Elev->externalRequests[i].type = EXTERNAL;
    //     Elev->externalRequests[i].targetFloor = -1;
    //     Elev->externalRequests[i].isProcessed = 0;
}

void Input_External_Requests(Elevator *Elev)
{
    printf("请输入外部楼层请求数量：");
    scanf("%d", &Elev->externalCount);
    printf("请输入电梯初始楼层：");
    scanf("%d", &Elev->currentFloor);
    printf("请输入外部楼层请求(1 2 3): ");

    int target = 0;
    for (int i = 0; i < Elev->externalCount; i++)
    {
        // 输入外部楼层请求
        scanf("%d", &target);
        Elev->externalRequests[i] = target;
        // // 先记录最终目标楼层,放入最终目标楼层队列
        // Elev->finalTargetCount++;
        // Elev->finalTargets[i] = target;
    }
    // 对外部请求进行排序
    Sort_External_Requests(Elev->externalRequests, Elev->externalCount,
                           Elev->currentFloor, Elev);
}

void Output_ElevatorInfo(Elevator *Elev)
{
    printf("电梯初始信息\n");
    printf("当前所在楼层：%d\n", Elev->currentFloor);
    printf("目标楼层数量：%d\n", Elev->externalCount);
    printf("目标楼层队列：");
    printf("%d", Elev->currentFloor);
    for (int i = 0; i < Elev->externalCount; i++)
    {
        printf(" -> %d", Elev->externalRequests[i]);
    }
    printf("\n");
}

void Input_Internal_Requests(Elevator *Elev)
{
    printf("输入乘客请求 \n");
    for (int i = 0; i < Elev->externalCount; i++)
    {
        printf("请输入%d楼的乘客目标楼层:", Elev->externalRequests[i]);
        scanf("%d", &Elev->internalRequests[i]);
        Elev->internalCount++;
    }
}

void Output_finalTargets(Elevator *Elev)
{
    printf("最终目标楼层队列：");
    int first = 1;
    for (int i = 0; i < MAX_TARGET_COUNT; i++)
    {
        if (Elev->finalTargets[i] != -1)
        {
            if (first)
            {
                printf("%d", Elev->finalTargets[i]);
                first = 0;
            } else
            {
                printf(" -> %d", Elev->finalTargets[i]);
            }
        }
    }
    printf("\n");
}

void Sort_External_Requests(int *array, int count, int currentFloor,
                            Elevator *Elev)
{
    // 对外部请求进行排序
    // int Red[MAX_FLOOR_COUNT] = {0};
    // int blue[MAX_FLOOR_COUNT] = {0};
    // int r_i = 0;
    // int b_i = 0;
    // 分为高于当前楼层和低于当前楼层的请求
    for (int i = 0; i < count; i++)
    {
        if (array[i] > currentFloor)
        {
            Red[r_i++] = array[i];
        } else
        {
            blue[b_i++] = array[i];
        }
    }
    // 对高于当前楼层的请求进行升序排序
    Sort_Red_Top(Red, r_i);
    // 对低于当前楼层的请求进行降序排序
    Sort_Blue_Bottom(blue, b_i);
    // 合并高于当前楼层的请求和低于当前楼层的请求
    for (int i = 0; i < r_i; i++)
    {
        array[i] = Red[i];
    }
    for (int i = 0; i < b_i; i++)
    {
        array[r_i + i] = blue[i];
    }
    // 存入最终目标楼层队列
    Elev->finalTargetCount = count;
    for (int i = 0; i < count; i++)
    {
        Elev->finalTargets[i] = array[i];
    }
}
void Sort_Red_Top(int *array, int count)
{
    // 对高于当前楼层的请求进行升序排序
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
void Sort_Blue_Bottom(int *array, int count)
{
    // 对低于当前楼层的请求进行降序排序
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (array[j] < array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
/*
目前规定了电梯默认方向为上行方向
通过每次插入对应楼层的请求，来排序内部请求
上行方向：高于当前楼层的请求，都加入Red数组并升序排序
下行方向：低于当前楼层的请求，都加入blue数组并降序排序
最后处理下行时，如果有上行请求，就加入到new_Red数组中并升序排序
最后把Red，blue，new_Red数组合并到finalTargets数组中就是最终的目标楼层队列

*/
void Look_Sort(Elevator *Elev)
{
    // 判断是否有重复请求
    int same_Red = 0;
    int same_Blue = 0;
    // Red数组的最后一个元素就是方向将翻转的位置

    int turn = r_i - 1;

    // 用来存储转向后的请求，会和Red数组有重复的元素
    int new_Red[MAX_FLOOR_COUNT] = {0};
    int new_r_i = 0;
    for (int i = 0; i < Elev->internalCount; i++)
    {
        // 同为上行方向
        if (Elev->direction == 0)
        {
            // 大于当前楼层的请求，都加入Red数组并升序排序（不是重复请求）
            if (Elev->internalRequests[i] > Elev->externalRequests[i])
            {
                for (int j = 0; j < r_i; j++)
                {
                    if (Red[j] == Elev->internalRequests[i])
                    {
                        same_Red = 1;
                        break;
                    }
                }
                if (!same_Red)
                {
                    Red[r_i++] = Elev->internalRequests[i];
                }
                Sort_Red_Top(Red, r_i);
                same_Red = 0;
            } else
            {
                // 小于当前楼层的请求，都加入blue数组并降序排序（不是重复请求）
                for (int j = 0; j < b_i; j++)
                {
                    if (blue[j] == Elev->internalRequests[i])
                    {
                        same_Blue = 1;
                        break;
                    }
                }
                if (!same_Blue)
                {
                    blue[b_i++] = Elev->internalRequests[i];
                }
                Sort_Blue_Bottom(blue, b_i);
                same_Blue = 0;
            }
        }
        // 反方向，则看blue数组是否重复
        else
        {
            // 小于当前楼层的请求，都加入blue数组并降序排序（不是重复请求）
            if (Elev->internalRequests[i] < Elev->externalRequests[i])
            {
                for (int j = 0; j < b_i; j++)
                {
                    if (blue[j] == Elev->internalRequests[i])
                    {
                        same_Blue = 1;
                        break;
                    }
                }
                if (!same_Blue)
                {
                    blue[b_i++] = Elev->internalRequests[i];
                }
                Sort_Blue_Bottom(blue, b_i);
                same_Blue = 0;
            } else
            {
                // 大于当前楼层的请求，都加入一个新的数组并升序排序
                new_Red[new_r_i++] = Elev->internalRequests[i];
                Sort_Red_Top(new_Red, new_r_i);
                same_Red = 0;
            }
        }

        // 到达翻转的位置
        if (i == turn)
        {
            Elev->direction = 1;
        }
    }
    // 最后把Red，blue，new_Red数组合并到finalTargets数组中
    for (int j = 0; j < r_i; j++)
    {
        Elev->finalTargets[j] = Red[j];
    }
    for (int j = 0; j < b_i; j++)
    {
        Elev->finalTargets[r_i + j] = blue[j];
    }
    for (int j = 0; j < new_r_i; j++)
    {
        Elev->finalTargets[r_i + b_i + j] = new_Red[j];
    }
}
