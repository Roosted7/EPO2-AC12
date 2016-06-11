
#include <stdio.h>
#include <stdlib.h>

#include "rs232.c"


#include "support.c"
#include "route.c"
#include "communication.c"

#define PRODUCT_VERSION "1.3"


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

int waypoints[4][3], route[100][4], routeLength;
unsigned char inBuf[BUF_SIZE];


void readInput () {

    int rawInput[4], i;

    for(i = 0; i < 4; i++) {

        scanf("%d", &rawInput[i]);

        if (rawInput[i] > -1 && rawInput[i] < 13) {
            waypoints[i][0] = yPos(rawInput[i]);
            waypoints[i][1] = xPos(rawInput[i]);
            waypoints[i][2] = richtingStationHalverwege(rawInput[i]);
            if (i == 0)
                waypoints[i][2] = richtingStationBegin(rawInput[i]);
        } else {
            printf("Please check your input!\nTry again: ");
            i--;
        }
    }
}

int main()
{

    printf("\nEPO2 Maze router %s\n\n", PRODUCT_VERSION);
    printf("Opening serial port:\n");

    setupSerial();

    printf("\n\nEnter first the starting point, and then 3 destinations:\n");

    readInput();
    printWaypoints();

    sortWaypoints();
    printWaypoints();

    fillRouteArray();
    printRoute();

    driveRoute();

    return 0;
}