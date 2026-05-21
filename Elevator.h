#ifndef ELEVATOR_H
#define ELEVATOR_H

// 电梯运行状态枚举（已删除冗余FAULT）
typedef enum {
    UP,     // 上行
    DOWN,   // 下行
    STOP    // 停止
} ElevatorState;

// 目标类型枚举（区分上客/下客，解决上下客判断问题）
typedef enum {
    EXTERNAL,   // 外部请求：需要上客
    INTERNAL    // 内部目标：需要下客
} TargetType;

// 外部请求结构体（关联对应的内部目标，解决脱节问题）
typedef struct {
    int floor;              // 请求所在楼层（外部请求楼层）
    ElevatorState direction;// 请求方向（与电梯状态枚举统一，避免类型错误）
    int targetFloors[5];    // 该请求所有乘客的目标楼层（最大载客5人）
    int targetCount;        // 目标楼层数量（等于乘客数量）
    int passengerCount;     // 该请求的乘客数量（默认1人）
    int isProcessed;        // 是否已接人处理（0-未接，1-已接）
} ExternalRequest;

// 调度目标结构体（核心调度队列，解决LOOK算法排序问题）
typedef struct {
    int floor;              // 目标楼层
    ElevatorState direction;// 停靠方向（用于生成"3(上)"格式的目标队列）
    TargetType type;        // 目标类型（区分上客/下客）
} Target;

// 电梯本体结构体（删除冗余，补充核心调度字段）
typedef struct {
    int currentFloor;       // 当前所在楼层（固定10层，无需floorNum字段）
    int maxPassenger;       // 最大载客数（固定为5）
    int currentPassenger;   // 当前载客数
    ElevatorState state;    // 当前运行状态
    
    ExternalRequest externalRequests[10]; // 外部请求队列（预输入所有请求）
    int externalCount;      // 外部请求数量
    
    Target targetQueue[20]; // 核心调度目标队列（最多20个目标，足够10层场景）
    int targetCount;        // 目标队列长度
    
    int stopSequence[50];   // 最终停靠序列存储
} Elevator;

void InitElevator(Elevator *Elev);
void InputFloor(Elevator *Elev);
    void ElevatorRun(Elevator *Elev);
    void SortRequest(Elevator *Elev);
    void output_ElevatorInfo(Elevator *Elev);


#endif