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
    int temp[MAX_FLOOR_COUNT];
    int hasDuplicate;

    do
    {
        hasDuplicate = 0;
        printf("══════════════════════════════════════════\n");
        printf("请输入外部楼层请求数量：");
        scanf("%d", &Elev->externalCount);
        if (Elev->externalCount > MAX_FLOOR_COUNT)
        {
            hasDuplicate = 1;
            printf("⚠️ 外部楼层请求数量不能超过 %d！\n", MAX_FLOOR_COUNT);
        }

        if (!hasDuplicate)
        {
            printf("请输入电梯初始楼层：");
            scanf("%d", &Elev->currentFloor);
            if (Elev->currentFloor > MAX_FLOOR_COUNT)
            {
                hasDuplicate = 1;
                printf("⚠️ 电梯初始楼层不能超过 %d！\n", MAX_FLOOR_COUNT);
            }
        }

        if (!hasDuplicate)
        {
            printf("请输入外部楼层请求(1 2 3): ");
            for (int i = 0; i < Elev->externalCount; i++)
            {
                scanf("%d", &temp[i]);
                if (temp[i] == Elev->currentFloor)
                {
                    hasDuplicate = 1;
                    printf("⚠️ 楼层 %d 和当前楼层重复！\n", temp[i]);
                    break;
                } else if (temp[i] > MAX_FLOOR_COUNT)
                {
                    hasDuplicate = 1;
                    printf("⚠️ 楼层 %d 超出最大楼层数范围！\n", temp[i]);
                    break;
                }
            }
        }

        if (hasDuplicate)
        {
            printf("══════════════════════════════════════════\n");
            printf("❌ 请重新输入所有请求！\n");
            // 清空输入缓冲区
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

    } while (hasDuplicate);

    // 复制到正式数组
    for (int i = 0; i < Elev->externalCount; i++)
    {
        Elev->externalRequests[i] = temp[i];
    }

    // 对外部请求进行排序
    Sort_External_Requests(Elev->externalRequests, Elev->externalCount,
                           Elev->currentFloor, Elev);
}

void Output_ElevatorInfo(Elevator *Elev)
{
    printf("══════════════════════════════════════════\n");
    printf("            电梯初始信息            \n");
    printf("══════════════════════════════════════════\n");
    printf("  当前所在楼层：%d\n", Elev->currentFloor);
    printf("  目标楼层数量：%d\n", Elev->externalCount);
    printf("  目标楼层队列：");
    printf("%d", Elev->currentFloor);
    for (int i = 0; i < Elev->externalCount; i++)
    {
        printf(" → %d", Elev->externalRequests[i]);
    }
    printf("\n");
    printf("══════════════════════════════════════════\n");
}

void Input_Internal_Requests(Elevator *Elev)
{
    printf("══════════════════════════════════════════\n");
    printf("            输入乘客请求            \n");
    printf("══════════════════════════════════════════\n");
    for (int i = 0; i < Elev->externalCount; i++)
    {
        printf("  请输入 %d 楼的乘客目标楼层：", Elev->externalRequests[i]);
        scanf("%d", &Elev->internalRequests[i]);
        Elev->internalCount++;
    }
    printf("══════════════════════════════════════════\n");
}

void Output_finalTargets(Elevator *Elev)
{
    printf("══════════════════════════════════════════\n");
    printf("            电梯最终运行结果            \n");
    printf("══════════════════════════════════════════\n");
    printf("  最终运行路径：");
    int first = 1;
    printf("%d", Elev->currentFloor);
    for (int i = 0; i < MAX_TARGET_COUNT; i++)
    {
        if (Elev->finalTargets[i] != -1)
        {
            printf(" → %d", Elev->finalTargets[i]);
        }
    }
    printf("\n");
    printf("══════════════════════════════════════════\n");
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
    // // 存入最终目标楼层队列
    // Elev->finalTargetCount = count;
    // for (int i = 0; i < count; i++)
    // {
    //     Elev->finalTargets[i] = array[i];
    // }
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
    // 用来存储转向后的请求，会和blue数组有重复的元素
    int new_Blue[MAX_FLOOR_COUNT] = {0};
    int new_b_i = 0;

    // 处理默认上行方向
    if (Elev->direction == 0)
    {
        int turn = r_i - 1;
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
    // 处理默认下行方向
    else
    {
        int turn = b_i - 1;
        for (int i = 0; i < Elev->internalCount; i++)
        {
            // 同为下行方向
            if (Elev->direction == 1)
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
                    // 大于当前楼层的请求，都加入Red数组并降序排序（不是重复请求）
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
                }
            }
            // 反方向，则看Red数组是否重复
            else
            {
                // 大于当前楼层的请求，都加入Red数组并降序排序（不是重复请求）
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
                    // 大于当前楼层的请求，都加入一个新的数组并升序排序
                    new_Blue[new_b_i++] = Elev->internalRequests[i];
                    Sort_Blue_Bottom(new_Blue, new_b_i);
                    same_Blue = 0;
                }
            }

            // 到达翻转的位置
            if (i == turn)
            {
                Elev->direction = !Elev->direction;
            }
        }
        // 最后把blue，Red,new_blue数组合并到finalTargets数组中
        for (int j = 0; j < b_i; j++)
        {
            Elev->finalTargets[j] = blue[j];
        }
        for (int j = 0; j < r_i; j++)
        {
            Elev->finalTargets[b_i + j] = Red[j];
        }
        for (int j = 0; j < new_b_i; j++)
        {
            Elev->finalTargets[r_i + b_i + j] = new_Blue[j];
        }
    }
}

void Determine_Initial_Direction(Elevator *Elev)
{
    // 由于默认排序是上行方向进行的排序
    // Red的第一个元素就是距离最近的上行请求
    // blue的第一个元素就是距离最近的下行请求
    int *array = Elev->externalRequests;
    int current = Elev->currentFloor;

    // 先检查是否有上行或下行请求
    if (r_i == 0)
    {                        // 只有下行请求
        Elev->direction = 1; // 下行
        return;
    }

    if (b_i == 0)
    {                        // 只有上行请求
        Elev->direction = 0; // 上行
        return;
    }
    int minUp = Red[0] - current;    // 上行中最近的
    int minDown = current - blue[0]; // 下行中最近的

    // 距离近的方向优先
    if (minDown <= minUp)
    {
        Elev->direction = 1; // 下行
        // 把现在外部请求的顺序调换一下
        //  合并高于当前楼层的请求和低于当前楼层的请求
        for (int i = 0; i < b_i; i++)
        {
            array[i] = blue[i];
        }
        for (int i = 0; i < r_i; i++)
        {
            array[b_i + i] = Red[i];
        }
    }

    else
        Elev->direction = 0; // 上行
}