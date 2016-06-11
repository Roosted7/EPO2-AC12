
extern int map[13][13], waypoints[4][3], route[100][4], routeLength;

void printMaze () {

    int i,j;

    printf("Printing the maze:\n");

    for (i = 0; i < 13; i++) {
        for (j = 0; j < 13; j++)
            printf("%d\t", map[i][j]);
        printf("\n");
    }
}

void printWaypoints() {

    int i, j;

    printf("Printing the Input Array:\n");

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++)
            printf("%d  ", waypoints[i][j]);
        printf("\n");
    }
}

void printRoute () {

    int i, j;

    printf("Printing the Route Array:\n");

    for (i = 0; i <= routeLength; i++) {
        for (j = 0; j < 4; j++)
            printf("%d  ", route[i][j]);
        printf("\n");
    }

}



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


int k_copyPoint(int punt[], int k) {
    int i;

    for (i = 0; i < 3; i++)
        route[routeLength][i] = punt[i];

    routeLength++;

    return k - 2;
}

void swapWaypoints (int swap1, int swap2) {

    int i, tempInput;

    for (i = 0; i < 3; i++) {
        tempInput = waypoints[swap1][i];
        waypoints[swap1][i] = waypoints[swap2][i];
        waypoints[swap2][i] = tempInput;
    }
    
}

void removeWaypoint (int waypointStep) {

    int i;

    for (i = 0; i < 3; i++)
        waypoints[waypointStep][i] = 99;
}

void setCurrentWaypoint (int curPos[]) {

    int i;

    for (i = 0; i < 3; i++)
        waypoints[0][i] = curPos[i];
}


