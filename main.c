#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Elevator.h"

int main()
{
    Elevator Elev;
    Init_Elevator(&Elev);
    Input_Floor(&Elev);
    Output_ElevatorInfo(&Elev);
    Input_Passenger(&Elev);
    Output_finalTargets(&Elev);
    return 0;
}