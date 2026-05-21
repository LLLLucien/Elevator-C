#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Elevator.h"

int main()
{
    Elevator Elev;
    InitElevator(&Elev);
    InputFloor(&Elev);
    ElevatorRun(&Elev);
    return 0;
}