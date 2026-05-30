#ifndef ELEVATOR_H
#define ELEVATOR_H
#define MAX_FLOOR_COUNT 10
#define MAX_TARGET_COUNT 20
/* 利用externalRequests[10]存储外部请求
[]里就是该楼层，targetFloor就是该楼层是否有请求
有请求则为0，没有请求则为-1，具体请求楼层就用数字表示
例如三楼初始需要接人，该人要去5楼，则是externalRequests[3-1].targetFloor = 5
*/
// typedef enum {
//     EXTERNAL,   // 外部请求：需要上客
//     INTERNAL    // 内部目标：需要下客
// } TargetType;

// typedef struct {
//     int floor;              // 请求所在楼层
//     TargetType type;        // 目标类型
//     int targetFloor;        // 目标楼层（-1表示该楼没有请求, 0表示该楼有请求不过还没输入）
//     int isProcessed;        // 是否已接人处理（0-未接，1-已接）
// } ExternalRequest;
// typedef struct Stack {
//     int data[20];
//     int top;
// } Stack;

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