#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Elevator.h"

int main()
{
    Elevator Elev;
    Init_Elevator(&Elev);
    Input_External_Requests(&Elev);
    Output_ElevatorInfo(&Elev);
    Input_Internal_Requests(&Elev);
    Look_Sort(&Elev);
    Output_finalTargets(&Elev);
    // Input_Passenger(&Elev);
    // Output_finalTargets(&Elev);
    return 0;
}