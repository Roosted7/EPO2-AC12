
#include <stdio.h>
#include <stdlib.h>

#include "rs232.c"


#include "support.c"
#include "route.c"
#include "communication.c"

#define PRODUCT_VERSION "1.5"


int map[13][13] =
{
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1},
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1},
    { -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1},
    { -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1},
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1},
    { -1, -1, -1, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1}
};

int waypoints[4][3], route[100][4], routeLength, robotDone = 0, numWaypoints;

void readInput () {

    int rawInput[4], i;

    for(i = 0; i < 4; i++) {

        scanf("%d", &rawInput[i]);

        if (rawInput[i] > -1 && rawInput[i] < 13) {
            waypoints[i][0] = yPos(rawInput[i]);
            waypoints[i][1] = xPos(rawInput[i]);
            waypoints[i][2] = richtingStation(rawInput[i]);
        } else {
            printf("Please check your input!\nTry again: ");
            i--;
        }
    }
}

void overWriteInput () {

    scanf("%d", &waypoints[0][0]); 
    scanf("%d", &waypoints[0][1]);   
    scanf("%d", &waypoints[0][2]);   
  
}


int main()
{

    printf("\nEPO2 Maze router %s\n\n", PRODUCT_VERSION);
    printf("Opening serial port:\n");

    setupSerial();

    printf("\n\nEnter first the starting point, and then 3 destinations:\n");

    readInput();
    /*overWriteInput();*/
    printWaypoints();

    while (!robotDone) {

        sortWaypoints();
        printWaypoints();

        fillRouteArray();
        printRoute();

        driveRoute();
    }

    printf("\nEnd of route! Program exiting :( Bye!\n\n");

    stopSerial();
    return 0;
}
