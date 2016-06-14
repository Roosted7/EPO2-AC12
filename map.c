
#define STRAIGHT_FACTOR 6
#define CORNER_FACTOR 7
#define MINE_FACTOR 6
#define REVERSE_FACTOR 100

#define NUM_MINES 13

extern int map[13][13][2], minesLeftOnField, unknownPositions;

void emptyMap () {

    int i, j;

    for (i=0; i<13; i++)
    {
        for (j=0; j<13; j++)
        {
            if (map[i][j][0] > 0) {
                map[i][j][0] = 0;
                map[i][j][1] = 0;
            }
        }
    }
}

void makeMap () {

    int i, j;

    /* Make all -1 */
    for (i = 0; i < 13; i++) {
        for (j = 0; j < 13; j++) {
            map[i][j][0] = -1;
            map[i][j][1] = 0;
        }
    }

    /* Make big lines */
    for (i = 4; i < 9; i+= 2) {
        for (j = 0; j < 13; j++) {
            map[i][j][0] = 0;
            map[j][i][0] = 0;
        }
    }

    /* Draw 'box' outer lines */
    for (i = 2; i < 11; i += 8) {
        for (j = 2; j < 11; j++) {
            map[i][j][0] = 0;
            map[j][i][0] = 0;
        }
    }

    minesLeftOnField = NUM_MINES;
    unknownPositions = 40;


}


void fillMap(int startC[], int endC[]) {

    int i, j, fillingActive;

    emptyMap();

    map[startC[0]][startC[1]][0] = 1;
    map[startC[0]][startC[1]][1] = startC[2];

    fillingActive = 1;
    while (fillingActive) {

        fillingActive = 0;

        for (i=0; i<13; i++) {
            for (j=0; j<13; j++) {

                if(map[i][j][0] != 0) {

                    if (map[i][j][1] == 1) {

                        if ( i > 12 && map[i+1][j][])

                    } else if (map[i][j][1] == 2) {

                    } else if (map[i][j][1] == 3) {

                    } else if (map[i][j][1] == 4) {

                    } else {
                        printf("Wierd number detected!\n");
                    }



                    if (i < 12 && map[i+1][j][0] == 0)
                            map[i+1][j][0] = k + 1;
                    if (i > 0 && map[i-1][j][0] == 0)
                            map[i-1][j][0] = k + 1;
                    if (j < 12 && map[i][j+1][0] == 0)
                            map[i][j+1][0] = k + 1;
                    if (j > 0 && map[i][j-1][0] == 0)
                            map[i][j-1][0] = k + 1;


                }




            }
        }



    }

    if (k == 1000) {
        printf("\nOH NO!\nI was asked to fill from: (%d, %d) to (%d, %d)\n", startc[0], startc[1], eindc[0], eindc[1]);
        printWaypoints();
        printMaze();
        exit(90);
    }
}

