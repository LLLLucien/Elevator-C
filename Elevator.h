#ifndef ELEVATOR_H
#define ELEVATOR_H
#define MAX_FLOOR_COUNT 10
#define MAX_TARGET_COUNT 20


typedef struct {
    int currentFloor;       // 当前所在楼层
  //  int targetCount;        // 目标楼层数量
    int externalRequests[10]; // 外部请求队列
    int internalRequests[10]; // 内部目标请求队列
    int externalCount;      // 外部请求数量
    int internalCount;      // 内部目标请求数量
    // 方向的标志位，0表示向上，1表示向下
    int direction;
    
    //最终目标楼层队列
    int finalTargetCount;
    //最终目标楼层队列，最多20个目标楼层
    int finalTargets[MAX_TARGET_COUNT];
} Elevator;

void Init_Elevator(Elevator *Elev);
void Output_ElevatorInfo(Elevator *Elev);
void Input_External_Requests(Elevator *Elev);
void Input_Internal_Requests(Elevator *Elev);
void Output_finalTargets(Elevator *Elev);
void Sort_Red_Top(int *array, int count);
void Sort_Blue_Bottom(int *array, int count);
void Sort_External_Requests(int *array, int count, int currentFloor,
                            Elevator *Elev);
void Look_Sort(Elevator *Elev);
void Determine_Initial_Direction(Elevator *Elev);

#endif