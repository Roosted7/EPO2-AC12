#define BOCHT_WEGING 7
#define WEGEN_WEGING 6


#define BUF_SIZE 50


extern int map[13][13], waypoints[4][3], route[100][4], routeLength;
extern unsigned char inBuf[BUF_SIZE];


void fillMap(int startc[], int eindc[]) {

    int i, j, k;

    for (i=0; i<13; i++)
    {
        for (j=0; j<13; j++)
        {
            if (map[i][j] > 0)
                map[i][j] = 0;
        }
    }

    map[eindc[0]][eindc[1]] = 1;

    /*Zolang de startpositie nog niet bereikt is*/
    for (k = 1; (map[startc[0]][startc[1]] == 0) && (k < 90); k++) {
        for (i=0; i<13; i++) {
            for (j=0; j<13; j++) {
                if(map[i][j] == k)
                {
                    if (i < 12 && map[i+1][j] == 0)
                            map[i+1][j] = k + 1;
                    if (i > 0 && map[i-1][j] == 0)
                            map[i-1][j] = k + 1;
                    if (j < 12 && map[i][j+1] == 0)
                            map[i][j+1] = k + 1;
                    if (j > 0 && map[i][j-1] == 0)
                            map[i][j-1] = k + 1;
                }
            }
        }
    }

    if (k == 90)
        exit(90);
}


int segmentLength (int startc[], int eindc[]) {

    int k, rechten = 0, bochten = 0, punt[3];

    if ( (startc[0] == 99 && startc[1] == 99) || (eindc[0] == 99 && eindc[1] == 99))
        return 0;

    fillMap(startc, eindc);

    for (k = 0; k < 3; k++)
        punt[k] = startc[k];

    k = map[startc[0]][startc[1]];

    while(k > 2)
    {
        if ((punt[0] < 11) && (map[punt[0]+2][punt[1]] == k-2) && (map[punt[0]+1][punt[1]] == k-1) && (punt[2] == 1)) {
            rechten++;
            k -= 2;
            punt[0] += 2;
        }
        else if ((punt[0] > 1) && (map[punt[0]-2][punt[1]] == k-2) && (map[punt[0]-1][punt[1]] == k-1) && (punt[2] == 2)) {
            rechten++;
            k -= 2;
            punt[0] -= 2;
        }
        else if ((punt[1] < 11) && (map[punt[0]][punt[1]+2] == k-2) && (map[punt[0]][punt[1]+1] == k-1) && (punt[2] == 3)) {
            rechten++;
            k -= 2;
            punt[1] += 2;
        }
        else if ((punt[1] > 1) && (map[punt[0]][punt[1]-2] == k-2) && (map[punt[0]][punt[1]-1] == k-1) && (punt[2] == 4)) {
            rechten++;
            k -= 2;
            punt[1] -= 2;
        }
        else if ((punt[0] < 11) && (map[punt[0]+2][punt[1]] == k-2) && (map[punt[0]+1][punt[1]] == k-1)) {
            bochten++;
            k -= 2;
            punt[2] = 1;
            punt[0] += 2;
        }
        else if ((punt[0] > 1) && (map[punt[0]-2][punt[1]] == k-2) && (map[punt[0]-1][punt[1]] == k-1)) {
            bochten++;
            k -= 2;
            punt[2] = 2;
            punt[0] -= 2;
        }
        else if ((punt[1] < 11) && (map[punt[0]][punt[1]+2] == k-2) && (map[punt[0]][punt[1]+1] == k-1)) {
            bochten++;
            k -= 2;
            punt[2] = 3;
            punt[1] += 2;
        }
        else if ((punt[1] > 1) && (map[punt[0]][punt[1]-2] == k-2) && (map[punt[0]][punt[1]-1] == k-1)) {
            bochten++;
            k -= 2;
            punt[2] = 4;
            punt[1] = punt[1] - 2;
        }
    }


    return (BOCHT_WEGING * bochten + WEGEN_WEGING * rechten);

}

void fillRouteArray () {

    int i, j;

    for (i = 0; i < 100; i++) {
        for (j = 0; j < 4; j++)
            route[i][j] = 0;
    }

    routeLength = 2;

    for (i = 0; i < 3; i++) {
        route[0][i] = waypoints[0][i];
        route[1][i] = waypoints[1][i];
    }

    for (i = 0; i < 3; i++) {
        if (waypoints[i+1][0] == 99 && waypoints[i+1][1] == 99) {
            routeLength = saveRouteSteps(waypoints[i], waypoints[i+2]);
            i++;
        } else {
            routeLength = saveRouteSteps(waypoints[i], waypoints[i+1]);
        }
    }

    for (i = 0; i < 4; i++) {
        route[routeLength][i] = -1;
    }

}


