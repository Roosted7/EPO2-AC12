
extern int map[13][13], waypoints[4][3], route[100][4], routeLength;

void printMaze () {                     /* This function prints the contents of the Maze */

    int i,j;

    printf("Printing the maze:\n");

    for (i = 0; i < 13; i++) {
        for (j = 0; j < 13; j++)
            printf("%d\t", map[i][j]);
        printf("\n");
    }
}

void printWaypoints() {                 /* This function prints out the waypoints array */

    int i, j;

    printf("Printing the Input Array:\n");

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++)
            printf("%d  ", waypoints[i][j]);
        printf("\n");
    }
}

void printRoute () {                    /* This function prints out the route array */

    int i, j;

    printf("Printing the Route Array:\n");

    for (i = 0; i <= routeLength; i++) {
        for (j = 0; j < 4; j++)
            printf("%d  ", route[i][j]);
        printf("\n");
    }

}


/* These next two functions determine the coordinates of a station */
int xPos (int punt) {

    if (punt == 10 || punt == 11 || punt == 12)
        return 0;
    if (punt == 1 || punt == 9)
        return 4;
    if (punt == 2 || punt == 8)
        return 6;
    if (punt == 3 || punt == 7)
        return 8;
    if (punt == 4 || punt == 5 || punt == 6)
        return 12;
    return 99;
}

int yPos (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 12;
    if (punt == 4 || punt == 12)    
        return 8;
    if (punt == 5 || punt == 11)
        return 6;
    if (punt == 6 || punt == 10)
        return 4;
    if (punt == 7 || punt == 8 || punt == 9)
        return 0;
    return 99;
}

/* This function determines the direction the robot will face when it just arrived at a station */
int richtingStation (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 1;
    if (punt == 4 || punt == 5 || punt == 6)
        return 3;
    if (punt == 7 || punt == 8 || punt == 9)
        return 2;
    if (punt == 10 || punt == 11 || punt == 12)
        return 4;
    return 99;
}

/* This function copy's the punt array to the route array and returns a new value for K */
int k_copyPoint(int punt[], int k) {
    int i;

    for (i = 0; i < 3; i++)
        route[routeLength][i] = punt[i];

    routeLength++;

    return k - 2;
}

/* This function swaps two waypoints without using (visible) pointers */
void swapWaypoints (int swap1, int swap2) {

    int i, tempInput;

    for (i = 0; i < 3; i++) {
        tempInput = waypoints[swap1][i];
        waypoints[swap1][i] = waypoints[swap2][i];
        waypoints[swap2][i] = tempInput;
    }
    
}

/* This functions sets a waypoint to all 99's, and removing it */
void removeWaypoint (int waypointStep) {

    int i;

    for (i = 0; i < 3; i++)
        waypoints[waypointStep][i] = 99;
}

/* This function sets the current position and direction in the waypoint array */
void setCurrentWaypoint (int curPos[]) {

    int i;

    for (i = 0; i < 3; i++)
        waypoints[0][i] = curPos[i];

}

/* This funcion marks a position as a mine */
void markMine(int minePos[]) {

    map[minePos[0]][minePos[1]] = -1;

}

/* This function inverts the direction of a waypoint (usefull when the robot hit a mine) */
void flipNextWaypointDir (int curPos[]) {

    if (curPos[2] % 2) {
        waypoints[0][2] = curPos[2] + 1;
    } else {
        waypoints[0][2] = curPos[2] - 1;
    }

}