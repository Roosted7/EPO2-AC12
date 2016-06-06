#define BOCHTWEGING 2
#define WEGENWEGING 1


extern int plattegrond[13][13];

void printMaze () {

    int i,j;

    printf("Printing the maze:\n");

    for (i = 0; i < 13; i++) {
        for (j = 0; j < 13; j++)
            printf("%d\t", plattegrond[i][j]);
        printf("\n");
    }

}

int xPos (int punt) {

    if (punt == 0 || punt == 10 || punt == 11 || punt == 12)
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

    if (punt == 0 || punt == 1 || punt == 2 || punt == 3)
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

int richtingStationBegin (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 2;
    if (punt == 4 || punt == 5 || punt == 6)
        return 4;
    if (punt == 7 || punt == 8 || punt == 9)
        return 1;
    if (punt == 10 || punt == 11 || punt == 12)
        return 3;
    return 99;
}

int richtingStationHalverwege (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 1;
    if (punt == 4 || punt == 5 || punt == 6)
        return 4;
    if (punt == 7 || punt == 8 || punt == 9)
        return 2;
    if (punt == 10 || punt == 11 || punt == 12)
        return 4;
    return 99;
}

void nulPlattegrond () {
    int i, j;
    
    for (i=0; i<13; i++)
    {
        for (j=0; j<13; j++)
        {
            if (plattegrond[i][j] > 0)
            {
                plattegrond[i][j] = 0;
            }
        }
    }
}

void vulPlattegrond(int startc[], int eindc[]) {

    int i, j, k;

    nulPlattegrond();

    /*De bestemming krijgt waarde i, ofwel 1*/
    plattegrond[eindc[0]][eindc[1]] = 1;

    /*Zolang de startpositie nog niet bereikt is*/
    for (k = 1; (plattegrond[startc[0]][startc[1]] == 0) && (k < 90); k++) {
        for (i=0; i<13; i++) {
            for (j=0; j<13; j++) {
                if(plattegrond[i][j] == k)
                {
                    if (i < 12 && plattegrond[i+1][j] == 0)
                            plattegrond[i+1][j] = k + 1;

                    if (i > 0 && plattegrond[i-1][j] == 0)
                            plattegrond[i-1][j] = k + 1;

                    if (j < 12 && plattegrond[i][j+1] == 0)
                            plattegrond[i][j+1] = k + 1;

                    if (j > 0 && plattegrond[i][j-1] == 0)
                            plattegrond[i][j-1] = k + 1;
                }
            }
        }
    }
}

int routeLength (int startc[], int eindc[]) {

    int k, rechten = 0, bochten = 0, punt[2], vorigerichting;

    vorigerichting = startc[0][2];

    vulPlattegrond(startc, eindc);

    k = plattegrond[startc[0]][startc[1]];


    /*Spring naar het eindpunt met de punt*/
    punt[0] = startc[0];
    punt[1] = startc[1];
    while(k > 3)
    {
        if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 1)) {
            rechten++;
            k = k - 2;
            punt[0] = punt[0] + 2;
        }
        else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 2)) {
            rechten++;
            k = k - 2;
            punt[0] = punt[0] - 2;
        }
        else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 3)) {
            rechten++;
            k = k - 2;
            punt[1] = punt[1] + 2;
        }
        else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 4)) {
            rechten++;
            k = k - 2;
            punt[1] = punt[1] - 2;
        }
        else if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1)) {
            bochten++;
            rechten++;
            k = k - 2;
            vorigerichting = 1;
            punt[0] = punt[0] + 2;
        }
        else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1)) {
            bochten++;
            rechten++;
            k = k - 2;
            vorigerichting = 2;
            punt[0] = punt[0] - 2;
        }
        else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1)) {
            bochten++;
            rechten++;
            k = k - 2;
            vorigerichting = 3;
            punt[1] = punt[1] + 2;
        }
        else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1)) {
            bochten++;
            rechten++;
            k = k - 2;
            vorigerichting = 4;
            punt[1] = punt[1] - 2;
        }
    }
    return (BOCHTWEGING*bochten + WEGENWEGING*rechten);

}


int bepaalVolgorde (int input[4][3]) {

    int i, kortste, perm[6], volgorde = 0; 

    /*Alle routes tussen de stations berekenen en opslaan in de array perm*/
    perm[0] = routeLength(input[0],input[1]);
    perm[1] = routeLength(input[0],input[2]);
    perm[2] = routeLength(input[0],input[3]);
    perm[3] = routeLength(input[1],input[2]);
    perm[4] = routeLength(input[1],input[3]);
    perm[5] = routeLength(input[2],input[3]);

    /*De korste route bepalen*/
    kortste = perm[0] + perm[3] + perm[5];
    if(perm[0] + perm[4] + perm[5] < kortste)
    {
        kortste = perm[0] + perm[4] + perm[5];
        volgorde = 1;
    }
    if(perm[1] + perm[3] + perm[4] < kortste)
    {
        kortste = perm[1] + perm[3] + perm[4];
        volgorde = 2;
    }
    if(perm[1] + perm[5] + perm[4] < kortste)
    {
        kortste = perm[1] + perm[5] + perm[4];
        volgorde = 3;
    }
    if(perm[2] + perm[4] + perm[3] < kortste)
    {
        kortste = perm[2] + perm[4] + perm[3];
        volgorde = 4;
    }
    if(perm[2] + perm[5] + perm[3] < kortste)
    {
        kortste = perm[2] + perm[5] + perm[3];
        volgorde = 5;
    }

    return volgorde;
}