int saveRouteSteps (int startC[], int endC[]) {

    int k, i, punt[3];

    fillMap(startC, endC);

    k = map[startC[0]][startC[1]];

    for (i = 0; i < 3; i++)
        punt[i] = startC[i];

    while(k > 2)
    {

        if ((punt[0] < 11) && (map[punt[0]+2][punt[1]] == k-2) && (map[punt[0]+1][punt[1]] == k-1) && (punt[2] == 1)) {
            punt[0] = punt[0] + 2;
            route[routeLength - 1][3] = 1;
            k = k_copyPoint(punt, k);
        }
        else if ((punt[0] > 1) && (map[punt[0]-2][punt[1]] == k-2) && (map[punt[0]-1][punt[1]] == k-1) && (punt[2] == 2)) {
            punt[0] = punt[0] - 2;
            route[routeLength - 1][3] = 1;
            k = k_copyPoint(punt, k);
        }
        else if ((punt[1] < 11) && (map[punt[0]][punt[1]+2] == k-2) && (map[punt[0]][punt[1]+1] == k-1) && (punt[2] == 3)) {
            punt[1] = punt[1] + 2;
            route[routeLength - 1][3] = 1;
            k = k_copyPoint(punt, k);
        }
        else if ((punt[1] > 1) && (map[punt[0]][punt[1]-2] == k-2) && (map[punt[0]][punt[1]-1] == k-1) && (punt[2] == 4)) {
            punt[1] = punt[1] - 2;
            route[routeLength - 1][3] = 1;
            k = k_copyPoint(punt, k);
        }
        else if ((punt[0] < 11) && (map[punt[0]+2][punt[1]] == k-2) && (map[punt[0]+1][punt[1]] == k-1)) {
            
            if (punt[2] == 4)
                route[routeLength - 1][3] = 2;
            if (punt[2] == 3)
                route[routeLength - 1][3] = 3;

            punt[2] = 1;
            punt[0] = punt[0] + 2;

            k = k_copyPoint(punt, k);
        }
        else if ((punt[0] > 1) && (map[punt[0]-2][punt[1]] == k-2) && (map[punt[0]-1][punt[1]] == k-1)) {

            if (punt[2] == 3)
                route[routeLength - 1][3] = 2;
            if (punt[2] == 4)
                route[routeLength - 1][3] = 3;

            punt[2] = 2;
            punt[0] = punt[0] - 2;
            k = k_copyPoint(punt, k);
        }
        else if ((punt[1] < 11) && (map[punt[0]][punt[1]+2] == k-2) && (map[punt[0]][punt[1]+1] == k-1)) {

            if (punt[2] == 1)
                route[routeLength - 1][3] = 2;
            if (punt[2] == 2)
                route[routeLength - 1][3] = 3;

            punt[2] = 3;
            punt[1] = punt[1] + 2;
            k = k_copyPoint(punt, k);
        }
        else if ((punt[1] > 1) && (map[punt[0]][punt[1]-2] == k-2) && (map[punt[0]][punt[1]-1] == k-1)) {

            if (punt[2] == 2)
                route[routeLength - 1][3] = 2;
            if (punt[2] == 1)
                route[routeLength - 1][3] = 3;

            punt[2] = 4;
            punt[1] = punt[1] - 2;
            k = k_copyPoint(punt, k);
        } else {

        }

    }

    route[routeLength - 2][3] += 10;

    printf("K: %d, routeL: %d\n", k, routeLength);

    return routeLength;

}


void sortWaypoints () {

    int i, kortste, segmLength[6], numWaypoints = 3;

    /*Alle routes tussen de stations berekenen en opslaan in de array perm*/
    segmLength[0] = segmentLength(waypoints[0],waypoints[1]);
    segmLength[1] = segmentLength(waypoints[0],waypoints[2]);
    segmLength[2] = segmentLength(waypoints[0],waypoints[3]);
    segmLength[3] = segmentLength(waypoints[1],waypoints[2]);
    segmLength[4] = segmentLength(waypoints[1],waypoints[3]);
    segmLength[5] = segmentLength(waypoints[2],waypoints[3]);

    /*De kortste route bepalen*/
    kortste = segmLength[0] + segmLength[3] + segmLength[5];
    if(segmLength[0] + segmLength[4] + segmLength[5] < kortste)
        kortste = segmLength[0] + segmLength[4] + segmLength[5];
    if(segmLength[1] + segmLength[3] + segmLength[4] < kortste)
        kortste = segmLength[1] + segmLength[3] + segmLength[4];
    if(segmLength[1] + segmLength[5] + segmLength[4] < kortste)
        kortste = segmLength[1] + segmLength[5] + segmLength[4];
    if(segmLength[2] + segmLength[4] + segmLength[3] < kortste)
        kortste = segmLength[2] + segmLength[4] + segmLength[3];
    if(segmLength[2] + segmLength[5] + segmLength[3] < kortste)
        kortste = segmLength[2] + segmLength[5] + segmLength[3];

    if (kortste == (segmLength[0] + segmLength[4] + segmLength[5])) {
        swapWaypoints(2, 3);
    } else if (kortste == (segmLength[1] + segmLength[3] + segmLength[4])) {
        swapWaypoints(1, 2);
    } else if (kortste == (segmLength[1] + segmLength[5] + segmLength[4])) {
        swapWaypoints(1, 2);
        swapWaypoints(2, 3);
    } else if (kortste == (segmLength[2] + segmLength[4] + segmLength[3])) {
        swapWaypoints(1, 2);
        swapWaypoints(1, 3);
    } else if (kortste == (segmLength[2] + segmLength[5] + segmLength[3])) {
        swapWaypoints(1, 3);
    }


}
