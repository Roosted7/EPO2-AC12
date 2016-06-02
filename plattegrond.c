

/* ini startPunt en eindPunt hiero  */

void leegPlattegrond () {
    plattegrond[13][13] ={
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
}

void setBegin(int punt) {

    startPunt[0] = xPos(punt);
    startPunt[1] = yPos(punt);

}


void setEind (int punt) {

    plattegrond[xPos(punt)][yPos(punt)] = 1;

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
    if (punt == 7 || punt == 8 || punt 9)
        return 0;
    return 99;
}

int richtingStationBegin (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 0;
    if (punt == 4 || punt == 5 || punt == 6)
        return 1;
    if (punt == 7 || punt == 8 || punt == 9)
        return 2;
    if (punt == 10 || punt == 11 || punt == 12)
        return 3;
    return 99;
}

int richtingStationHalverwege (int punt) {

    if (punt == 1 || punt == 2 || punt == 3)
        return 2;
    if (punt == 4 || punt == 5 || punt == 6)
        return 4;
    if (punt == 7 || punt == 8 || punt == 9)
        return 0;
    if (punt == 10 || punt == 11 || punt == 12)
        return 1;
    return 99;
}



int vulPlattegrond () {

    int i, j, stap;

     /* Maak alles boven 0, een 0   */
    for (i=0; i<13; i++)
    {
        for (j=0; j<13; j++)
        {
            if (plattegrond[i][j] > 0)
                plattegrond[i][j] = 0;
        }
    }


    /*  Vul de kaart met getallen, eind tot begin   */
    for (stap = 1, (plattegrond[startPunt[0]][startPunt[1]] == 0) && stap < 90, stap++) {

        for (i = 0; i < 13; i++)
        {
            for (j = 0; j < 13; j++)
            {
                if(plattegrond[i][j] == stap)
                {
                    /* Verhoog omliggende vakjes, indien ze 0 zijn */

                        if (i < 12 && plattegrond[i+1][j] == 0)
                            plattegrond[i+1][j] = stap + 1;

                        if (i > 0 && plattegrond[i-1][j] == 0)
                            plattegrond[i-1][j] = stap + 1;

                        if (j < 12 && plattegrond[i][j+1] == 0)
                            plattegrond[i][j+1] = stap + 1;

                        if (j > 0 && plattegrond[i][j-1] == 0)
                            plattegrond[i][j-1] = stap + 1;

                }
            }
        }
    }

    /*  return aantal stapjes   */
    return stap + 1;
}


float routeLength (int startPunt, int eindPunt) {

    int i, j, stap;
    int huidigePos[3]; /* x, y, richting */
    int bochten = 0, rechtPad = 0;


    huidigePos[0] = xPos(startPunt);
    huidigePos[1] = yPos(startPunt);
    huidigePos[2] = richtingPunt(startPunt);

    stap = plattegrond[xPos(startPunt)][yPos(startPunt)];


    while(stap > 3)
        {
            /*Voorkeursburen*/
            if ((huidigePos[0] < 11) && (plattegrond[huidigePos[0]+2][huidigePos[1]] == stap-2) && (plattegrond[huidigePos[0]+1][huidigePos[1]] == stap-1) && (vorigerichting == 3))
            {
                /*  TODO send add straight line command */
                rechtPad++;
                stap -= 2;
                huidigePos[0] += 2;
            }
            else if ((huidigePos[0] > 1) && (plattegrond[huidigePos[0]-2][huidigePos[1]] == stap-2) && (plattegrond[huidigePos[0]-1][huidigePos[1]] == stap-1) && (vorigerichting == 1))
            {
                /*  TODO send add straight line command */
                rechtPad++;
                stap -= 2;
                huidigePos[0] -= 2;
            }
            else if ((huidigePos[1] < 11) && (plattegrond[huidigePos[0]][huidigePos[1]+2] == stap-2) && (plattegrond[huidigePos[0]][huidigePos[1]+1] == stap-1) && (vorigerichting == 2))
            {
                /*  TODO send add straight line command */
                rechtPad++;
                stap -= 2;
                huidigePos[1] += 2;
            }
            else if ((huidigePos[1] > 1) && (plattegrond[huidigePos[0]][huidigePos[1]-2] == stap-2) && (plattegrond[huidigePos[0]][huidigePos[1]-1] == stap-1) && (vorigerichting == 0))
            {
                /*  TODO send add straight line command */
                rechtPad++;
                stap -= 2;
                huidigePos[1] -= 2;
            }
            /* VANAF HIER NOG RICHTINGEN DOEN!  */
            else if ((huidigePos[0] < 11) && (plattegrond[huidigePos[0]+2][huidigePos[1]] == stap-2) && (plattegrond[huidigePos[0]+1][huidigePos[1]] == stap-1))
            {

                bochten++;
                rechtPad++;
                stap -= 2;

                vorigerichting = 1;
                huidigePos[0] += 2;
            }
            else if ((huidigePos[0] > 1) && (plattegrond[huidigePos[ 0]-2][huidigePos[ 1]] == stap-2) && (plattegrond[huidigePos[ 0]-1][huidigePos[ 1]] == stap-1))
            {
                bochten++;
                rechtPad++;
                stap -= 2;
                vorigerichting = 2;
                huidigePos[ 0] -= 2;
            }
            else if ((huidigePos[ 1] < 11) && (plattegrond[huidigePos[ 0]][huidigePos[ 1]+2] == stap-2) && (plattegrond[huidigePos[ 0]][huidigePos[ 1]+1] == stap-1))
            {
                bochten++;
                rechtPad++;
                stap -= 2;
                vorigerichting = 3;
                huidigePos[1] += 2;
            }
            else if ((huidigePos[ 1] > 1) && (plattegrond[huidigePos[ 0]][huidigePos[ 1]-2] == stap-2) && (plattegrond[huidigePos[ 0]][huidigePos[ 1]-1] == stap-1))
            {
                bochten++;
                rechtPad++;
                stap -= 2;

                vorigerichting = 4;
                huidigePos[1] -= 2;
            }
        }


    /*Lengte terugsturen*/
    return (BOCHTWEGING*bochten + WEGENWEGING*rechten);


}

