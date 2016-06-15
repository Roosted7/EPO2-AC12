
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
char challengeType;

void readInput () {

    int rawInput[4], i;

     printf("\n\nEnter first the starting point, and then 3 destinations:\n");

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

void readChallenge () {

    char inChar;

    printf("Please enter the challenge the robot has to complete ('A' or 'B'): ");
    scanf("%c", &inChar);

    if (inChar == 'a' || inChar == 'A') {
        challengeType = 'A';
    } else if (inChar == 'b' || inChar == 'B') {
        challengeType = 'B';
    } else if (inChar == 'c' || inChar == 'C') {
        printf("Not yet implemented!\n");
        readChallenge();
    } else {
        printf("Invalid input! Please try again:\n");
        readChallenge();
    }

}


int main()
{

    printf("\nEPO2 Maze router %s\n\n", PRODUCT_VERSION);
    printf("Opening serial port:\n");

    setupSerial();

    readChallenge();

    readInput();
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
