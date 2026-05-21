#ifndef ELEVATOR_H
#define ELEVATOR_H

typedef enum {
    UP,     // 上行
    DOWN,   // 下行
    STOP,   // 停止
    FAULT   // 故障
} ElevatorState;

//外部请求结构体
typedef struct {
   
    int floor;              // 请求所在楼层（外部请求楼层）
    char direction;          // 请求方向（UP/DOWN，仅外部请求必填）
    //int isProcessed;        // 是否已接人处理（0-未接，1-已接）
} Request;

typedef struct {
  int floorNum;             // 总楼层数量
  int currentFloor;       // 当前所在楼层
    int maxPassenger;       // 最大载客数（固定为5）
    int currentPassenger;   // 当前载客数
    ElevatorState state;    // 当前运行状态
    Request Request_out[10];   // 外部请求队列
    Request Request_in[10]; // 内部请求队列
    int targetCount;        // 目标楼层数量
    int stopSequence[50];   // 最终停靠序列存储
    int stopCount;          // 停靠次数
} Elevator;

void InitElevator(Elevator *Elev);
void InputFloor(Elevator *Elev);
    void ElevatorRun(Elevator *Elev);
    void SortRequest(Elevator *Elev);
    void output_ElevatorInfo(Elevator *Elev);


#endif