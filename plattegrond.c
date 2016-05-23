

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

int richtingPunt (int punt) {

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






int loop(int startpunt, int eindpunt)
{
    int i = 0, j = 0, k = 0; /*Willekeurige integers om te doorlopen in een lus*/
    int startc[2]; /*Array met startpuntcoordinaten*/
    int eindc[2]; /*Array met eindpuntcoordinaten*/
    int punt[2]; /*Array met de coordinaten van het pad om terug te komen*/
    int vorigerichting = 0; /*Om zo min mogelijk bochten te maken in de route*/
    int bochten = 0, rechten = 0;

    /*De bestemming krijgt waarde i, ofwel 1*/
    plattegrond[eindc[0]][eindc[1]] = k;

    

    if (k < 90)
    {
        /*Spring naar het eindpunt met de punt*/
        punt[0] = startc[0];
        punt[1] = startc[1];
        while(k > 3)
        {
            /*Voorkeursburen*/
            /*Voorkeursbuur 1*/
            if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1) && (vorigerichting == 1))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[0] = punt[0] + 2;
            }
            /*Voorkeursbuur 2*/
            else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1) && (vorigerichting == 2))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[0] = punt[0] - 2;
            }
            /*Voorkeursbuur 3*/
            else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1) && (vorigerichting == 3))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[1] = punt[1] + 2;
            }
            /*Voorkeursbuur 4*/
            else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1) && (vorigerichting == 4))
            {
                rechten++;
                k = k - 2;
                /*Punt doorschuiven*/
                punt[1] = punt[1] - 2;
            }

            /*Standaardlijstje buren*/
            /*Buur 1*/
            else if ((punt[0] < 11) && (plattegrond[punt[0]+2][punt[1]] == k-2) && (plattegrond[punt[0]+1][punt[1]] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 1;
                /*Punt doorschuiven*/
                punt[0] = punt[0] + 2;
            }
            /*Buur 2*/
            else if ((punt[0] > 1) && (plattegrond[punt[0]-2][punt[1]] == k-2) && (plattegrond[punt[0]-1][punt[1]] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 2;
                /*Punt doorschuiven*/
                punt[0] = punt[0] - 2;
            }
            /*Buur 3*/
            else if ((punt[1] < 11) && (plattegrond[punt[0]][punt[1]+2] == k-2) && (plattegrond[punt[0]][punt[1]+1] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 3;
                /*Punt doorschuiven*/
                punt[1] = punt[1] + 2;
            }
            /*Buur 4*/
            else if ((punt[1] > 1) && (plattegrond[punt[0]][punt[1]-2] == k-2) && (plattegrond[punt[0]][punt[1]-1] == k-1))
            {
                bochten++;
                rechten++;
                k = k - 2;
                vorigerichting = 4;
                /*Punt doorschuiven*/
                punt[1] = punt[1] - 2;
            }
        }
    }
    /*Lengte terugsturen*/
    return (BOCHTWEGING*bochten + WEGENWEGING*rechten);
}
