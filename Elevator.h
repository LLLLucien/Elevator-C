#ifndef ELEVATOR_H
#define ELEVATOR_H
#define MAX_FLOOR_COUNT 10
#define MAX_TARGET_COUNT 20
/* 利用externalRequests[10]存储外部请求
[]里就是该楼层，targetFloor就是该楼层是否有请求
有请求则为0，没有请求则为-1，具体请求楼层就用数字表示
例如三楼初始需要接人，该人要去5楼，则是externalRequests[3-1].targetFloor = 5
*/
typedef enum {
    EXTERNAL,   // 外部请求：需要上客
    INTERNAL    // 内部目标：需要下客
} TargetType;

typedef struct {
    int floor;              // 请求所在楼层
    TargetType type;        // 目标类型
    int targetFloor;        // 目标楼层（-1表示该楼没有请求, 0表示该楼有请求不过还没输入）
    int isProcessed;        // 是否已接人处理（0-未接，1-已接）
} ExternalRequest;

typedef struct {
    int currentFloor;       // 当前所在楼层
    int targetCount;        // 目标楼层数量
    ExternalRequest externalRequests[10]; // 外部请求队列
    int externalCount;      // 外部请求数量
    
    //最终目标楼层队列
    int finalTargetCount;
    //最终目标楼层队列，最多20个目标楼层
    int finalTargets[MAX_TARGET_COUNT];
} Elevator;

void Init_Elevator(Elevator *Elev);
void Input_Floor(Elevator *Elev);
void Output_ElevatorInfo(Elevator *Elev);
void Input_Passenger(Elevator *Elev);
void Output_finalTargets(Elevator *Elev);

#endif